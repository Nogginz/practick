#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>
#include <vector>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QList>
#include <QVector>
#include <QTableWidgetItem>
#include <QtSql>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slotCreateListOfGroup(QTableWidgetItem *tab_item);
private:
    QFile file;
    QString filename;
    QVector <QVector<QString>> csv_body;
    QVector <QString> csv_head;
    QStringList lines_buffer;
    QString line_buffer;
    Ui::MainWindow *ui;
    QSqlQuery query;
    QString buf;
signals:
    void signalFromItem(QString name);
};
#endif // MAINWINDOW_H
