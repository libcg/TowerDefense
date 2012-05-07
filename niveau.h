#ifndef NIVEAU_H
#define NIVEAU_H

#include "terrain.h"
#include "vague.h"
#include <QObject>
#include <QPoint>
#include <QString>

class Niveau : public QObject
{
    Q_OBJECT

private:
    bool estCharge;
    int sesCredits;
    std::vector<Vague> *sesVagues;
    std::vector<QPoint> *sonChemin;

public:
    explicit Niveau(QObject *parent = 0);
    explicit Niveau(QString unChemin, QObject *parent = 0);
    ~Niveau();
    bool charge();
    int getSesCredits();
    std::vector<Vague> *getSesVagues();
    std::vector<QPoint> *getSonChemin();
};

#endif // NIVEAU_H
