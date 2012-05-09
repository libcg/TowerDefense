#ifndef CURSEUR_H
#define CURSEUR_H

#include <QPoint>

/*!
  * \brief Cette classe représente un curseur virtuel de la souris.
  */
class Curseur
{
private:
    QPoint saPosition;                  /*!< \brief Position d'un curseur */
    Qt::MouseButton sonBouton;          /*!< \brief Type de bouton appuyé */
    Qt::MouseButton sonDernierBouton;   /*!< \brief Type de bouton appuyé plus tôt */

public:
    /*!
      * \brief Constructeur de la classe Curseur
      */
    Curseur();

    /*!
      * \brief Définit la position d'un curseur
      *
      * @param unePosition Coordonnées d'un curseur
      */
    void setPosition(QPoint unePosition);

    /*!
      * \brief Définit le bouton actif d'un curseur
      *
      * @param unBouton Bouton actif d'un curseur
      */
    void setBouton(Qt::MouseButton unBouton);

    /*!
      * \brief Définit le dernier bouton actif d'un curseur
      *
      * @param unDernierBouton Dernier bouton actif d'un curseur
      */
    void setDernierBouton(Qt::MouseButton unDernierBouton);

    /*!
      * \brief Récupère la coordonnée X d'un curseur
      *
      * @return Coordonnée X d'un curseur
      */
    int getX();

    /*!
      * \brief Récupère la coordonnée Y d'un curseur
      *
      * @return Coordonnée Y d'un curseur
      */
    int getY();

    /*!
      * \brief Récupère le bouton actif d'un curseur
      *
      * @return Bouton actif d'un curseur
      */
    Qt::MouseButton getBouton();

    /*!
      * \brief Récupère le dernier bouton actif d'un curseur
      *
      * @return Dernier bouton actif d'un curseur
      */
    Qt::MouseButton getDernierBouton();
};

#endif // CURSEUR_H
