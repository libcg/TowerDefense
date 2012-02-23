#include "game.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  Game game;

  app.setApplicationName(QString("TowerDefense"));

  game.show();

  return app.exec();
}
