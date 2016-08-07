#ifndef DEMMODEL_H
#define DEMMODEL_H
#include "deminterface.h"

class DemModel : public DemInterface
{
private:
    QVector<GLfloat> m_data;
    GDALDataset* dataSet;
    int m_count;
public:
    DemModel();
    int count();
    int vertexCount();
    const GLfloat *constData();
    void add(const QVector3D &v, const QVector3D &n);
    void clean();
    void setSize(int);
    void quad(QVector3D v1, QVector3D v2, QVector3D v3, QVector3D v4);
    void tri(QVector3D v1, QVector3D v2, QVector3D v3);

    void setGDALDataSet(GDALDataset *dataSet);
    GDALDataset *getGDALDataSet();
};

#endif // DEMMODEL_H
