#ifndef ENNEMI_H
#define ENNEMI_H

#include <vector>
#include <QPoint>
#include <QImage>
#include <QPainter>
#include <QTextStream>

#define TAILLE_ENNEMI 32

/*!
  * \brief Cette classe représente un ennemi.
  */
class Ennemi : public QObject
{
    Q_OBJECT

private:
    std::vector<QPoint> *sonChemin;     /*!< \brief Pointeur vers le chemin emprunté par un ennemi */
    QImage sonImage;                    /*!< \brief Image utilisée lorsque sonDegat égal à zéro */
    QImage sonImageDegat;               /*!< \brief Image utilisée lorsque sonDegat supérieur à zéro */
    unsigned int sonNombrePas;          /*!< \brief Nombre de pas à effectuer pour traverser une case */
    unsigned int sonType;               /*!< \brief Identifiant de type d'ennemi */
    unsigned int sonPrix;               /*!< \brief Nombre de crédits donnés à la mort d'un ennemi */

    QPointF saPosition;                 /*!< \brief Coordonnées */
    QPointF sonIncrement;               /*!< \brief Direction, incrémente les coordonnées à chaque pas */
    unsigned int sonPas;                /*!< \brief Pas actuel, strictement inférieur à sonNombrePas */
    unsigned int sonEtapeChemin;        /*!< \brief Etape actuelle du chemin */
    int sesPV;                          /*!< \brief Points de vie */
    int sonDegat;                       /*!< \brief Indique si un ennemi encaisse un tir de tourelle */
    bool aSupprimer;                    /*!< \brief Indique qu'un ennemi doit être supprimé */

    /*!
      * \brief Construit un ennemi en fonction de sonType
      */
    void type();

    /*!
      * \brief Calcule sonIncrement en fonction de saPosition et de unePositionArrivee
      *
      * @param unePositionArrivee Coordonnées de l'arrivée
      */
    void calcul(QPointF unePositionArrivee);

    /*!
      * \brief Déplace un ennemi, incrémente sonEtapeChemin et/ou le supprime si nécessaire
      */
    void deplace();

public:

    /*!
      * \brief Constructeur de la classe Ennemi
      *
      * @param unChemin Pointeur vers un chemin qu'empruntera un ennemi
      * @param unType Type de l'ennemi
      * @param parent Pointeur optionel vers un QObject parent
      */
    explicit Ennemi(std::vector<QPoint> *unChemin, int unType, QObject *parent = 0);

    /*!
      * \brief Charge les propriétés d'un ennemi depuis un flot de texte
      *
      * @param unStream Pointeur vers un flot de texte
      */
    void charge(QTextStream *unStream);

    /*!
      * \brief Sauvegarde les propriétés d'un ennemi vers un flot de texte
      *
      * @param unStream Pointeur vers un flot de texte
      */
    void sauvegarde(QTextStream *unStream);

    /*!
      * \brief Logique d'un ennemi (déplacement)
      */
    void logique();

    /*!
      * \brief Affiche un ennemi
      *
      * @param unPainter Pointeur vers un painter
      */
    void affiche(QPainter *unPainter);

    /*!
      * \brief Inflige des dégâts à un ennemi
      *
      * @param unDegat Points de vie à enlever
      */
    void infligerDegat(int unDegat);

    /*!
      * \brief Retourne la position d'un ennemi
      *
      * @return Coordonnées d'un ennemi
      */
    QPointF getSaPosition();

    /*!
      * \brief Détermine si un ennemi est arrivé à la base alliée
      *
      * @return Booléen
      */
    bool estArrivee();

    /*!
      * \brief Détermine si un ennemi doit être supprimé
      *
      * @return Booléen
      */
    bool estASupprimer();

    /*!
      * \brief Retourne le prix d'un ennemi
      *
      * @return Prix d'un ennemi
      */
    int getSonPrix();

    /*!
      * \brief Retourne l'identifiant de type d'un ennemi
      *
      * @return Identifiant de type
      */
    int getSonType();
};

#endif // UNITEMOBILE_H
