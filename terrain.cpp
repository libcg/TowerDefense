#include "terrain.h"
#include "jeu.h"
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <cmath>
#include <string>

Terrain::Terrain(Partie *unePartie, QObject *parent) :
    QObject(parent), saPartie(unePartie)
{
    sonImageSol = QImage("data/terrain_sol.png");
    sonImageChemin = QImage("data/terrain_chemin.png");
    sonImageBaseAllie = QImage("data/base_allie.png");
    sonImageBaseEnnemi = QImage("data/base_ennemi.png");
    saGrilleUnite = new std::vector< std::vector<UniteStatique*> > (TAILLE_GRILLE, std::vector<UniteStatique*>(TAILLE_GRILLE, (UniteStatique*)NULL));
    saListeUniteMobile = new std::list< UniteMobile* >();
    saGrilleChemin = new std::vector< std::vector<bool> > (TAILLE_GRILLE, std::vector<bool>(TAILLE_GRILLE, false));
    sonChemin = new std::vector<QPoint>();

    charge(QString("data/1.lvl"));
}


Terrain::~Terrain()
{
    for (std::vector< std::vector<UniteStatique*> >::iterator it = saGrilleUnite->begin(); it != saGrilleUnite->end(); it++)
    {
        for (std::vector<UniteStatique*>::iterator jt = it->begin(); jt != it->end(); jt++)
        {
            delete *jt;
        }
    }

    delete saGrilleUnite;
    delete saListeUniteMobile;
    delete saGrilleChemin;
    delete sonChemin;
}


void Terrain::supprimeUnitesMobiles()
{
    std::list<UniteMobile*>::iterator it;
    bool laSuppression;

    do
    {
        laSuppression = false;

        for (it = saListeUniteMobile->begin(); it != saListeUniteMobile->end(); it++)
        {
            if ((*it)->estASupprimer())
            {
                if ((*it)->estArrivee()) saPartie->infligerDegat(10);

                laSuppression = true;
                delete (*it);
                saListeUniteMobile->erase(it);
                break;
            }
        }
    } while (laSuppression);
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

    (*saGrilleUnite)[y][x] = new UniteStatique(QPoint(x, y), saListeUniteMobile);
}


void Terrain::affiche(Curseur* unCurseur, QPainter* unPainter)
{
    /* On affiche le sol */

    for (int i=0; i<=HEIGHT/TAILLE_SOL; i++)
    {
        for (int j=0; j<=WIDTH/TAILLE_SOL; j++)
        {
            unPainter->drawImage(TAILLE_SOL*j, TAILLE_SOL*i, sonImageSol);
        }
    }

    /* On affiche les bases */

    unPainter->drawImage((WIDTH-32*TAILLE_GRILLE)/2-64, HEIGHT/2-96/2, sonImageBaseAllie);
    unPainter->drawImage((WIDTH+32*TAILLE_GRILLE)/2, HEIGHT/2-96/2, sonImageBaseEnnemi);

    /* On affiche le chemin */

    unPainter->save();
    unPainter->resetTransform();
    unPainter->translate((WIDTH-32*TAILLE_GRILLE)/2, 0.0);

    for (int i=0; i<TAILLE_GRILLE; i++)
    {
        for (int j=0; j<TAILLE_GRILLE; j++)
        {
            if ((*saGrilleChemin)[i][j])
            {
                unPainter->drawImage(TAILLE_CHEMIN*j, TAILLE_CHEMIN*i, sonImageChemin);
            }
        }
    }

    unPainter->restore();

    /* On affiche les unités statiques */

    unPainter->save();

    for (unsigned int i=0; i<TAILLE_GRILLE; i++)
    {
        for (unsigned int j=0; j<TAILLE_GRILLE; j++)
        {
            if ((*saGrilleUnite)[i][j] != NULL)
            {
                (*saGrilleUnite)[i][j]->affiche(unPainter);
            }
        }
    }

    unPainter->restore();

    /* On affiche les unités mobiles */

    unPainter->save();

    std::list<UniteMobile*>::iterator it;
    for (it = saListeUniteMobile->begin(); it != saListeUniteMobile->end(); it++)
    {
        (*it)->affiche(unPainter);
    }

    unPainter->restore();
}

void Terrain::logique(Curseur* unCurseur)
{
    int decalage = WIDTH/2-32*TAILLE_GRILLE/2;

    if (unCurseur->getClic())
    {
        saListeUniteMobile->push_back(new UniteMobile(sonChemin));
    }

    for (unsigned int i=0; i<TAILLE_GRILLE; i++)
    {
        for (unsigned int j=0; j<TAILLE_GRILLE; j++)
        {
            if ((*saGrilleUnite)[i][j] == NULL)
            {
                /* Création lors d'un clic */

                if (unCurseur->getClic() &&
                    !(*saGrilleChemin)[i][j] &&
                    QRect(decalage+32*j, 32*i, 32, 32).contains(QPoint(unCurseur->getX(), unCurseur->getY())))
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

    supprimeUnitesMobiles();

    for (std::list<UniteMobile*>::iterator it = saListeUniteMobile->begin(); it != saListeUniteMobile->end(); it++)
    {
        (*it)->logique();
    }
}
