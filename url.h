/****************************************************************************
 * url.h
 *
 *   Copyright (c) 2017 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#ifndef URL_H_
#define URL_H_

#include <cstdint>
#include <string>

struct URLComponent {
  std::string host;
  uint16_t port;
  std::string path;
};

bool IsURL(const std::string &url);
struct URLComponent ParseURL(const std::string &url);

#endif  // URL_H_


