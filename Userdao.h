#ifndef USERDAO_H
#define USERDAO_H

#include "User.h"
#include <iostream>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QString>
#include <QSqlDatabase>

class UserDAO
{
public:
    UserDAO(const QString& path);
    virtual ~UserDAO();
    User getById(int& id);
    User getByName(string& name);
    vector<User> getAll();
    bool addUser(const User& user);
    bool existIn(const User& user);

private:
    QSqlDatabase m_db;
};

#endif // USERDAO_H
