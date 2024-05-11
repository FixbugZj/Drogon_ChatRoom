#ifndef CRYPTOPP_H
#define CRYPTOPP_H

#include<string>

namespace utils
{

class Cryptopp
{
public:
    std::string hashPassword(const std::string&password);
    std::string generateSale();
};

}


#endif