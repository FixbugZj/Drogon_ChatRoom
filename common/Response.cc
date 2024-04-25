#include "Response.h"


using namespace common;


Json::Value common::Response::getJson(){
  Json::Value res;
  if (this->code!=0){
    res["code"]=this->code;
  }
  if (this->message!=""){
    res["message"]=this->message;
  }
  
  return res;
}
