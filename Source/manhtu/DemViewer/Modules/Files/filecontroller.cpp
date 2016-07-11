#include "filecontroller.h"
#include <QDebug>

FileController::FileController(QObject *parent): QObject(parent)
{

}
void FileController::openFile()
{
    qDebug() << "At Filecontroller::openFile";
}

void FileController::initAction()
{

}
void FileController::terminalAction()
{

}
QString FileController::getActionName()
{
    return QString("File.FileController");
}
bool FileController::loadOnBoot()
{
    return false;
}
bool FileController::requireDemObject()
{
    return false;
}
void FileController::setDemObject(DemInterface *)
{

}

