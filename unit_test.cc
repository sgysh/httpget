/****************************************************************************
 * unit_test.cc
 *
 *   Copyright (c) 2017 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include "url.h"
#include "http.h"

TEST_CASE("Check if a URL is valid", "[URL]") {
  CHECK(IsURL("http://aa.bb.cc") == true);
  CHECK(IsURL("http://aa.bb.cc/") == true);
  CHECK(IsURL("http://aa.bb.cc:80") == true);
  CHECK(IsURL("http://aa.bb.cc:80/") == true);
  CHECK(IsURL("http://aa.bb.cc:80/aa") == true);
  CHECK(IsURL("http://aa.bb.cc:80/aa/") == true);
  CHECK(IsURL("http://aa.bb.cc:80/aa/bb") == true);
  CHECK(IsURL("http://aa.bb.cc:80/aa/bb/") == true);

  CHECK(IsURL("http://") == false);
  CHECK(IsURL("http:///") == false);
  CHECK(IsURL("http://:80") == false);
  CHECK(IsURL("aa.bb.cc") == false);
}

TEST_CASE("Check if a URL is parsed into its individual components correctly", "[URL]") {
  SECTION("all") {
    auto url_component = ParseURL("http://aa.bb.cc:80/aa/bb");
    CHECK(url_component.host == "aa.bb.cc");
    CHECK(url_component.port == 80);
    CHECK(url_component.path == "/aa/bb");
  }

  SECTION("all with slash") {
    auto url_component = ParseURL("http://aa.bb.cc:80/aa/bb/");
    CHECK(url_component.host == "aa.bb.cc");
    CHECK(url_component.port == 80);
    CHECK(url_component.path == "/aa/bb");
  }

  SECTION("host and path") {
    auto url_component = ParseURL("http://aa.bb.cc/aa/bb");
    CHECK(url_component.host == "aa.bb.cc");
    CHECK(url_component.port == 80);
    CHECK(url_component.path == "/aa/bb");
  }

  SECTION("host and path with slash") {
    auto url_component = ParseURL("http://aa.bb.cc/aa/bb/");
    CHECK(url_component.host == "aa.bb.cc");
    CHECK(url_component.port == 80);
    CHECK(url_component.path == "/aa/bb");
  }

  SECTION("host and port") {
    auto url_component = ParseURL("http://aa.bb.cc:80");
    CHECK(url_component.host == "aa.bb.cc");
    CHECK(url_component.port == 80);
    CHECK(url_component.path == "/");
  }

  SECTION("host and port with slash") {
    auto url_component = ParseURL("http://aa.bb.cc:80/");
    CHECK(url_component.host == "aa.bb.cc");
    CHECK(url_component.port == 80);
    CHECK(url_component.path == "/");
  }

  SECTION("host") {
    auto url_component = ParseURL("http://aa.bb.cc");
    CHECK(url_component.host == "aa.bb.cc");
    CHECK(url_component.port == 80);
    CHECK(url_component.path == "/");
  }

  SECTION("host with slash") {
    auto url_component = ParseURL("http://aa.bb.cc/");
    CHECK(url_component.host == "aa.bb.cc");
    CHECK(url_component.port == 80);
    CHECK(url_component.path == "/");
  }
}

TEST_CASE("Check connection", "[HTTP]") {
  CHECK(Connect((char *)"httpbin.org", 80) != nullptr);
}

