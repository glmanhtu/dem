#include "filecontroller.h"
#include <QDebug>

FileController::FileController(QObject *parent): QObject(parent)
{

}
void FileController::openFile()
{
    qDebug() << "At Filecontroller::openFile";
}

