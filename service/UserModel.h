#include <common/Response.h>
#include "User.h"

using namespace common;

namespace service {

class UserModel {
    public:
    common::Response login(std::string &account, std::string &password);

    common::Response register(std::string &account,std::string &password,std::string nickname);

    bool updateState(User& user);

    void resetState();

    User query(int id);
    
};

}  // namespace service

