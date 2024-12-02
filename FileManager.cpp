#include "FileManager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

FileManager::FileManager(const QString& filename) : filename(filename) {}

void FileManager::saveToFile(const QList<Track>& tracks) {
    QFile file(filename);
    try {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Не удалось открыть файл для записи.";
            return;
        }
        QTextStream out(&file);
        for (const Track& track : tracks) {
            QString coverPath = track.getCoverPath();
            coverPath.replace("|", "_");
            out << track.getTitle() << "|"
                << track.getArtist() << "|"
                << track.getGenre() << "|"
                << track.getAlbum() << "|"
                << track.getYear() << "|"
                << coverPath << "|"
                << track.getAudioPath() << "\n";
        }
        file.close();
    } catch (const std::exception& e) {
        qDebug() << "Ошибка при сохранении данных в файл: " << e.what();
    }
}

QList<Track> FileManager::loadFromFile() {
    QList<Track> tracks;
    QFile file(filename);
    try {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Не удалось открыть файл для чтения.";
            return tracks;
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("|");
            if (parts.size() == 7) {
                QString title = parts[0];
                QString artist = parts[1];
                QString genre = parts[2];
                QString album = parts[3];
                int year = parts[4].toInt();
                QString coverPath = parts[5];
                QString audioPath = parts[6];
                tracks.append(Track(title, artist, genre, album, year, coverPath, audioPath));
            }
        }
        file.close();
    } catch (const std::exception& e) {
        qDebug() << "Ошибка при загрузке данных из файла: " << e.what();
    }
    return tracks;
}
