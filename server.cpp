#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <grpcpp/grpcpp.h>
#include <unordered_map>
#include "task.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using worker::Task;
using worker::TaskStatus;
using worker::Scheduler;

struct LocalTask {
    int task_id; // Changed task_id to int
    std::string command;
    std::string status;
    int error_code;

    LocalTask(int id, const std::string& cmd)
        : task_id(id), command(cmd), status("in-progress"), error_code(0) {}
};

class Worker {
private:
    std::string worker_id;
    int type;
    int total_capacity;
    int current_capacity;
    std::list<LocalTask> tasks; // List to store tasks
    std::unordered_map<int, std::string> previous_statuses; // Map to store previous statuses
    std::mutex tasks_mutex;
    std::condition_variable task_cv;
    bool stop_flag = false;
    std::vector<std::thread> thread_pool; // Thread pool

    void processTask() {
        while (true) {
            LocalTask task(0, ""); // Default task_id is 0
            {
                std::unique_lock<std::mutex> lock(tasks_mutex);
                task_cv.wait(lock, [this] { return !tasks.empty() || stop_flag; });

                if (stop_flag && tasks.empty()) break;

                // Find the first task with status "in-progress"
                auto it = std::find_if(tasks.begin(), tasks.end(), [](const LocalTask& t) { return t.status == "in-progress"; });
                if (it != tasks.end()) {
                    task = *it;
                    it->status = "processing"; // Update the task status to "processing"
                }
                else {
                    continue;
                }
            }

            int result = system(task.command.c_str()); // Execute the command and store the result

            {
                std::lock_guard<std::mutex> guard(tasks_mutex);
                auto it = std::find_if(tasks.begin(), tasks.end(), [&](const LocalTask& t) { return t.task_id == task.task_id; });
                if (it != tasks.end()) {
                    if (result == 0) {
                        it->status = "completed";
                    }
                    else {
                        it->status = "failed";
                        it->error_code = result; // Store the error code from the system command
                    }
                }
                current_capacity++;
            }
        }
    }

public:
    Worker(const std::string& id, int tp, int cap)
        : worker_id(id), type(tp), total_capacity(cap), current_capacity(cap) {
        for (int i = 0; i < total_capacity; ++i) {
            thread_pool.emplace_back(&Worker::processTask, this);
        }
    }

    ~Worker() {
        {
            std::lock_guard<std::mutex> guard(tasks_mutex);
            stop_flag = true;
        }
        task_cv.notify_all();
        for (std::thread& t : thread_pool) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

    void receiveTask(int task_id, const std::string& command) {
        {
            std::lock_guard<std::mutex> guard(tasks_mutex);
            if (current_capacity > 0) {
                tasks.emplace_back(task_id, command);
                current_capacity--;
                task_cv.notify_one();
                previous_statuses[task_id] = "in-progress"; // Initialize the previous status
            }
            else {
                std::cerr << "No capacity to handle new task." << std::endl;
            }
        }
    }

    void sendHeartbeat() {
        // Construct heartbeat message with current status
        std::lock_guard<std::mutex> guard(tasks_mutex);
        std::cout << "Worker ID: " << worker_id << "\n";
        std::cout << "Total Capacity: " << total_capacity << "\n";
        std::cout << "Current Capacity: " << current_capacity << "\n";
        std::cout << "Task List:\n";
        for (const auto& task : tasks) {
            auto prev_status_it = previous_statuses.find(task.task_id);
            if (prev_status_it == previous_statuses.end() || prev_status_it->second != task.status) {
                std::cout << "  Task ID: " << task.task_id << ", Status: " << task.status;
                if (task.status == "failed") {
                    std::cout << ", Error Code: " << task.error_code;
                }
                std::cout << std::endl;
                previous_statuses[task.task_id] = task.status; // Update the previous status
            }
        }
        std::cout << std::endl;
    }

    void run() {
        // Simulation of periodic heartbeat
        while (true) {
            sendHeartbeat();
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Adjust timing as needed
        }
    }
};

class WorkerService final : public Scheduler::Service {
public:
    WorkerService(Worker* worker) : worker_(worker) {}

    Status SubmitTask(ServerContext* context, const Task* task, TaskStatus* status) override {
        // Print basic task info
        std::cout << "Received task with ID: " << task->taskid()
            << ", Priority: " << task->priority()
            << ", Command: " << task->commands()
            << ", Status: " << task->status() << std::endl;

        // Receive task into worker
        worker_->receiveTask(task->taskid(), task->commands());

        // Set status and return a successful response
        status->set_status("Received");
        status->set_taskid(task->taskid());
        return Status::OK;
    }

private:
    Worker* worker_;
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    Worker worker("13454476000", 1, 3); // Changed capacity from 10 to 5
    WorkerService service(&worker);

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    std::thread worker_thread(&Worker::run, &worker);
    server->Wait();
    worker_thread.join();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
