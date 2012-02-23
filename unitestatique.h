#ifndef UNITESTATIQUE_H
#define UNITESTATIQUE_H

#include <QImage>

#define TAILLE_UNITESTATIQUE 32

class UniteStatique
{
private:
    int saPuissance;
    int sonType; // FIXME type
    int sonCout;
    int sonX;
    int sonY;
    double sonAngle;
    QImage sonImageBase;
    QImage sonImageCanon;
    QImage sonImageCanonFeu;
public:
    UniteStatique(int x, int y);
    void affiche(QPainter* painter);
    void logique();
};

#endif // UNITESTATIQUE_H
