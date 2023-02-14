#ifndef SRC_PROGRAM_1_SENDER_H_
#define SRC_PROGRAM_1_SENDER_H_

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <mutex>
#include <string>

#include "buffer.h"

using std::cout;
using std::isdigit;
using std::mutex;
using std::string;

class Sender {
 public:
  Sender(Buffer *buffer, mutex *syncronizer)
      : buffer_(buffer), syncronizer_(syncronizer) {}
  ~Sender() {}

  void Run() {
    while (true) {
      (*syncronizer_).lock();
      string temp = buffer_->GetBuffer();
      buffer_->Clear();
      cout << " Got data: " << temp << "\n";
      int sum = CalculateDigitsSum(temp);
      SendData(sum);
    }
  }

 private:
  Buffer *buffer_;
  mutex *syncronizer_;

  int CalculateDigitsSum(string &str) {
    int sum = 0;
    for (int i = 0; i < str.size(); ++i) {
      if (isdigit(str[i])) {
        sum += (int)(str[i] - '0');
      }
    }
    return sum;
  }

  void SendData(int data) {}
};

#endif  // SRC_PROGRAM_1_SENDER_H_
