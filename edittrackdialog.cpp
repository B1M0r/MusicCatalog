#include "EditTrackDialog.h"
#include <QFileDialog>
#include <QVBoxLayout>

#include "EditTrackDialog.h"
#include <QFileDialog>
#include <QVBoxLayout>

EditTrackDialog::EditTrackDialog(const QString& title, const QString& artist,
                                 const QString& genre, const QString& album, int year,
                                 const QString& coverPath, const QString& audioPath,
                                 QWidget* parent)
    : FormDialog(parent), coverPath(coverPath), audioPath(audioPath) {
    setWindowTitle("Редактировать трек");

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Используем методы FormDialog для создания полей
    addFormRow(layout, "Название:", titleEdit);
    titleEdit->setText(title);

    addFormRow(layout, "Исполнитель:", artistEdit);
    artistEdit->setText(artist);

    addFormRow(layout, "Жанр:", genreEdit);
    genreEdit->setText(genre);

    addFormRow(layout, "Альбом:", albumEdit);
    albumEdit->setText(album);

    yearSpinBox = new QSpinBox(this);
    yearSpinBox->setMaximum(2024);
    yearSpinBox->setValue(year);
    layout->addWidget(new QLabel("Год:"));
    layout->addWidget(yearSpinBox);

    // Обложка
    QPushButton* coverButton = new QPushButton("Выбрать обложку", this);
    connect(coverButton, &QPushButton::clicked, this, &EditTrackDialog::chooseCoverImage);
    layout->addWidget(coverButton);

    coverLabel = new QLabel(this);
    coverLabel->setText(coverPath.isEmpty() ? "Обложка не выбрана" : coverPath);
    layout->addWidget(coverLabel);

    // Аудио
    QPushButton* audioButton = new QPushButton("Выбрать аудио", this);
    connect(audioButton, &QPushButton::clicked, this, &EditTrackDialog::chooseAudioFile);
    layout->addWidget(audioButton);

    audioLabel = new QLabel(this);
    audioLabel->setText(audioPath.isEmpty() ? "Аудиофайл не выбран" : audioPath);
    layout->addWidget(audioLabel);

    // Добавляем кнопки OK и Cancel
    addOkCancelButtons(layout);

    setLayout(layout);
}

// Метод для выбора изображения обложки
void EditTrackDialog::chooseCoverImage() {
    QString file = QFileDialog::getOpenFileName(this, "Выбрать обложку", QString(), "Изображения (*.png *.jpg *.jpeg)");
    if (!file.isEmpty()) {
        coverPath = file;
        coverLabel->setText(file);
    }
}

void EditTrackDialog::chooseAudioFile() {
    QString file = QFileDialog::getOpenFileName(this, "Выбрать аудио", QString(), "Аудиофайлы (*.mp3 *.wav)");
    if (!file.isEmpty()) {
        audioPath = file;
        audioLabel->setText(file);
    }
}

QString EditTrackDialog::getAudioPath() const {
    return audioPath;
}

// Геттеры для получения значений полей
QString EditTrackDialog::getTitle() const {
    return titleEdit->text();
}

QString EditTrackDialog::getArtist() const {
    return artistEdit->text();
}

QString EditTrackDialog::getGenre() const {
    return genreEdit->text();
}

QString EditTrackDialog::getAlbum() const {
    return albumEdit->text();
}

int EditTrackDialog::getYear() const {
    return yearSpinBox->value();
}

QString EditTrackDialog::getCoverPath() const {
    return coverPath;
}
