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

/*!
  * \brief Cette classe représente un terrain.
  */
class Terrain : public QObject
{
    Q_OBJECT

private:
    QImage sonImageSol;                                         /*!< \brief Image du sol */
    QImage sonImageChemin;                                      /*!< \brief Image d'une case du chemin */
    QImage sonImageBaseAllie;                                   /*!< \brief Image de la base alliée */
    QImage sonImageBaseEnnemi;                                  /*!< \brief Image de la base ennemie */
    std::vector< std::vector<bool> > *saGrilleChemin;           /*!< \brief Pointeur vers la grille du chemin */
    Partie *saPartie;                                           /*!< \brief Pointeur vers une partie */

    std::vector< std::vector<Tourelle*> > *saGrilleTourelles;   /*!< \brief Pointeur vers la grille de tourelles */
    std::list<Ennemi*> *saListeEnnemis;                         /*!< \brief Pointeur vers la liste d'ennemis */

    /*!
      * \brief Nettoie la liste des ennemis, en supprimant ceux qui sont marqués à supprimer
      */
    void nettoieListeEnnemis();

public:
    /*!
      * \brief Constructeur de la classe Terrain
      *
      * @param unePartie Pointeur vers une partie
      * @param unChemin Pointeur vers un chemin
      * @param parent Pointeur optionel vers un QObject parent
      */
    explicit Terrain(Partie *unePartie, std::vector<QPoint>* unChemin, QObject *parent = 0);

    /*!
      * \brief Destructeur de la classe Terrain
      */
    ~Terrain();

    /*!
      * \brief Charge les propriétés d'un terrain depuis un flot de texte
      *
      * @param unStream Pointeur vers un flot de texte
      */
    void charge(QTextStream *unStream);

    /*!
      * \brief Sauvegarde les propriétés d'un terrain vers un flot de texte
      *
      * @param unStream Pointeur vers un flot de texte
      */
    void sauvegarde(QTextStream *unStream);

    /*!
      * \brief Affiche un terrain
      *
      * @param unPainter Pointeur vers un painter
      */
    void affiche(QPainter *unPainter);

    /*!
      * \brief Affiche une tourelle en survol
      *
      * @param unCurseur Pointeur vers un curseur virtuel
      * @param unPainter Pointeur vers un painter
      * @param uneImageBaseTourelle Pointeur vers une image de base de tourelle
      * @param uneImageTypeTourelle Pointeur vers une image de type de tourelle
      */
    void afficheSurvol(Curseur *unCurseur, QPainter *unPainter, QImage *uneImageBaseTourelle, QImage *uneImageTypeTourelle);

    /*!
      * \brief Logique d'un terrain
      */
    void logique();

    /*!
      * \brief Ajoute un ennemi au terrain
      *
      * @param unEnnemi Pointeur vers un ennemi
      */
    void ajouteEnnemi(Ennemi *unEnnemi);

    /*!
      * \brief Ajoute une tourelle au terrain
      *
      * @param unCurseur Pointeur vers un curseur virtuel
      * @param unType Type de la tourelle
      */
    bool ajouteTourelle(Curseur *unCurseur, int unType);

    /*!
      * \brief Retourne la liste des ennemis
      *
      * @return Pointeur vers une liste d'ennemis
      */
    std::list<Ennemi*>* getSaListeEnnemis();
};

#endif // TERRAIN_H
