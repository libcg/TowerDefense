#include "fenetre.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  Fenetre *laFenetre = new Fenetre();

  laFenetre->show();

  return app.exec();
}
