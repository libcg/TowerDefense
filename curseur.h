#ifndef CURSEUR_H
#define CURSEUR_H

#include <QPoint>

class Curseur
{
private:
    QPoint saPosition;
    bool sonClic;

public:
    Curseur();
    void setPosition(QPoint unePosition);
    void setClic(bool unClic);
    int getX();
    int getY();
    bool getClic();
};

#endif // CURSEUR_H
