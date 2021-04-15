#include "mainwindow.h"
#include "ui_mainwindow.h"

//#define CPPHTTPLIB_OPENSSL_SUPPORT
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "httplib.h"

#include "QDebug"
#include <renderer.h>
#include <htmldata.h>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->url->placeholderText().append("enter url");

    renderobj = new class renderer();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_load_clicked()
{
    loadPage(ui->url->text());

}

void MainWindow::loadPage(QString url){

    const char *urlstd = url.toUtf8();
    //httplib::Client cli(url);
    httplib::Client cli("http://inventobot.com");

    //Use your CA bundle
    //cli.set_ca_cert_path("./ca-bundle.crt");

    // Disable cert verification
    //cli.enable_server_certificate_verification(false);

    try {
        auto res = cli.Get("/");
        qDebug() << QString::fromStdString(res->body);

        //ui->log->setText(QString::fromStdString(res->body));

        ui->log->append(QString::fromStdString(res->body));
    }  catch (_exception e) {
        qDebug() << "failed due to " << e.name;
    }

    QVector<htmldata> dummydata = QVector<htmldata>();
    dummydata.append(htmldata(htmldata::text, "test", "test"));
    dummydata.append(htmldata(htmldata::link, "test link", "test"));
    dummydata.append(htmldata(htmldata::link, "tttttteeeeeessssstttttt", "test"));

    renderobj->renderPage(ui->page, dummydata);

}

