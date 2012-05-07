#ifndef TERRAIN_H
#define TERRAIN_H

#include "tourelle.h"
#include "ennemi.h"
#include "curseur.h"
#include "partie.h"
#include <QTextStream>
#include <QObject>
#include <QImage>
#include <list>
#include <vector>

#define TAILLE_GRILLE 17
#define TAILLE_SOL 256
#define TAILLE_CHEMIN 32
#define HAUTEUR_BASE 96
#define LARGEUR_BASE 64

class Partie;

class Terrain : public QObject
{
    Q_OBJECT

private:
    QImage sonImageSol;
    QImage sonImageChemin;
    QImage sonImageBaseAllie;
    QImage sonImageBaseEnnemi;
    std::vector< std::vector<bool> > *saGrilleChemin;
    Partie *saPartie;

    std::vector< std::vector<Tourelle*> > *saGrilleTourelles;
    std::list<Ennemi*> *saListeEnnemis;

    void nettoieListeEnnemis();

public:
    explicit Terrain(Partie *unePartie, std::vector<QPoint>* unChemin, QObject *parent = 0);
    ~Terrain();
    void charge(QTextStream *unStream);
    void sauvegarde(QTextStream *unStream);
    void affiche(Curseur *unCurseur, QPainter *unPainter);
    void logique(Curseur *unCurseur);
    void ajouteEnnemi(Ennemi *unEnnemi);
    bool ajouteTourelle(Curseur *unCurseur);
    std::list<Ennemi*>* getSaListeEnnemis();
};

#endif // TERRAIN_H
