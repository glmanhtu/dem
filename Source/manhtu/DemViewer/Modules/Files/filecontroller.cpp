#include "filecontroller.h"
#include <QDebug>
#include <QFileDialog>
#include "gdal.h"
#include "gdal_priv.h"
#include "View/graphics.h"
#include <QFileInfo>

FileController::FileController(QObject *parent): QObject(parent)
{    
    hasFile = false;
}

void FileController::setGraphics(GraphicsComposite *graphics)
{
    this->graphics = graphics;
}

bool fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    return check_file.exists() && check_file.isFile();
}

void FileController::openFile()
{
    QString fileName = QFileDialog::getOpenFileName((Graphics*)graphics->getMainGraphics(),
        QString("Open Dem file"), "/home", QString("Image Files (*.dt0 *.dt1 *.dt2 *.tif *.ddf *.dem)"));
    if (fileExists(fileName)) {
        GDALAllRegister();
        hasFile = true;
        QByteArray ba = fileName.toLatin1();
        const char *c_fileName = ba.data();
        GDALDataset* pFileDS = (GDALDataset*) GDALOpen(c_fileName, GA_ReadOnly);
        demObject->setDataSet(pFileDS);
        graphics->updateGraphics();
    }
}

void FileController::setActionPerform(ActionListener *)
{

}

void FileController::readFile()
{

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

