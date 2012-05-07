#ifndef VAGUE_H
#define VAGUE_H

class Vague
{
private:
    int sonDelai;
    int sonNombreEnnemis;
    int sonTypeEnnemis;

public:
    Vague(int unDelai, int unNombreEnnemis, int unTypeEnnemis);
    int getSonDelai();
    int getSonNombreEnnemis();
    int getSonTypeEnnemis();
};

#endif // VAGUE_H
