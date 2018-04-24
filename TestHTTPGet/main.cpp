#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
  MainWindow w;
  w.show();

  return a.exec();
}
