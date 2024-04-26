//#include <common/Response.h>
#pragma once



namespace service{

class UserModel 
{
public:

    void login(std::string &username, std::string &password);

    void registdo(std::string &username,std::string &password,std::string nickname);

    bool updateState();

    void resetState();

    
};



class FriendModel
{
public:



};

}






