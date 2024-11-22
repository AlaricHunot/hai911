#include "glwidget.h"
#include "window.h"
#include "mainwindow.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>  // Inclure pour ouvrir la boîte de dialogue de sélection de fichier

Window::Window(MainWindow *mw)
    : mainWindow(mw)
{
    glWidget = new GLWidget;

    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();

    connect(xSlider, &QSlider::valueChanged, glWidget, &GLWidget::setXRotation);
    connect(ySlider, &QSlider::valueChanged, glWidget, &GLWidget::setYRotation);
    connect(zSlider, &QSlider::valueChanged, glWidget, &GLWidget::setZRotation);

    connect(glWidget, &GLWidget::XRotationChanged, xSlider, &QSlider::setValue);
    connect(glWidget, &GLWidget::YRotationChanged, ySlider, &QSlider::setValue);
    connect(glWidget, &GLWidget::ZRotationChanged, zSlider, &QSlider::setValue);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(glWidget);
    container->addWidget(xSlider);
    container->addWidget(ySlider);
    container->addWidget(zSlider);

    // Ajouter un bouton pour charger un fichier OFF
    loadOFFBtn = new QPushButton(tr("Charger .off"), this);
    connect(loadOFFBtn, &QPushButton::clicked, this, &Window::onLoadOFFButtonClicked);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);
    
    // Ajouter le bouton dans l'interface principale
    mainLayout->addWidget(loadOFFBtn);  // Ajouter le bouton pour charger un fichier OFF
    dockBtn = new QPushButton(tr("Undock"), this);
    connect(dockBtn, &QPushButton::clicked, this, &Window::dockUndock);
    mainLayout->addWidget(dockBtn);

    setLayout(mainLayout);

    xSlider->setValue(15 * 16);
    ySlider->setValue(345 * 16);
    zSlider->setValue(0 * 16);

    setWindowTitle(tr("Qt OpenGL"));
}

QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void Window::dockUndock()
{
    if (parent()) {
        setParent(0);
        setAttribute(Qt::WA_DeleteOnClose);
        move(QApplication::desktop()->width() / 2 - width() / 2,
             QApplication::desktop()->height() / 2 - height() / 2);
        dockBtn->setText(tr("Dock"));
        show();
    } else {
        if (!mainWindow->centralWidget()) {
            if (mainWindow->isVisible()) {
                setAttribute(Qt::WA_DeleteOnClose, false);
                dockBtn->setText(tr("Undock"));
                mainWindow->setCentralWidget(this);
            } else {
                QMessageBox::information(0, tr("Cannot dock"), tr("Main window already closed"));
            }
        } else {
            QMessageBox::information(0, tr("Cannot dock"), tr("Main window already occupied"));
        }
    }
}

// Slot pour le bouton de chargement de fichier OFF
void Window::onLoadOFFButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open OFF File"), "", tr("OFF Files (*.off)"));
    if (!fileName.isEmpty()) {
        loadOFF(fileName);  // Appeler la fonction pour charger le fichier OFF
    }
}

void Window::loadOFF(const QString &fileName)
{
    glWidget->loadOFF(fileName);  // Charger le fichier OFF dans le widget OpenGL
}
