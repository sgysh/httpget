/****************************************************************************
 * http.cc
 *
 *   Copyright (c) 2017 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#include "http.h"

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <memory>
#include <string>

namespace {

std::shared_ptr<int> socketIPv4() {
  return std::shared_ptr<int>(new int{socket(AF_INET, SOCK_STREAM, 0)},
                                  [](int *fd) -> void {
    if (*fd != -1) close(*fd);
  });
}

}  // namespace

std::shared_ptr<int> Connect(const char *host, uint16_t port) {
  struct sockaddr_in server{};

  server.sin_family = AF_INET;  // IPv4

  auto host_ent = gethostbyname(host);
  if (host_ent == nullptr) return nullptr;
  std::memcpy(&server.sin_addr, host_ent->h_addr, host_ent->h_length);

  server.sin_port = htons(port);

  auto fd_ptr = socketIPv4();
  if (*fd_ptr == -1) return nullptr;

  if (connect(*fd_ptr, (struct sockaddr *)&server, sizeof(server)) != 0) return nullptr;

  return fd_ptr;
}

void RequestGet(int fd, const std::string &host, uint16_t port, const std::string &path) {
  std::string buf;
  buf = "GET " + path + " HTTP/1.0\r\n";  // Request Line
  buf += "Host: " + host + ":" + std::to_string(port) + "\r\n";  // Request Header
  buf += "\r\n";
  write(fd, buf.c_str(), buf.length());
}

void ReceiveAndShowResponse(int fd) {
  constexpr const size_t buffer_size = 256;
  char buf[buffer_size];

  while (true) {
    auto read_size = read(fd, buf, buffer_size);
    if (read_size <= 0) break;

    for (decltype(read_size) i = 0; i < read_size; i++) {
      write(STDOUT_FILENO, buf + i, 1);
    }
  }
}

