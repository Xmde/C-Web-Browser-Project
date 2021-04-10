#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "httplib.h"
#include "QDebug"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#define WIN32_LEAN_AND_MEAN

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
    // HTTP
    const char *urlString = "https://google.com";//url->text().toUtf8();
    qDebug() << urlString;

    httplib::Client cli(urlString);


    // Use your CA bundle
    cli.set_ca_cert_path("./ca-bundle.crt");

    // Disable cert verification
    cli.enable_server_certificate_verification(false);

    //httplib::Client cli("http://inventobot.com");
    auto res = cli.Get("/");
    site->append(QString::fromStdString(res->body));

    log->appendHtml(QString::fromStdString(res->body));
}
