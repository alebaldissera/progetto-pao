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
#include <QStackedLayout>

typedef Katalog::vector<Katalog::DeepPtr<Katalog::BaseNode>> FileList;

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(const Katalog::BaseNode* sel_file, QWidget *parent = nullptr);
    VideoPlayer(const FileList *fileVector, QWidget *parent = nullptr);
    virtual ~VideoPlayer();

public slots:
    void setFile(const Katalog::BaseNode* file);
    void setFolder(const FileList* filesVector);

private slots:
    void playPause();
    void mediaStatusChanged(QMediaPlayer::MediaStatus state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void handleError();
    void playerStateChanged(QMediaPlayer::State state);
    void triggerMuting();
    void muteHandler(bool isMute);
    void nextMedia();
    void previousMedia();
    void setMedia(const Katalog::BaseNode* file);

private:
    QVBoxLayout* playLayout;
    QHBoxLayout* controlsLayout;
    QStackedLayout *view;

    QMediaPlayer* mediaPlayer;
    QVideoWidget *videoWidget;
    QLabel *imageView;

    QPushButton *playButton;
    QPushButton *previousButton;
    QPushButton *nextButton;
    QPushButton *volumeIcon;

    QSlider *positionSlider;
    QSlider* sliderVolume;
    QLabel *errorLabel;

    QLabel *imageLabel;
    QImage *image;
    QStackedLayout *staked;

    const FileList* files;
    unsigned int mediaIndex;

    void buildWidget();
    void addControls(QLayout *l);

protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // VIDEOPLAYER_H

