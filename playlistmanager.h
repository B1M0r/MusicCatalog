#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <QList>
#include <QString>
#include "Playlist.h"
#include "MediaManager.h"

// Класс для управления плейлистами (добавление, удаление, загрузка и сохранение)
class PlaylistManager {
public:
    // Конструктор, принимает имя файла для работы с плейлистами
    explicit PlaylistManager(const QString& filename, MediaManager& mediaManager);

    // Добавление нового плейлиста
    void addPlaylist(const Playlist& playlist);

    // Удаление плейлиста по индексу
    void removePlaylist(int index);

    // Получение списка всех плейлистов
    QList<Playlist> getPlaylists() const;

    // Загрузка плейлистов из файла
    void loadPlaylists();

    // Сохранение плейлистов в файл
    void savePlaylists();

    // Получить плейлист по индексу
    Playlist& getPlaylist(int index);

    // Новый метод: доступ к MediaManager
    MediaManager& getMediaManager();

private:
    QList<Playlist> playlists; // Список всех плейлистов
    QString filename;          // Имя файла для работы с плейлистами
    MediaManager& mediaManager; // Ссылка на MediaManager
};

#endif // PLAYLISTMANAGER_H
