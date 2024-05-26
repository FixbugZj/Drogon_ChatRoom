#pragma once

#include <drogon/HttpController.h>

#include <drogon/WebSocketController.h>
#include <drogon/WebSocketConnection.h>
#include <trantor/net/TcpConnection.h>


#include "../models/Users.h"
#include "../models/Friends.h"
#include "../models/Groupuser.h"
#include "../models/Allgroup.h"
#include "../models/Offlinemessages.h"
#include "../service/UserModel.h"

using namespace drogon;

namespace controllers
{

  class personalCenter : public drogon::HttpController<personalCenter>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(personalCenter::get, "/{2}/{1}", Get); // path is /personalCenter/{arg2}/{arg1}
    // METHOD_ADD(personalCenter::your_method_name, "/{1}/{2}/list", Get); // path is /personalCenter/{arg1}/{arg2}/list
    // ADD_METHOD_TO(personalCenter::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

    ADD_METHOD_TO(personalCenter::getUserInfo,"/user/personal",Get,Options);

    ADD_METHOD_TO(personalCenter::changeUserInfo,"/user/personalChange",Post,Options);

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;

    void getUserInfo(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void changeUserInfo(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const;
    
    

};

}

