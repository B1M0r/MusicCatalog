#ifndef EDITTRACKDIALOG_H
#define EDITTRACKDIALOG_H

#include "FormDialog.h"
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

class EditTrackDialog : public FormDialog {
    Q_OBJECT

public:
    EditTrackDialog(const QString& title, const QString& artist,
                    const QString& genre, const QString& album,
                    int year, const QString& coverPath,
                    const QString& audioPath, QWidget* parent = nullptr);

    QString getTitle() const;
    QString getArtist() const;
    QString getGenre() const;
    QString getAlbum() const;
    int getYear() const;
    QString getCoverPath() const;
    QString getAudioPath() const;

private slots:
    void chooseCoverImage();
    void chooseAudioFile();

private:
    QLineEdit* titleEdit;
    QLineEdit* artistEdit;
    QLineEdit* genreEdit;
    QLineEdit* albumEdit;
    QSpinBox* yearSpinBox;
    QLabel* coverLabel;
    QString coverPath;
    QLabel* audioLabel;
    QString audioPath;
};

#endif // EDITTRACKDIALOG_H
