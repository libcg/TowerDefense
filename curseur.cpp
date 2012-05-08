#include "curseur.h"
#include "jeu.h"

Curseur::Curseur()
{
    saPosition = QPoint(WIDTH/2, HEIGHT/2);
    sonBouton = Qt::NoButton;
    sonDernierBouton = Qt::NoButton;
}


void Curseur::setPosition(QPoint unePosition)
{
    saPosition = unePosition;
}


void Curseur::setBouton(Qt::MouseButton unBouton)
{
    sonBouton = unBouton;
}


void Curseur::setDernierBouton(Qt::MouseButton unBouton)
{
    sonDernierBouton = unBouton;
}


int Curseur::getX()
{
    return saPosition.x();
}


int Curseur::getY()
{
    return saPosition.y();
}


Qt::MouseButton Curseur::getBouton()
{
    return sonBouton;
}


Qt::MouseButton Curseur::getDernierBouton()
{
    return sonDernierBouton;
}
