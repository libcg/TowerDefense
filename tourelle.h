#ifndef TOURELLE_H
#define TOURELLE_H

#include <ennemi.h>
#include <QImage>
#include <QTimer>
#include <QObject>
#include <QTextStream>

#define TAILLE_TOURELLE 32
#define ROTATION_TOURELLE 1.7
#define DUREE_TIR 7

class Tourelle : public QObject
{
    Q_OBJECT

private:
    std::list<Ennemi*> *saListeEnnemis;
    QImage sonImageBase;
    QImage sonImageCanon;
    QImage sonImageCanonFeu;
    Ennemi *sonEnnemiCible;
    QTimer *sonTimerTir;
    int sonType;
    double saPortee;
    double sonTPS; // tir par seconde
    int sesDegats;

    QPoint saPosition;
    double sonAngle;
    unsigned int sonTir;

    Ennemi* rechercheEnnemi();

private slots:
    void type();
    void tir();

public:
    Tourelle(QPoint unePosition, std::list<Ennemi*> *uneListeEnnemis, int unType, QObject *parent = 0);
    ~Tourelle();
    void charge(QTextStream *unStream);
    void sauvegarde(QTextStream *unStream);
    void affiche(QPainter *unPainter);
    void logique();
    int getSonType();

    static int prix(int unType);
};

#endif // TOURELLE_H
