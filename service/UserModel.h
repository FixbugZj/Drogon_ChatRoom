//#include <common/Response.h>
#pragma once
#include "../controllers/userfunc.h"
#include <string>
#include <vector>

#include "../models/Users.h"
#include "../models/Friends.h"
#include "../models/Groupuser.h"
#include "../models/Allgroup.h"
#include "../models/Offlinemessages.h"


namespace service{



class UserModel 
{
public:

    void login(std::string &username, std::string &password);

    void registdo(std::string &username,std::string &password,std::string nickname);


    void updateState(const std::string state,int id);

    void resetState();

    
};



class FriendModel
{
public:
    void insert(int userid,int friendid);

    //vector<User> query(int userid); //返回好友列表
};


class Group
{

};


class GroupModel
{
public:

    void createGroup(std::string groupname,std::string groupdesc);
    void addGroup(int userid,int groupid,std::string role);
    // 查询用户所在群组信息
    //vector<Group> queryGroups(int userid);
    // 根据指定的groupid查询群组用户id列表，除userid自己，主要用户群聊业务给群组其它成员群发消息
    std::vector<int> queryGroupUsers(int userid, int groupid);
};

class GroupUser 
{
public:

};


class offlineMessageModel
{
public:
    //存储
    void insert(int userid,std::string msg);
    //移除
    void remove(int userid);
    //查询用户离线消息
    std::vector<std::string> query(int userid);

};

}






