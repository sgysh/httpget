/****************************************************************************
 * http.h
 *
 *   Copyright (c) 2017 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#ifndef HTTP_H_
#define HTTP_H_

#include <cstdint>
#include <memory>

std::shared_ptr<int> Connect(const char *host, uint16_t port);
void RequestGet(int fd, const std::string &host, uint16_t port, const std::string &path);
void ReceiveAndShowResponse(int fd);

#endif  // HTTP_H_

