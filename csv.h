#ifndef CSV_H
#define CSV_H
#include <iostream>
#include <vector>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QList>
#include <QVector>
using namespace std;
class csv
{
private:
    QFile file;
    QString filename;
    QVector <QVector<QString>> csv_body;
    QVector <QString> csv_head;
    QStringList lines_buffer;
    QString line_buffer;
public:
    csv(QString filename);
};

#endif // CSV_H
