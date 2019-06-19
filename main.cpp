#include<QApplication>
#include<QtWidgets>

#include "fenprincipale.h"
#include "Box.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    FenPrincipale fenetre;
    fenetre.show();
    fenetre.setWindowTitle("Sudoku by SCHUTZ Lucas");
    return app.exec();
}
