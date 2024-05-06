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
        auto res = clientPtr->execSqlSync("insert into friends values(?, ?)",userid,friendid);
        LOG_ERROR<<"添加成功";
    }
    catch(const DrogonDbException& e){
        LOG_ERROR<<"添加失败";
    }


}

void service::GroupModel::createGroup(std::string groupname,std::string groupdesc)
{
    auto clientPtr = drogon::app().getDbClient();
    try{
        auto res = clientPtr->execSqlSync("insert into allgroup(groupname, groupdesc) values(?, ?)",groupname,groupdesc);
        LOG_ERROR<<"创建成功";
    }
    catch(const DrogonDbException& e){
        LOG_ERROR<<"创建失败";
    }


}

void service::GroupModel::addGroup(int userid,int groupid,std::string role)
{
    auto clientPtr = drogon::app().getDbClient();
    try{
        auto res = clientPtr->execSqlSync("insert into groupuser values(?, ?, ?)",groupid,userid,role);
        LOG_ERROR<<"加入成功";
    }
    catch(const DrogonDbException& e){
        LOG_ERROR<<"加入失败";
    }


}




//根据指定groupid 查询群组用户id列表 ，除userid自己，主要用户群聊业务给群组其它成员群发消息
std::vector<int> service::GroupModel::queryGroupUsers(int userid, int groupid)
{
    auto clientPtr = drogon::app().getDbClient();

    std::vector<int> idVec;
    try{
        auto res = clientPtr->execSqlSync("select userid from groupuser where groupid = ? and userid != ?",groupid,userid);        
        LOG_ERROR<<"查询成功";

        for(auto row:res)
        {
            int id = row["userid"].as<int>();
            LOG_ERROR<<id;
            idVec.push_back(id);
        }

        return idVec;
    }
    catch(const DrogonDbException& e){
        LOG_ERROR<<"查询失败";
    }
    
}


//存储
void service::offlineMessageModel::insert(int userid,std::string msg)
{
    auto clientPtr = drogon::app().getDbClient();
    try{
    auto res = clientPtr->execSqlSync("insert into offlinemessage values(?, ?)",userid,msg);        
        LOG_ERROR<<"插入成功";
    }
    catch(const DrogonDbException& e){
        LOG_ERROR<<"插入失败";
    }

}
//移除
void service::offlineMessageModel::remove(int userid)
{
    auto clientPtr = drogon::app().getDbClient();
    try{
    auto res = clientPtr->execSqlSync("delete from offlinemessage where userid=?",userid);        
        LOG_ERROR<<"删除成功";
    }
    catch(const DrogonDbException& e){
        LOG_ERROR<<"删除失败";
    }


}
//查询用户离线消息
std::vector<std::string> service::offlineMessageModel::query(int userid)
{
    auto clientPtr = drogon::app().getDbClient();
    std::vector<std::string> vec;
    try{
    auto res = clientPtr->execSqlSync("select message from offlinemessage where userid = ?",userid);        
        LOG_ERROR<<"成功";
        for(auto row :res)
        {
            std::string message = row["message"].as<std::string>();
            LOG_ERROR<<message;
            vec.push_back(message);
        }
        return vec;
    }   
    catch(const DrogonDbException& e){
        LOG_ERROR<<"失败";
    }

}


