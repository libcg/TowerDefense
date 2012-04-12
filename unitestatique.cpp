#include "unitestatique.h"
#include "jeu.h"
#include <QPainter>
#include <cmath>
#include <string>

UniteStatique::UniteStatique(QPoint unePosition, std::list< UniteMobile* >* uneListeUniteMobile, QObject *parent) :
    QObject(parent), sonAngle(0.0), saPortee(100), sonTir(false), saListeUniteMobile(uneListeUniteMobile), sonUniteCible(NULL)
{
    saPosition = QPoint(unePosition.x()*TAILLE_UNITESTATIQUE + (WIDTH-32*TAILLE_GRILLE)/2,
                        unePosition.y()*TAILLE_UNITESTATIQUE);
    sonImageBase = QImage("data/unitestatique_base.png");
    sonImageCanon = QImage("data/unitestatique_canon.png");
    sonImageCanonFeu = QImage("data/unitestatique_canon_feu.png");

    sonTimerTir = new QTimer(this);
    QObject::connect(sonTimerTir, SIGNAL(timeout()), this, SLOT(tir()));
    sonTimerTir->start(1000/3);
}


UniteMobile* UniteStatique::rechercheUnite()
{
    std::list<UniteMobile*>::iterator it;

    for (it = saListeUniteMobile->begin(); it != saListeUniteMobile->end(); it++)
    {
        QPointF laPos = (*it)->getSaPosition();

        if (hypot(laPos.x() - saPosition.x(), laPos.y() - saPosition.y()) < saPortee)
        {
            return *it;
        }
    }

    return NULL;
}


void UniteStatique::tir()
{
    if (sonUniteCible != NULL)
    {
        sonUniteCible->infligerDegat(5);
        sonTir = DUREE_TIR;
    }
}


void UniteStatique::affiche(QPainter* unPainter)
{
    unPainter->save();

    /* On affiche la base */

    unPainter->translate(saPosition);
    unPainter->drawImage(0, 0, sonImageBase);

    /* On affiche le canon */

    unPainter->translate(TAILLE_UNITESTATIQUE/2, TAILLE_UNITESTATIQUE/2);
    unPainter->rotate(this->sonAngle);
    unPainter->drawImage(-TAILLE_UNITESTATIQUE/2, -TAILLE_UNITESTATIQUE/2, sonImageCanon);
    if (sonTir)
    {
        unPainter->setOpacity(double(sonTir) / DUREE_TIR);
        unPainter->drawImage(-TAILLE_UNITESTATIQUE/2, -TAILLE_UNITESTATIQUE/2, sonImageCanonFeu);
    }

    unPainter->restore();

    if (sonTir > 0) sonTir--;
}


void UniteStatique::logique()
{
    sonUniteCible = rechercheUnite();

    if (sonUniteCible == NULL)
    {
        sonAngle += ROTATION_UNITESTATIQUE;
    }
    else
    {
        QPointF laPos = sonUniteCible->getSaPosition();

        double lAngleCible = fmod(atan2(laPos.y() - saPosition.y(), laPos.x() - saPosition.x()) * 180 / 3.14159, 360);
        double lAngleTemp = fmod(sonAngle, 360);
        if (lAngleCible < 0) lAngleCible += 360;
        if (lAngleTemp < 0) lAngleTemp += 360;

        double laDiff = lAngleTemp - lAngleCible;
        if (laDiff >  180) laDiff -= 360;
        if (laDiff < -180) laDiff += 360;

        if (laDiff < 0) sonAngle += 2*ROTATION_UNITESTATIQUE;
        else if (laDiff > 0) sonAngle -= 2*ROTATION_UNITESTATIQUE;
    }
}
