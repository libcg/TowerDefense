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
    Jeu* sonJeu;

public:
    explicit Fenetre(QWidget *parent = 0);
    ~Fenetre();
    
private:
    Ui::Fenetre *ui;
};

#endif // FENETRE_H
