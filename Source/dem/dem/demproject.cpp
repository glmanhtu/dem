#include "demproject.h"
#include "ui_demproject.h"
#include <QDebug>
#include <QFileDialog>
#include "gdal.h"
#include "gdal_priv.h"
#include <QLabel>

DemProject::DemProject(QWidget *parent) :
    QWidget(parent), ui(new Ui::DemProject)
{
    setFixedSize(900, 600);
    setWindowTitle(tr("Dem Viewer"));
    createActions();
    QMenuBar *menu = new QMenuBar(parent);
    QMenu* file = new QMenu("File");

    file->addAction(openAct);

    menu->addMenu(file);
    openGL = new GLWidget(&helper, this);

    layout = new QGridLayout;
    layout->setHorizontalSpacing(0);
    QScrollArea* cameraModeParametersPanel_ = new QScrollArea();
    //cameraModeParametersPanel_->setFixedSize(900, 600);
    cameraModeParametersPanel_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cameraModeParametersPanel_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cameraModeParametersPanel_->setWidget(openGL);
    layout->addWidget(cameraModeParametersPanel_);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    ui->setupUi(this);
}

void DemProject::createActions()
{
    openAct = new QAction(tr("&Open"), this);
    openAct->setStatusTip(tr("Open a dem file"));
    connect(openAct, &QAction::triggered, this, &DemProject::openFile);
}

void DemProject::openFile()
{
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open Dem file"), "/home", tr("Image Files (*.dt0 *.dt1 *.dt2 *.tif)"));
    qDebug() << "File name: " << fileName;
    GDALAllRegister();
    QByteArray ba = fileName.toLatin1();
    const char *c_fileName = ba.data();
    pFileDS = (GDALDataset*) GDALOpen(c_fileName, GA_ReadOnly);

    openGL->setDEMObject(pFileDS);
    openGL->animate();
}


DemProject::~DemProject()
{
    if (layout != NULL) {
        delete layout;
    }
    if (openAct != NULL) {
        delete openAct;
    }
    if (openGL != NULL) {
        delete openGL;
    }
    if (pFileDS != NULL) {
        GDALClose((GDALDatasetH)pFileDS);
    }
    delete ui;
}
