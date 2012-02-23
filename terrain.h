#ifndef TERRAIN_H
#define TERRAIN_H

#include "unitestatique.h"
#include "curseur.h"

#include <QImage>
#include <vector>

#define TAILLE_GRILLE 17
#define TAILLE_SOL 256
#define TAILLE_CHEMIN 32
#define HAUTEUR_BASE 96
#define LARGEUR_BASE 64

class Terrain
{
private:
    QImage sonImageSol;
    QImage sonImageChemin;
    QImage sonImageBaseAllie;
    QImage sonImageBaseEnnemi;
    std::vector< std::vector<UniteStatique*> >* saGrilleUnite;
    std::vector< std::vector<bool> >* saGrilleChemin;
public:
    Terrain();
    ~Terrain();
    void charge(QString unChemin);
    void pose(int x, int y);
    void affiche(Curseur* curseur, QPainter* painter);
    void logique(Curseur* curseur);
};

#endif // TERRAIN_H
