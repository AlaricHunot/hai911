#include "mainwindow.h"
#include "window.h"
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow()
{
    QMenuBar *menuBar = new QMenuBar;
    QMenu *menuWindow = menuBar->addMenu(tr("&Window"));

    // Ajouter une action pour créer une nouvelle fenêtre
    QAction *addNew = new QAction(menuWindow);
    addNew->setText(tr("Add new"));
    menuWindow->addAction(addNew);
    connect(addNew, &QAction::triggered, this, &MainWindow::onAddNew);

    // Ajouter une action pour charger un fichier .off
    loadOFFAction = new QAction(menuWindow);
    loadOFFAction->setText(tr("Charger .off"));
    menuWindow->addAction(loadOFFAction);
    connect(loadOFFAction, &QAction::triggered, this, &MainWindow::onLoadOFF);

    setMenuBar(menuBar);
    onAddNew();
}

void MainWindow::onAddNew()
{
    if (!centralWidget())
        setCentralWidget(new Window(this));
    else
        QMessageBox::information(0, tr("Cannot add new window"), tr("Already occupied. Undock first."));
}

// Fonction pour charger un fichier .off
void MainWindow::onLoadOFF()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open OFF File"), "", tr("OFF Files (*.off)"));
    if (!fileName.isEmpty()) {
        dynamic_cast<Window*>(centralWidget())->loadOFF(fileName);
    }
}
