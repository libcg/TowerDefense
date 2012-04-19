#ifndef PARTIE_H
#define PARTIE_H

#include "jeu.h"
#include <QObject>
#include <QPainter>

class Partie : public QObject
{
    Q_OBJECT

private:
    int saVie;
    bool sonEchec;

    void afficheBarreVie(QPainter *unPainter);

public:
    explicit Partie(QObject *parent = 0);
    void infligerDegat(int unDegat);
    void affiche(QPainter *unPainter);
    bool getSonEchec();
};

#endif // PARTIE_H
