#ifndef GAME_H
#define GAME_H

#include "terrain.h"
#include "curseur.h"
#include <QtOpenGL/QGLWidget>
#include <QKeyEvent>

#define WIDTH 960
#define HEIGHT 544

class Game : public QGLWidget
{
  Q_OBJECT

private:
  QPainter* painter;
  Curseur* curseur;
  Terrain terrain;

public:
    Game(QGLWidget *parent = 0);
    ~Game();

protected:
    void logicEvent();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // GAME_H
