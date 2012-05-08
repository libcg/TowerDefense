#include "fenetre.h"
#include "ui_fenetre.h"

Fenetre::Fenetre(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Fenetre)
{
    ui->setupUi(this);

    sonJeu = new Jeu();
    setFixedSize(WIDTH, HEIGHT+24);
    setCentralWidget(sonJeu);
    setWindowTitle("TowerDefense");
}


Fenetre::~Fenetre()
{
    delete ui;
}


void Fenetre::on_actionNouvellePartie_triggered()
{
    sonJeu->getSaPartie()->nouvellePartie();
}


void Fenetre::on_actionChargerPartie_triggered()
{
    sonJeu->getSaPartie()->chargerPartie();
}


void Fenetre::on_actionSauvegarderPartie_triggered()
{
    sonJeu->getSaPartie()->sauvegarderPartie();
}


void Fenetre::on_actionRecommencer_triggered()
{
    sonJeu->getSaPartie()->recommencerNiveau();
}
