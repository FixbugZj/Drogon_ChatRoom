/**
 *
 *  Offlinemessages.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Offlinemessages.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::koi;

const std::string Offlinemessages::Cols::_id = "id";
const std::string Offlinemessages::Cols::_message = "message";
const std::string Offlinemessages::Cols::_time = "time";
const std::string Offlinemessages::Cols::_from_id = "from_id";
const std::string Offlinemessages::primaryKeyName = "";
const bool Offlinemessages::hasPrimaryKey = false;
const std::string Offlinemessages::tableName = "offlinemessages";

const std::vector<typename Offlinemessages::MetaData> Offlinemessages::metaData_={
{"id","int32_t","int",4,0,0,1},
{"message","std::string","varchar(500)",500,0,0,1},
{"time","::trantor::Date","timestamp",0,0,0,0},
{"from_id","int32_t","int",4,0,0,0}
};
const std::string &Offlinemessages::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Offlinemessages::Offlinemessages(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["message"].isNull())
        {
            message_=std::make_shared<std::string>(r["message"].as<std::string>());
        }
        if(!r["time"].isNull())
        {
            auto timeStr = r["time"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                time_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["from_id"].isNull())
        {
            fromId_=std::make_shared<int32_t>(r["from_id"].as<int32_t>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 4 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            id_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            message_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            auto timeStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                time_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            fromId_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
    }

}

Offlinemessages::Offlinemessages(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 4)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            message_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            auto timeStr = pJson[pMasqueradingVector[2]].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                time_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            fromId_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[3]].asInt64());
        }
    }
}

Offlinemessages::Offlinemessages(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("message"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["message"].isNull())
        {
            message_=std::make_shared<std::string>(pJson["message"].asString());
        }
    }
    if(pJson.isMember("time"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["time"].isNull())
        {
            auto timeStr = pJson["time"].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                time_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
    if(pJson.isMember("from_id"))
    {
        dirtyFlag_[3]=true;
        if(!pJson["from_id"].isNull())
        {
            fromId_=std::make_shared<int32_t>((int32_t)pJson["from_id"].asInt64());
        }
    }
}

void Offlinemessages::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 4)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            message_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            auto timeStr = pJson[pMasqueradingVector[2]].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                time_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            fromId_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[3]].asInt64());
        }
    }
}

void Offlinemessages::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        dirtyFlag_[0] = true;
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("message"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["message"].isNull())
        {
            message_=std::make_shared<std::string>(pJson["message"].asString());
        }
    }
    if(pJson.isMember("time"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["time"].isNull())
        {
            auto timeStr = pJson["time"].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                time_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
    if(pJson.isMember("from_id"))
    {
        dirtyFlag_[3] = true;
        if(!pJson["from_id"].isNull())
        {
            fromId_=std::make_shared<int32_t>((int32_t)pJson["from_id"].asInt64());
        }
    }
}

const int32_t &Offlinemessages::getValueOfId() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Offlinemessages::getId() const noexcept
{
    return id_;
}
void Offlinemessages::setId(const int32_t &pId) noexcept
{
    id_ = std::make_shared<int32_t>(pId);
    dirtyFlag_[0] = true;
}

const std::string &Offlinemessages::getValueOfMessage() const noexcept
{
    static const std::string defaultValue = std::string();
    if(message_)
        return *message_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Offlinemessages::getMessage() const noexcept
{
    return message_;
}
void Offlinemessages::setMessage(const std::string &pMessage) noexcept
{
    message_ = std::make_shared<std::string>(pMessage);
    dirtyFlag_[1] = true;
}
void Offlinemessages::setMessage(std::string &&pMessage) noexcept
{
    message_ = std::make_shared<std::string>(std::move(pMessage));
    dirtyFlag_[1] = true;
}

const ::trantor::Date &Offlinemessages::getValueOfTime() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(time_)
        return *time_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Offlinemessages::getTime() const noexcept
{
    return time_;
}
void Offlinemessages::setTime(const ::trantor::Date &pTime) noexcept
{
    time_ = std::make_shared<::trantor::Date>(pTime);
    dirtyFlag_[2] = true;
}
void Offlinemessages::setTimeToNull() noexcept
{
    time_.reset();
    dirtyFlag_[2] = true;
}

const int32_t &Offlinemessages::getValueOfFromId() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(fromId_)
        return *fromId_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Offlinemessages::getFromId() const noexcept
{
    return fromId_;
}
void Offlinemessages::setFromId(const int32_t &pFromId) noexcept
{
    fromId_ = std::make_shared<int32_t>(pFromId);
    dirtyFlag_[3] = true;
}
void Offlinemessages::setFromIdToNull() noexcept
{
    fromId_.reset();
    dirtyFlag_[3] = true;
}

void Offlinemessages::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Offlinemessages::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "message",
        "time",
        "from_id"
    };
    return inCols;
}

void Offlinemessages::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getId())
        {
            binder << getValueOfId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getMessage())
        {
            binder << getValueOfMessage();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getTime())
        {
            binder << getValueOfTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getFromId())
        {
            binder << getValueOfFromId();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Offlinemessages::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[0])
    {
        ret.push_back(getColumnName(0));
    }
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if(dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    return ret;
}

void Offlinemessages::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getId())
        {
            binder << getValueOfId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getMessage())
        {
            binder << getValueOfMessage();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getTime())
        {
            binder << getValueOfTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getFromId())
        {
            binder << getValueOfFromId();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Offlinemessages::toJson() const
{
    Json::Value ret;
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getMessage())
    {
        ret["message"]=getValueOfMessage();
    }
    else
    {
        ret["message"]=Json::Value();
    }
    if(getTime())
    {
        ret["time"]=getTime()->toDbStringLocal();
    }
    else
    {
        ret["time"]=Json::Value();
    }
    if(getFromId())
    {
        ret["from_id"]=getValueOfFromId();
    }
    else
    {
        ret["from_id"]=Json::Value();
    }
    return ret;
}

Json::Value Offlinemessages::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 4)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getId())
            {
                ret[pMasqueradingVector[0]]=getValueOfId();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getMessage())
            {
                ret[pMasqueradingVector[1]]=getValueOfMessage();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getTime())
            {
                ret[pMasqueradingVector[2]]=getTime()->toDbStringLocal();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getFromId())
            {
                ret[pMasqueradingVector[3]]=getValueOfFromId();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getMessage())
    {
        ret["message"]=getValueOfMessage();
    }
    else
    {
        ret["message"]=Json::Value();
    }
    if(getTime())
    {
        ret["time"]=getTime()->toDbStringLocal();
    }
    else
    {
        ret["time"]=Json::Value();
    }
    if(getFromId())
    {
        ret["from_id"]=getValueOfFromId();
    }
    else
    {
        ret["from_id"]=Json::Value();
    }
    return ret;
}

bool Offlinemessages::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    else
    {
        err="The id column cannot be null";
        return false;
    }
    if(pJson.isMember("message"))
    {
        if(!validJsonOfField(1, "message", pJson["message"], err, true))
            return false;
    }
    else
    {
        err="The message column cannot be null";
        return false;
    }
    if(pJson.isMember("time"))
    {
        if(!validJsonOfField(2, "time", pJson["time"], err, true))
            return false;
    }
    if(pJson.isMember("from_id"))
    {
        if(!validJsonOfField(3, "from_id", pJson["from_id"], err, true))
            return false;
    }
    return true;
}
bool Offlinemessages::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                         const std::vector<std::string> &pMasqueradingVector,
                                                         std::string &err)
{
    if(pMasqueradingVector.size() != 4)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty())
      {
          if(pJson.isMember(pMasqueradingVector[0]))
          {
              if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[0] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[1].empty())
      {
          if(pJson.isMember(pMasqueradingVector[1]))
          {
              if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[1] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[2].empty())
      {
          if(pJson.isMember(pMasqueradingVector[2]))
          {
              if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[3].empty())
      {
          if(pJson.isMember(pMasqueradingVector[3]))
          {
              if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, true))
                  return false;
          }
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Offlinemessages::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, false))
            return false;
    }
    if(pJson.isMember("message"))
    {
        if(!validJsonOfField(1, "message", pJson["message"], err, false))
            return false;
    }
    if(pJson.isMember("time"))
    {
        if(!validJsonOfField(2, "time", pJson["time"], err, false))
            return false;
    }
    if(pJson.isMember("from_id"))
    {
        if(!validJsonOfField(3, "from_id", pJson["from_id"], err, false))
            return false;
    }
    return true;
}
bool Offlinemessages::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                       const std::vector<std::string> &pMasqueradingVector,
                                                       std::string &err)
{
    if(pMasqueradingVector.size() != 4)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
      {
          if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
              return false;
      }
      if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
      {
          if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
              return false;
      }
      if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
      {
          if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, false))
              return false;
      }
      if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
      {
          if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, false))
              return false;
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Offlinemessages::validJsonOfField(size_t index,
                                       const std::string &fieldName,
                                       const Json::Value &pJson,
                                       std::string &err,
                                       bool isForCreation)
{
    switch(index)
    {
        case 0:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 1:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 500)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 500)";
                return false;
            }

            break;
        case 2:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 3:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        default:
            err="Internal error in the server";
            return false;
    }
    return true;
}
