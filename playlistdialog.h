#ifndef PLAYLISTDIALOG_H
#define PLAYLISTDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "PlaylistManager.h"

class PlaylistDialog : public QDialog {
    Q_OBJECT

public:
    explicit PlaylistDialog(PlaylistManager& playlistManager, QWidget* parent = nullptr);

private slots:
    void addPlaylist();
    void deletePlaylist();
    void viewPlaylistDetails();
    void addTrackToPlaylist();


private:
    PlaylistManager& playlistManager;
    QListWidget* playlistListWidget;

    void loadPlaylists();

};

#endif // PLAYLISTDIALOG_H
