#include "PlaylistDialog.h"
#include "Playlist.h"
#include <QInputDialog>
#include <QMessageBox>

PlaylistDialog::PlaylistDialog(PlaylistManager& playlistManager, QWidget* parent)
    : QDialog(parent), playlistManager(playlistManager) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    playlistListWidget = new QListWidget(this);
    layout->addWidget(playlistListWidget);

    QHBoxLayout* buttonLayout = new QHBoxLayout;

    QPushButton* addButton = new QPushButton("Добавить плейлист", this);
    buttonLayout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, &PlaylistDialog::addPlaylist);

    QPushButton* deleteButton = new QPushButton("Удалить плейлист", this);
    buttonLayout->addWidget(deleteButton);
    connect(deleteButton, &QPushButton::clicked, this, &PlaylistDialog::deletePlaylist);

    QPushButton* detailsButton = new QPushButton("Просмотр плейлиста", this);
    buttonLayout->addWidget(detailsButton);
    connect(detailsButton, &QPushButton::clicked, this, &PlaylistDialog::viewPlaylistDetails);

    QPushButton* addTrackButton = new QPushButton("Добавить трек", this);
    buttonLayout->addWidget(addTrackButton);
    connect(addTrackButton, &QPushButton::clicked, this, &PlaylistDialog::addTrackToPlaylist);

    layout->addLayout(buttonLayout);

    loadPlaylists();
}

void PlaylistDialog::loadPlaylists() {
    playlistListWidget->clear();
    QList<Playlist> playlists = playlistManager.getPlaylists();
    for (const auto& playlist : playlists) {
        playlistListWidget->addItem(playlist.getName());
    }
}

void PlaylistDialog::addPlaylist() {
    bool ok;
    QString name = QInputDialog::getText(this, "Добавить плейлист", "Введите название плейлиста:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
        playlistManager.addPlaylist(Playlist(name));
        loadPlaylists();
    }
}

void PlaylistDialog::deletePlaylist() {
    QListWidgetItem* selectedItem = playlistListWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите плейлист для удаления.");
        return;
    }

    int row = playlistListWidget->row(selectedItem);
    playlistManager.removePlaylist(row);
    loadPlaylists();
}

void PlaylistDialog::viewPlaylistDetails() {
    QListWidgetItem* selectedItem = playlistListWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите плейлист для просмотра.");
        return;
    }

    int row = playlistListWidget->row(selectedItem);
    Playlist playlist = playlistManager.getPlaylists().at(row);

    QString details;
    for (const auto& track : playlist.getTracks()) {
        details += QString("%1 - %2\n").arg(track.getTitle(), track.getArtist());
    }

    QMessageBox::information(this, playlist.getName(), details.isEmpty() ? "Плейлист пуст" : details);
}

void PlaylistDialog::addTrackToPlaylist() {
    QListWidgetItem* selectedItem = playlistListWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите плейлист для добавления трека.");
        return;
    }

    // Выбор трека из всех доступных
    QStringList trackTitles;
    QList<Track> tracks = playlistManager.getMediaManager().getTracks(); // Получаем треки через MediaManager
    for (const auto& track : tracks) {
        trackTitles.append(QString("%1 - %2").arg(track.getTitle(), track.getArtist()));
    }

    bool ok;
    QString selectedTrack = QInputDialog::getItem(
        this,
        "Добавить трек",
        "Выберите трек для добавления:",
        trackTitles,
        0,
        false,
        &ok
        );

    if (ok && !selectedTrack.isEmpty()) {
        int trackIndex = trackTitles.indexOf(selectedTrack);
        if (trackIndex >= 0 && trackIndex < tracks.size()) {
            int playlistIndex = playlistListWidget->row(selectedItem);
            Playlist& playlist = playlistManager.getPlaylist(playlistIndex);
            playlist.addTrack(tracks[trackIndex]);
            playlistManager.savePlaylists(); // Сохраняем изменения
            QMessageBox::information(this, "Успех", "Трек успешно добавлен в плейлист.");
        } else {
            QMessageBox::warning(this, "Ошибка", "Неверный индекс плейлиста.");
        }
    }
}
