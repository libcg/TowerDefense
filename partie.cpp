#include "partie.h"

Partie::Partie(QObject *parent) :
    QObject(parent), saVie(100)
{
}

void Partie::infligerDegat(int unDegat)
{
    saVie -= unDegat;

    if (saVie <= 0)
    {
        saVie = 0;
        sonEchec = true;
    }
}

void Partie::afficheBarreVie(QPainter *unPainter)
{
    unPainter->save();

    unPainter->translate(20, 20);
    unPainter->setPen(Qt::black);
    unPainter->setBrush(Qt::green);
    unPainter->drawRect(QRect(0, 0, 22, 102));
    unPainter->setPen(Qt::green);
    unPainter->setBrush(Qt::red);
    unPainter->drawRect(QRect(1, 1, 20, 100-saVie));

    unPainter->restore();
}

void Partie::affiche(QPainter *unPainter)
{
    afficheBarreVie(unPainter);

    if (sonEchec)
    {
        unPainter->save();

        unPainter->setPen(Qt::transparent);
        unPainter->setBrush(QColor(0, 0, 0, 50));
        unPainter->drawRect(QRect(0, 0, WIDTH, HEIGHT));

        unPainter->setPen(Qt::white);
        unPainter->setFont(QFont("Arial", 80));
        unPainter->drawText(0, 0, WIDTH, HEIGHT, Qt::AlignCenter, "Echec");

        unPainter->restore();
    }
}

bool Partie::getSonEchec()
{
    return sonEchec;
}
