/****************************************************************************
 * httpget.cc
 *
 *   Copyright (c) 2017 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#include <cstdlib>
#include <iostream>
#include <string>

#include "url.h"
#include "http.h"

namespace {

void exit_failure() {
  std::cout << "ERROR" << std::endl;
  std::exit(EXIT_FAILURE);
}

}  // namespace

int main(int argc, char *argv[]) {
  if (argc != 2) exit_failure();

  std::string url(argv[1]);

  if (!IsURL(url)) exit_failure();

  auto url_component = ParseURL(url);

  auto fd_ptr = Connect(url_component.host.c_str(), url_component.port);
  if (fd_ptr == nullptr) exit_failure();

  RequestGet(*fd_ptr, url_component.host, url_component.port, url_component.path);

  ReceiveAndShowResponse(*fd_ptr);

  return EXIT_SUCCESS;
}

