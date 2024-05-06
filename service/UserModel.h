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

class User
{
    public:
    User(int id = -1, std::string name = "", std::string pwd = "", std::string state = "offline")
    {
        this->id = id;
        this->name = name;
        this->password = pwd;
        this->state = state;
    }

    void setId(int id) { this->id = id; }
    void setName(std::string name) { this->name = name; }
    void setPwd(std::string pwd) { this->password = pwd; }
    void setState(std::string state) { this->state = state; }

    int getId() { return this->id; }
    std::string getName() { return this->name; }
    std::string getPwd() { return this->password; }
    std::string getState() { return this->state; }

protected:
    int id;
    std::string name;
    std::string password;
    std::string state;

};


class GroupUser : public User
{
public:
    void setRole(std::string role) { this->role = role; }
    std::string getRole() { return this->role; }
private:
    std::string role;
};


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

    std::vector<User> query(int userid); //返回好友列表
};


class Group
{
    public:
    Group(int id = -1, std::string name = "", std::string desc = "")
    {
        this->id = id;
        this->name = name;
        this->desc = desc;
    }

    void setId(int id) { this->id = id; }
    void setName(std::string name) { this->name = name; }
    void setDesc(std::string desc) { this->desc = desc; }

    int getId() { return this->id; }
    std::string getName() { return this->name; }
    std::string getDesc() { return this->desc; }
    std::vector<GroupUser> &getUsers() { return this->users; }

private:
    int id;
    std::string name;
    std::string desc;
    std::vector<GroupUser> users;
};


class GroupModel
{
public:

    void createGroup(std::string groupname,std::string groupdesc);
    void addGroup(int userid,int groupid,std::string role);
    // 查询用户所在群组信息
    std::vector<Group> queryGroups(int userid);
    // 根据指定的groupid查询群组用户id列表，除userid自己，主要用户群聊业务给群组其它成员群发消息
    std::vector<int> queryGroupUsers(int userid, int groupid);
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






