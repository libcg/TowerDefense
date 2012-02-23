#-------------------------------------------------
#
# Project created by QtCreator 2012-01-23T09:25:07
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = TowerDefense
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    terrain.cpp \
    unitestatique.cpp \
    curseur.cpp \
    unitemobile.cpp

HEADERS  += \
    game.h \
    terrain.h \
    unitestatique.h \
    curseur.h \
    unitemobile.h

OTHER_FILES += \
    data/1.lvl \
    data/base_allie.png \
    data/base_ennemi.png \
    data/terrain_chemin.png \
    data/terrain_sol.png \
    data/unitestatique_base.png \
    data/unitestatique_canon_feu.png \
    data/unitestatique_canon.png
