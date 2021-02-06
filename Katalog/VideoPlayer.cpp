#include "VideoPlayer.h"

VideoPlayer::VideoPlayer(Katalog::BaseNode* sel_file, QWidget *parent) : QWidget(parent)
{
    playLayout = new QHBoxLayout(this);
    controlsLayout = new QHBoxLayout(this);

    if (sel_file == dynamic_cast<Katalog::Video*>(sel_file) || sel_file == dynamic_cast<Katalog::Audio*>(sel_file))
    {
        m_mediaPlayer = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
        QVideoWidget *videoWidget = new QVideoWidget;

        m_playButton = new QPushButton;
        m_playButton->setEnabled(false);
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

        connect(m_playButton, &QAbstractButton::clicked,
                this, &VideoPlayer::play);

        m_volumeIcon = new QPushButton;
        m_volumeIcon->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

        m_positionSlider = new QSlider(Qt::Horizontal);
        m_positionSlider->setRange(0, 0);

        connect(m_positionSlider, &QAbstractSlider::sliderMoved,
                this, &VideoPlayer::setPosition);

        sliderVolume = new QSlider(Qt::Horizontal, this); // Put slider where you want.
        sliderVolume->setRange(0, 100);
        sliderVolume->setValue(m_mediaPlayer->volume());

        connect(sliderVolume, &QSlider::valueChanged, m_mediaPlayer, &QMediaPlayer::setVolume);

        m_errorLabel = new QLabel;
        m_errorLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

        controlsLayout->setContentsMargins(0, 0, 0, 0);
        controlsLayout->addWidget(m_playButton);
        controlsLayout->addWidget(m_positionSlider);
        controlsLayout->addWidget(m_volumeIcon);
        controlsLayout->addWidget(sliderVolume);

        playLayout->addWidget(videoWidget);
        playLayout->addLayout(controlsLayout);
        playLayout->addWidget(m_errorLabel);

        setLayout(playLayout);

        m_mediaPlayer->setVideoOutput(videoWidget);
        connect(m_mediaPlayer, &QMediaPlayer::stateChanged,
                this, &VideoPlayer::mediaStateChanged);
        connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, &VideoPlayer::positionChanged);
        connect(m_mediaPlayer, &QMediaPlayer::durationChanged, this, &VideoPlayer::durationChanged);
        connect(m_mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
                this, &VideoPlayer::handleError);
    }
    else if (sel_file == dynamic_cast<Katalog::Photo*>(sel_file))
    {
        QLabel *photodisplay = new QLabel(this);
        QImage img(QString::fromStdString(sel_file->getName()));
        photodisplay->setPixmap(QPixmap::fromImage(img.scaled(1024, 768, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        playLayout->addWidget(photodisplay);
    }
    setLayout(playLayout);
    setAttribute(Qt::WA_DeleteOnClose, true);
}

void VideoPlayer::setUrl(const QUrl &url)
{
    m_errorLabel->setText(QString());
    setWindowFilePath(url.isLocalFile() ? url.toLocalFile() : QString());
    m_mediaPlayer->setMedia(url);
    m_playButton->setEnabled(true);
}

void VideoPlayer::play()
{
    switch (m_mediaPlayer->state()) {
    case QMediaPlayer::PlayingState:
        m_mediaPlayer->pause();
        break;
    default:
        m_mediaPlayer->play();
        break;
    }
}

void VideoPlayer::mediaStateChanged(QMediaPlayer::State state)
{
    switch(state) {
    case QMediaPlayer::PlayingState:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void VideoPlayer::positionChanged(qint64 position)
{
    m_positionSlider->setValue(position);
}

void VideoPlayer::durationChanged(qint64 duration)
{
    m_positionSlider->setRange(0, duration);
}

void VideoPlayer::setPosition(int position)
{
    m_mediaPlayer->setPosition(position);
}

void VideoPlayer::handleError()
{
    m_playButton->setEnabled(false);
    const QString errorString = m_mediaPlayer->errorString();
    QString message = "Error: ";
    if (errorString.isEmpty())
        message += " #" + QString::number(int(m_mediaPlayer->error()));
    else
        message += errorString;
    m_errorLabel->setText(message);
}

