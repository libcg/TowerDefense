#ifndef PARTIE_H
#define PARTIE_H

#include "jeu.h"
#include "terrain.h"
#include "niveau.h"
#include <QObject>
#include <QTimer>
#include <QPainter>
#include <QTextStream>

#define INTERVALLE_ENNEMI 2

typedef enum
{
    JOUE,
    DEFAITE,
    VICTOIRE,
    FIN
} EtatPartie;

class Niveau;
class Terrain;

class Partie : public QObject
{
    Q_OBJECT

private:
    Terrain *sonTerrain;
    Niveau *sonNiveau;
    QTimer *sonTimerDecompte;
    QImage sonImageBaseTourelle;
    QImage sonImageTypeTourelle;

    int sonNumeroNiveau;
    int saVie;
    int sesCredits;
    int sonEtat;
    int saVague;
    int sonDecompteTemps;
    int sonDecompteEnnemi;
    int sonTypeTourelle;

    void afficheBarreVie(QPainter *unPainter);
    void afficheInfoVague(QPainter *unPainter);
    void afficheEtat(QPainter *unPainter, QString unTitre);
    void afficheCredits(QPainter *unPainter);
    bool fin();
    void chargerNiveau();
    void niveauSuivant();
    void chargeImageTypeTourelle();

private slots:
    void decompte();

public:
    explicit Partie(QObject *parent = 0);
    void infligerDegat(int unDegat);
    void ajoutCredits(Ennemi* unEnnemi);
    void nouvellePartie();
    void chargerPartie();
    void sauvegarderPartie();
    void recommencerNiveau();
    void affiche(Curseur *unCurseur, QPainter *unPainter);
    void logique(Curseur *unCurseur);
    Niveau* getSonNiveau();
};

#endif // PARTIE_H
