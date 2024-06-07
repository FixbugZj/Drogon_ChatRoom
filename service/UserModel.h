//#include <common/Response.h>
#pragma once

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
    User(int id = -1, std::string nickname = "", std::string account = "",std::string phone = "" )
    {
        this->id = id;
        this->nickname = nickname;
        this->account = account;
        this->phone = phone;
    }

    void setId(int id) { this->id = id; }
    void setNickName(std::string nickname) { this->nickname = nickname; }
    void setAccount(std::string account) { this->account = account; }
    void setPhone(std::string phone) {this->phone = phone;}

    int getId() { return this->id; }
    std::string getName() { return this->nickname; }
    std::string getAccount() { return this->account; }
    std::string getPhone() {return this->phone;}


private:
    int id;
    std::string account;
    std::string nickname;
    std::string phone;

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

    void login(std::string &account, std::string &password);

    void registdo(std::string account,std::string &password);
    void registdo(std::string account,std::string &password,std::string &nickname);


    void updateState(const std::string state,int id);

    void resetState();

    
};


class FriendModel
{
public:
    void insert(int rid,int friendid);

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

    int createGroup(std::string groupname,std::string groupdesc,int id);
    void addGroup(int userid,int groupid,std::string role);
    // 查询用户所在群组信息
    std::vector<Group> queryGroups(int userid);

    std::vector<int> queryGroupUsers( int groupid);
    
    // 根据指定的groupid查询群组用户id列表，除userid自己，主要用户群聊业务给群组其它成员群发消息
    std::vector<int> queryGroupUsers(int id, int groupid);

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


