#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include "mesh.h"
#include "offmesh.h"  // Inclusion de la nouvelle classe pour les fichiers OFF
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    static bool isTransparent() { return m_transparent; }
    static void setTransparent(bool t) { m_transparent = t; }

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void cleanup();
    void loadOFF(const QString &fileName);  // Nouveau slot pour charger un fichier OFF

signals:
    void XRotationChanged(int angle);
    void YRotationChanged(int angle);
    void ZRotationChanged(int angle);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void setupVertexAttribs();
    bool m_core;
    int m_xRot;
    int m_yRot;
    int m_zRot;
    QPoint m_last_position;
    QOpenGLShaderProgram *m_program;
    int m_mvp_matrix_loc;
    int m_normal_matrix_loc;
    int m_light_pos_loc;
    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;
    QMatrix4x4 m_model;
    static bool m_transparent;
    Mesh *mesh = nullptr;  // Cube par défaut
    OFFMesh *offMesh = nullptr;  // OFFMesh pour gérer les fichiers OFF
};

#endif // GLWIDGET_H
