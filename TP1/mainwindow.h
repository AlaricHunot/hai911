#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void onAddNew();   // Slot pour ajouter une nouvelle fenêtre
    void onLoadOFF();  // Slot pour charger un fichier .off

private:
    QAction *loadOFFAction;  // Action pour le bouton de chargement de fichier .off
};

#endif // MAINWINDOW_H
