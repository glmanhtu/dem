/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "glwidget.h"
#include "helper.h"

#include <QPainter>
#include <QTimer>
#include <QDebug>
#include "meshing.h"
//! [0]
GLWidget::GLWidget(Helper *helper, QWidget *parent)
    : QOpenGLWidget(parent), helper(helper)
{
    setAutoFillBackground(false);
}

void GLWidget::animate()
{
    update();
}
void GLWidget::setDEMObject(GDALDataset *ds)
{
    this->pDataset = ds;


//    int rows, cols;
//    double transform[6];
//    cols = pDataset->GetRasterXSize();
//    rows = pDataset->GetRasterYSize();
//    setFixedSize(cols, rows);
//    int channels = pDataset->GetRasterCount();
//    pDataset->GetGeoTransform(transform);

//    glGenTextures(1, &texture[0]);
//    glBindTexture(GL_TEXTURE_2D, texture[0]);

//    for (int i = 1; i <= channels; ++i)
//    {
//        // Fetch the band
//        GDALRasterBand* band = pDataset->GetRasterBand(i);
//        std::vector<float> band_data(cols*rows);

//        // Read the data
//        band->RasterIO( GF_Read, 0, 0,
//                        cols, rows,
//                        band_data.data(),
//                        cols, rows,
//                        GDT_Float32,
//                        0, 0);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cols, rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, band_data.data());
//    }
//    std::vector<float> band_data = m->createVertexArray();
//    glEnableClientState(GL_VERTEX_ARRAY);

//    glVertexPointer(3, GL_FLOAT, 0, band_data.data());
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cols, rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, band_data.data());
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//    glBindTexture( GL_TEXTURE_2D, 0 );
}



void GLWidget::initializeGL()
{
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    int WWIDTH = this->width();
    int WHEIGHT = this->height();

    glClearColor(0, 0, 0, 1);

    glClearDepth(1.0f);

    glViewport(0, 0, WWIDTH, WHEIGHT);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(0, WWIDTH, WHEIGHT, 0, 1, -1);

    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintGL()
{
    if (pDataset != NULL) {

//            GLfloat colors[] = {
//                1.0f, 0.0f, 0.0f,
//                0.0f, 1.0f, 0.0f,
//                0.0f, 0.0f, 1.0f
//            };
//                Meshing* m = new Meshing(pDataset);
//                std::vector<float> band_data = m->createVertexArray();
//            glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, band_data.data());
//            //glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

//            glEnableVertexAttribArray(0);
//            glEnableVertexAttribArray(1);

//            glDrawArrays(GL_TRIANGLES, 0, 3);

//            glDisableVertexAttribArray(1);
//            glDisableVertexAttribArray(0);
//        glShadeModel( GL_FLAT );
//        glEnable(GL_LIGHTING);
//        glEnable(GL_LIGHT0);
//        glEnable(GL_DEPTH_TEST);
//        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f);
//                glColor3f(0.5, 0.5, 0);
//        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT  );
////        glMatrixMode( GL_PROJECTION );
//        glLoadIdentity();
        Meshing* m = new Meshing(pDataset);
        std::vector<float> band_data = m->createVertexArray();
//        glEnableClientState(GL_VERTEX_ARRAY);
//        glVertexPointer(3, GL_FLOAT, 0, band_data.data());
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//        glDisableClientState(GL_VERTEX_ARRAY);
        glPointSize(5.0f);
            glBegin(GL_POINTS);
            for (int i=0; i<band_data.size(); i=i+3){
                float x = band_data[i];
                float y = band_data[i+1];
                float z = band_data[i+2];
                glVertex3f(x, y, z); // origin of the FIRST line
            }
            glEnd( );
////        glEnable(GL_TEXTURE_2D);

////        glBindTexture(GL_TEXTURE_2D, texture[0]);
//        glBegin(GL_QUADS);
//        glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
//        glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
//        glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
//        glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
//        glEnd();
//        glDisable(GL_TEXTURE_2D);

//        glFlush();

//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    }


//    glBegin(GL_TRIANGLES);
//        glColor3f(1.0, 0.0, 0.0);
//        glVertex3f(-0.5, -0.5, 0);
//        glColor3f(0.0, 1.0, 0.0);
//        glVertex3f( 0.5, -0.5, 0);
//        glColor3f(0.0, 0.0, 1.0);
//        glVertex3f( 0.0,  0.5, 0);
//    glEnd();

//    glBegin(GL_POINTS);
//    glVertex3f(100.0f, 100.0f, -25.0f);
//    glEnd( );

    // next code will draw a line at starting and ending coordinates specified by glVertex3f
//    glBegin(GL_LINES);
//    glVertex3f(100.0f, 100.0f, 0.0f); // origin of the line
//    glVertex3f(200.0f, 140.0f, 5.0f); // ending point of the line
//    glEnd( );

//    // the following code draws a triangle
//    glBegin(GL_TRIANGLES);
//    glVertex3f(100.0f, 100.0f, 0.0f);
//    glVertex3f(150.0f, 100.0f, 0.0f);
//    glVertex3f(125.0f, 50.0f, 0.0f);
//    glEnd( );

//    // this code will draw two lines "at a time" to save
//    // the time it takes to call glBegin and glEnd.

//    glBegin(GL_LINES);
//    glVertex3f(100.0f, 100.0f, 0.0f); // origin of the FIRST line
//    glVertex3f(200.0f, 140.0f, 5.0f); // ending point of the FIRST line
//    glVertex3f(120.0f, 170.0f, 10.0f); // origin of the SECOND line
//    glVertex3f(240.0f, 120.0f, 5.0f); // ending point of the SECOND line
//    glEnd( );
}

void GLWidget::resizeGL(int w, int h)
{

}

GLWidget::~GLWidget() {

}
