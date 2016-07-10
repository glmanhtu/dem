#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H
#include <QObject>

class FileController : public QObject
{
Q_OBJECT
public:
    FileController(QObject *parent = 0);
    void openFile();
};

#endif // FILECONTROLLER_H
