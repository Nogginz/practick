#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QtSql>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("E:/SQLite/example");

    if (!db.open()) {
          qDebug() << db.lastError().text();
    }else{
        qDebug() << "ОТКРЫТО";
    }

    query = QSqlQuery(db);
    query.exec("SELECT COUNT(*) FROM list_of_activities;");
    query.next();
    int RowCount = query.value(0).toInt();

    ui->setupUi(this);
    ui->btn_start->setEnabled(false);
    int ColCount = csv_head.size();
    //int RowCount = csv_body.size();
    ui->list_of_activities->setColumnCount(1);
    ui->list_of_activities->setRowCount(RowCount);
    //qDebug() << RowCount;
    ui->list_of_activities->setColumnWidth(0,300);

    query.exec("SELECT * FROM list_of_activities");
    while(query.next()){
        for(int i=0;i<4;i++) buf += query.value(i).toString() + "\n";
        ui->list_of_activities->setRowHeight(query.at(),100);
        QTableWidgetItem *tab_item = new QTableWidgetItem();
        tab_item->setText(buf);
        tab_item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEnabled);
        ui->list_of_activities->setItem(query.at(),0,tab_item);
        buf = "";
    }

    QObject::connect(ui->list_of_activities,SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(slotCreateListOfGroup(QTableWidgetItem *)));

    ui->list_of_activities->verticalHeader()->hide();
    ui->list_of_activities->horizontalHeader()->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotCreateListOfGroup(QTableWidgetItem *tab_item)
{

    line_buffer = tab_item->text().remove("\r");
    lines_buffer = line_buffer.split("\n");
    lines_buffer = lines_buffer[3].split("/");
    int row_count=0;
    for(int i = 0;i<lines_buffer.size();i++){
        buf = "SELECT COUNT(\""+lines_buffer[i]+"\") FROM list_group WHERE \""+lines_buffer[i]+"\" IS NOT NULL AND \""+lines_buffer[i]+"\" IS NOT \"\";";
        query.exec(buf);
        query.next();
        row_count += query.value(0).toInt();
    }
    ui->list_group->setColumnCount(1);
    ui->list_group->setRowCount(row_count);
    ui->list_group->setColumnWidth(0,300);
    ui->list_group->setColumnWidth(1,1);
    ui->list_group->verticalHeader()->hide();
    ui->list_group->horizontalHeader()->hide();
    int count = -1;
    for(int i = 0;i<lines_buffer.size();i++){
        count++;
        QTableWidgetItem *new_tab_item = new QTableWidgetItem();
        new_tab_item->setText(lines_buffer[i]);
        new_tab_item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEnabled);
        ui->list_group->setItem(count,0,new_tab_item);
        query.exec("SELECT \""+lines_buffer[i]+"\" FROM list_group WHERE \""+lines_buffer[i]+"\" IS NOT NULL AND \""+lines_buffer[i]+"\" IS NOT \"\";");
        while(query.next()){
            if(query.value(0).toString()!=""){
                count++;
                QTableWidgetItem *new_tab_item = new QTableWidgetItem();
                new_tab_item->setText(query.value(0).toString());
                new_tab_item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
                new_tab_item->setCheckState(Qt::Unchecked);
                ui->list_group->setItem(count,0,new_tab_item);
                /*
                    Для отслеживания чекбокса можно использовать:
                    connect(ui->list_group,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(tableItemClicked(QTableWidgetItem *)));
                    Но в рамках данной работы возможность сохранять состояние чекбокса не предусмотрена,
                    поскольку используется всего две таблицы в БД.
                    Для добавления такой возможности как вариант можно создать таблицу
                    CREATE TABLE spisok_studentov(
                        ID INTEGER PRIMARY KEY AUTOINCREMENT,
                        student VARCHAR(50),
                        ngroup VARCHAR(50),
                        [date] VARCHAR(50)
                    );
                */

            }
        }
    }
}
