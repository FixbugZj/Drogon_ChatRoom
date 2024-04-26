#pragma once
#include <drogon/HttpController.h>
#include "../service/UserModel.h"
#include <models/Users.h>


using namespace drogon;


struct User
{
    std::string username;
    std::string password;
    std::string state;
    std::string nickename;
};



class userfunc : public drogon::HttpController<userfunc>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(userlogin::get, "/{2}/{1}", Get); // path is /userlogin/{arg2}/{arg1}
    // METHOD_ADD(userlogin::your_method_name, "/{1}/{2}/list", Get); // path is /userlogin/{arg1}/{arg2}/list
    // ADD_METHOD_TO(userlogin::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

    ADD_METHOD_TO(userfunc::loginPage, "/login", Get); 
    ADD_METHOD_TO(userfunc::dologin,"/login",Post);
    ADD_METHOD_TO(userfunc::doregister,"/register",Post);
    //ADD_METHOD_TO(userlogin::logout,"/logout",Post);

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    void loginPage (const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void dologin   (const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback,User user) const; //rogon_model::db::Users
    
    void doregister(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const; //drogon_model::db::Users
    //void logout(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)const;


};


namespace drogon
{
template<>

inline drogon_model::db::Users fromRequest(const HttpRequest&req)
{
  auto jsonPtr = req.getJsonObject();
  if(jsonPtr == nullptr)
  {
    throw std::invalid_argument("请求体格式错误, 请使用json");
  }

  auto &json = *jsonPtr;
  if(!json.isMember("username") || json["username"].type() != Json::stringValue )
  {
    throw std::invalid_argument("缺少必备字段: username.userlog");
  }

  if(!json.isMember("password") || json["password"].type() != Json::stringValue ) /*!= Json::stringValue*/
  {
    throw std::invalid_argument("缺少必备字段: password.userlog");
  }
  drogon_model::db::Users user;
  user.updateByJson(json);
  return user;
}

template<>
inline User fromRequest(const HttpRequest&req)
{
  auto json = req.getJsonObject();

  User value;
  if(json == nullptr)
  {
    throw std::invalid_argument("请求体格式错误, 请使用json");
  }
  if(json->isMember("username"))
  {
    const auto &temp = (*json)["username"].asString();
    if(temp.size()<1)
    {
      throw std::runtime_error("用户名长度过短");
    }
    value.username = temp;
  }
  else
  {
    throw std::runtime_error("缺少必备字段： username");
  }

  if(json->isMember("password"))
  {
    const auto &temp = (*json)["password"].asString();
    if(temp.size()<6)
    {
      throw std::runtime_error("密码长度过短");
    }
    value.password = temp;
  }
  else
  {
    throw std::runtime_error("缺少必备字段： password");
  }
  
  return value;
}

}


