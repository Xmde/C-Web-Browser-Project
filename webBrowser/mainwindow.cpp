#include "mainwindow.h"
#include "ui_mainwindow.h"


#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "httplib.h"


#include "QDebug"

//#define CPPHTTPLIB_OPENSSL_SUPPORT

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->url->placeholderText().append("enter url");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_load_clicked()
{
    // HTTP only
    const char *urlString = ui->url->text().toUtf8();

    httplib::Client cli(urlString);


    // Use your CA bundle
//    cli.set_ca_cert_path("./ca-bundle.crt");

//    // Disable cert verification
//    cli.enable_server_certificate_verification(false);

    //httplib::Client cli("http://inventobot.com");
    auto res = cli.Get("/");
    //ui->log->setText(QString::fromStdString(res->body));

    ui->log->append(QString::fromStdString(res->body));
}
