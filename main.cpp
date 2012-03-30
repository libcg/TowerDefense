#include "jeu.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  Jeu *jeu = new Jeu();

  app.setApplicationName(QString("TowerDefense"));

  jeu->show();

  return app.exec();
}
