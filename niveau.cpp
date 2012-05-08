#include "niveau.h"
#include <QTextStream>
#include <QFile>

Niveau::Niveau(QObject *parent) :
    QObject(parent), estCharge(false)
{
    sonChemin = new std::vector<QPoint>();
    sesVagues = new std::vector<Vague>();
}


Niveau::Niveau(QString unChemin, QObject *parent) :
    QObject(parent), estCharge(false)
{
    sonChemin = new std::vector<QPoint>();
    sesVagues = new std::vector<Vague>();

    QFile file(unChemin);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream stream(&file);
    QString s;
    int x, y, z;

    // Crédits
    stream.readLine();
    {
        stream >> x;
        sesCredits = x;
    }
    stream.read(2);

    // Vagues
    stream >> s;
    for (;;)
    {
        if (stream.read(2) == "\n;") break;
        else stream.seek(stream.pos() - 2);

        stream >> x >> y >> z;
        sesVagues->push_back(Vague(x, y, z));
    }

    // Chemin
    stream >> s;
    for (;;)
    {
        if (stream.read(2) == "\n;") break;
        else stream.seek(stream.pos() - 1);

        stream >> x >> y;

        sonChemin->push_back(QPoint(x, y));
    }

    file.close();

    estCharge = true;
}


Niveau::~Niveau()
{
    delete sesVagues;
    delete sonChemin;
}


bool Niveau::charge()
{
    return estCharge;
}


int Niveau::getSesCredits()
{
    return sesCredits;
}


std::vector< Vague > *Niveau::getSesVagues()
{
    return sesVagues;
}


std::vector<QPoint> *Niveau::getSonChemin()
{
    return sonChemin;
}
