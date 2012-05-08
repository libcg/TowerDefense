#ifndef ENNEMI_H
#define ENNEMI_H

#include <vector>
#include <QPoint>
#include <QImage>
#include <QPainter>
#include <QTextStream>

#define TAILLE_ENNEMI 32

class Ennemi : public QObject
{
    Q_OBJECT

private:
    std::vector<QPoint> *sonChemin;
    QImage sonImage;
    QImage sonImageDegat;
    unsigned int sonNombrePas;
    unsigned int sonType;
    unsigned int sonPrix;

    QPointF saPosition;
    QPointF sonIncrement;
    unsigned int sonPas;
    unsigned int sonEtapeChemin;
    int sesPV;
    int sonDegat;
    bool aSupprimer;

    void type();
    void calcul(QPointF unePositionArrivee);
    void deplace();

public:
    explicit Ennemi(std::vector<QPoint> *unChemin, int unType, QObject *parent = 0);
    void charge(QTextStream *unStream);
    void sauvegarde(QTextStream *unStream);
    void logique();
    void affiche(QPainter *unPainter);
    void infligerDegat(int unDegat);
    QPointF getSaPosition();
    bool estArrivee();
    bool estASupprimer();
    int getSonPrix();
    int getSonType();
};

#endif // UNITEMOBILE_H
