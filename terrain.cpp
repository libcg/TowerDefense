#include "terrain.h"
#include "jeu.h"
#include <QPainter>
#include <QFile>
#include <cmath>
#include <string>

Terrain::Terrain(Partie *unePartie, std::vector<QPoint>* unChemin, QObject *parent) :
    QObject(parent), saPartie(unePartie)
{
    sonImageSol = QImage("data/terrain_sol.png");
    sonImageChemin = QImage("data/terrain_chemin.png");
    sonImageBaseAllie = QImage("data/base_allie.png");
    sonImageBaseEnnemi = QImage("data/base_ennemi.png");
    saGrilleTourelles = new std::vector< std::vector<Tourelle*> >(TAILLE_GRILLE, std::vector<Tourelle*>(TAILLE_GRILLE, (Tourelle*)NULL));
    saListeEnnemis = new std::list<Ennemi*>();

    saGrilleChemin = new std::vector< std::vector<bool> >(TAILLE_GRILLE, std::vector<bool>(TAILLE_GRILLE, false));
    for (unsigned int i=0; i<unChemin->size(); i++)
        (*saGrilleChemin)[unChemin->at(i).y()][unChemin->at(i).x()] = true;
}


Terrain::~Terrain()
{
    for (std::vector< std::vector<Tourelle*> >::iterator it = saGrilleTourelles->begin(); it != saGrilleTourelles->end(); it++)
    {
        for (std::vector<Tourelle*>::iterator jt = it->begin(); jt != it->end(); jt++)
        {
            delete *jt;
        }
    }

    delete saGrilleTourelles;
    delete saListeEnnemis;
    delete saGrilleChemin;
}


void Terrain::charge(QTextStream *unStream)
{
    int i, j;

    unStream->readLine();
    {
        for (;;)
        {
            if (unStream->read(2) == ";\n") break;
            else unStream->seek(unStream->pos() - 2);

            *unStream >> i >> j;
            (*saGrilleTourelles)[i][j] = new Tourelle(QPoint(j, i), saListeEnnemis);
            (*saGrilleTourelles)[i][j]->charge(unStream);

            unStream->read(1); // '\n'
        }
    }
    unStream->read(1);

    unStream->readLine();
    {
        for (;;)
        {
            if (unStream->read(2) == ";\n") break;
            else unStream->seek(unStream->pos() - 2);

            *unStream >> i;
            saListeEnnemis->push_back(new Ennemi(saPartie->getSonNiveau()->getSonChemin(), i));
            saListeEnnemis->back()->charge(unStream);

            unStream->read(1); // '\n'
        }
    }
    unStream->read(1);
}


void Terrain::sauvegarde(QTextStream *unStream)
{
    *unStream << "terrain/tourelles" << endl;
    {
        for (unsigned int i=0; i<TAILLE_GRILLE; i++)
            for (unsigned int j=0; j<TAILLE_GRILLE; j++)
                if ((*saGrilleTourelles)[i][j] != NULL)
                {
                    *unStream << i << ' ' << j << endl;
                    (*saGrilleTourelles)[i][j]->sauvegarde(unStream);
                }
    }
    *unStream << ';' << endl;

    *unStream << "terrain/ennemis" << endl;
    {
        for (std::list<Ennemi*>::iterator it=saListeEnnemis->begin(); it != saListeEnnemis->end(); it++)
        {
            *unStream << (*it)->getSonType() << endl;
            (*it)->sauvegarde(unStream);
        }
    }
    *unStream << ';' << endl;
}


void Terrain::nettoieListeEnnemis()
{
    std::list<Ennemi*>::iterator it;
    bool laSuppression;

    do
    {
        laSuppression = false;

        for (it = saListeEnnemis->begin(); it != saListeEnnemis->end(); it++)
        {
            if ((*it)->estASupprimer())
            {
                if ((*it)->estArrivee())
                    saPartie->infligerDegat(10);
                else
                    saPartie->ajoutCredits(*it);

                laSuppression = true;
                delete (*it);
                saListeEnnemis->erase(it);
                break;
            }
        }
    } while (laSuppression);
}


bool Terrain::ajouteTourelle(Curseur *unCurseur)
{
    int decalage = WIDTH/2 - 32*TAILLE_GRILLE/2;

    for (unsigned int i=0; i<TAILLE_GRILLE; i++)
        for (unsigned int j=0; j<TAILLE_GRILLE; j++)
            if ((*saGrilleTourelles)[i][j] == NULL &&
                (*saGrilleChemin)[i][j] == false &&
                QRect(decalage+32*j, 32*i, 32, 32).contains(QPoint(unCurseur->getX(), unCurseur->getY())))
            {
                (*saGrilleTourelles)[i][j] = new Tourelle(QPoint(j, i), saListeEnnemis);
                return true;
            }

    return false;
}


void Terrain::affiche(Curseur* unCurseur, QPainter* unPainter)
{
    /* On affiche le sol */

    for (int i=0; i<=HEIGHT/TAILLE_SOL; i++)
        for (int j=0; j<=WIDTH/TAILLE_SOL; j++)
            unPainter->drawImage(TAILLE_SOL*j, TAILLE_SOL*i, sonImageSol);

    /* On affiche les bases */

    unPainter->drawImage((WIDTH-32*TAILLE_GRILLE)/2-64, HEIGHT/2-96/2, sonImageBaseAllie);
    unPainter->drawImage((WIDTH+32*TAILLE_GRILLE)/2, HEIGHT/2-96/2, sonImageBaseEnnemi);

    /* On affiche le chemin */

    unPainter->save();
    unPainter->resetTransform();
    unPainter->translate((WIDTH-32*TAILLE_GRILLE)/2, 0.0);

    for (int i=0; i<TAILLE_GRILLE; i++)
        for (int j=0; j<TAILLE_GRILLE; j++)
            if ((*saGrilleChemin)[i][j])
            {
                unPainter->drawImage(TAILLE_CHEMIN*j, TAILLE_CHEMIN*i, sonImageChemin);
            }

    unPainter->restore();

    /* On affiche les tourelles */

    unPainter->save();

    for (unsigned int i=0; i<TAILLE_GRILLE; i++)
        for (unsigned int j=0; j<TAILLE_GRILLE; j++)
            if ((*saGrilleTourelles)[i][j] != NULL)
            {
                (*saGrilleTourelles)[i][j]->affiche(unPainter);
            }

    unPainter->restore();

    /* On affiche les ennemis */

    unPainter->save();

    std::list<Ennemi*>::iterator it;
    for (it = saListeEnnemis->begin(); it != saListeEnnemis->end(); it++)
    {
        (*it)->affiche(unPainter);
    }

    unPainter->restore();
}


void Terrain::logique(Curseur* unCurseur)
{
    for (unsigned int i=0; i<TAILLE_GRILLE; i++)
        for (unsigned int j=0; j<TAILLE_GRILLE; j++)
            if ((*saGrilleTourelles)[i][j] != NULL)
            {
                (*saGrilleTourelles)[i][j]->logique();
            }

    nettoieListeEnnemis();

    for (std::list<Ennemi*>::iterator it = saListeEnnemis->begin(); it != saListeEnnemis->end(); it++)
        (*it)->logique();
}


std::list<Ennemi*>* Terrain::getSaListeEnnemis()
{
    return saListeEnnemis;
}


void Terrain::ajouteEnnemi(Ennemi *unEnnemi)
{
    saListeEnnemis->push_back(unEnnemi);
}
