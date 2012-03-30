#include "unitestatique.h"
#include "jeu.h"
#include <QPainter>
#include <cmath>

UniteMobile* UniteStatique::rechercheUnite()
{
    std::vector<UniteMobile*>::iterator it;

    for (it = sonVecUniteMobile->begin(); it != sonVecUniteMobile->end(); it++)
    {
        QPointF laPos = (*it)->getSaPosition();

        if (hypot(laPos.x() - saPosition.x(), laPos.y() - saPosition.y()) < saPortee)
        {
            return *it;
        }
    }

    return NULL;
}

UniteStatique::UniteStatique(QPoint unePosition, std::vector< UniteMobile* >* unVecUniteMobile) :
    sonAngle(0.0), saPortee(100), sonVecUniteMobile(unVecUniteMobile), sonUniteCible(NULL)
{
    saPosition = QPoint(unePosition.x()*TAILLE_UNITESTATIQUE + (WIDTH-32*TAILLE_GRILLE)/2,
                        unePosition.y()*TAILLE_UNITESTATIQUE);
    sonImageBase = QImage("data/unitestatique_base.png");
    sonImageCanon = QImage("data/unitestatique_canon.png");
    sonImageCanonFeu = QImage("data/unitestatique_canon_feu.png");
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

    unPainter->restore();
}

void UniteStatique::logique()
{
    sonUniteCible = rechercheUnite();

    if (sonUniteCible == NULL)
    {
        sonAngle += 1.7;
    }
    else
    {
        QPointF laPos = sonUniteCible->getSaPosition();

        sonAngle = atan2(laPos.y() - saPosition.y(), laPos.x() - saPosition.x()) * 180 / 3.14159;
    }
}
