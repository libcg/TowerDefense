#include "unitemobile.h"
#include "jeu.h"

UniteMobile::UniteMobile(std::vector<QPoint>* unChemin) :
    sonImage("data/unitestatique_canon_feu.png"), sonChemin(unChemin), sonEtapeChemin(0)
{
    saPosition = QPointF((*sonChemin)[0].x()*TAILLE_UNITEMOBILE + (WIDTH-32*TAILLE_GRILLE)/2,
                         (*sonChemin)[0].y()*TAILLE_UNITEMOBILE);

    calcul((*sonChemin)[1]);
    sonPas = 0;
}

void UniteMobile::calcul(QPointF unePositionArrivee)
{
    QPointF saPositionCible;

    saPositionCible = QPointF(unePositionArrivee.x()*TAILLE_UNITEMOBILE + (WIDTH-32*TAILLE_GRILLE)/2,
                              unePositionArrivee.y()*TAILLE_UNITEMOBILE);

    sonIncrement = (saPositionCible - saPosition) / PAS;
}


void UniteMobile::deplace()
{
    saPosition += sonIncrement;
    sonPas++;

    if (sonPas == PAS)
    {
        if (sonEtapeChemin+2 < sonChemin->size())
        {
            calcul((*sonChemin)[++sonEtapeChemin + 1]);
            sonPas = 0;
        }
        else sonIncrement = QPointF(0, 0);
    }
}


void UniteMobile::logique()
{
    deplace();
}

void UniteMobile::affiche(QPainter* unPainter)
{
    unPainter->save();

    unPainter->translate(saPosition);
    unPainter->drawImage(0, 0, sonImage);

    unPainter->restore();
}

QPointF UniteMobile::getSaPosition()
{
    return saPosition;
}
