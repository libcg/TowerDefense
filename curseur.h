#ifndef CURSEUR_H
#define CURSEUR_H

#include <QPoint>

class Curseur
{
private:
    QPoint saPosition;
    Qt::MouseButton sonBouton;
    Qt::MouseButton sonDernierBouton;

public:
    Curseur();
    void setPosition(QPoint unePosition);
    void setBouton(Qt::MouseButton unBouton);
    void setDernierBouton(Qt::MouseButton unDernierBouton);
    int getX();
    int getY();
    Qt::MouseButton getBouton();
    Qt::MouseButton getDernierBouton();
};

#endif // CURSEUR_H
