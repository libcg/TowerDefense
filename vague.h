#ifndef VAGUE_H
#define VAGUE_H

/*!
  * \brief Cette classe représente une vague d'ennemis.
  */
class Vague
{
private:
    int sonDelai;               /*!< \brief Délai avant l'apparition d'ennemis */
    int sonNombreEnnemis;       /*!< \brief Nombre d'ennemis d'une vague */
    int sonTypeEnnemis;         /*!< \brief Type d'ennemis d'une vague */

public:
    /*!
      * \brief Constructeur de la classe Vague
      *
      * @param unDelai Délai avant l'apparition d'ennemis
      * @param unNombreEnnemis Nombre d'ennemis d'une vague
      * @param unTypeEnnemis Type d'ennemis d'une vague
      */
    Vague(int unDelai, int unNombreEnnemis, int unTypeEnnemis);

    /*!
      * \brief Retourne le délai avant l'apparition d'ennemis
      *
      * @return Le délai
      */
    int getSonDelai();

    /*!
      * \brief Retourne le nombre d'ennemis d'une vague
      *
      * @return Le nombre d'ennemis
      */
    int getSonNombreEnnemis();

    /*!
      * \brief Retourne le type d'ennemis d'une vague
      *
      * @return Le type d'ennemis
      */
    int getSonTypeEnnemis();
};

#endif // VAGUE_H
