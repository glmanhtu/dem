#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include "vertex.h"

class QOpenGLShaderProgram;

class Window : public QOpenGLWidget,
               protected QOpenGLFunctions
{
  Q_OBJECT

// OpenGL Events
public:
  void initializeGL();
  void resizeGL(int width, int height);
  void paintGL();
protected slots:
  void teardownGL();

private:
  // OpenGL State Information
  QOpenGLBuffer m_vertex;
  QOpenGLVertexArrayObject m_object;
  QOpenGLShaderProgram *m_program;
  std::vector<Vertex> vectexs;

  // Private Helpers
  void printVersionInformation();
};

#endif // WINDOW_H
