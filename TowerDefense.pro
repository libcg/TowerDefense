#-------------------------------------------------
#
# Project created by QtCreator 2012-01-23T09:25:07
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = TowerDefense
TEMPLATE = app


SOURCES += main.cpp \
    terrain.cpp \
    curseur.cpp \
    jeu.cpp \
    partie.cpp \
    fenetre.cpp \
    niveau.cpp \
    tourelle.cpp \
    ennemi.cpp \
    vague.cpp

HEADERS  += \
    terrain.h \
    curseur.h \
    jeu.h \
    partie.h \
    fenetre.h \
    niveau.h \
    tourelle.h \
    ennemi.h \
    vague.h

OTHER_FILES += \
    data/1.lvl \
    data/base_allie.png \
    data/base_ennemi.png \
    data/terrain_chemin.png \
    data/terrain_sol.png \
    data/unitestatique_base.png \
    data/unitestatique_canon_feu.png \
    data/unitestatique_canon.png \
    TODO.txt

FORMS += \
    fenetre.ui
