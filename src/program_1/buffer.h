#ifndef SRC_PROGRAM_1_BUFFER_H_
#define SRC_PROGRAM_1_BUFFER_H_

#include <string>

using std::string;

class Buffer {
 public:
  Buffer() {}
  ~Buffer() {}

  void SetBuffer(string &value) { buffer_ = value; }
  string GetBuffer() { return buffer_; }
  void Clear() { buffer_.clear(); }

 private:
  string buffer_;
};

#endif  // SRC_PROGRAM_1_BUFFER_H_
