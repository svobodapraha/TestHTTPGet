#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QtNetwork>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void timerEvent(QTimerEvent *event);

private slots:
  void on_btnAsk_clicked();
  void managerFinished(QNetworkReply *reply);

  void on_btnAsk2_clicked();

  void on_btnClear_clicked();

  void on_pushAskSocket_clicked();

private:
  Ui::MainWindow *ui;
  QNetworkAccessManager *manager;
  QNetworkRequest request;
  int iMainTimerID;

};

#endif // MAINWINDOW_H
