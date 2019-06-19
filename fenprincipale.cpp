#include "fenprincipale.h"


FenPrincipale::~FenPrincipale(){}

FenPrincipale::FenPrincipale()
{
    qRegisterMetaType<Board>("Board");

    th = new myThread();

    QWidget *zoneCentrale = new QWidget;
    boardLayout = new QGridLayout;
    btnLayout = new QVBoxLayout;
    gridAndBtn = new QVBoxLayout;
    allLayout = new QHBoxLayout;
    btnBackNext = new QHBoxLayout;

    btn_validate = new QPushButton;
    btn_quit = new QPushButton;
    btn_correct = new QPushButton;
    btn_cancel = new QPushButton;
    btn_openFile = new QPushButton;
    btn_backward = new QPushButton;
    btn_forward = new QPushButton;

    btn_openFile->setText("&Open file");
    btn_quit->setText("&Quit");
    btn_validate->setText("&Validate");
    btn_correct->setText("&Correct");
    btn_cancel->setText("&Cancel");
    btn_forward->setText("&Next");
    btn_backward->setText("&Back");

    btnLayout->addWidget(btn_openFile);
    btnLayout->addWidget(btn_validate);
    btnLayout->addWidget(btn_correct);
    btnLayout->addWidget(btn_cancel);
    btnLayout->addWidget(btn_quit);

    btnBackNext->addWidget(btn_backward);
    btnBackNext->addWidget(btn_forward);

    gridAndBtn->addLayout(btnBackNext);
    gridAndBtn->addLayout(boardLayout);

    btn_forward->setVisible(false);
    btn_backward->setVisible(false);

    allLayout->addLayout(gridAndBtn);
    allLayout->addLayout(btnLayout);

    btn_validate->setEnabled(false);
    btn_correct->setEnabled(false);
    btn_cancel->setEnabled(false);

    QObject::connect(btn_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(btn_openFile, SIGNAL(clicked()), this, SLOT(openBoard()));
    QObject::connect(btn_validate, SIGNAL(clicked()), this, SLOT(verificationBoard()));

    QObject::connect(btn_correct, SIGNAL(clicked()), this, SLOT(resolveBoard()));
    QObject::connect(th, SIGNAL(updateBoard(Board)), this, SLOT(updateBoard(Board)));
    QObject::connect(th, SIGNAL(thIsStopped()), this, SLOT(thIsStopped()));

    QObject::connect(btn_backward, SIGNAL(clicked()), this, SLOT(getPreviousBoard()));
    QObject::connect(btn_forward, SIGNAL(clicked()), this, SLOT(getNextBoard()));
    QObject::connect(btn_cancel, SIGNAL(clicked()), this, SLOT(reset()));

    player = User("");


    zoneCentrale->setLayout(allLayout);

    setCentralWidget(zoneCentrale);

}

void FenPrincipale::openBoard(){
    QString file = QFileDialog::getOpenFileName(this, "open a file", QString(), "Text (*.txt)");
    char * cstr;
    string fname = file.toStdString();
    cstr = new char[fname.size()+1];
    strcpy(cstr, fname.c_str());

    this->Grid = Board(cstr);

    QIntValidator *numberOnly = new QIntValidator(1,9,this);
    listWid.clear();
    listBoardResolve.clear();
    QPalette palette;
    palette.setColor(QPalette::Base, QColor(229,229,229,255));
    if(this->Grid.isValid()){
        actualScore = Score();
        QString boardName = file.split(QDir::separator()).last();
        actualScore.setBoard(boardName.toStdString());
        this->userCreation();
        th->setBoard(this->Grid);
        for(int i(0); i<9; ++i){
            for(int j(0); j<9; ++j){
                if(this->Grid.getBox(j,i).getDefValue() == 0){
                    QLineEdit * new_edit = new QLineEdit;
                    new_edit->setMaximumSize(QSize(32,32));
                    new_edit->setMinimumSize(QSize(32,32));
                    new_edit->setAlignment(Qt::AlignVCenter);
                    new_edit->setAlignment(Qt::AlignHCenter);
                    new_edit->setText("");
                    new_edit->setValidator(numberOnly);
                    listWid.push_back(new_edit);
                    boardLayout->addWidget(new_edit, j, i);
                }
                else {
                    QLineEdit * new_edit = new QLineEdit;
                    new_edit->setText(QString::number(this->Grid.getBox(j,i).getDefValue()));
                    new_edit->setReadOnly(true);
                    new_edit->setMaximumSize(QSize(32,32));
                    new_edit->setMinimumSize(QSize(32,32));
                    new_edit->setAlignment(Qt::AlignVCenter);
                    new_edit->setAlignment(Qt::AlignHCenter);
                    new_edit->setPalette(palette);
                    new_edit->setValidator(numberOnly);
                    listWid.push_back(new_edit);
                    boardLayout->addWidget(new_edit, j, i);
                }
            }
        }
        btn_validate->setEnabled(true);
        btn_correct->setEnabled(true);
        btn_cancel->setEnabled(true);
        boardLayout->setEnabled(true);
    }
    btn_backward->setVisible(false);
    btn_forward->setVisible(false);
}

void FenPrincipale::verificationBoard(){
    // i can get all the value in my text field
    QString valeur;
    for(int i(0); i<(int)this->listWid.size(); ++i){
        if(listWid[i]->text().size() == 0){
            valeur.append("0");
        }
        else{
            valeur.append(listWid[i]->text());
        }
    }
    valeur = valeur.trimmed();
    int v(0);
    Board test = this->Grid;
    for(int i(0); i<9; ++i){
        for(int j(0); j<9; ++j){
            if(test.getBox(i,j).getDefValue() == 0 && valeur[v].digitValue() != 0){
                test.setDefinitiveValue(i,j,valeur[v].digitValue());
            }
            v++;
        }
    }
    if(test.isSolved()){
        this->Grid = test;
        QMessageBox::information(this, "Oh well done, the board is valid", "You're awesome !");
    }
    else{
        QMessageBox::information(this, "Oh no, the board is not valid", "There are some mistakes, try again, you can do it !");
    }
}


/*
    take a board in parameter and update all the lineEdit with the new values 
*/
void FenPrincipale::updateBoard(Board b){
    int v(0), count(0);
    QPalette palette;
    QPalette baseChoose;
    QPalette baseEmpty;
    palette.setColor(QPalette::Base, QColor(66, 244, 143,255));
    baseChoose.setColor(QPalette::Base, QColor(229,229,229,255));
    baseEmpty.setColor(QPalette::Base, QColor(255,255,255,255));
    for(int j(0); j<9; ++j){
        for(int i(0); i<9; ++i){
            if(b.getBox(i,j).getDefValue() != 0 && !(this->listWid[v]->isReadOnly())){
                this->listWid[v]->setReadOnly(false);
                this->listWid[v]->setEnabled(true);
                this->listWid[v]->setText(QString::number(b.getBox(i,j).getDefValue()));
                this->listWid[v]->setReadOnly(true);
                this->listWid[v]->setAlignment(Qt::AlignHCenter);
                this->listWid[v]->setPalette(palette);
                this->listWid[v]->repaint();
                count++;
            }
            else if (b.getBox(i,j).getDefValue() == 0){
                this->listWid[v]->setText("");
                this->listWid[v]->setReadOnly(false);
                this->listWid[v]->setAlignment(Qt::AlignHCenter);
                this->listWid[v]->setPalette(baseEmpty);
                this->listWid[v]->setEnabled(false);
                this->listWid[v]->repaint();
            }
            else if(b.getBox(i,j).getDefValue() != 0 && (this->listWid[v]->isReadOnly())){
                listWid[v]->setPalette(baseChoose);
                this->listWid[v]->setEnabled(true);
                count++;
            }
            v++;
        }
    }
    if (count != 0){
        this->listBoardResolve.push_back(b);
    }
}

void FenPrincipale::screenBoard(Board &b){
    int v(0);
    QPalette palette;
    QPalette baseChoose;
    QPalette baseEmpty;
    palette.setColor(QPalette::Base, QColor(66, 244, 143,255));
    baseChoose.setColor(QPalette::Base, QColor(229,229,229,255));
    baseEmpty.setColor(QPalette::Base, QColor(255,255,255,255));
    for(int j(0); j<9; ++j){
        for(int i(0); i<9; ++i){
            if(b.getBox(i,j).getDefValue() != 0 && !(this->listWid[v]->isReadOnly())){
                this->listWid[v]->setReadOnly(false);
                this->listWid[v]->setEnabled(true);
                this->listWid[v]->setText(QString::number(b.getBox(i,j).getDefValue()));
                this->listWid[v]->setReadOnly(true);
                this->listWid[v]->setAlignment(Qt::AlignHCenter);
                this->listWid[v]->setPalette(palette);
                this->listWid[v]->repaint();
            }
            else if (b.getBox(i,j).getDefValue() == 0){
                this->listWid[v]->setText("");
                this->listWid[v]->setReadOnly(false);
                this->listWid[v]->setAlignment(Qt::AlignHCenter);
                this->listWid[v]->setPalette(baseEmpty);
                this->listWid[v]->setEnabled(false);
                this->listWid[v]->repaint();
            }
            else if(b.getBox(i,j).getDefValue() != 0 && (this->listWid[v]->isReadOnly())){
                listWid[v]->setPalette(baseChoose);
                this->listWid[v]->setEnabled(true);
            }
            v++;
        }
    }
}

/*
    disable all the button that we can't use during the resolution 
    and launch the thread
*/
void FenPrincipale::resolveBoard(){
    btn_validate->setEnabled(false);
    btn_correct->setEnabled(false);
    btn_cancel->setEnabled(false);
    btn_openFile->setEnabled(false);
    boardLayout->setEnabled(false);
    actualScore.setUse(true);
    actualScore.setScore(100);
    actualScore.calculDuration();

    if (!th->isRunning()){
        th->start();
    }
}

void FenPrincipale::getPreviousBoard(){
    int index(0);
    for(int j(0); j<(int)this->listBoardResolve.size(); ++j){
        if(this->Grid == this->listBoardResolve[j]){
            index = j;
        }
    }
    this->Grid = this->listBoardResolve[index - 1];
    this->screenBoard(this->Grid);

    if(index-1 == 0){
        btn_backward->setEnabled(false);
    }
    else{
        btn_backward->setEnabled(true);
    }
    btn_forward->setEnabled(true);
}

void FenPrincipale::getNextBoard(){
    int index(0);
    for(int j(0); j<(int)this->listBoardResolve.size(); ++j){
        if(this->Grid == this->listBoardResolve[j]){
            index = j;
        }
    }
    this->Grid = this->listBoardResolve[index + 1];
    this->screenBoard(this->Grid);
    if(index+1 == (int)this->listBoardResolve.size()-1){
        btn_forward->setEnabled(false);
    }
    else{
        btn_forward->setEnabled(true);
    }
    btn_backward->setEnabled(true);
}

/*
    reset all the textLines with the value of the original board 
*/
void FenPrincipale::reset(){
    this->screenBoard(this->Grid);
}

/*
    Open a dialog who ask the name to create a user
*/
void FenPrincipale::userCreation(){
    QString name = ""; 
    do{
        name = QInputDialog::getText(this, "user name", "enter the user name");
        player.setName(name.toStdString());
        if(name != ""){
            player.getUser();
            cout << player.getId() << endl;
            actualScore.setUser(player.getId());
            player.getUserScore();
            cout << "Score du joueur : " << player.getScore()[0].getBoard() << " : " << player.getScore()[0].getScore() << endl;
        }
    }while(name == "");
}

/*
    run the thread that resolve the board 
    call the step function of board 
    emit two signals : updateBoard and thIsStopped
*/
void myThread::run(){
    Board tmp;
    int step(1);
    do
    {
        step++;
        tmp = this->thBoard;
        this->thBoard.step();   
        emit(updateBoard(this->thBoard));
        sleep(1);
    } while (this->thBoard != tmp);
    emit(thIsStopped());
    exec();
}

/*
    at the end of the resolveBoard thread make all the button enable again
*/
void FenPrincipale::thIsStopped(){
    this->Grid = this->listBoardResolve[this->listBoardResolve.size() - 1];
    this->listBoardResolve.pop_back();
    cout << this->listBoardResolve.size();
    btn_backward->setVisible(true);
    btn_forward->setVisible(true);
    btn_forward->setEnabled(false);
    btn_openFile->setEnabled(true);
    boardLayout->setEnabled(true);
    actualScore.setNbStep(10);
    actualScore.addThisScore();
    cout << actualScore.getBoard() << " : " << actualScore.getDate() << " : " << actualScore.getNbStep() << " : " << actualScore.getScore() << " : " << actualScore.getTime().toString().toStdString() << " : " << actualScore.getUserId() << endl;

    th->quit();
}
