#ifndef FENETRE_H
#define FENETRE_H

#include "jeu.h"
#include <QMainWindow>

namespace Ui {
class Fenetre;
}

class Fenetre : public QMainWindow
{
    Q_OBJECT
    
private:
    Ui::Fenetre *ui;
    Jeu* sonJeu;

private slots:
    void on_actionNouvellePartie_triggered();
    void on_actionChargerPartie_triggered();
    void on_actionSauvegarderPartie_triggered();
    void on_actionRecommencer_triggered();

public:
    explicit Fenetre(QWidget *parent = 0);
    ~Fenetre();
};

#endif // FENETRE_H
