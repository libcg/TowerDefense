#ifndef FENETRE_H
#define FENETRE_H

#include "jeu.h"
#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class Fenetre;
}

/*!
  * \brief Cette classe représente une fenêtre principale.
  */
class Fenetre : public QMainWindow
{
    Q_OBJECT
    
private:
    Ui::Fenetre *ui;                /*!< \brief Pointeur vers une UI, nécessaire pour Qt Designer */
    Jeu* sonJeu;                    /*!< \brief Pointeur vers un jeu */
    QMessageBox *saMessageBox;      /*!< \brief Pointeur vers une boîte à message */

private slots:
    /*!
      * \brief Fonction appelée lors d'un évènement QAction
      */
    void on_actionNouvellePartie_triggered();

    /*!
      * \brief Fonction appelée lors d'un évènement QAction
      */
    void on_actionChargerPartie_triggered();

    /*!
      * \brief Fonction appelée lors d'un évènement QAction
      */
    void on_actionSauvegarderPartie_triggered();

    /*!
      * \brief Fonction appelée lors d'un évènement QAction
      */
    void on_actionRecommencer_triggered();

    /*!
      * \brief Fonction appelée lors d'un évènement QAction
      */
    void on_actionCommentJouer_triggered();

public:
    /*!
      * \brief Constructeur de la classe Fenetre
      *
      * @param parent Pointeur optionel vers un QObject parent
      */
    explicit Fenetre(QWidget *parent = 0);

    /*!
      * \brief Destructeur de la classe Fenetre
      */
    ~Fenetre();
};

#endif // FENETRE_H
