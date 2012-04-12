#ifndef UNITEMOBILE_H
#define UNITEMOBILE_H

#include <vector>
#include <QPoint>
#include <QImage>
#include <QPainter>

#define TAILLE_UNITEMOBILE 32
#define PAS 30

class UniteMobile
{
private:
    QImage sonImage;
    QImage sonImageDegat;
    QPointF saPosition;
    QPointF sonIncrement;
    std::vector<QPoint>* sonChemin;
    unsigned int sonPas;
    unsigned int sonEtapeChemin;
    int sesPV;
    int sonDegat;
    bool aSupprimer;

    void calcul(QPointF unePositionArrivee);
    void deplace();

public:
    UniteMobile(std::vector<QPoint>* unChemin);
    void logique();
    void affiche(QPainter* unPainter);
    void infligerDegat(int unDegat);
    QPointF getSaPosition();
    bool estASupprimer();
};

#endif // UNITEMOBILE_H
