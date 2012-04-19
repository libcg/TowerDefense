#ifndef TERRAIN_H
#define TERRAIN_H

#include "unitestatique.h"
#include "unitemobile.h"
#include "curseur.h"
#include "partie.h"

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
    std::vector< std::vector<UniteStatique*> > *saGrilleUnite;
    std::list< UniteMobile* > *saListeUniteMobile;
    std::vector< std::vector<bool> > *saGrilleChemin;
    std::vector<QPoint>* sonChemin;
    Partie *saPartie;

    void supprimeUnitesMobiles();

public:
    explicit Terrain(Partie *unePartie, QObject *parent = 0);
    ~Terrain();
    void charge(QString unChemin);
    void pose(int unX, int unY);
    void affiche(Curseur *unCurseur, QPainter *unPainter);
    void logique(Curseur *unCurseur);
};

#endif // TERRAIN_H
