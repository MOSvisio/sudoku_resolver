#include "Userdao.h"

UserDAO::UserDAO(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(!m_db.open()){
        std::cout << "Error connection with database fail" << endl;
    }
    else {
        std::cout << "Database: connection ok" << endl;
    }
}

UserDAO::~UserDAO(){
   QSqlDatabase::removeDatabase("QSQLITE");
}

bool UserDAO::addUser(const User &user){
    if(!this->existIn(user)){
        QString name = QString::fromStdString(user.getName());

        QSqlQuery query;
        query.prepare("INSERT INTO user(name) VALUES(:name)");
        query.bindValue(":name", name);

        if(query.exec()){
            return false;
        }
     }
     return true;
}

User UserDAO::getById(int &id){
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE id = (:id)");
    query.bindValue(":id", id);
    User tmp;
    if(query.exec())
        if(query.next()){
            int idId = query.record().indexOf("id");
            int idName = query.record().indexOf("name");
            tmp = User(query.value(idId).toInt(), query.value(idName).toString().toStdString());
        }
    return tmp;
}

User UserDAO::getByName(string& name){
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE name = (:name)");
    query.bindValue(":name", QString::fromStdString(name));
    User tmp;
    if(query.exec())
        if(query.next()){
            int idId = query.record().indexOf("id");
            int idName = query.record().indexOf("name");
            tmp = User(query.value(idId).toInt(), query.value(idName).toString().toStdString());
        }
    return tmp;
}

bool UserDAO::existIn(const User &user){
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE name = (:name)");
    query.bindValue(":name", QString::fromStdString(user.getName()));

    if (query.exec())
    {
       if (query.next())
       {
          // it exists
           return true;
       }
    }
    return false;
}

vector<User> UserDAO::getAll(){
    vector<User> tmp;
    QSqlQuery query("SELECT * FROM user");
    int idId = query.record().indexOf("id");
    int idName = query.record().indexOf("name");

    while(query.next()){
        tmp.push_back(User(query.value(idId).toInt(), query.value(idName).toString().toStdString()));
    }
    return tmp;
}
