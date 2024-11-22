#include "offmesh.h"
#include <QFile>
#include <QTextStream>

OFFMesh::OFFMesh(const QString &fileName)
    : vertexBuffer(QOpenGLBuffer::VertexBuffer),
      indexBuffer(QOpenGLBuffer::IndexBuffer)
{
    loadOFF(fileName);
}

void OFFMesh::loadOFF(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString header;
    in >> header;

    if (header != "OFF") {
        qDebug() << "Ce fichier n'est pas un fichier OFF valide.";
        return;
    }

    int numVertices, numFaces, numEdges;
    in >> numVertices >> numFaces >> numEdges;

    QVector<QVector3D> vertices;
    QVector<int> indices;

    // Lire les sommets
    for (int i = 0; i < numVertices; ++i) {
        float x, y, z;
        in >> x >> y >> z;
        vertices.append(QVector3D(x, y, z));
    }

    // Lire les faces
    for (int i = 0; i < numFaces; ++i) {
        int numVerticesInFace, v1, v2, v3;
        in >> numVerticesInFace >> v1 >> v2 >> v3;
        indices.append(v1);
        indices.append(v2);
        indices.append(v3);
    }

    file.close();

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.allocate(vertices.constData(), vertices.size() * sizeof(QVector3D));

    indexBuffer.create();
    indexBuffer.bind();
    indexBuffer.allocate(indices.constData(), indices.size() * sizeof(int));
}

void OFFMesh::draw(QOpenGLShaderProgram *program)
{
    vertexBuffer.bind();
    indexBuffer.bind();

    int vertexLocation = program->attributeLocation("vertex");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));

    glDrawElements(GL_TRIANGLES, indexBuffer.size() / sizeof(int), GL_UNSIGNED_INT, 0);
}
