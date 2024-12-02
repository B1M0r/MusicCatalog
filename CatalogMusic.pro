QT += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CatalogMusic
TEMPLATE = app

SOURCES += main.cpp \
    Track.cpp \
    FileManager.cpp \
    MediaManager.cpp \
    MainWindow.cpp \
    basedialog.cpp \
    edittrackdialog.cpp \
    formdialog.cpp \
    playlist.cpp \
    playlistdialog.cpp \
    playlistmanager.cpp \
    trackplayerdialog.cpp

HEADERS  += Track.h \
    FileManager.h \
    MediaManager.h \
    MainWindow.h \
    basedialog.h \
    edittrackdialog.h \
    formdialog.h \
    playlist.h \
    playlistdialog.h \
    playlistmanager.h \
    trackplayerdialog.h
