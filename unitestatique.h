#ifndef UNITESTATIQUE_H
#define UNITESTATIQUE_H

#include <QImage>

#define TAILLE_UNITESTATIQUE 32

class UniteStatique
{
private:
    //int saPuissance;
    //int sonType;
    //int sonCout;
    QPoint saPosition;
    double sonAngle;
    QImage sonImageBase;
    QImage sonImageCanon;
    QImage sonImageCanonFeu;

public:
    UniteStatique(QPoint unePosition);
    void affiche(QPainter* painter);
    void logique();
};

#endif // UNITESTATIQUE_H
