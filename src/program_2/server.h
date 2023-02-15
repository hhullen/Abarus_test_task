#ifndef SRC_PROGRAM_2_SERVER_H_
#define SRC_PROGRAM_2_SERVER_H_

#include <netinet/in.h>
#include <unistd.h>

#include <string>

using std::string;

class Server {
 public:
  Server() {
    address_.sin_family = AF_INET;
    address_.sin_addr.s_addr = INADDR_ANY;
    address_.sin_port = htons(kPort_);
  }
  ~Server() {
    shutdown(socket_, SHUT_RDWR);
    close(accepted_socket_);
  }

  bool SetupSocketConnection() {
    bool is_connected = false;
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    is_connected = socket_ >= 0;

    if (is_connected) {
      socklen_t addres_len = sizeof(address_);
      is_connected =
          bind(socket_, (struct sockaddr*)&address_, addres_len) >= 0;
    }
    return is_connected;
  }

  bool Listen() {
    bool is_success = false;
    is_success = listen(socket_, 3) >= 0;

    if (is_success) {
      socklen_t addres_len = sizeof(address_);
      accepted_socket_ =
          accept(socket_, (struct sockaddr*)&address_, &addres_len);
      is_success = accepted_socket_ >= 0;
    }
    return is_success;
  }

  string Read() {
    read(accepted_socket_, buffer_, kBufferSize_);
    close(accepted_socket_);
    return string(buffer_);
  }

 private:
  const int kPort_ = 4221;
  const int kBufferSize_ = 1024;
  struct sockaddr_in address_;
  int socket_ = 0;
  int accepted_socket_ = 0;
  char buffer_[1024] = {0};
};

#endif  // SRC_PROGRAM_2_SERVER_H_
