#include "partie.h"
#include <QTextStream>

Partie::Partie(QObject *parent) :
    QObject(parent)
{
    sonNiveau = new Niveau();
    sonTerrain = NULL;
    sonTimerDecompte = new QTimer();

    sonTimerDecompte->start(1000);
    QObject::connect(sonTimerDecompte, SIGNAL(timeout()), this, SLOT(decompte()));

    nouvellePartie();
}


void Partie::decompte()
{
    if (sonDecompteTemps > 0)
        sonDecompteTemps--;
    else if (sonDecompteEnnemi > 0)
    {
        sonTerrain->ajouteEnnemi
            (
                new Ennemi(sonNiveau->getSonChemin(),
                           sonNiveau->getSesVagues()->at(saVague).getSonTypeEnnemis())
            );
        sonDecompteEnnemi--;
    }
    else if ((unsigned int)saVague+1 < sonNiveau->getSesVagues()->size())
    {
        saVague++;
        sonDecompteTemps = sonNiveau->getSesVagues()->at(saVague).getSonDelai();
        sonDecompteEnnemi = sonNiveau->getSesVagues()->at(saVague).getSonNombreEnnemis();
    }
    else if (sonTerrain->getSaListeEnnemis()->size() == 0)
        sonEtat = fin() ? FIN : VICTOIRE;
}

void Partie::infligerDegat(int unDegat)
{
    saVie -= unDegat;

    if (saVie <= 0)
    {
        saVie = 0;
        sonEtat = DEFAITE;
    }
}


void Partie::ajoutCredits(Ennemi *unEnnemi)
{
    sesCredits += unEnnemi->getSonPrix();
}


void Partie::nouvellePartie()
{
    sonNumeroNiveau = 1;

    chargerNiveau();
}


void Partie::chargerPartie()
{
    QFile file("data/1.sav");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream stream(&file);

    stream.readLine();
    {
        stream >> sonNumeroNiveau;
        chargerNiveau();
        stream >> saVie;
        stream >> sesCredits;
        stream >> sonEtat;
        stream >> saVague;
        stream >> sonDecompteTemps;
        stream >> sonDecompteEnnemi;
    }
    stream.read(3);

    sonTerrain->charge(&stream);

    file.close();
}


void Partie::sauvegarderPartie()
{
    QFile file("data/1.sav");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream stream(&file);

    stream << "partie" << endl;
    {
        stream << sonNumeroNiveau << endl;
        stream << saVie << endl;
        stream << sesCredits << endl;
        stream << sonEtat << endl;
        stream << saVague << endl;
        stream << sonDecompteTemps << endl;
        stream << sonDecompteEnnemi << endl;
    }
    stream << ';' << endl;

    sonTerrain->sauvegarde(&stream);

    file.close();
}


bool Partie::fin()
{
    Niveau *leNiveau;

    leNiveau = new Niveau("data/" + QString::number(sonNumeroNiveau+1) + ".lvl");

    if (!leNiveau->charge())
        return true;

    delete leNiveau;
    return false;
}


void Partie::chargerNiveau()
{
    delete sonNiveau;
    sonNiveau = new Niveau("data/" + QString::number(sonNumeroNiveau) + ".lvl");

    if (!sonNiveau->charge())
        return;

    recommencerNiveau();
}


void Partie::niveauSuivant()
{
    sonNumeroNiveau++;

    chargerNiveau();
}


void Partie::recommencerNiveau()
{
    delete sonTerrain;
    sonTerrain = new Terrain(this, sonNiveau->getSonChemin());

    saVie = 100;
    sesCredits = sonNiveau->getSesCredits();
    sonEtat = JOUE;
    saVague = 0;
    sonDecompteTemps = sonNiveau->getSesVagues()->at(0).getSonDelai();
    sonDecompteEnnemi = sonNiveau->getSesVagues()->at(0).getSonNombreEnnemis();
}


void Partie::afficheBarreVie(QPainter *unPainter)
{
    unPainter->save();

    unPainter->translate(20, 20);
    unPainter->setPen(Qt::black);
    unPainter->setBrush(Qt::green);
    unPainter->drawRect(QRect(0, 0, 22, 102));
    unPainter->setPen(Qt::green);
    unPainter->setBrush(Qt::red);
    unPainter->drawRect(QRect(1, 1, 20, 100-saVie));

    unPainter->restore();
}


void Partie::afficheInfoVague(QPainter *unPainter)
{
    unPainter->save();

    unPainter->translate(10, HEIGHT-50);
    unPainter->setPen(Qt::white);
    unPainter->setBrush(Qt::black);
    if (sonDecompteTemps > 0)
    {
        unPainter->drawText(0, 0, "Prochaine vague dans :");
        unPainter->drawText(0, 20, QString::number(sonDecompteTemps) + " seconde(s)");
    }
    else
    {
        unPainter->drawText(0, 20, QString::number(sonDecompteEnnemi) + " ennemi(s) restant(s)");
    }

    unPainter->restore();
}


void Partie::afficheEtat(QPainter *unPainter, QString unTitre)
{
    unPainter->save();

    unPainter->setPen(Qt::transparent);
    unPainter->setBrush(QColor(0, 0, 0, 50));
    unPainter->drawRect(QRect(0, 0, WIDTH, HEIGHT));

    unPainter->setPen(Qt::white);
    unPainter->setFont(QFont("Arial", 80));
    unPainter->drawText(0, 0, WIDTH, HEIGHT, Qt::AlignCenter, unTitre);

    unPainter->restore();
}


void Partie::afficheCredits(QPainter *unPainter)
{
    unPainter->save();

    unPainter->translate(0, HEIGHT-50);
    unPainter->setPen(Qt::white);
    unPainter->setBrush(Qt::black);
    unPainter->drawText(0, 0, WIDTH-10, 50, Qt::AlignRight, QString::number(sesCredits) + " credit(s)");

    unPainter->restore();
}


void Partie::affiche(Curseur *unCurseur, QPainter *unPainter)
{
    sonTerrain->affiche(unCurseur, unPainter);

    afficheBarreVie(unPainter);
    afficheInfoVague(unPainter);
    afficheCredits(unPainter);

    switch (sonEtat)
    {
        case DEFAITE:
            afficheEtat(unPainter, "Defaite");
        break;
        case VICTOIRE:
            afficheEtat(unPainter, "Victoire");
        break;
        case FIN:
            afficheEtat(unPainter, "Fin de partie");
        break;
    }
}


void Partie::logique(Curseur *unCurseur)
{
    switch (sonEtat)
    {
        case JOUE:
        {
            if (unCurseur->getClic() && sesCredits - Tourelle::prix() >= 0)
                if (sonTerrain->ajouteTourelle(unCurseur))
                    sesCredits -= Tourelle::prix();

            sonTerrain->logique(unCurseur);
        }
        break;
        case VICTOIRE:
        {
            if (unCurseur->getClic())
                niveauSuivant();
        }
        break;
    }
}


Niveau* Partie::getSonNiveau()
{
    return sonNiveau;
}
