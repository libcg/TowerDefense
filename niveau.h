#ifndef NIVEAU_H
#define NIVEAU_H

#include "terrain.h"
#include "vague.h"
#include <QObject>
#include <QPoint>
#include <QString>

/*!
  * \brief Cette classe représente un niveau.
  */
class Niveau : public QObject
{
    Q_OBJECT

private:
    bool estCharge;                     /*!< \brief Indique si un niveau est bien chargé */
    int sesCredits;                     /*!< \brief Nombre de crédits accordés */
    std::vector<Vague> *sesVagues;      /*!< \brief Vagues d'ennemis */
    std::vector<QPoint> *sonChemin;     /*!< \brief Chemin des ennemis */

public:
    /*!
      * \brief Constructeur de la classe Niveau
      *
      * @param parent Pointeur optionel vers un QObject parent
      */
    explicit Niveau(QObject *parent = 0);

    /*!
      * \brief Constructeur de la classe Niveau, charge un niveau depuis un fichier texte
      *
      * @param unChemin Chemin du fichier
      * @param parent Pointeur optionel vers un QObject parent
      */
    explicit Niveau(QString unChemin, QObject *parent = 0);

    /*!
      * \brief Destructeur de la classe Niveau
      */
    ~Niveau();

    /*!
      * \brief Détermine si un niveau est chargé
      *
      * @return Booléen
      */
    bool charge();

    /*!
      * \brief Retourne les crédits d'un niveau
      *
      * @return Montant des crédits
      */
    int getSesCredits();

    /*!
      * \brief Retourne un pointeur vers les vagues d'un niveau
      *
      * @return Pointeur vers les vagues d'ennemis
      */
    std::vector<Vague> *getSesVagues();

    /*!
      * \brief Retourne un pointeur vers le chemin d'un niveau
      *
      * @return Pointeur vers le chemin
      */
    std::vector<QPoint> *getSonChemin();
};

#endif // NIVEAU_H
