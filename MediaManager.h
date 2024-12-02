#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H

#include <QList>
#include "Track.h"
#include "FileManager.h"

// Класс для управления треками (добавление, удаление, загрузка и сохранение)
class MediaManager {
public:
    // Конструктор, принимает имя файла для загрузки/сохранения данных
    MediaManager(const QString& filename);

    // Добавление нового трека
    void addTrack(const Track& track);

    // Удаление трека по индексу
    void removeTrack(int index);

    // Получение списка всех треков
    QList<Track> getTracks() const;

    // Загрузка треков из файла
    void loadTracks();

    // Сохранение треков в файл
    void saveTracks();

    void updateTrack(int index, const Track& updatedTrack);

private:
    QList<Track> tracks;       // Список треков
    FileManager fileManager;   // Менеджер для работы с файлом
};

#endif // MEDIAMANAGER_H
