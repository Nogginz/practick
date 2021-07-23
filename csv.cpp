#include "csv.h"
#include <QFile>
#include <QString>
#include <QStringList>
#include <QList>
using namespace std;
csv::csv(QString filename){
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd()){
        line_buffer = file.readLine();
        lines_buffer = line_buffer.split(',');

    }
}
