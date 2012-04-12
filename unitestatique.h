#ifndef UNITESTATIQUE_H
#define UNITESTATIQUE_H

#include <unitemobile.h>
#include <QImage>
#include <QTimer>
#include <QObject>

#define TAILLE_UNITESTATIQUE 32
#define ROTATION_UNITESTATIQUE 1.7
#define DUREE_TIR 7

class UniteStatique : public QObject
{
    Q_OBJECT

private:
    QPoint saPosition;
    double sonAngle;
    const double saPortee;
    unsigned sonTir;
    QImage sonImageBase;
    QImage sonImageCanon;
    QImage sonImageCanonFeu;
    std::list<UniteMobile*> *saListeUniteMobile;
    UniteMobile *sonUniteCible;
    QTimer *sonTimerTir;

    UniteMobile* rechercheUnite();

private slots:
    void tir();

public:
    UniteStatique(QPoint unePosition, std::list< UniteMobile* > *uneListeUniteMobile, QObject *parent = 0);
    void affiche(QPainter* unPainter);
    void logique();
};

#endif // UNITESTATIQUE_H
