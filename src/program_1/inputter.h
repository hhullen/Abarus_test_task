#ifndef SRC_PROGRAM_1_INPUTTER_H_
#define SRC_PROGRAM_1_INPUTTER_H_

#include <algorithm>
#include <iostream>
#include <mutex>
#include <string>

#include "buffer.h"

using std::all_of;
using std::cin;
using std::isdigit;
using std::mutex;
using std::sort;
using std::string;

class Inputter {
 public:
  Inputter(Buffer *buffer, mutex *syncronizer)
      : buffer_(buffer), syncronizer_(syncronizer) {}
  ~Inputter() { buffer_ = nullptr; }
  void Run() {
    while (true) {
      cin >> input_;
      ProcessInput();
    }
  }

 private:
  const int kMaxLength = 64;
  const string kReplacer = "KB";
  string input_;
  Buffer *buffer_;
  mutex *syncronizer_;

  void ProcessInput() {
    if (IsInputCorrect()) {
      SortInDescent();
      ReplaceEvenValuesWith(kReplacer);
      PlaceToBuffer();
    }
  }

  bool IsInputCorrect() { return IsCorrectLength() && IsAllDigits(); }

  bool IsCorrectLength() { return input_.size() <= kMaxLength; }

  bool IsAllDigits() {
    return all_of(input_.begin(), input_.end(),
                  [](char sym) { return isdigit(sym); });
  }

  void SortInDescent() {
    sort(input_.begin(), input_.end(), [](char a, char b) { return a > b; });
  }

  void ReplaceEvenValuesWith(const string &str) {
    for (int i = input_.size() - 1; i >= 0; --i) {
      if (input_[i] % 2 == 0) {
        input_ = input_.erase(i, 1);
        input_.insert(i, str);
      }
    }
  }

  void PlaceToBuffer() {
    if (buffer_) {
      buffer_->SetBuffer(input_);
      (*syncronizer_).unlock();
    }
  }
};

#endif  // SRC_PROGRAM_1_INPUTTER_H_
