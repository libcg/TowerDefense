#include "tourelle.h"
#include "jeu.h"
#include <QPainter>
#include <QFile>
#include <cmath>
#include <string>

Tourelle::Tourelle(QPoint unePosition, std::list<Ennemi*>* uneListeEnnemis, int unType, QObject *parent) :
    QObject(parent),
    saListeEnnemis(uneListeEnnemis), sonEnnemiCible(NULL), sonType(unType),
    sonAngle(0.0), sonTir(false)
{
    saPosition = QPoint(unePosition.x()*TAILLE_TOURELLE + (WIDTH-32*TAILLE_GRILLE)/2,
                        unePosition.y()*TAILLE_TOURELLE);

    type();

    sonTimerTir = new QTimer();
    QObject::connect(sonTimerTir, SIGNAL(timeout()), this, SLOT(tir()));
    sonTimerTir->start(1000 / sonTPS);
}


Tourelle::~Tourelle()
{
    delete sonTimerTir;
}


void Tourelle::type()
{
    int portee[] = { 100, 400 };
    double tps[] = { 3, 0.5 };
    int degats[] = { 5, 50 };

    sonImageBase = QImage("data/tourelle_base.png");
    sonImageCanon = QImage("data/tourelle" + QString::number(sonType) + "_canon.png");
    sonImageCanonFeu = QImage("data/tourelle" + QString::number(sonType) + "_canon_feu.png");
    saPortee = portee[sonType];
    sonTPS = tps[sonType];
    sesDegats = degats[sonType];
}


void Tourelle::charge(QTextStream *unStream)
{
    int x, y;

    *unStream >> x >> y; saPosition = QPoint(x, y);
    *unStream >> sonAngle;
    *unStream >> sonTir;
}


void Tourelle::sauvegarde(QTextStream *unStream)
{
    *unStream << saPosition.x() << ' ' << saPosition.y() << endl;
    *unStream << sonAngle << endl;
    *unStream << sonTir << endl;
}


Ennemi* Tourelle::rechercheEnnemi()
{
    std::list<Ennemi*>::iterator it;

    for (it = saListeEnnemis->begin(); it != saListeEnnemis->end(); it++)
    {
        QPointF laPos = (*it)->getSaPosition();

        if (hypot(laPos.x() - saPosition.x(), laPos.y() - saPosition.y()) < saPortee)
            return *it;
    }

    return NULL;
}


void Tourelle::tir()
{
    if (sonEnnemiCible != NULL)
    {
        sonEnnemiCible->infligerDegat(sesDegats);
        sonTir = DUREE_TIR;
    }
}


void Tourelle::affiche(QPainter* unPainter)
{
    unPainter->save();

    /* On affiche la base */

    unPainter->translate(saPosition);
    unPainter->drawImage(0, 0, sonImageBase);

    /* On affiche le canon */

    unPainter->translate(TAILLE_TOURELLE/2, TAILLE_TOURELLE/2);
    unPainter->rotate(sonAngle);
    unPainter->drawImage(-TAILLE_TOURELLE/2, -TAILLE_TOURELLE/2, sonImageCanon);
    if (sonTir)
    {
        unPainter->setOpacity(double(sonTir) / DUREE_TIR);
        unPainter->drawImage(-TAILLE_TOURELLE/2, -TAILLE_TOURELLE/2, sonImageCanonFeu);
    }

    unPainter->restore();

    if (sonTir > 0) sonTir--;
}


void Tourelle::logique()
{
    sonEnnemiCible = rechercheEnnemi();

    if (sonEnnemiCible == NULL)
    {
        sonAngle += ROTATION_TOURELLE;
    }
    else
    {
        QPointF laPos = sonEnnemiCible->getSaPosition();

        double lAngleCible = fmod(atan2(laPos.y() - saPosition.y(), laPos.x() - saPosition.x()) * 180 / 3.14159, 360);
        double lAngleTemp = fmod(sonAngle, 360);
        if (lAngleCible < 0) lAngleCible += 360;
        if (lAngleTemp < 0) lAngleTemp += 360;

        double laDiff = lAngleTemp - lAngleCible;
        if (laDiff >  180) laDiff -= 360;
        if (laDiff < -180) laDiff += 360;

        if (laDiff < 0) sonAngle += 2*ROTATION_TOURELLE;
        else if (laDiff > 0) sonAngle -= 2*ROTATION_TOURELLE;
    }
}


int Tourelle::getSonType()
{
    return sonType;
}


int Tourelle::prix(int unType)
{
    int prix[] = { 2000, 3000 };

    return prix[unType];
}
