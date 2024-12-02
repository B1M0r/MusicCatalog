#include "Track.h"

// Конструктор класса Track, инициализирует все параметры трека
Track::Track(const QString& title, const QString& artist,
             const QString& genre, const QString& album, int year,
             const QString& coverPath, const QString& audioPath)
    : title(title), artist(artist),genre(genre), album(album),
    year(year), coverPath(coverPath),audioPath(audioPath) {}

// Геттер для обложки
QString Track::getCoverPath() const {
    return coverPath;
}

// Сеттер для обложки
void Track::setCoverPath(const QString& path) {
    coverPath = path;
}

// Геттеры для полей трека
QString Track::getTitle() const {
    return title;
}

QString Track::getArtist() const {
    return artist;
}

QString Track::getGenre() const {
    return genre;
}

QString Track::getAlbum() const {
    return album;
}

int Track::getYear() const {
    return year;
}

// Метод для получения строки с деталями трека
QString Track::getDetails() const {
    return QString("%1 - %2 (%3) | %4 | %5")
    .arg(title, artist, QString::number(year), genre, album);
}

QString Track::getAudioPath() const {
    return audioPath;
}

void Track::setAudioPath(const QString& path) {
    audioPath = path;
}
