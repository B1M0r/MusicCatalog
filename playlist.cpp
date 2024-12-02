#include "Playlist.h"

// Конструктор
Playlist::Playlist(const QString& name) : name(name) {}

// Получение имени плейлиста
QString Playlist::getName() const {
    return name;
}

// Установка имени плейлиста
void Playlist::setName(const QString& name) {
    this->name = name;
}

// Добавление трека
void Playlist::addTrack(const Track& track) {
    tracks.append(track);
}

// Удаление трека
void Playlist::removeTrack(int index) {
    if (index >= 0 && index < tracks.size()) {
        tracks.removeAt(index);
    }
}

// Получение всех треков
QList<Track> Playlist::getTracks() const {
    return tracks;
}
