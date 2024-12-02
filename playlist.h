#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include <QList>
#include "Track.h"

// Класс для описания плейлиста
class Playlist {
public:
    explicit Playlist(const QString& name = "");

    // Получение и установка имени плейлиста
    QString getName() const;
    void setName(const QString& name);

    // Добавление и удаление трека
    void addTrack(const Track& track);
    void removeTrack(int index);

    // Получение всех треков
    QList<Track> getTracks() const;

private:
    QString name;          // Название плейлиста
    QList<Track> tracks;   // Список треков
};

#endif // PLAYLIST_H
