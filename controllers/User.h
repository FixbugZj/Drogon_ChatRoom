#pragma once

#include <drogon/HttpController.h>

#include "../models/Users.h"
#include "../models/Friends.h"
#include "../models/Groupuser.h"
#include "../models/Allgroup.h"
#include "../models/Offlinemessages.h"
#include "../service/UserModel.h"

using namespace drogon;

namespace controllers
{

class User : public drogon::HttpController<User>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(UserService::get, "/{2}/{1}", Get); // path is /UserService/{arg2}/{arg1}
    // METHOD_ADD(UserService::your_method_name, "/{1}/{2}/list", Get); // path is /UserService/{arg1}/{arg2}/list
    // ADD_METHOD_TO(UserService::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

    ADD_METHOD_TO(User::loginPage, "/login", Get); 
    ADD_METHOD_TO(User::doLogin,"/login",Post);
    ADD_METHOD_TO(User::doregister,"/register",Post);
  
    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
    void loginPage (const HttpRequestPtr& req,
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void doLogin   (const HttpRequestPtr& req, 
    std::function<void (const HttpResponsePtr &)> &&callback) const; //drogon_model::db::Users  //User users ,User users
    
    void doregister(const HttpRequestPtr& req, 
    std::function<void (const HttpResponsePtr &)> &&callback) const; //drogon_model::db::Users

};

}


