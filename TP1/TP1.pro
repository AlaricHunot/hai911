MOC_DIR = ./moc
OBJECTS_DIR = ./obj

INCLUDEPATH += $$PWD

HEADERS       = glwidget.h \
                window.h \
                mainwindow.h \
                logo.h \
                offmesh.cpp \
                mesh.h
SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
                mainwindow.cpp \
                logo.cpp \
                offmesh.cpp \
                mesh.cpp

RESOURCES += \
    shaders.qrc

QT           += widgets


