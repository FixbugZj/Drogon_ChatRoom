/**
 *
 *  Role.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/BaseBuilder.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}
}
namespace drogon_model
{
namespace koi
{

class Role
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _name;
        static const std::string _code;
        static const std::string _api;
        static const std::string _roleRoutes;
        static const std::string _firstPage;
        static const std::string _desc;
        static const std::string _createTime;
        static const std::string _updateTime;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = uint64_t;
    const PrimaryKeyType &getPrimaryKey() const;

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column names,
     * otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select all
     * columns by an asterisk), please set the offset to -1.
     */
    explicit Role(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Role(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Role(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Role() = default;

    void updateByJson(const Json::Value &pJson) noexcept(false);
    void updateByMasqueradedJson(const Json::Value &pJson,
                                 const std::vector<std::string> &pMasqueradingVector) noexcept(false);
    static bool validateJsonForCreation(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForCreation(const Json::Value &,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                    std::string &err);
    static bool validateJsonForUpdate(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForUpdate(const Json::Value &,
                                          const std::vector<std::string> &pMasqueradingVector,
                                          std::string &err);
    static bool validJsonOfField(size_t index,
                          const std::string &fieldName,
                          const Json::Value &pJson,
                          std::string &err,
                          bool isForCreation);

    /**  For column id  */
    ///Get the value of the column id, returns the default value if the column is null
    const uint64_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<uint64_t> &getId() const noexcept;
    ///Set the value of the column id
    void setId(const uint64_t &pId) noexcept;

    /**  For column name  */
    ///Get the value of the column name, returns the default value if the column is null
    const std::string &getValueOfName() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getName() const noexcept;
    ///Set the value of the column name
    void setName(const std::string &pName) noexcept;
    void setName(std::string &&pName) noexcept;

    /**  For column code  */
    ///Get the value of the column code, returns the default value if the column is null
    const std::string &getValueOfCode() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getCode() const noexcept;
    ///Set the value of the column code
    void setCode(const std::string &pCode) noexcept;
    void setCode(std::string &&pCode) noexcept;

    /**  For column api  */
    ///Get the value of the column api, returns the default value if the column is null
    const std::string &getValueOfApi() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getApi() const noexcept;
    ///Set the value of the column api
    void setApi(const std::string &pApi) noexcept;
    void setApi(std::string &&pApi) noexcept;
    void setApiToNull() noexcept;

    /**  For column roleRoutes  */
    ///Get the value of the column roleRoutes, returns the default value if the column is null
    const std::string &getValueOfRoleroutes() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getRoleroutes() const noexcept;
    ///Set the value of the column roleRoutes
    void setRoleroutes(const std::string &pRoleroutes) noexcept;
    void setRoleroutes(std::string &&pRoleroutes) noexcept;
    void setRoleroutesToNull() noexcept;

    /**  For column firstPage  */
    ///Get the value of the column firstPage, returns the default value if the column is null
    const std::string &getValueOfFirstpage() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getFirstpage() const noexcept;
    ///Set the value of the column firstPage
    void setFirstpage(const std::string &pFirstpage) noexcept;
    void setFirstpage(std::string &&pFirstpage) noexcept;
    void setFirstpageToNull() noexcept;

    /**  For column desc  */
    ///Get the value of the column desc, returns the default value if the column is null
    const std::string &getValueOfDesc() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getDesc() const noexcept;
    ///Set the value of the column desc
    void setDesc(const std::string &pDesc) noexcept;
    void setDesc(std::string &&pDesc) noexcept;
    void setDescToNull() noexcept;

    /**  For column createTime  */
    ///Get the value of the column createTime, returns the default value if the column is null
    const ::trantor::Date &getValueOfCreatetime() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getCreatetime() const noexcept;
    ///Set the value of the column createTime
    void setCreatetime(const ::trantor::Date &pCreatetime) noexcept;
    void setCreatetimeToNull() noexcept;

    /**  For column updateTime  */
    ///Get the value of the column updateTime, returns the default value if the column is null
    const ::trantor::Date &getValueOfUpdatetime() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getUpdatetime() const noexcept;
    ///Set the value of the column updateTime
    void setUpdatetime(const ::trantor::Date &pUpdatetime) noexcept;
    void setUpdatetimeToNull() noexcept;


    static size_t getColumnNumber() noexcept {  return 9;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;
    /// Relationship interfaces
  private:
    friend drogon::orm::Mapper<Role>;
    friend drogon::orm::BaseBuilder<Role, true, true>;
    friend drogon::orm::BaseBuilder<Role, true, false>;
    friend drogon::orm::BaseBuilder<Role, false, true>;
    friend drogon::orm::BaseBuilder<Role, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Role>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<uint64_t> id_;
    std::shared_ptr<std::string> name_;
    std::shared_ptr<std::string> code_;
    std::shared_ptr<std::string> api_;
    std::shared_ptr<std::string> roleroutes_;
    std::shared_ptr<std::string> firstpage_;
    std::shared_ptr<std::string> desc_;
    std::shared_ptr<::trantor::Date> createtime_;
    std::shared_ptr<::trantor::Date> updatetime_;
    struct MetaData
    {
        const std::string colName_;
        const std::string colType_;
        const std::string colDatabaseType_;
        const ssize_t colLength_;
        const bool isAutoVal_;
        const bool isPrimaryKey_;
        const bool notNull_;
    };
    static const std::vector<MetaData> metaData_;
    bool dirtyFlag_[9]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where id = ?";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where id = ?";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
            sql += "id,";
            ++parametersCount;
        if(dirtyFlag_[1])
        {
            sql += "name,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "code,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "api,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "roleRoutes,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "firstPage,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "desc,";
            ++parametersCount;
        }
        sql += "createTime,";
        ++parametersCount;
        if(!dirtyFlag_[7])
        {
            needSelection=true;
        }
        if(dirtyFlag_[8])
        {
            sql += "updateTime,";
            ++parametersCount;
        }
        needSelection=true;
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";

        sql +="default,";
        if(dirtyFlag_[1])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[2])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[3])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[4])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[5])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[6])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[7])
        {
            sql.append("?,");

        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[8])
        {
            sql.append("?,");

        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        sql.append(1, ')');
        LOG_TRACE << sql;
        return sql;
    }
};
} // namespace koi
} // namespace drogon_model
