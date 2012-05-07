#include "vague.h"

Vague::Vague(int unDelai, int unNombreEnnemis, int unTypeEnnemis) :
    sonDelai(unDelai), sonNombreEnnemis(unNombreEnnemis), sonTypeEnnemis(unTypeEnnemis)
{
}


int Vague::getSonDelai()
{
    return sonDelai;
}


int Vague::getSonNombreEnnemis()
{
    return sonNombreEnnemis;
}


int Vague::getSonTypeEnnemis()
{
    return sonTypeEnnemis;
}
