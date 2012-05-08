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

    saMessageBox = new QMessageBox(
                QMessageBox::NoIcon, "Comment jouer?",
                "Clic gauche pour placer une tourelle,\n"
                "Clic droit pour changer de type de tourelle.\n"
                "\n\n"
                "Vos credits sont limites, et augmenteront lorsque les ennemis sont detruits.\n"
                "\n\n"
                "Bonne chance !",
                QMessageBox::NoButton, this);
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


void Fenetre::on_actionCommentJouer_triggered()
{
    saMessageBox->show();
}
