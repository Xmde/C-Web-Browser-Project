#include "mainwindow.h"
#include "ui_mainwindow.h"

//#define CPPHTTPLIB_OPENSSL_SUPPORT
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "httplib.h"

#include "QDebug"
#include <renderer.h>
#include <htmldata.h>
#include <QMessageBox>


MainProgramWindow::MainProgramWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->url->placeholderText().append("enter url");

    renderobj = new class renderer();

    urls = new QVector<QString>;

    backPresses = 0;
}

MainProgramWindow::~MainProgramWindow()
{
    delete ui;
}


void MainProgramWindow::on_load_clicked()
{
   loadLink(ui->url->text());

}

//loads a link and puts it in the list of pages you have gone to
void MainProgramWindow::loadLink(QString url){
    urls->append(url);
    loadPage(url);
    backPresses = 0;
}



//loads a page but does NOT put the url in the list of pages loaded
void MainProgramWindow::loadPage(QString url){

    //makes links change url
    ui->url->setText(url);

    const char *urlstd = url.toUtf8();
    httplib::Client cli(urlstd);
    //httplib::Client cli("http://inventobot.com");

    //Use your CA bundle
    //cli.set_ca_cert_path("./ca-bundle.crt");

    // Disable cert verification
    //cli.enable_server_certificate_verification(false);

    QString page = "<p>ERROR: PAGE COULD NOT BE LOADED<\p>";
    try {
        auto res = cli.Get("/");

        if(res.error() > 0){
            throw "invalid url";
        }
        qDebug() << QString::fromStdString(res->body);

        //ui->log->setText(QString::fromStdString(res->body));

        page = QString::fromStdString(res->body);
    }  catch (...) {
        QMessageBox::warning(this, tr("error"), tr("url could not be loaded"));
    }

    ui->log->append(page);

    //data for testing the renderer
    QVector<htmldata> dummydata = QVector<htmldata>();
    dummydata.append(htmldata(htmldata::text, "the link is " + url, "test"));
    dummydata.append(htmldata(htmldata::text, "the page is " + page, "test"));
    dummydata.append(htmldata(htmldata::text, "test", "test"));
    dummydata.append(htmldata(htmldata::link, "test link", "test"));
    dummydata.append(htmldata(htmldata::link, "tttttteeeeeessssstttttt", "test"));
    dummydata.append(htmldata(htmldata::text, "test", "test"));
    dummydata.append(htmldata(htmldata::text, "test", "test"));
    dummydata.append(htmldata(htmldata::text, "test", "test"));
    dummydata.append(htmldata(htmldata::text, "test", "test"));
    dummydata.append(htmldata(htmldata::text, "test", "test"));
    dummydata.append(htmldata(htmldata::text, "test", "test"));
    dummydata.append(htmldata(htmldata::text, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris consectetur dui risus, finibus consequat enim egestas eu. Donec pulvinar ex fringilla tincidunt iaculis. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Cras lacinia vel lectus ut convallis. Proin dignissim, risus id commodo finibus, dui sapien vestibulum dui, in facilisis nisl magna eget leo. Proin quis maximus eros. Aliquam vel malesuada risus. Morbi sit amet felis est. Cras porttitor in diam ut venenatis. Sed sollicitudin ut purus vitae aliquet. Pellentesque sagittis, justo vitae congue euismod, ante turpis faucibus quam, a iaculis neque neque id tortor. Morbi congue ex eget enim egestas, sit amet dignissim nisl ornare. Quisque quis congue tellus. Maecenas vel mi odio. Mauris in tristique turpis, eu vestibulum nibh. Maecenas porta lacus non lacinia tempor. Phasellus sodales ornare pretium. Maecenas vel placerat ex. Aenean dictum ultricies semper. Phasellus sed urna sed ante fringilla cursus. Mauris tristique viverra metus in laoreet. Mauris lacinia lorem nec ex faucibus pharetra ac sed elit. Nullam egestas pellentesque ante ut tincidunt. Nunc sagittis ligula ut vehicula suscipit. Maecenas finibus dolor vitae est dictum, nec tincidunt velit fermentum. Morbi et pharetra leo, nec egestas tortor. Curabitur commodo, dolor et venenatis luctus, odio est laoreet dui, vitae mattis dolor tellus eget massa. Etiam fermentum justo sit amet ligula tristique, vel vestibulum felis rutrum.", "test"));
    //dummydata.append(htmldata(htmldata::text, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "test"));
    renderobj->renderPage(ui->page, dummydata, this);

}


void MainProgramWindow::on_back_clicked()
{
    //allows you to go back
    backPresses++;
    int index = urls->length() - (backPresses+1);
    if(index < 0){
        QMessageBox::warning(this, tr("error"), tr("no page to go back to"));
    }
    else{
        QString url = urls->at(index);
        loadPage(url);
    }
}

//c++ is dumb
void MainProgramWindow::ConnectButtonToLink(QPushButton* b, QString url){
    connect(b, &QPushButton::clicked, this, [this, url](){loadLink(url);});
}
