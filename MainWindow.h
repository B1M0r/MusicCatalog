#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QObject>
#include "MediaManager.h"
#include "PlaylistManager.h"

namespace Ui {
class MainWindow;
}

// Главное окно приложения, отображает список треков и основные функции
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // Конструктор и деструктор
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    // Слот для отображения информации о треке (только чтение)
    void showReadonlyTrackDetails(QListWidgetItem* item);


    // Загрузка треков в виджет списка
    void loadTracks();

    // Удаление выбранного трека
    void deleteTrack();

    void filterTracks();

private:
    Ui::MainWindow* ui;            // Указатель на элементы интерфейса
    MediaManager mediaManager;     // Менеджер для работы с треками
    QListWidget* trackListWidget;  // Виджет списка треков
    PlaylistManager playlistManager; // Менеджер для работы с плейлистами
    QLineEdit* searchLineEdit;

    // Инициализация пользовательского интерфейса
    void setupUi();
};

#endif // MAINWINDOW_H
