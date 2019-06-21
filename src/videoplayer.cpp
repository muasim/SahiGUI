#include "moc_videoplayer.cpp"

#include <assert.h>
#include <string>

#include <QtWidgets/QtWidgets>

#include <whereami++.hpp>

VideoPlayer::VideoPlayer(QWidget *parent) :
    QFrame(parent)
{
    this->_vlcinstance = libvlc_new(0 ,NULL);
    assert(NULL != this->_vlcinstance);

    this->_m = libvlc_media_new_location(
        this->_vlcinstance,
        "udp://@127.0.1.0:2004");
    assert(NULL != this->_m);
    
    std::string media_options(":sout=#duplicate{dst=standard{access=file,mux=ts,dst=");
    media_options.append(whereami::executable_dir());
    media_options.append("/output.mkv");
    media_options.append("},dst=display}");
    libvlc_media_add_option(this->_m , media_options.c_str());

    this->_mp = libvlc_media_player_new_from_media(this->_m);
    assert(NULL != this->_mp);

    #if defined(Q_OS_WIN)
        libvlc_media_player_set_drawable(_mp, reinterpret_cast<unsigned int>(_videoWidget->winId()), &_vlcexcep );
    #elif defined(Q_OS_MAC)
        libvlc_media_player_set_drawable(_mp, _videoWidget->winId(), &_vlcexcep );
    #else //Linux
        libvlc_media_player_set_xwindow (this->_mp, this->winId() );
    #endif

    libvlc_media_player_play(this->_mp);
}