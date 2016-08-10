#include "demmodel.h"


DemModel::DemModel() {
    m_data.resize(1);
}

int DemModel::count() {
    m_count;
}

int DemModel::vertexCount() {
    return m_count/6;
}
const GLfloat* DemModel::constData() {
    return m_data.constData();
}

void DemModel::add(const QVector3D &v, const QVector3D &n)
{
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    m_count += 6;
}

void DemModel::setSize(int size) {
    m_data.resize(size);
}

void DemModel::quad(QVector3D v1, QVector3D v2, QVector3D v3, QVector3D v4)
{
    QVector3D n = QVector3D::normal(
                QVector3D(v4.x() - v1.x(), v4.y() - v1.y(), 0.0f),
                QVector3D(v2.x() - v1.x(), v2.y() - v1.y(), 0.0f)
                );

    add(QVector3D(v1.x(), v1.y(), -0.05f), n);
    add(QVector3D(v4.x(), v4.y(), -0.05f), n);
    add(QVector3D(v2.x(), v2.y(), -0.05f), n);

    add(QVector3D(v3.x(), v3.y(), -0.05f), n);
    add(QVector3D(v2.x(), v2.y(), -0.05f), n);
    add(QVector3D(v4.x(), v4.y(), -0.05f), n);

}

void DemModel::tri(QVector3D v1, QVector3D v2, QVector3D v3)
{
    QVector3D n = QVector3D::normal(
                QVector3D(v3.x() - v1.x(), v3.y() - v1.y(), 0.0f),
                QVector3D(v2.x() - v1.x(), v2.y() - v1.y(), 0.0f)
                );

    add(QVector3D(v1.x(), v1.y(), -0.05f), n);
    add(QVector3D(v3.x(), v3.y(), -0.05f), n);
    add(QVector3D(v2.x(), v2.y(), -0.05f), n);
}

GDALDataset* DemModel::getGDALDataSet()
{
    return dataSet;
}

void DemModel::setGDALDataSet(GDALDataset *dataSet)
{
    this->dataSet = dataSet;
}

void DemModel::clean()
{
    m_data.clear();
}
