#include "unitemobile.h"
#include "jeu.h"

UniteMobile::UniteMobile(std::vector<QPoint>* unChemin, QObject *parent) :
    QObject(parent), sonImage("data/unitemobile.png"), sonImageDegat("data/unitemobile_degat.png"),
    sonChemin(unChemin), sonEtapeChemin(0), sesPV(100), sonDegat(0), aSupprimer(false)
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
        else
        {
            sonIncrement = QPointF(0, 0);
            aSupprimer = true;
        }
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
    unPainter->drawImage(0, 0, sonDegat ? sonImageDegat : sonImage);

    unPainter->restore();

    if(sonDegat > 0) sonDegat--;
}

void UniteMobile::infligerDegat(int unDegat)
{
    sonDegat = 5;
    sesPV -= unDegat;
    if (sesPV <= 0) aSupprimer = true;
}

QPointF UniteMobile::getSaPosition()
{
    return saPosition;
}

bool UniteMobile::estArrivee()
{
    return sonIncrement == QPointF(0, 0);
}

bool UniteMobile::estASupprimer()
{
    return aSupprimer;
}
