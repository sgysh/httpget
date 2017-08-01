/****************************************************************************
 * url.cc
 *
 *   Copyright (c) 2017 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#include "url.h"

#include <arpa/inet.h>
#include <netdb.h>

#include <cstdint>
#include <string>
#include <regex>

namespace {

constexpr const uint16_t kDefaultPort = 80;

}  // namespace

bool IsURL(const std::string &url) {
  std::regex r(R"(http://[^/:]+(:\d+)?(/[^/:]+)*/?)");  // Raw string literals

  return std::regex_match(url, r);
}

struct URLComponent ParseURL(const std::string &url) {
  struct URLComponent url_component{};
  std::string::size_type pos_start;
  std::string::size_type pos_end;

  pos_start = std::string("http://").length();

  if ((pos_end = url.find_first_of("/", pos_start)) != std::string::npos) {
    url_component.host = url.substr(pos_start, pos_end - pos_start);
  } else {
    url_component.host = url.substr(pos_start);
  }

  std::string::size_type pos_colon;
  if ((pos_colon = url_component.host.find_first_of(":")) != std::string::npos) {
    url_component.port = std::stoul(url_component.host.substr(pos_colon + 1));
    url_component.host = url_component.host.substr(0, pos_colon);
  } else {
    auto servent = getservbyname("http", "tcp");

    if (servent) {
      url_component.port = ntohs(servent->s_port);
    } else {
      url_component.port = kDefaultPort;
    }
  }

  if (pos_end != std::string::npos) {
    url_component.path = url.substr(pos_end + 1);
  } else {
    url_component.path = "";
  }

  if (*url_component.path.rbegin() == '/') {
    url_component.path.erase(url_component.path.length() - 1);
  }

  url_component.path = "/" + url_component.path;

  return url_component;
}

