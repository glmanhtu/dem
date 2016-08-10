#include "filecontroller.h"
#include <QDebug>
#include <QFileDialog>
#include "gdal.h"
#include "gdal_priv.h"
#include "View/graphics.h"

FileController::FileController(QObject *parent): QObject(parent)
{    
    hasFile = false;
}

void FileController::setGraphics(GraphicsComposite *graphics)
{
    this->graphics = graphics;
}

void FileController::openFile()
{
    QString fileName = QFileDialog::getOpenFileName((Graphics*)graphics->getMainGraphics(),
        QString("Open Dem file"), "/home", QString("Image Files (*.dt0 *.dt1 *.dt2 *.tif *.ddf *.dem)"));
    GDALAllRegister();
    hasFile = true;
    QByteArray ba = fileName.toLatin1();
    const char *c_fileName = ba.data();
    GDALDataset* pFileDS = (GDALDataset*) GDALOpen(c_fileName, GA_ReadOnly);    
    demObject->setDataSet(pFileDS);
    graphics->updateGraphics();    
}

bool FileController::isOpenedFile()
{
    return hasFile;
}

void FileController::initAction()
{

}
void FileController::terminalAction()
{

}
QString FileController::getActionName()
{
    return "File.FileController";
}
bool FileController::loadOnBoot()
{
    return false;
}
bool FileController::requireDemObject()
{
    return true;
}
void FileController::setDemObject(DemInterface *dem)
{
    demObject = dem;
}

DemInterface* FileController::getDemObject()
{
    return demObject;
}

