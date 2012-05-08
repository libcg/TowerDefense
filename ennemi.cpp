#include "ennemi.h"
#include "jeu.h"

std::vector<QPoint> *sonChemin;
QImage sonImage;
QImage sonImageDegat;

Ennemi::Ennemi(std::vector<QPoint>* unChemin, int unType, QObject *parent) :
    QObject(parent),
    sonChemin(unChemin), sonType(unType), sonEtapeChemin(0),
    sonDegat(0), aSupprimer(false)
{
    saPosition = QPointF((*sonChemin)[0].x()*TAILLE_ENNEMI + (WIDTH-32*TAILLE_GRILLE)/2,
                         (*sonChemin)[0].y()*TAILLE_ENNEMI);
    sonIncrement = QPointF();

    type();

    calcul((*sonChemin)[1]);
    sonPas = 0;
}


void Ennemi::type()
{
    int n_pas[] = { 30, 35, 60 };
    int pv[] = { 100, 300, 1000 };
    int prix[] = { 500, 1000, 5000 };

    sonImage = QImage("data/ennemi" + QString::number(sonType) + ".png");
    sonImageDegat = QImage("data/ennemi" + QString::number(sonType) + "_degat.png");
    sonNombrePas = n_pas[sonType];
    sesPV = pv[sonType];
    sonPrix = prix[sonType];
}


void Ennemi::charge(QTextStream *unStream)
{
    double x, y;
    int t;

    *unStream >> x >> y; saPosition = QPointF(x, y);
    *unStream >> x >> y; sonIncrement = QPointF(x, y);
    *unStream >> sonPas;
    *unStream >> sonEtapeChemin;
    *unStream >> sesPV;
    *unStream >> sonDegat;
    *unStream >> t; aSupprimer = t;
}


void Ennemi::sauvegarde(QTextStream *unStream)
{
    *unStream << saPosition.x() << ' ' << saPosition.y() << endl;
    *unStream << sonIncrement.x() << ' ' << sonIncrement.y() << endl;
    *unStream << sonPas << endl;
    *unStream << sonEtapeChemin << endl;
    *unStream << sesPV << endl;
    *unStream << sonDegat << endl;
    *unStream << aSupprimer << endl;
}


void Ennemi::calcul(QPointF unePositionArrivee)
{
    QPointF saPositionCible;

    saPositionCible = QPointF(unePositionArrivee.x()*TAILLE_ENNEMI + (WIDTH-32*TAILLE_GRILLE)/2,
                              unePositionArrivee.y()*TAILLE_ENNEMI);

    sonIncrement = (saPositionCible - saPosition) / sonNombrePas;
}


void Ennemi::deplace()
{
    saPosition += sonIncrement;
    sonPas++;

    if (sonPas == sonNombrePas)
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


void Ennemi::logique()
{
    deplace();
}


void Ennemi::affiche(QPainter* unPainter)
{
    unPainter->save();

    unPainter->translate(saPosition);
    unPainter->drawImage(0, 0, sonDegat ? sonImageDegat : sonImage);

    unPainter->restore();

    if(sonDegat > 0) sonDegat--;
}


void Ennemi::infligerDegat(int unDegat)
{
    sonDegat = 5;
    sesPV -= unDegat;
    if (sesPV <= 0) aSupprimer = true;
}


QPointF Ennemi::getSaPosition()
{
    return saPosition;
}


bool Ennemi::estArrivee()
{
    return sonIncrement == QPointF(0, 0);
}


bool Ennemi::estASupprimer()
{
    return aSupprimer;
}


int Ennemi::getSonPrix()
{
    return sonPrix;
}


int Ennemi::getSonType()
{
    return sonType;
}
