#ifndef SRC_PROGRAM_1_APP1_H_
#define SRC_PROGRAM_1_APP1_H_

#include <mutex>
#include <thread>

#include "buffer.h"
#include "inputter.h"
#include "sender.h"

using std::mutex;
using std::thread;

class App1 {
 public:
  App1() {
    syncronizer_.lock();
    buffer_ = new Buffer();
    input_ = new Inputter(buffer_, &syncronizer_);
    sender_ = new Sender(buffer_, &syncronizer_);
  }

  ~App1() {
    if (input_) {
      delete input_;
    }
    if (buffer_) {
      delete buffer_;
    }
    if (sender_) {
      delete sender_;
    }
  }

  void Execute() {
    thread_1_ = new thread(&Inputter::Run, input_);
    thread_2_ = new thread(&Sender::Run, sender_);
    thread_2_->join();
    thread_1_->join();
    delete thread_1_;
    delete thread_2_;
  }

 private:
  mutex syncronizer_;
  Inputter *input_;
  Buffer *buffer_;
  Sender *sender_;
  thread *thread_1_;
  thread *thread_2_;
};

#endif  // SRC_PROGRAM_1_APP1_H_
