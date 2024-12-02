#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QList>
#include "Track.h"

// Класс для работы с файлом (сохранение и загрузка данных о треках)
class FileManager {
public:
    // Конструктор, принимает имя файла для работы
    FileManager(const QString& filename);

    // Сохраняет список треков в файл
    void saveToFile(const QList<Track>& tracks);

    // Загружает список треков из файла
    QList<Track> loadFromFile();

private:
    QString filename; // Имя файла для работы
};

#endif // FILEMANAGER_H
