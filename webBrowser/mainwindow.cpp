#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "httplib.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //gets the pointers for the ui elements we need to read data from
    url = ui->centralwidget->children().at(0)->findChild<QVBoxLayout*>("controls")->findChild<QLineEdit*>("url");
    log = ui->centralwidget->children().at(0)->findChild<QPlainTextEdit*>("log");
    site = ui->centralwidget->children().at(0)->findChild<QTextEdit*>("site");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_load_clicked()
{
    // HTTPS
    //httplib::Client cli(url->text().toUtf8());

    httplib::Client cli("https://inventobot.com");

    auto res = cli.Get("/");
    site->append(QString::fromStdString(res->body));

    log->appendHtml(QString::fromStdString(res->body));
}
