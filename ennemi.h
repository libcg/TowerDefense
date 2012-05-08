#ifndef ENNEMI_H
#define ENNEMI_H

#include <vector>
#include <QPoint>
#include <QImage>
#include <QPainter>
#include <QTextStream>

#define TAILLE_ENNEMI 32
#define PAS 30

class Ennemi : public QObject
{
    Q_OBJECT

private:
    std::vector<QPoint> *sonChemin;
    QImage sonImage;
    QImage sonImageDegat;

    QPointF saPosition;
    QPointF sonIncrement;
    unsigned int sonPas;
    unsigned int sonEtapeChemin;
    int sonDegat;
    bool aSupprimer;
    int sonType;
    int sesPV;
    int sonPrix;

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
};

#endif // UNITEMOBILE_H
