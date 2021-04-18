#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <renderer.h>
#include <QVector>
#include <QPushButton>
#include <parser.h>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainProgramWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainProgramWindow(QWidget *parent = nullptr);
    ~MainProgramWindow();
    void loadPage(QString url);
    void loadLink(QString url);
    void ConnectButtonToLink(QPushButton* b, QString url);

private slots:
    void on_load_clicked();

    void on_back_clicked();

private:
    Ui::MainWindow *ui;
    //i dont understand c++ en
    class renderer* renderobj;
    QVector<QString>* urls;
    int backPresses;


};
#endif // MAINWINDOW_H
