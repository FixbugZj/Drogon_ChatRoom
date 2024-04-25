#include "userlogin.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Exception.h>
#include <stdexcept>

using namespace orm;
using namespace drogon_model::db;

// Add definition of your processing function here
void userlogin::loginPage(const HttpRequestPtr& req, 
        std::function<void (const HttpResponsePtr &)> &&callback) const
{
    
   // data.insert("nickname",std::string("于森"));
    auto session = req->session();
    auto userinfo = session->get<drogon_model::db::Users>("userinfo");
    
    auto sessionID = req->session().get()->sessionId();
    HttpViewData data;
    data.insert("nickname",userinfo.getValueOfNickname());

    auto resp = HttpResponse::newHttpViewResponse("login",data);
    callback(resp);
}


void userlogin::dologin(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback,
drogon_model::db::Users user) const
{
    auto clientDb=app().getDbClient();
    Mapper<Users> mapper(clientDb);

    auto userInDb = 
            mapper.findOne({Users::Cols::_username,user.getValueOfUsername()});

    
    if(userInDb.getValueOfPassword() != user.getValueOfPassword())
    {
        throw std::runtime_error("密码错误");
    }
    

    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);

    //userInDb.setState("online");
    userInDb.setUpdateTime(trantor::Date::now());
    mapper.update(userInDb);

    auto session = req->session();
    session->insert("userinfo",userInDb);
}



void userlogin::doregister(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback,
drogon_model::db::Users,
User user) const
{   
    auto clientPtr = app().getDbClient();
    //Json::Value json;

    // Mapper<Users> mapper(app().getDbClient());
    // auto userInDb =mapper.findOne({Users::Cols::_username,user.username});
    try
    {
        // if(userInDb.getValueOfUsername() == user.username)
        // {
        //     throw std::runtime_error("用户名冲突");
        // }
        auto value1 = req->getParameter("username");
        auto Result = clientPtr->execSqlSync("select username from users where username = ? ",value1);
        if(Result.empty())
        {
            clientPtr->execSqlSync("INSERT INTO users(username,password,nickname,create_time) VALUES (?,?,?,?)",user.username,user.password,user.nickname,trantor::Date::now());
     
            throw std::runtime_error("注册成功");
    
        }
        else
        {
            throw std::runtime_error("用户名冲突");
        }
        //throw std::runtime_error("注册成功");
        //json["message"] = "注册成功";
        
    }
    catch(const DrogonDbException& e)
    {
        //std::cerr << e.what() << '\n';
        throw std::runtime_error("注册失败,用户名冲突");
        //json["error"] = "注册失败";
    }  
    
    
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);   
    // auto resp = HttpResponse::newHttpJsonResponse(json);
    // callback(resp);

}


//-------------------------



