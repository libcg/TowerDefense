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

/*!
  * \brief Cette classe représente une tourelle.
  */
class Tourelle : public QObject
{
    Q_OBJECT

private:
    std::list<Ennemi*> *saListeEnnemis;     /*!< \brief Pointeur vers une liste d'ennemis */
    QImage sonImageBase;                    /*!< \brief Image de la base d'une tourelle */
    QImage sonImageCanon;                   /*!< \brief Image du canon d'une tourelle */
    QImage sonImageCanonFeu;                /*!< \brief Image du canon d'une tourelle lorsqu'elle tire */
    Ennemi *sonEnnemiCible;                 /*!< \brief Pointeur vers un ennemi ciblé */
    QTimer *sonTimerTir;                    /*!< \brief Pointeur vers un timer de tir */
    int sonType;                            /*!< \brief Type de tourelle */
    double saPortee;                        /*!< \brief Portée d'une tourelle */
    double sonTPS;                          /*!< \brief Tirs par seconde d'une tourelle */
    int sesDegats;                          /*!< \brief Dégâts qu'inflige une tourelle */

    QPoint saPosition;                      /*!< \brief Position d'une tourelle en pixels */
    double sonAngle;                        /*!< \brief Angle d'une tourelle */
    unsigned int sonTir;                    /*!< \brief Etat du tir d'une tourelle */

    /*!
      * \brief Recherche le premier ennemi à portée
      */
    Ennemi* rechercheEnnemi();

    /*!
      * \brief Construit une tourelle en fonction de sonType
      */
    void type();

private slots:
    /*!
      * \brief Évènement de tir déclenché par le timer de tir
      */
    void tir();

public:
    /*!
      * \brief Constructeur de la classe Tourelle
      *
      * @param unePosition Position sur la grille
      * @param uneListeEnnemis Pointeur vers une liste d'ennemis
      * @param unType Identifiant de type de la tourelle
      * @param parent Pointeur optionel vers un QObject parent
      */
    Tourelle(QPoint unePosition, std::list<Ennemi*> *uneListeEnnemis, int unType, QObject *parent = 0);

    /*!
      * \brief Destructeur de la classe Tourelle
      */
    ~Tourelle();

    /*!
      * \brief Charge les propriétés d'une tourelle depuis un flot de texte
      *
      * @param unStream Pointeur vers un flot de texte
      */
    void charge(QTextStream *unStream);

    /*!
      * \brief Sauvegarde les propriétés d'une tourelle vers un flot de texte
      *
      * @param unStream Pointeur vers un flot de texte
      */
    void sauvegarde(QTextStream *unStream);

    /*!
      * \brief Affiche une tourelle
      *
      * @param unPainter Pointeur vers un painter
      */
    void affiche(QPainter *unPainter);

    /*!
      * \brief Logique d'une tourelle
      */
    void logique();

    /*!
      * \brief Retourne le type d'une tourelle
      *
      * @return Identifiant de type
      */
    int getSonType();

    /*!
      * \brief Retourne le prix d'une tourelle
      *
      * @param unType Identifiant de type de tourelle
      */
    static int prix(int unType);
};

#endif // TOURELLE_H
