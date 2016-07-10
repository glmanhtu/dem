#include "filegraphics.h"

FileGraphics::FileGraphics(FileController* fileController)
{
    fcontroller = fileController;
}

void FileGraphics::initial()
{
    QAction* action = createQAction(QString("Open DEM File"));
    addMenu(QString("File"), action);
    QIODevice::connect(action, &QAction::triggered, fcontroller, &FileController::openFile);
}

FileGraphics::~FileGraphics()
{
}

void FileGraphics::initializeGL()
{


}
void FileGraphics::paintGL()
{

}
void FileGraphics::resizeGL(int width, int height)
{

}
