// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: task.proto
#ifndef GRPC_task_2eproto__INCLUDED
#define GRPC_task_2eproto__INCLUDED

#include "task.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace worker {

class Scheduler final {
 public:
  static constexpr char const* service_full_name() {
    return "worker.Scheduler";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status SubmitTask(::grpc::ClientContext* context, const ::worker::Task& request, ::worker::TaskStatus* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::worker::TaskStatus>> AsyncSubmitTask(::grpc::ClientContext* context, const ::worker::Task& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::worker::TaskStatus>>(AsyncSubmitTaskRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::worker::TaskStatus>> PrepareAsyncSubmitTask(::grpc::ClientContext* context, const ::worker::Task& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::worker::TaskStatus>>(PrepareAsyncSubmitTaskRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void SubmitTask(::grpc::ClientContext* context, const ::worker::Task* request, ::worker::TaskStatus* response, std::function<void(::grpc::Status)>) = 0;
      virtual void SubmitTask(::grpc::ClientContext* context, const ::worker::Task* request, ::worker::TaskStatus* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::worker::TaskStatus>* AsyncSubmitTaskRaw(::grpc::ClientContext* context, const ::worker::Task& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::worker::TaskStatus>* PrepareAsyncSubmitTaskRaw(::grpc::ClientContext* context, const ::worker::Task& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status SubmitTask(::grpc::ClientContext* context, const ::worker::Task& request, ::worker::TaskStatus* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::worker::TaskStatus>> AsyncSubmitTask(::grpc::ClientContext* context, const ::worker::Task& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::worker::TaskStatus>>(AsyncSubmitTaskRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::worker::TaskStatus>> PrepareAsyncSubmitTask(::grpc::ClientContext* context, const ::worker::Task& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::worker::TaskStatus>>(PrepareAsyncSubmitTaskRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void SubmitTask(::grpc::ClientContext* context, const ::worker::Task* request, ::worker::TaskStatus* response, std::function<void(::grpc::Status)>) override;
      void SubmitTask(::grpc::ClientContext* context, const ::worker::Task* request, ::worker::TaskStatus* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::worker::TaskStatus>* AsyncSubmitTaskRaw(::grpc::ClientContext* context, const ::worker::Task& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::worker::TaskStatus>* PrepareAsyncSubmitTaskRaw(::grpc::ClientContext* context, const ::worker::Task& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_SubmitTask_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status SubmitTask(::grpc::ServerContext* context, const ::worker::Task* request, ::worker::TaskStatus* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_SubmitTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_SubmitTask() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_SubmitTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SubmitTask(::grpc::ServerContext* /*context*/, const ::worker::Task* /*request*/, ::worker::TaskStatus* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSubmitTask(::grpc::ServerContext* context, ::worker::Task* request, ::grpc::ServerAsyncResponseWriter< ::worker::TaskStatus>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_SubmitTask<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_SubmitTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_SubmitTask() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::worker::Task, ::worker::TaskStatus>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::worker::Task* request, ::worker::TaskStatus* response) { return this->SubmitTask(context, request, response); }));}
    void SetMessageAllocatorFor_SubmitTask(
        ::grpc::MessageAllocator< ::worker::Task, ::worker::TaskStatus>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::worker::Task, ::worker::TaskStatus>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_SubmitTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SubmitTask(::grpc::ServerContext* /*context*/, const ::worker::Task* /*request*/, ::worker::TaskStatus* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* SubmitTask(
      ::grpc::CallbackServerContext* /*context*/, const ::worker::Task* /*request*/, ::worker::TaskStatus* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_SubmitTask<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_SubmitTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_SubmitTask() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_SubmitTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SubmitTask(::grpc::ServerContext* /*context*/, const ::worker::Task* /*request*/, ::worker::TaskStatus* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_SubmitTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_SubmitTask() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_SubmitTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SubmitTask(::grpc::ServerContext* /*context*/, const ::worker::Task* /*request*/, ::worker::TaskStatus* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSubmitTask(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_SubmitTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_SubmitTask() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->SubmitTask(context, request, response); }));
    }
    ~WithRawCallbackMethod_SubmitTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SubmitTask(::grpc::ServerContext* /*context*/, const ::worker::Task* /*request*/, ::worker::TaskStatus* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* SubmitTask(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_SubmitTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_SubmitTask() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::worker::Task, ::worker::TaskStatus>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::worker::Task, ::worker::TaskStatus>* streamer) {
                       return this->StreamedSubmitTask(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_SubmitTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status SubmitTask(::grpc::ServerContext* /*context*/, const ::worker::Task* /*request*/, ::worker::TaskStatus* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedSubmitTask(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::worker::Task,::worker::TaskStatus>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_SubmitTask<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_SubmitTask<Service > StreamedService;
};

}  // namespace worker


#endif  // GRPC_task_2eproto__INCLUDED
