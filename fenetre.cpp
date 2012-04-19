#include "fenetre.h"
#include "ui_fenetre.h"

Fenetre::Fenetre(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Fenetre)
{
    ui->setupUi(this);

    sonJeu = new Jeu(this);
    this->setFixedSize(WIDTH, HEIGHT);
    this->setCentralWidget(sonJeu);
    this->setWindowTitle("TowerDefense");
}

Fenetre::~Fenetre()
{
    delete ui;
}
