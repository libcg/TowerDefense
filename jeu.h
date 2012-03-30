#ifndef JEU_H
#define JEU_H

#include "terrain.h"
#include "curseur.h"
#include <QtOpenGL/QGLWidget>
#include <QTimer>
#include <QKeyEvent>

#define WIDTH 960
#define HEIGHT 544

class Jeu : public QGLWidget
{
    Q_OBJECT

private:
    QTimer* sonTimer;
    QPainter* sonPainter;
    Curseur* sonCurseur;
    Terrain* sonTerrain;

public:
    Jeu(QWidget *parent = 0);
    ~Jeu();

protected:
    void logicEvent();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // JEU_H
