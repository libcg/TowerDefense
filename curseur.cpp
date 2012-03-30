#include "curseur.h"
#include "jeu.h"

Curseur::Curseur()
{
    saPosition = QPoint(WIDTH/2, HEIGHT/2);
    sonClic = false;
}


void Curseur::setPosition(QPoint unePosition)
{
    saPosition = unePosition;
}


void Curseur::setClic(bool unClic)
{
    sonClic = unClic;
}


int Curseur::getX()
{
    return saPosition.x();
}


int Curseur::getY()
{
    return saPosition.y();
}


bool Curseur::getClic()
{
    return sonClic;
}
