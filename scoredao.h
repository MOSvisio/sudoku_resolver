#ifndef SCOREDAO_H
#define SCOREDAO_H

#include "Score.h"
#include <vector>
#include <iostream>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QString>
#include <QSqlDatabase>

class ScoreDAO
{
public:
    ScoreDAO();
    ScoreDAO(const QString& path);
    bool addScore(const Score& score);
    vector<Score> getAll();
    vector<Score> getAllById(int id);
    bool existIn(const Score& score);
private:
    QSqlDatabase m_db;
    Score e;
};

#endif // SCOREDAO_H
