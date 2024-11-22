#include "mesh.h"
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLVertexArrayObject>
struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

Mesh::Mesh() : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();
    arrayBuf.create();
    indexBuf.create();
    initCubeGeometry();
}

Mesh::~Mesh()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void Mesh::initCubeGeometry(){
      VertexData vertices[] = {
          //face 1
          {QVector3D(-0.1f, -0.1f,  0.1f), QVector2D(0.0f, 0.0f)},  
          {QVector3D( 0.1f, -0.1f,  0.1f), QVector2D(0.33f, 0.0f)},
          {QVector3D(-0.1f,  0.1f,  0.1f), QVector2D(0.0f, 0.5f)}, 
          {QVector3D( 0.1f,  0.1f,  0.1f), QVector2D(0.33f, 0.5f)}, 
          //face 2
          {QVector3D( 0.1f, -0.1f,  0.1f), QVector2D( 0.0f, 0.5f)},
          {QVector3D( 0.1f, -0.1f, -0.1f), QVector2D(0.33f, 0.5f)}, 
          {QVector3D( 0.1f,  0.1f,  0.1f), QVector2D(0.0f, 1.0f)},  
          {QVector3D( 0.1f,  0.1f, -0.1f), QVector2D(0.33f, 1.0f)}, 
          //face 3
          {QVector3D( 0.1f, -0.1f, -0.1f), QVector2D(0.66f, 0.5f)}, 
          {QVector3D(-0.1f, -0.1f, -0.1f), QVector2D( 1.0f, 0.5f)},  
          {QVector3D( 0.1f,  0.1f, -0.1f), QVector2D(0.66f,  1.0f)}, 
          {QVector3D(-0.1f,  0.1f, -0.1f), QVector2D( 1.0f,  1.0f)},  
          //face 4
          {QVector3D(-0.1f, -0.1f, -0.1f), QVector2D(0.66f, 0.0f)}, 
          {QVector3D(-0.1f, -0.1f,  0.1f), QVector2D( 1.0f, 0.0f)},  
          {QVector3D(-0.1f,  0.1f, -0.1f), QVector2D(0.66f, 0.5f)}, 
          {QVector3D(-0.1f,  0.1f,  0.1f), QVector2D( 1.0f, 0.5f)},  
          //face 5
          {QVector3D(-0.1f, -0.1f, -0.1f), QVector2D(0.33f, 0.0f)}, 
          {QVector3D( 0.1f, -0.1f, -0.1f), QVector2D(0.66f, 0.0f)}, 
          {QVector3D(-0.1f, -0.1f,  0.1f), QVector2D(0.33f, 0.5f)}, 
          {QVector3D( 0.1f, -0.1f,  0.1f), QVector2D(0.66f, 0.5f)}, 
          //face 6
          {QVector3D(-0.1f,  0.1f,  0.1f), QVector2D(0.33f, 0.5f)},
          {QVector3D( 0.1f,  0.1f,  0.1f), QVector2D(0.66f, 0.5f)}, 
          {QVector3D(-0.1f,  0.1f, -0.1f), QVector2D(0.33f,  1.0f)}, 
          {QVector3D( 0.1f,  0.1f, -0.1f), QVector2D(0.66f,  1.0f)}  
      };

      GLushort indices[] = {
           0,  1,  2,  3,  3,     //face 1
           4,  4,  5,  6,  7,  7, //face 2
           8,  8,  9, 10, 11, 11, //face 3
          12, 12, 13, 14, 15, 15, //face 4
          16, 16, 17, 18, 19, 19, //face 5
          20, 20, 21, 22, 23      //face 6
      };

      arrayBuf.bind();
      arrayBuf.allocate(vertices, 24 * sizeof(VertexData));
      indexBuf.bind();
      indexBuf.allocate(indices, 34 * sizeof(GLushort));
}

void Mesh::drawCubeGeometry(QOpenGLShaderProgram *program){
       arrayBuf.bind();
       indexBuf.bind();
       quintptr offset = 0;
       int vertexLocation = program->attributeLocation("vertex");
       program->enableAttributeArray(vertexLocation);
       program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
       offset += sizeof(QVector3D);
       int texcoordLocation = program->attributeLocation("normal");
       program->enableAttributeArray(texcoordLocation);
       program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));
       glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, nullptr);
       arrayBuf.release();
       indexBuf.release();
}
