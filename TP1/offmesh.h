#ifndef OFFMESH_H
#define OFFMESH_H

#include <QOpenGLBuffer>
#include <QVector>
#include <QVector3D>
#include <QOpenGLShaderProgram>

class OFFMesh
{
public:
    OFFMesh(const QString &fileName);
    void draw(QOpenGLShaderProgram *program);

private:
    void loadOFF(const QString &fileName);

    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer indexBuffer;
};

#endif // OFFMESH_H
