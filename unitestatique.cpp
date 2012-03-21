#include "unitestatique.h"
#include "game.h"
#include <QPainter>

UniteStatique::UniteStatique(QPoint unePosition)
{
    //saPuissance = 0;
    //sonType = 0;
    //sonCout = 0;
    saPosition = QPoint(unePosition.x()*TAILLE_UNITESTATIQUE + (WIDTH-32*TAILLE_GRILLE)/2,
                        unePosition.y()*TAILLE_UNITESTATIQUE);
    sonAngle = 0.0;
    sonImageBase = QImage("data/unitestatique_base.png");
    sonImageCanon = QImage("data/unitestatique_canon.png");
    sonImageCanonFeu = QImage("data/unitestatique_canon_feu.png");
}


void UniteStatique::affiche(QPainter* painter)
{
    painter->save();

    /* On affiche la base */

    painter->translate(saPosition);
    painter->drawImage(0, 0, sonImageBase);

    /* On affiche le canon */

    painter->translate(TAILLE_UNITESTATIQUE/2, TAILLE_UNITESTATIQUE/2);
    painter->rotate(this->sonAngle);
    painter->drawImage(-TAILLE_UNITESTATIQUE/2, -TAILLE_UNITESTATIQUE/2, sonImageCanon);

    painter->restore();
}


void UniteStatique::logique()
{
    /* Aucun ennemi n'est à proximité, on tourne */

    this->sonAngle += 1.7;
}
