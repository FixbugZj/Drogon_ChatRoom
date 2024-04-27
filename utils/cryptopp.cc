#include "cryptopp.h"
#include <crypto++/hex.h>
#include <crypto++/sha.h>
#include <crypto++/osrng.h>
#include <string>



std::string Cryptopp::hashPassword(const std::string& password)
{
    CryptoPP::SHA256 hash;

    byte digest[CryptoPP::SHA256::DIGESTSIZE];
    hash.CalculateDigest(digest,(byte*)password.data(),password.size());
    
    //将哈希值转换为十六进制字符串
    CryptoPP::HexEncoder encoder;
    std::string output;
    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest,sizeof(digest));
    encoder.MessageEnd();

    return output;
}



std::string Cryptopp::generateSale()
{
    // 生成随机盐值
    CryptoPP::AutoSeededRandomPool rng;
    byte salt[8];
    rng.GenerateBlock(salt, sizeof(salt));

    // 将盐值转换为十六进制字符串
    CryptoPP::HexEncoder encoder;
    std::string output;
    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(salt, sizeof(salt));
    encoder.MessageEnd();

    return output;
}


