#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "task.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using worker::Task;
using worker::TaskStatus;
using worker::Scheduler;

class SchedulerClient {
public:
    SchedulerClient(std::shared_ptr<Channel> channel)
        : stub_(Scheduler::NewStub(channel)) {}

    std::string SubmitTask(int taskId, int priority, const std::string& commands, const std::string& status) {
        Task task;
        task.set_taskid(taskId);
        task.set_priority(priority);
        task.set_commands(commands);
        task.set_status(status);

        TaskStatus taskStatus;
        ClientContext context;

        Status grpcStatus = stub_->SubmitTask(&context, task, &taskStatus);

        if (grpcStatus.ok()) {
            return "Task submitted successfully: ID " + std::to_string(taskStatus.taskid());
        }
        else {
            return "Failed to submit task: " + grpcStatus.error_message();
        }
    }

private:
    std::unique_ptr<Scheduler::Stub> stub_;
};

int main(int argc, char** argv) {
    SchedulerClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    // Example task submissions
    std::string r1 = client.SubmitTask(123, 1, "echo Hello World", "in-progress");
    std::cout << "Client received: " << r1 << std::endl;

    std::string r2 = client.SubmitTask(456, 5, "echo Process File", "in-progress");
    std::cout << "Client received: " << r2 << std::endl;

    std::string r3 = client.SubmitTask(11, 5, "echo Backup Logs", "in-progress");
    std::cout << "Client received: " << r3 << std::endl;

    std::string r4 = client.SubmitTask(22, 3, "echo Clean Temp", "in-progress");
    std::cout << "Client received: " << r4 << std::endl;

    std::string r5 = client.SubmitTask(54, 4, "echo Update System", "in-progress");
    std::cout << "Client received: " << r5 << std::endl;

    std::string r6 = client.SubmitTask(60, 2, "echo Update System1", "in-progress");
    std::cout << "Client received: " << r6 << std::endl;

    std::string r7 = client.SubmitTask(3, 5, "echo Update System2", "in-progress");
    std::cout << "Client received: " << r7 << std::endl;

    std::string r8 = client.SubmitTask(2093, 4, "echo Update System3", "in-progress");
    std::cout << "Client received: " << r8 << std::endl;

    std::string r9 = client.SubmitTask(56823, 2, "echo Update System4", "in-progress");
    std::cout << "Client received: " << r9 << std::endl;

    std::string r10 = client.SubmitTask(15479, 5, "echo Update System5", "in-progress");
    std::cout << "Client received: " << r10 << std::endl;

    return 0;
}
