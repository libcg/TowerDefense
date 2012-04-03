#ifndef UNITESTATIQUE_H
#define UNITESTATIQUE_H

#include <unitemobile.h>
#include <QImage>

#define TAILLE_UNITESTATIQUE 32
#define ROTATION_UNITESTATIQUE 1.7

class UniteStatique
{
private:
    QPoint saPosition;
    double sonAngle;
    const double saPortee;
    QImage sonImageBase;
    QImage sonImageCanon;
    QImage sonImageCanonFeu;
    std::vector< UniteMobile* >* sonVecUniteMobile;
    UniteMobile *sonUniteCible;

    UniteMobile* rechercheUnite();

public:
    UniteStatique(QPoint unePosition, std::vector< UniteMobile* >* unVecUniteMobile);
    void affiche(QPainter* unPainter);
    void logique();
};

#endif // UNITESTATIQUE_H
