#include "MainWindow.h"
#include "EditTrackDialog.h"
#include "TrackPlayerDialog.h"
#include "PlaylistDialog.h"
#include "playlistmanager.h"
#include "MediaManager.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>

// Конструктор главного окна
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), mediaManager("tracks.txt"), playlistManager("playlists.txt", mediaManager) {
    setupUi();        // Инициализация элементов интерфейса
    loadTracks();     // Загрузка треков из файла

    // Устанавливаем размер окна
    resize(800, 600);

    // Подключение сигнала двойного клика на элементе списка
    connect(trackListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::showReadonlyTrackDetails);

}

// Деструктор
MainWindow::~MainWindow() {}

// Инициализация элементов интерфейса
void MainWindow::setupUi() {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    // Список треков
    trackListWidget = new QListWidget(this);
    layout->addWidget(trackListWidget);

    // Кнопка "Добавить трек"
    QPushButton* addButton = new QPushButton("Добавить трек", this);
    layout->addWidget(addButton);

    connect(addButton, &QPushButton::clicked, [this]() {
        // Ввод названия трека
        bool ok;
        QString title = QInputDialog::getText(this, "Добавить трек", "Название трека:", QLineEdit::Normal, "", &ok);
        if (ok && !title.isEmpty()) {
            // Ввод исполнителя
            QString artist = QInputDialog::getText(this, "Добавить трек", "Исполнитель:", QLineEdit::Normal, "", &ok);
            if (ok) {
                // Создаем трек с минимальной информацией
                mediaManager.addTrack(Track(title, artist, "Не указан", "Не указан", 0));
                loadTracks(); // Обновляем список
            }
        }
    });

    QPushButton* editButton = new QPushButton("Редактировать трек", this);
    layout->addWidget(editButton);

    connect(editButton, &QPushButton::clicked, [this]() {
        QListWidgetItem* selectedItem = trackListWidget->currentItem();
        if (!selectedItem) {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите трек для редактирования.");
            return;
        }

        int row = trackListWidget->row(selectedItem);
        QList<Track> tracks = mediaManager.getTracks();
        if (row >= 0 && row < tracks.size()) {
            Track selectedTrack = tracks[row];

            EditTrackDialog editDialog(
                selectedTrack.getTitle(),
                selectedTrack.getArtist(),
                selectedTrack.getGenre(),
                selectedTrack.getAlbum(),
                selectedTrack.getYear(),
                selectedTrack.getCoverPath(),
                selectedTrack.getAudioPath(),
                this
                );

            if (editDialog.exec() == QDialog::Accepted) {
                // Обновляем данные трека
                selectedTrack = Track(
                    editDialog.getTitle(),
                    editDialog.getArtist(),
                    editDialog.getGenre(),
                    editDialog.getAlbum(),
                    editDialog.getYear(),
                    editDialog.getCoverPath(),
                    editDialog.getAudioPath()
                    );

                // Обновляем трек в модели
                mediaManager.updateTrack(row, selectedTrack);
                loadTracks(); // Обновляем список
            }
        }
    });

    // Кнопка "Удалить трек"
    QPushButton* deleteButton = new QPushButton("Удалить трек", this);
    layout->addWidget(deleteButton);

    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteTrack);

    QPushButton* playlistButton = new QPushButton("Управление плейлистами", this);
    layout->addWidget(playlistButton);

    connect(playlistButton, &QPushButton::clicked, [this]() {
        PlaylistDialog playlistDialog(playlistManager, this);
        playlistDialog.exec();
    });
}

// Загрузка треков в список
void MainWindow::loadTracks() {
    trackListWidget->clear();
    QList<Track> tracks = mediaManager.getTracks();
    for (int i = 0; i < tracks.size(); ++i) {
        const Track& track = tracks[i];
        trackListWidget->addItem(QString("%1. %2 - %3")
                                     .arg(i + 1)
                                     .arg(track.getTitle())
                                     .arg(track.getArtist()));
    }
}

// Отображение окна с информацией о треке (только для чтения)
void MainWindow::showReadonlyTrackDetails(QListWidgetItem* item) {
    int row = trackListWidget->row(item);
    QList<Track> tracks = mediaManager.getTracks();
    if (row >= 0 && row < tracks.size()) {
        const Track& selectedTrack = tracks[row];

        // Открытие окна воспроизведения трека
        TrackPlayerDialog playerDialog(selectedTrack, this);
        playerDialog.exec();
    }
}

// Удаление трека
void MainWindow::deleteTrack() {
    QListWidgetItem* selectedItem = trackListWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите трек для удаления.");
        return;
    }

    // Подтверждение удаления
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение удаления",
                                  "Вы уверены, что хотите удалить этот трек?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        int row = trackListWidget->row(selectedItem);
        mediaManager.removeTrack(row); // Удаляем трек
        loadTracks(); // Обновляем список
    }
    // Если пользователь нажал "Нет", ничего не происходит
}
