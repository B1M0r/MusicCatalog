#ifndef TRACKPLAYERDIALOG_H
#define TRACKPLAYERDIALOG_H

#include "BaseDialog.h"
#include <QDialog>
#include <QMediaPlayer>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QSlider>
#include <QMessageBox>

#include "Track.h"

class TrackPlayerDialog : public BaseDialog {
    Q_OBJECT

public:
    explicit TrackPlayerDialog(const Track& track, QWidget* parent = nullptr);
    ~TrackPlayerDialog();

private slots:
    void playPauseTrack();
    void stopTrack();
    void setVolume(int volume);
    void updatePlaybackProgress(qint64 position);
    void seekTrack(int position);

private:

    QMediaPlayer* mediaPlayer;
    int trackDuration;
    bool isPlaying;

    QString formatTime(int milliseconds);


    QPushButton* playPauseButton;
    QPushButton* stopButton;
    QLabel* coverLabel;
    QLabel* titleLabel;
    QLabel* artistLabel;
    QLabel* additionalInfoLabel;
    QSlider* volumeSlider;
    QSlider* seekSlider;
    QLabel* elapsedTimeLabel;

};

#endif // TRACKPLAYERDIALOG_H
