#include "graphicsglobal.h"
#include "ui_widget.h"
#include "scrollviewport.h"

GraphicsGlobal::GraphicsGlobal(QWidget *parent) :
    QWidget(parent), ui(new Ui::GraphicsGlobal)
{
    setFixedSize(900, 600);
    setWindowTitle(tr("Dem Viewer"));
    graphics = new Graphics(this);
    QGridLayout *layout = new QGridLayout();
    layout->setHorizontalSpacing(0);
    ScrollViewport* scroll = new ScrollViewport(this);
    scroll->setViewport(graphics);
    QScrollArea* cameraModeParametersPanel_ = new QScrollArea(this);
    cameraModeParametersPanel_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cameraModeParametersPanel_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cameraModeParametersPanel_->setWidget(graphics);
    layout->addWidget(cameraModeParametersPanel_);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    ui->setupUi(this);
}

GraphicsGlobal::~GraphicsGlobal()
{
    delete ui;
}

Graphics* GraphicsGlobal::getGraphicsWidget()
{
    return graphics;
}
