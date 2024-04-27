//#include <common/Response.h>
#include <models/Users.h>
#include <drogon/orm/Exception.h>
#include <drogon/drogon.h>
#include "UserModel.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::db;



void service::UserModel::login(std::string &username,
                        std::string &password) 
{
    auto clientDb=drogon::app().getDbClient();
    Mapper<Users> mapper(clientDb);

    auto userInDb = 
            mapper.findOne({Users::Cols::_username,username});
    
    
    if(userInDb.getValueOfPassword() != password)
    {
        throw std::runtime_error("密码错误");
    }
    
}



void service::UserModel::registdo(std::string &username,std::string &password,std::string nickname)
{
    auto clientPtr = drogon::app().getDbClient();
    auto res = clientPtr->execSqlSync("select username from users where username = ?",username);

    try{
        if(res.empty())
        {
            clientPtr->execSqlSync("INSERT INTO users(username,password,nickname) VALUES (?,?,?)",
                        username,password,nickname);
    
            throw std::runtime_error("注册成功");
            //return common::Response(200,"注册成功");
        }
        else
        {
        throw std::runtime_error("用户名冲突");
        //return common::Response(300,"用户名冲突");

        }
    }
    catch(const DrogonDbException& e){
        throw std::runtime_error("注册失败,用户名冲突");
        // LOG_ERROR<<"用户名冲突";.3
        //return common::Response(300,"用户名冲突");
    }


}

// User service::UserModel::quert(int id)
// {
//     auto clientPtr = drogon::app().getDbClient();
//     auto res = clientPtr->execSqlSync("select * from users where id = ?",id);
//     if(res !=nullptr)
//     {
//         User user;
//         user.
        
//     }
    
// }


void service::UserModel::updateState(const std::string state,int id)
{
    auto clientPtr = drogon::app().getDbClient();
    LOG_ERROR<<"数据库连接成功";
    try{
        auto res = clientPtr->execSqlSync("update user set state = ? where id=? ",state,id);
        LOG_ERROR<<"更新状态成功";
    }
    catch(const DrogonDbException& e){
        LOG_ERROR<<"状态更新失败";
    }
}



void service::UserModel::resetState()
{
    auto clientPtr = drogon::app().getDbClient();
    LOG_ERROR<<"数据库连接成功";
    try{
        auto res = clientPtr->execSqlSync("update user set state = 'offline' where state = 'online'");
        LOG_ERROR<<"更新状态成功";
    }
    catch(const DrogonDbException& e){
        LOG_ERROR<<"状态更新失败";
    }
    
}


void service::FriendModel::insert(int userid,int friendid)
{
    auto clientPtr = drogon::app().getDbClient();
        LOG_ERROR<<"数据库连接成功";
    try{
        auto res = clientPtr->execSqlSync("insert into friend values(?, ?)",userid,friendid);
        LOG_ERROR<<"添加成功";
    }
    catch(const DrogonDbException& e){
        LOG_ERROR<<"添加失败";
    }


}