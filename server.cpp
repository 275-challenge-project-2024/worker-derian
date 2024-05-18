#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <grpcpp/grpcpp.h>
#include <unordered_map>
#include <chrono>
#include <random>
#include "task.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using worker::Task;
using worker::TaskStatus;
using worker::Scheduler;

struct LocalTask {
    int task_id;
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
    std::list<LocalTask> tasks;
    std::unordered_map<int, std::string> previous_statuses;
    std::mutex tasks_mutex;
    std::condition_variable task_cv;
    bool stop_flag = false;
    std::vector<std::thread> thread_pool;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
    std::uniform_int_distribution<int> status_distribution;

    void processTask() {
        while (true) {
            LocalTask task(0, "");
            {
                std::unique_lock<std::mutex> lock(tasks_mutex);
                task_cv.wait(lock, [this] { return !tasks.empty() || stop_flag; });

                if (stop_flag && tasks.empty()) break;

                auto it = std::find_if(tasks.begin(), tasks.end(), [](const LocalTask& t) { return t.status == "in-progress"; });
                if (it != tasks.end()) {
                    task = *it;
                    it->status = "processing";
                }
                else {
                    continue;
                }
            }

            // Simulate processing time
            int processing_time = distribution(generator);
            std::this_thread::sleep_for(std::chrono::milliseconds(processing_time));

            // Randomly determine the status (0 for completed, 1 for failed)
            int result = status_distribution(generator);

            {
                std::lock_guard<std::mutex> guard(tasks_mutex);
                auto it = std::find_if(tasks.begin(), tasks.end(), [&](const LocalTask& t) { return t.task_id == task.task_id; });
                if (it != tasks.end()) {
                    if (result == 0) {
                        it->status = "completed";
                    }
                    else {
                        it->status = "failed";
                        it->error_code = 1; // You can set any non-zero value for error_code to indicate failure
                    }
                }
                current_capacity++;
            }
        }
    }

public:
    Worker(const std::string& id, int tp, int cap)
        : worker_id(id), type(tp), total_capacity(cap), current_capacity(cap), distribution(1000, 2000), status_distribution(0, 1) { // Distribution range set to 1 to 2 seconds in milliseconds
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
                previous_statuses[task_id] = "in-progress";
            }
            else {
                std::cerr << "No capacity to handle new task." << std::endl;
            }
        }
    }

    void sendHeartbeat() {
        std::lock_guard<std::mutex> guard(tasks_mutex);
        std::cout << "Worker ID: " << worker_id << "\n";
        std::cout << "Type: " << type << "\n";
        std::cout << "Total Capacity: " << total_capacity << "\n";
        std::cout << "Current Capacity: " << current_capacity << "\n";
        std::cout << "Task List:\n";
        for (const auto& task : tasks) {
            auto prev_status_it = previous_statuses.find(task.task_id);
            if ((task.status == "completed" || task.status == "failed") &&
                (prev_status_it == previous_statuses.end() || prev_status_it->second != task.status)) {
                std::cout << "  Task ID: " << task.task_id << ", Status: " << task.status;
                if (task.status == "failed") {
                    std::cout << ", Error Code: " << task.error_code;
                }
                std::cout << std::endl;
                previous_statuses[task.task_id] = task.status;
            }
        }
        std::cout << std::endl;
    }

    void run() {
        while (true) {
            sendHeartbeat();
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
};

class WorkerService final : public Scheduler::Service {
public:
    WorkerService(Worker* worker) : worker_(worker) {}

    Status SubmitTask(ServerContext* context, const Task* task, TaskStatus* status) override {
       // std::cout << "Received task with ID: " << task->taskid()
         //   << ", Priority: " << task->priority()
           // << ", Status: " << task->status() << std::endl;

        worker_->receiveTask(task->taskid(), task->commands());

        status->set_status("Received");
        status->set_taskid(task->taskid());
        return Status::OK;
    }

private:
    Worker* worker_;
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    Worker worker("13454476000", 1, 20);
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
