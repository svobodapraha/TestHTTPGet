#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  manager = new QNetworkAccessManager();
  QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(managerFinished(QNetworkReply*)));


  //timer
#define MAIN_TIMER_PERIOD 5000
  //iMainTimerID = this->startTimer(MAIN_TIMER_PERIOD);

}

void MainWindow::timerEvent(QTimerEvent * event)
{
  static int iCounter;
  iCounter++;
  if (event->timerId() == iMainTimerID)
  {
    qDebug() << "MAIN" << MAIN_TIMER_PERIOD << this->objectName();
    //this->on_btnAsk_clicked();

    QUrlQuery LogQuery;
    LogQuery.addQueryItem("Number", QString::number(iCounter));

    QUrl LogUrl("http://svobodav.PHP5.cz/test_get.php/");
    //QUrl LogUrl("http://localhost");
    //QUrl LogUrl("http://localhost/myFile");
    LogUrl.setQuery(LogQuery.query());

    QNetworkRequest LoqRequest(LogUrl);

    manager->clearAccessCache();
    manager->get(LoqRequest);

  }
}


MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_btnAsk_clicked()
{
  //request.setUrl(QUrl("http://svobodav.php5.cz"));
  request.setUrl(QUrl("http://localhost"));
  QNetworkReply* tmpReply = manager->get(request);
  QThread::msleep(1000);
  tmpReply->abort();
  tmpReply->deleteLater();
}


void MainWindow::managerFinished(QNetworkReply *reply)
{
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();

    qDebug() << answer;
    reply->deleteLater();
}

void MainWindow::on_btnAsk2_clicked()
{
    //QUrl LogUrl("http://localhost");
    QUrl LogUrl("http://svobodav.PHP5.cz/test_get.php/");
    QUrlQuery LogQuery;
    LogQuery.addQueryItem("Number", "31");
    LogUrl.setQuery(LogQuery.query());
    QNetworkRequest LoqRequest(LogUrl);
    manager->clearAccessCache();
    manager->get(LoqRequest);
}


void MainWindow::on_btnClear_clicked()
{
    manager->clearAccessCache();
}

void MainWindow::on_pushAskSocket_clicked()
{
    static int iCounter;
    iCounter++;

    QTcpSocket *insertData = new QTcpSocket(this);
    //insertData->connectToHost("localhost", 80);
    insertData->connectToHost("svobodav.PHP5.cz", 80);
    qDebug() << "Trying to Connect";
    bool boResult;
    boResult = insertData->waitForConnected(5000);
    if (boResult)
    {
      qDebug() << "Connected";
      QString asSendString = QString("GET /test_get.php?Number=%1 HTTP/1.1\r\n").arg(iCounter + 1000);
      insertData->write(asSendString.toLatin1());
    //  insertData->write("Connection: Keep-Alive\r\n");
    //  insertData->write("Accept-Encoding: gzip, deflate\r\n");
    //  insertData->write("User-Agent: Mozilla/5.0\r\n");
      insertData->write("Host: svobodav.PHP5.cz\r\n");
      insertData->write("\r\n");
      insertData->waitForBytesWritten(2000);
    //  insertData->waitForReadyRead(3000);
    //  qDebug() << "Reading: " << insertData->bytesAvailable();
    //  qDebug() << insertData->readAll();

      insertData->close();
    }
    else
    {
      qDebug() << "Not Connected";
    }

}
