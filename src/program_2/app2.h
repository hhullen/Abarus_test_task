#ifndef SRC_PROGRAM_2_APP2_H_
#define SRC_PROGRAM_2_APP2_H_

#include <iostream>
#include <thread>

#include "server.h"

using std::atoi;
using std::cout;
using std::chrono::seconds;
using std::this_thread::sleep_for;

class App2 {
 public:
  App2() {}
  ~App2() {}
  void Execute() {
    while (true) {
      bool is_connected = server_.SetupSocketConnection();
      if (is_connected) {
        ListenAndReadClients();
      } else {
        cout << "Connection failed.\n";
        sleep_for(seconds(2));
      }
    }
  }

 private:
  Server server_;
  string message_;

  void ListenAndReadClients() {
    bool is_accepted = true;

    while (is_accepted) {
      is_accepted = server_.Listen();
      if (is_accepted) {
        message_ = server_.Read();
        ProccessMessage();
      } else {
        cout << "Message acception failed.\n";
      }
    }
  }

  void ProccessMessage() {
    int number = atoi(message_.data());
    if (number > 99 && number % 32 == 0) {
      cout << "Data recieved: " << number << "\n";
    } else {
      cout << "Error. Wrong data recieved.\n";
    }
  }
};

#endif  // SRC_PROGRAM_2_APP2_H_
