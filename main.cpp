#include "fenetre.h"
#include <QApplication>
#include <QThread>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QDir leDir("data/");
    if (!leDir.exists())
    {
        QMessageBox sonAvertissement(
            QMessageBox::NoIcon, "Erreur",
            "Le dossier data/ n'existe pas.\n"
            "Copiez-le depuis le dossier du projet.",
            QMessageBox::Ok);

        sonAvertissement.exec();
        return 1;
    }

    Fenetre *laFenetre = new Fenetre();

    laFenetre->show();

    return app.exec();
}
