#include "terrain.h"
#include "game.h"
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <cmath>

Terrain::Terrain()
{
    sonImageSol = QImage("data/terrain_sol.png");
    sonImageChemin = QImage("data/terrain_chemin.png");
    sonImageBaseAllie = QImage("data/base_allie.png");
    sonImageBaseEnnemi = QImage("data/base_ennemi.png");
    saGrilleUnite = new std::vector< std::vector<UniteStatique*> > (TAILLE_GRILLE, std::vector<UniteStatique*>(TAILLE_GRILLE, (UniteStatique*)NULL));
    sonVecUniteMobile = new std::vector< UniteMobile* >();
    saGrilleChemin = new std::vector< std::vector<bool> > (TAILLE_GRILLE, std::vector<bool>(TAILLE_GRILLE, false));
    sonChemin = new std::vector<QPoint>();

    charge(QString("data/1.lvl"));
}


Terrain::~Terrain()
{
    // FIXME tout plante pour une raison obscure.

    /*for (std::vector< std::vector<UniteStatique*> >::iterator it = saGrilleUnite->begin(); it != saGrilleUnite->end(); it++)
    {
        for (std::vector<UniteStatique*>::iterator jt = it->begin(); jt != it->end(); jt++)
        {
            if (*jt != NULL)
            {
                delete *jt;
            }
        }
    }

    delete saGrilleUnite;
    delete saGrilleChemin;*/
}


void Terrain::charge(QString unChemin)
{
    QFile file(unChemin);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream stream(&file);
    int x, y;

    for (;;)
    {
        stream >> x >> y;

        if (stream.atEnd())
        {
            break;
        }

        sonChemin->push_back(QPoint(x, y));
        (*saGrilleChemin)[y][x] = true;
    }

    file.close();
}


void Terrain::pose(int x, int y)
{
    if (!(0 <= x && x < TAILLE_GRILLE) ||
        !(0 <= y && y < TAILLE_GRILLE))
    {
        return;
    }

    (*saGrilleUnite)[y][x] = new UniteStatique(QPoint(x, y));
}


void Terrain::affiche(Curseur* curseur, QPainter* painter)
{
    /* On affiche le sol */

    for (int i=0; i<=HEIGHT/TAILLE_SOL; i++)
    {
        for (int j=0; j<=WIDTH/TAILLE_SOL; j++)
        {
            painter->drawImage(TAILLE_SOL*j, TAILLE_SOL*i, sonImageSol);
        }
    }

    /* On affiche les bases */

    painter->drawImage((WIDTH-32*TAILLE_GRILLE)/2-64, HEIGHT/2-96/2, sonImageBaseAllie);
    painter->drawImage((WIDTH+32*TAILLE_GRILLE)/2, HEIGHT/2-96/2, sonImageBaseEnnemi);

    /* On affiche le chemin */

    painter->save();
    painter->resetTransform();
    painter->translate((WIDTH-32*TAILLE_GRILLE)/2, 0.0);

    for (int i=0; i<TAILLE_GRILLE; i++)
    {
        for (int j=0; j<TAILLE_GRILLE; j++)
        {
            if ((*saGrilleChemin)[i][j])
            {
                painter->drawImage(TAILLE_CHEMIN*j, TAILLE_CHEMIN*i, sonImageChemin);
            }
        }
    }

    painter->restore();

    /* On affiche les unités statiques */

    painter->save();

    for (unsigned int i=0; i<TAILLE_GRILLE; i++)
    {
        for (unsigned int j=0; j<TAILLE_GRILLE; j++)
        {
            if ((*saGrilleUnite)[i][j] != NULL)
            {
                (*saGrilleUnite)[i][j]->affiche(painter);
            }
        }
    }

    painter->restore();

    /* On affiche les unités mobiles */

    painter->save();

    for (unsigned int i=0; i<sonVecUniteMobile->size(); i++)
    {
        (*sonVecUniteMobile)[i]->affiche(painter);
    }

    painter->restore();
}


void Terrain::logique(Curseur* curseur)
{
    int decalage = WIDTH/2-32*TAILLE_GRILLE/2;

    if (curseur->getClic())
    {
        sonVecUniteMobile->push_back(new UniteMobile(sonChemin));
    }

    for (unsigned int i=0; i<TAILLE_GRILLE; i++)
    {
        for (unsigned int j=0; j<TAILLE_GRILLE; j++)
        {
            if ((*saGrilleUnite)[i][j] == NULL)
            {
                /* Création lors d'un clic */

                if (curseur->getClic() &&
                    !(*saGrilleChemin)[i][j] &&
                    QRect(decalage+32*j, 32*i, 32, 32).contains(QPoint(curseur->getX(), curseur->getY())))
                {
                    this->pose(j, i);
                }
            }
            else
            {
                /* Logique de l'unité statique */

                (*saGrilleUnite)[i][j]->logique();
            }
        }
    }

    for (unsigned int i=0; i<sonVecUniteMobile->size(); i++)
    {
        (*sonVecUniteMobile)[i]->logique();
    }
}
