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

    std::string r1 = client.SubmitTask(1023, 1, "echo Taks 1", "in-progress");
    std::cout << "Client received: " << r1 << std::endl;

    std::string r2 = client.SubmitTask(1987, 2, "echo Task 2", "in-progress");
    std::cout << "Client received: " << r2 << std::endl;

    std::string r3 = client.SubmitTask(1456, 3, "echo Task 3", "in-progress");
    std::cout << "Client received: " << r3 << std::endl;

    std::string r4 = client.SubmitTask(589, 4, "echo Task 4", "in-progress");
    std::cout << "Client received: " << r4 << std::endl;

    std::string r5 = client.SubmitTask(1221, 5, "echo Task 5", "in-progress");
    std::cout << "Client received: " << r5 << std::endl;

    std::string r6 = client.SubmitTask(756, 6, "echo Task 6", "in-progress");
    std::cout << "Client received: " << r6 << std::endl;

    std::string r7 = client.SubmitTask(1945, 7, "echo Task 7", "in-progress");
    std::cout << "Client received: " << r7 << std::endl;

    std::string r8 = client.SubmitTask(300, 8, "echo Task 8", "in-progress");
    std::cout << "Client received: " << r8 << std::endl;

    std::string r9 = client.SubmitTask(1749, 9, "echo Task 9", "in-progress");
    std::cout << "Client received: " << r9 << std::endl;

    std::string r10 = client.SubmitTask(1348, 10, "echo Task 10", "in-progress");
    std::cout << "Client received: " << r10 << std::endl;

    std::string r11 = client.SubmitTask(622, 11, "echo Task 11", "in-progress");
    std::cout << "Client received: " << r11 << std::endl;

    std::string r12 = client.SubmitTask(1589, 12, "echo Task 12", "in-progress");
    std::cout << "Client received: " << r12 << std::endl;

    std::string r13 = client.SubmitTask(947, 13, "echo Task 13", "in-progress");
    std::cout << "Client received: " << r13 << std::endl;

    std::string r14 = client.SubmitTask(1934, 14, "echo Task 14", "in-progress");
    std::cout << "Client received: " << r14 << std::endl;

    std::string r15 = client.SubmitTask(122, 15, "echo Task 15", "in-progress");
    std::cout << "Client received: " << r15 << std::endl;

    std::string r16 = client.SubmitTask(1811, 16, "echo Task 16", "in-progress");
    std::cout << "Client received: " << r16 << std::endl;

    std::string r17 = client.SubmitTask(763, 17, "echo Task 17", "in-progress");
    std::cout << "Client received: " << r17 << std::endl;

    std::string r18 = client.SubmitTask(1366, 18, "echo Task 18", "in-progress");
    std::cout << "Client received: " << r18 << std::endl;

    std::string r19 = client.SubmitTask(547, 19, "echo Task 19", "in-progress");
    std::cout << "Client received: " << r19 << std::endl;

    std::string r20 = client.SubmitTask(1894, 20, "echo Task 20", "in-progress");
    std::cout << "Client received: " << r20 << std::endl;


    return 0;
}
