#pragma once

#include <drogon/HttpController.h>
#include "../models/Users.h"
#include "../models/Friends.h"
#include "../models/Groupuser.h"
#include "../models/Allgroup.h"
#include "../models/Offlinemessages.h"
#include "userlogin.h"

using namespace drogon;



class chatpage : public drogon::HttpController<chatpage>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(chatpage::get, "/{2}/{1}", Get); // path is /chatpage/{arg2}/{arg1}
    // METHOD_ADD(chatpage::your_method_name, "/{1}/{2}/list", Get); // path is /chatpage/{arg1}/{arg2}/list
    // ADD_METHOD_TO(chatpage::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
    ADD_METHOD_TO(chatpage::getchatPage,"/user/chat",Get);

    ADD_METHOD_TO(chatpage::getchat,"/chat",Get);

    ADD_METHOD_TO(chatpage::addfriend,"/user/addfriend",Post);
    ADD_METHOD_TO(chatpage::addgroup,"/user/addgroup",Post);
    METHOD_LIST_END

    void getchat(const HttpRequestPtr& req, 
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void getchatPage(const HttpRequestPtr& req, 
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void addfriend(const HttpRequestPtr& req, 
    std::function<void (const HttpResponsePtr &)> &&callback) const;
    
    void addgroup(const HttpRequestPtr& req, 
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
};


