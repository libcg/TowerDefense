#include "jeu.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>

Jeu::Jeu(QWidget *parent) :
    QGLWidget(parent)
{
    sonTimer = new QTimer(this);
    sonPainter = new QPainter();
    sonCurseur = new Curseur();
    saPartie = new Partie();
    sonTerrain = new Terrain(saPartie);

    /* On centre la fenêtre */

    QDesktopWidget *desktop = QApplication::desktop();
    int x = (desktop->width() - WIDTH) / 2;
    int y = (desktop->height() - HEIGHT) / 2;
    this->setGeometry(x, y, WIDTH, HEIGHT);

    setFixedSize(WIDTH, HEIGHT);

    /* On active le suivi de curseur */

    setMouseTracking(true);

    /* On active la boucle de jeu (60 ips) */

    QObject::connect(sonTimer, SIGNAL(timeout()), this, SLOT(update()));
    sonTimer->start(1000/60);
}


Jeu::~Jeu()
{
    delete sonTimer;
    delete sonCurseur;
    delete sonPainter;
    delete saPartie;
    delete sonTerrain;
}

void Jeu::logicEvent()
{
    if (!saPartie->getSonEchec())
    {
        sonTerrain->logique(sonCurseur);
    }

    sonCurseur->setClic(false);
}


void Jeu::paintEvent(QPaintEvent *event)
{
    /* Logique de jeu */

    logicEvent();

    /* On commence le rendu */

    sonPainter->begin(this);

    /* Filtre bilinéaire et antialiasing pour le texte */

    sonPainter->setRenderHint(QPainter::SmoothPixmapTransform);
    sonPainter->setRenderHint(QPainter::TextAntialiasing);

    /* On affiche le terrain et ses unités */

    sonTerrain->affiche(sonCurseur, sonPainter);

    /* On affiche les informations de partie */

    saPartie->affiche(sonPainter);

    /* On termine le rendu */

    sonPainter->end();
}


void Jeu::mouseMoveEvent(QMouseEvent *event)
{
    sonCurseur->setPosition(event->pos());
}


void Jeu::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        sonCurseur->setClic(true);
    }
}
