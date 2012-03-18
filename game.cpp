#include "game.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>

Game::Game(QWidget *parent) :
    QGLWidget(parent)
{
    timer = new QTimer(this);
    painter = new QPainter();
    curseur = new Curseur();
    terrain = Terrain();

    /* On centre la fenêtre */

    QDesktopWidget *desktop = QApplication::desktop();
    int x = (desktop->width() - WIDTH) / 2;
    int y = (desktop->height() - HEIGHT) / 2;
    this->setGeometry(x, y, WIDTH, HEIGHT);

    setFixedSize(WIDTH, HEIGHT);

    /* On active le suivi de curseur */

    setMouseTracking(true);

    /* On active la boucle de jeu (60 ips) */

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000/60);
}


Game::~Game()
{
    delete painter;
    delete curseur;
}

void Game::logicEvent()
{
    terrain.logique(curseur);

    curseur->setClic(false);
}


void Game::paintEvent(QPaintEvent *event)
{
    /* Logique de jeu */

    logicEvent();

    /* On commence le rendu */

    painter->begin(this);

    /* On active le filtre bilinéaire */

    painter->setRenderHint(QPainter::SmoothPixmapTransform);

    /* On affiche le terrain et ses unités */

    terrain.affiche(curseur, painter);

    /* On termine le rendu */

    painter->end();
}


void Game::mouseMoveEvent(QMouseEvent *event)
{
    curseur->setPosition(event->pos());
}


void Game::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        curseur->setClic(true);
    }
}
