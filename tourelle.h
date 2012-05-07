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

    QPoint saPosition;
    double sonAngle;
    double saPortee;
    unsigned int sonTir;

    Ennemi* rechercheEnnemi();

private slots:
    void tir();

public:
    Tourelle(QPoint unePosition, std::list<Ennemi*> *uneListeEnnemis, QObject *parent = 0);
    ~Tourelle();
    void charge(QTextStream *unStream);
    void sauvegarde(QTextStream *unStream);
    void affiche(QPainter *unPainter);
    void logique();

    static int prix();
};

#endif // TOURELLE_H
