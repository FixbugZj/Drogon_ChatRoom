#pragma

#include <common/Response.h>

namespace service {

class User {
    User(int id = -1,string name = "",string pwd = "",string state = "offline")
    {
        this->id = id;
        this->name = name;
        this->password = pwd;
        this->state = state;
    }

    void setId(int id) {this->id = id;}
    void setName(string name) { this->name = name; }
    void setPwd(string pwd) { this->password = pwd; }
    void setState(string state) { this->state = state; }

    int getId() { return this->id; }
    string getName() { return this->name; }
    string getPwd() { return this->password; }
    string getState() { return this->state; }


private:
    int id;
    std::string name ;
    std::string password ;
    std::string state;
};

}  // namespace service