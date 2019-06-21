#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QtWidgets/QFrame>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaRecorder>

#include <vlc/vlc.h>

class VideoPlayer : public QFrame
{
    Q_OBJECT

public:
    VideoPlayer(QWidget *parent = nullptr);

private:
    libvlc_instance_t *_vlcinstance;
    libvlc_media_player_t *_mp;
    libvlc_media_t *_m;
};

#endif