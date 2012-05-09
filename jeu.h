#ifndef JEU_H
#define JEU_H

#include "terrain.h"
#include "curseur.h"
#include "partie.h"
#include <QtOpenGL/QGLWidget>
#include <QTimer>
#include <QKeyEvent>

#define WIDTH 960
#define HEIGHT 544

class Terrain;
class Partie;

/*!
  * \brief Cette classe représente un jeu et son widget.
  */
class Jeu : public QGLWidget
{
    Q_OBJECT

private:
    QTimer *sonTimer;           /*!< \brief Pointeur un timer */
    QPainter *sonPainter;       /*!< \brief Pointeur un painter */
    Curseur *sonCurseur;        /*!< \brief Pointeur vers un curseur */
    Partie *saPartie;           /*!< \brief Pointeur vers un partie */

    /*!
      * \brief Évènement de logique (non défini par Qt)
      */
    void logicEvent();

    /*!
      * \brief Évènement de mouvement de souris
      *
      * @param event
      */
    void mouseMoveEvent(QMouseEvent *event);

    /*!
      * \brief Évènement d'appui de bouton de souris
      *
      * @param event
      */
    void mousePressEvent(QMouseEvent *event);

    /*!
      * \brief Évènement de dessin
      *
      * @param event
      */
    void paintEvent(QPaintEvent *event);

public:
    /*!
      * \brief Constructeur de la classe Jeu
      *
      * @param parent Pointeur optionel vers un QObject parent
      */
    explicit Jeu(QWidget *parent = 0);

    /*!
      * \brief Destructeur de la classe Jeu
      */
    ~Jeu();

    /*!
      * \brief Retourne une partie
      *
      * @return Pointeur vers une partie
      */
    Partie *getSaPartie();
};

#endif // JEU_H
