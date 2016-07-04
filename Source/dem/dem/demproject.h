#ifndef DEMPROJECT_H
#define DEMPROJECT_H

#include <QWidget>
#include <QMenuBar>
#include "helper.h"
#include "glwidget.h"
#include <QGridLayout>
#include <QScrollArea>

namespace Ui {
class DemProject;
}

class DemProject : public QWidget
{
    Q_OBJECT
public:
    explicit DemProject(QWidget *parent = 0);
    QAction *openAct;
    QString fileName;

    void openFile();
    ~DemProject();

private:
    void createActions();
    Helper helper;
    GLWidget *openGL;
    GDALDataset *pFileDS;
    QGridLayout *layout;
    Ui::DemProject *ui;
};

#endif // DEMPROJECT_H
