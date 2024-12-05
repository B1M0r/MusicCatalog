#include "MediaManager.h"

// Конструктор, инициализирует FileManager и загружает треки из файла
MediaManager::MediaManager(const QString& filename) : fileManager(filename) {
    loadTracks();
}

// Добавление трека в список
void MediaManager::addTrack(const Track& track) {
    tracks.append(track);
    saveTracks(); // Сохраняем изменения
}

// Удаление трека по индексу
void MediaManager::removeTrack(int index) {
    if (index >= 0 && index < tracks.size()) {
        tracks.removeAt(index);
        saveTracks(); // Сохраняем изменения
    }
}

void MediaManager::updateTrack(int index, const Track& updatedTrack) {
    if (index >= 0 && index < tracks.size()) {
        tracks[index] = updatedTrack; // Обновляем трек
        saveTracks(); // Сохраняем изменения
    }
}

// Получение списка всех треков
QList<Track> MediaManager::getTracks() const {
    return tracks;
}

// Загрузка треков из файла
void MediaManager::loadTracks() {
    tracks = fileManager.loadFromFile();
}

// Сохранение треков в файл
void MediaManager::saveTracks() {
    fileManager.saveToFile(tracks);
}

QList<Track> MediaManager::searchTracks(const QString& query) const {
    QList<Track> filteredTracks;
    for (const Track& track : tracks) {
        if (track.getTitle().contains(query, Qt::CaseInsensitive) ||
            track.getArtist().contains(query, Qt::CaseInsensitive)) {
            filteredTracks.append(track);
        }
    }
    return filteredTracks;
}
