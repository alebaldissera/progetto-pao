/**
  * Per il widget di riproduzione audio e video e' stato seguito l'esempio fornito da Qt a questo link:
  * https://doc.qt.io/qt-5/qtmultimedia-multimediawidgets-videowidget-example.html
  *
  * L'esempio e' stato modificato per adattarsi al programma ed all'inserimento di altri controlli.
  */

#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QPushButton>
#include <QAbstractButton>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QStandardPaths>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include "DeepPtr.h"
#include "BaseNode.h"
#include "Photo.h"
#include "Video.h"
#include "Audio.h"
#include "FlowLayout.h"
#include "PreviewWindow.h"

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QSlider;
class QLabel;
class QUrl;
QT_END_NAMESPACE

typedef Katalog::vector<Katalog::DeepPtr<Katalog::BaseNode>> FileList;

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(Katalog::BaseNode* sel_file, QWidget *parent = nullptr);
    virtual ~VideoPlayer() = default;

    void setUrl(const QUrl &url);

public slots:
    void play();

private slots:
    void mediaStateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void handleError();

private:
    QMediaPlayer* m_mediaPlayer;
    QAbstractButton *m_playButton;
    QSlider *m_positionSlider;
    QLabel *m_errorLabel;
    QAbstractButton *m_volumeIcon;
    QSlider* sliderVolume;
    QHBoxLayout* playLayout;
    QHBoxLayout* controlsLayout;
};

#endif // VIDEOPLAYER_H

