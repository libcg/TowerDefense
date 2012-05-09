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

/*!
  * \brief Cette classe représente une partie.
  */
class Partie : public QObject
{
    Q_OBJECT

private:
    Terrain *sonTerrain;                /*!< \brief Pointeur vers un terrain */
    Niveau *sonNiveau;                  /*!< \brief Pointeur vers un niveau */
    QTimer *sonTimerDecompte;           /*!< \brief Pointeur vers un timer de décompte */
    QImage sonImageBaseTourelle;        /*!< \brief Image de la base d'une tourelle */
    QImage sonImageTypeTourelle;        /*!< \brief Image du type d'une tourelle */

    int sonNumeroNiveau;                /*!< \brief Identifiant d'un niveau en cours */
    int saVie;                          /*!< \brief Points de vie */
    int sesCredits;                     /*!< \brief Montant des crédits */
    int sonEtat;                        /*!< \brief Etat de la partie */
    int saVague;                        /*!< \brief Identifiant d'une vague d'ennemi en cours */
    int sonDecompteTemps;               /*!< \brief Décompte de temps avant la vague */
    int sonDecompteEnnemi;              /*!< \brief Décompte d'ennemis avant la fin de la vague */
    int sonTypeTourelle;                /*!< \brief Type de tourelle choisi */

    /*!
      * \brief Affiche la barre de vie
      *
      * @param unPainter Pointeur vers un painter
      */
    void afficheBarreVie(QPainter *unPainter);

    /*!
      * \brief Affiche les informations d'une vague en cours
      *
      * @param unPainter Pointeur vers un painter
      */
    void afficheInfoVague(QPainter *unPainter);

    /*!
      * \brief Affiche l'état de la partie
      *
      * @param unPainter Pointeur vers un painter
      * @param unTitre Un titre
      * @param unSousTitre Un sous-titre
      */
    void afficheEtat(QPainter *unPainter, QString unTitre, QString unSousTitre);

    /*!
      * \brief Affiche les crédits
      *
      * @param unPainter Pointeur vers un painter
      */
    void afficheCredits(QPainter *unPainter);

    /*!
      * \brief Détermine si un niveau suivant est existant
      *
      * @return Booléen
      */
    bool fin();

    /*!
      * \brief Charge le niveau en fonction de sonNumeroNiveau
      */
    void chargerNiveau();

    /*!
      * \brief Charge le niveau suivant en incrémentant sonNumeroNiveau
      */
    void niveauSuivant();

    /*!
      * \brief Charge l'image de prévision de tourelle en fonction de sonTypeTourelle
      */
    void chargeImageTypeTourelle();

private slots:
    /*!
      * \brief Évènement de décompte activé par le timer, agit sur les vagues et sur l'état de la partie
      */
    void decompte();

public:
    /*!
      * \brief Constructeur de la classe Partie
      *
      * @param parent Pointeur optionel vers un QObject parent
      */
    explicit Partie(QObject *parent = 0);

    /*!
      * \brief Inflige un dégât à la base
      *
      * @param unDegat Points de vie à enlever
      */
    void infligerDegat(int unDegat);

    /*!
      * \brief Ajoute des crédits en fonction d'un ennemi détruit
      *
      * @param unEnnemi Ennemi détruit
      */
    void ajoutCredits(Ennemi* unEnnemi);

    /*!
      * \brief Commencer une nouvelle partie
      */
    void nouvellePartie();

    /*!
      * \brief Charger une partie depuis un fichier texte
      */
    void chargerPartie();

    /*!
      * \brief Sauvegarder une partie vers un fichier texte
      */
    void sauvegarderPartie();

    /*!
      * \brief Recommencer le niveau en cours
      */
    void recommencerNiveau();

    /*!
      * \brief Affiche une partie
      *
      * @param unCurseur Pointeur vers un curseur virtuel
      * @param unPainter Pointeur vers un painter
      */
    void affiche(Curseur *unCurseur, QPainter *unPainter);

    /*!
      * \brief Logique d'une partie
      *
      * @param unCurseur Pointeur vers un curseur virtuel
      */
    void logique(Curseur *unCurseur);

    /*!
      * \brief Retourne un niveau
      *
      * @return Pointeur vers un niveau
      */
    Niveau* getSonNiveau();
};

#endif // PARTIE_H
