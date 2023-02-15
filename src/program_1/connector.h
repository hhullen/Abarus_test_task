#ifndef SRC_PROGRAM_1_CONNECTOR_H_
#define SRC_PROGRAM_1_CONNECTOR_H_

#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <string>

using std::string;

class Connector {
 public:
  Connector() {
    address_.sin_family = AF_INET;
    address_.sin_port = htons(kPort_);
  }

  ~Connector() { Close(); }

  bool SendData(string &data) {
    bool is_sent = false;
    if (TryConnection() == true) {
      int sent = send(socket_, data.data(), data.size(), 0);
      if (sent > 0) {
        is_sent = true;
      }
    }
    Close();
    return is_sent;
  }

  void Close() { close(socket_); }

 private:
  const int kPort_ = 4221;
  struct sockaddr_in address_;
  int socket_ = 0;
  int client_ = 0;

  bool TryConnection() {
    bool is_connected = true;

    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    is_connected = socket_ >= 0;

    if (is_connected) {
      is_connected = inet_pton(AF_INET, "127.0.0.1", &address_.sin_addr) > 0;
    }

    if (is_connected) {
      client_ =
          connect(socket_, (struct sockaddr *)&address_, sizeof(address_));
      is_connected = client_ >= 0;
    }

    return is_connected;
  }
};

#endif  // SRC_PROGRAM_1_CONNECTOR_H_
