#pragma once

#include <string>
#include <any>
#include <jsoncpp/json/json.h>

namespace common {

class Response {
 private:
  int code;
  std::string message;
  // Json::Value data;

 public:
  Response(/* args */){};
  Response(int code, std::string message) : code(code), message(message) {}
  ~Response(){};
  Json::Value getJson();
};

}