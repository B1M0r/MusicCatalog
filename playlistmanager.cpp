#include "PlaylistManager.h"
#include "playlist.h"
#include <QFile>
#include <QTextStream>

// Конструктор
PlaylistManager::PlaylistManager(const QString& filename, MediaManager& mediaManager)
    : filename(filename), mediaManager(mediaManager) {
    loadPlaylists();
}

// Реализация метода getMediaManager
MediaManager& PlaylistManager::getMediaManager() {
    return mediaManager;
}

// Добавление нового плейлиста
void PlaylistManager::addPlaylist(const Playlist& playlist) {
    playlists.append(playlist);
    savePlaylists(); // Сохраняем изменения
}

// Удаление плейлиста по индексу
void PlaylistManager::removePlaylist(int index) {
    if (index >= 0 && index < playlists.size()) {
        playlists.removeAt(index);
        savePlaylists(); // Сохраняем изменения
    }
}

// Получение списка всех плейлистов
QList<Playlist> PlaylistManager::getPlaylists() const {
    return playlists;
}

Playlist& PlaylistManager::getPlaylist(int index) {
    if (index >= 0 && index < playlists.size()) {
        return playlists[index];
    }
    throw std::out_of_range("Индекс плейлиста вне диапазона");
}


// Сохранение плейлистов в файл
void PlaylistManager::savePlaylists() {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto& playlist : playlists) {
            out << playlist.getName() << '\n';
            for (const auto& track : playlist.getTracks()) {
                out << track.getTitle() << ',' << track.getArtist() << ',' << track.getGenre() << ','
                    << track.getAlbum() << ',' << track.getYear() << ',' << track.getCoverPath() << ','
                    << track.getAudioPath() << '\n';
            }
            out << "---\n"; // Разделитель плейлистов
        }
    }
}

// Загрузка плейлистов из файла
void PlaylistManager::loadPlaylists() {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        playlists.clear();
        Playlist currentPlaylist;
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line == "---") {
                playlists.append(currentPlaylist);
                currentPlaylist = Playlist(); // Новый плейлист
            } else if (!line.contains(',')) {
                currentPlaylist.setName(line);
            } else {
                QStringList fields = line.split(',');
                if (fields.size() >= 7) {
                    Track track(fields[0], fields[1], fields[2], fields[3], fields[4].toInt(), fields[5], fields[6]);
                    currentPlaylist.addTrack(track);
                }
            }
        }
        if (!currentPlaylist.getTracks().isEmpty()) {
            playlists.append(currentPlaylist);
        }
    }
}
