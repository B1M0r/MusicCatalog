#ifndef TRACK_H
#define TRACK_H

#include <QString>

class Track {
public:
    Track(const QString& title, const QString& artist,
          const QString& genre = "Не указан", const QString& album = "Не указан",
          int year = 0, const QString& coverPath = "", const QString& audioPath = "");

    QString getTitle() const;
    QString getArtist() const;
    QString getGenre() const;
    QString getAlbum() const;
    int getYear() const;
    QString getCoverPath() const;
    QString getAudioPath() const; // Новый геттер

    QString getDetails() const;

    void setCoverPath(const QString& path);
    void setAudioPath(const QString& path); // Новый сеттер

private:
    QString title;
    QString artist;
    QString genre;
    QString album;
    int year;
    QString coverPath;   // Путь к изображению
    QString audioPath;   // Новый: путь к аудиофайлу
};

#endif // TRACK_H
