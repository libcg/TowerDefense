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

class Jeu : public QGLWidget
{
    Q_OBJECT

private:
    QTimer* sonTimer;
    QPainter* sonPainter;
    Curseur* sonCurseur;
    Partie* saPartie;

    void logicEvent();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

public:
    explicit Jeu(QWidget *parent = 0);
    ~Jeu();
    Partie* getSaPartie();
};

#endif // JEU_H
