#include "scoredao.h"

ScoreDAO::ScoreDAO(){

}

ScoreDAO::ScoreDAO(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(!m_db.open()){
        std::cout << "Error connection with database fail";
    }
    else {
        std::cout << "Database: connection ok";
    }
}

bool ScoreDAO::addScore(const Score &score){
        int Score = score.getScore();
        QString date = QString::fromStdString(score.getDate());
        QString board = QString::fromStdString(score.getBoard());
        QString duree = score.getTime().toString();
        int use = score.getUse();
        int nbStep = score.getNbStep();
        int idUser = score.getUserId();
        cout << "idUser = " << idUser << endl;
        QSqlQuery query;
        query.prepare("INSERT INTO score(score, date, board, duree, useSolver, nbStep, user) VALUES (:score, :date, :board, :duree, :useSolver, :nbStep, :user)");
        query.bindValue(":score", Score);
        query.bindValue(":date", date);
        query.bindValue(":board",board);
        query.bindValue(":duree", duree);
        query.bindValue(":useSolver", use);
        query.bindValue(":nbStep", nbStep);
        query.bindValue(":user", idUser);

        if(query.exec()){
            return true;
        }

    return false;
}

vector<Score> ScoreDAO::getAllById(int id){
    vector<Score> scores;
    QSqlQuery query;
    query.prepare("SELECT * FROM score WHERE user = (:id)");
    query.bindValue(":id", id);
    if(query.exec())
        while(query.next()){
            int idScore = query.record().indexOf("score");
            int idDate = query.record().indexOf("date");
            int idBoard = query.record().indexOf("board");
            int idDuree = query.record().indexOf("duree");
            int idNb = query.record().indexOf("nbStep");
            int idUse = query.record().indexOf("useSolver");
            int idUser = query.record().indexOf("user");
            scores.push_back(Score(    (int)query.value(idScore).toInt(),
                                       query.value(idDate).toString().toStdString(),
                                       query.value(idBoard).toString().toStdString(),
                                       QTime::fromString(query.value(idDuree).toString()),
                                       query.value(idUse).toInt(),
                                       query.value(idNb).toInt(),
                                       query.value(idUser).toInt()));
    }
    return scores;
}

vector<Score> ScoreDAO::getAll(){
    vector<Score> scores;
    QSqlQuery query("SELECT * FROM score");

    while(query.next()){
        int idScore = query.record().indexOf("score");
        int idDate = query.record().indexOf("date");
        int idBoard = query.record().indexOf("board");
        int idDuree = query.record().indexOf("duree");
        int idNb = query.record().indexOf("nbStep");
        int idUse = query.record().indexOf("useSolver");
        int idUser = query.record().indexOf("user");
        scores.push_back(Score(    query.value(idScore).toInt(),
                                   query.value(idDate).toString().toStdString(),
                                   query.value(idBoard).toString().toStdString(),
                                   QTime::fromString(query.value(idDuree).toString()),
                                   query.value(idUse).toInt(),
                                   query.value(idNb).toInt(),
                                   query.value(idUser).toInt()));
    }
    return scores;
}

bool ScoreDAO::existIn(const Score &score){
    QSqlQuery query;
    query.prepare("SELECT score FROM score WHERE date = (:date)");
    query.bindValue(":date", QString::fromStdString(score.getDate()));

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
