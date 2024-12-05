#include "TrackPlayerDialog.h"
#include <QHBoxLayout>
#include <QPixmap>
#include <QFile>

TrackPlayerDialog::TrackPlayerDialog(const Track& track, QWidget* parent)
    : BaseDialog(parent), mediaPlayer(nullptr), trackDuration(), isPlaying(false) {
    setWindowTitle("Просмотр трека");

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Отображение обложки
    coverLabel = new QLabel(this);
    QPixmap pixmap;
    if (!track.getCoverPath().isEmpty() && QFile::exists(track.getCoverPath())) {
        pixmap.load(track.getCoverPath());
    } else {
        // Загружаем изображение-заглушку
        pixmap.load("D:/2 kurs/Kursovaya PnaYaVU/CatalogMusic/build/Desktop_Qt_5_15_15_static_MinGW_w64_MINGW64_MSYS2-Debug/5341742214805582116.jpg"); // Укажите путь к ресурсу
    }

    // Устанавливаем обложку (или заглушку)
    coverLabel->setPixmap(pixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    layout->addWidget(coverLabel);


    // Отображение названия и исполнителя
    titleLabel = new QLabel(QString("Название: %1").arg(track.getTitle()), this);
    artistLabel = new QLabel(QString("Исполнитель: %1").arg(track.getArtist()), this);
    layout->addWidget(titleLabel);
    layout->addWidget(artistLabel);

    // Проверка наличия аудиофайла
    if (QFile::exists(track.getAudioPath()) && !track.getAudioPath().isEmpty()) {
        // Инициализация медиа-плеера
        mediaPlayer = new QMediaPlayer(this);
        mediaPlayer->setMedia(QUrl::fromLocalFile(track.getAudioPath()));

        // Подключение для получения длительности трека
        connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status) {
            if (status == QMediaPlayer::LoadedMedia) {
                trackDuration = mediaPlayer->duration();
                if (seekSlider) {
                    seekSlider->setRange(0, trackDuration);
                }

                // Обновляем текст метки для отображения полной длительности
                elapsedTimeLabel->setText(QString("0:00 / %1").arg(formatTime(trackDuration)));
            }
        });



        // Обработка ошибок медиа-плеера
        connect(mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, [this]() {
            QMessageBox::critical(this, "Ошибка", "Не удалось загрузить аудиофайл.");
        });

        // Элементы управления
        QHBoxLayout* controlLayout = new QHBoxLayout();
        playPauseButton = new QPushButton("▶", this);
        stopButton = new QPushButton("■", this);

        volumeSlider = new QSlider(Qt::Horizontal, this);
        volumeSlider->setRange(0, 100);
        volumeSlider->setValue(100);

        controlLayout->addWidget(playPauseButton);
        controlLayout->addWidget(stopButton);
        controlLayout->addWidget(new QLabel("Громкость:", this));
        controlLayout->addWidget(volumeSlider);
        layout->addLayout(controlLayout);

        // Ползунок перемотки
        seekSlider = new QSlider(Qt::Horizontal, this);
        layout->addWidget(seekSlider);

        // Метка для прошедшего времени и полной длительности
        elapsedTimeLabel = new QLabel("0:00 / 0:00", this); // Инициализация
        layout->addWidget(elapsedTimeLabel);               // Добавляем метку в макет

        // Подключение кнопок и слайдеров
        connect(playPauseButton, &QPushButton::clicked, this, &TrackPlayerDialog::playPauseTrack);
        connect(stopButton, &QPushButton::clicked, this, &TrackPlayerDialog::stopTrack);
        connect(volumeSlider, &QSlider::valueChanged, this, &TrackPlayerDialog::setVolume);
        connect(seekSlider, &QSlider::sliderMoved, this, &TrackPlayerDialog::seekTrack);

        // Обновление прогресса воспроизведения
        connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &TrackPlayerDialog::updatePlaybackProgress);
    } else {
        // Если аудиофайл отсутствует, отображаем только сообщение
        QLabel* noAudioLabel = new QLabel("Аудиофайл отсутствует.", this);
        layout->addWidget(noAudioLabel);

        // Отключаем элементы управления
        playPauseButton = nullptr;
        stopButton = nullptr;
        volumeSlider = nullptr;
        seekSlider = nullptr;
        elapsedTimeLabel = nullptr;
    }

    // Отображение дополнительной информации
    additionalInfoLabel = new QLabel(QString("Жанр: %1\nАльбом: %2\nГод: %3")
                                         .arg(track.getGenre())
                                         .arg(track.getAlbum())
                                         .arg(track.getYear()),
                                     this);
    layout->addWidget(additionalInfoLabel);

    addOkCancelButtons(layout);

    setLayout(layout);
}

TrackPlayerDialog::~TrackPlayerDialog() {
    if (mediaPlayer) {
        delete mediaPlayer;
        mediaPlayer = nullptr;
    }
}

void TrackPlayerDialog::playPauseTrack() {
    if (!mediaPlayer) return;

    if (isPlaying) {
        mediaPlayer->pause();
        playPauseButton->setText("▶");
    } else {
        mediaPlayer->play();
        playPauseButton->setText("⏸");
    }
    isPlaying = !isPlaying;
}

void TrackPlayerDialog::stopTrack() {
    if (!mediaPlayer) return;

    mediaPlayer->stop();
    if (seekSlider) {
        seekSlider->setValue(0);
    }
    if (elapsedTimeLabel) {
        elapsedTimeLabel->setText("0:00");
    }
    isPlaying = false;
    playPauseButton->setText("▶");
}

void TrackPlayerDialog::setVolume(int volume) {
    if (!mediaPlayer) return;
    mediaPlayer->setVolume(volume);
}

void TrackPlayerDialog::updatePlaybackProgress(qint64 position) {
    if (!mediaPlayer || !seekSlider || !elapsedTimeLabel) return;

    seekSlider->setValue(static_cast<int>(position));

    // Обновляем метку времени: прошедшее время / полная длительность
    elapsedTimeLabel->setText(QString("%1 / %2")
                                  .arg(formatTime(static_cast<int>(position)))
                                  .arg(formatTime(trackDuration)));
}


void TrackPlayerDialog::seekTrack(int position) {
    if (!mediaPlayer) return;

    mediaPlayer->setPosition(position);
}

QString TrackPlayerDialog::formatTime(int milliseconds) {
    int seconds = (milliseconds / 1000) % 60;
    int minutes = (milliseconds / 60000) % 60;
    return QString("%1:%2")
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0'));
}
