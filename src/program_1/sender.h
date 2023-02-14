#ifndef SRC_PROGRAM_1_SENDER_H_
#define SRC_PROGRAM_1_SENDER_H_

#include <mutex>
#include <queue>
#include <string>

#include "buffer.h"
#include "connector.h"

using std::cout;
using std::isdigit;
using std::mutex;
using std::queue;
using std::string;
using std::to_string;

class Sender {
 public:
  Sender(Buffer *buffer, mutex *syncronizer)
      : buffer_(buffer), syncronizer_(syncronizer) {}

  ~Sender() {
    buffer_ = nullptr;
    syncronizer_ = nullptr;
  }

  void Run() {
    while (true) {
      (*syncronizer_).lock();
      string temp = buffer_->GetBuffer();
      buffer_->Clear();
      cout << "Got data: " << temp << "\n";
      int sum = CalculateDigitsSum(temp);
      dispatch_queue_.push(to_string(sum));
      TrySendData();
    }
  }

 private:
  Buffer *buffer_;
  mutex *syncronizer_;
  queue<string> dispatch_queue_;
  Connector connector_;

  int CalculateDigitsSum(string &str) {
    int sum = 0;
    for (int i = 0; i < str.size(); ++i) {
      if (isdigit(str[i])) {
        sum += (int)(str[i] - '0');
      }
    }
    return sum;
  }

  void TrySendData() {
    bool is_sent = true;
    while (dispatch_queue_.size() > 0 && is_sent) {
      string &data = dispatch_queue_.front();
      is_sent = connector_.SendData(data);
      if (is_sent) {
        dispatch_queue_.pop();
      } else {
        cout << "Failed to send. Connection is lost.\n";
      }
    }
  }
};

#endif  // SRC_PROGRAM_1_SENDER_H_
