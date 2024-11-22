#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QSlider;
class QPushButton;
QT_END_NAMESPACE

class GLWidget;
class MainWindow;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(MainWindow *mw);
    void loadOFF(const QString &fileName);  // Fonction pour charger un fichier OFF

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void dockUndock();
    void onLoadOFFButtonClicked();  // Slot pour charger un fichier OFF avec le bouton

private:
    QSlider *createSlider();

    GLWidget *glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QPushButton *dockBtn;
    QPushButton *loadOFFBtn;  // Nouveau bouton pour charger un fichier OFF
    MainWindow *mainWindow;
};

#endif // WINDOW_H
