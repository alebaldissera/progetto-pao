#include "VideoPlayer.h"

//debug stuff
#include <iostream>
using std::cout;
using std::endl;
//end debug stuff

VideoPlayer::VideoPlayer(const Katalog::BaseNode* sel_file, QWidget *parent) : QWidget(parent), files(nullptr), mediaIndex(0)
{
    buildWidget();
    setFile(sel_file);
    setAttribute(Qt::WA_DeleteOnClose, true); //permette di deallocare il widget quando viene chiuso
}

VideoPlayer::VideoPlayer(const FileList *fileVector, QWidget *parent) : QWidget(parent), files(nullptr), mediaIndex(0)
{
    buildWidget();
    setFolder(fileVector);
    setAttribute(Qt::WA_DeleteOnClose, true);
}

VideoPlayer::~VideoPlayer()
{
    if(image) delete image;
}

void VideoPlayer::setFile(const Katalog::BaseNode *file)
{
    mediaPlayer->stop();
    mediaPlayer->setMedia(QMediaContent());
    files = nullptr;
    if(file != nullptr && (dynamic_cast<const Katalog::Photo*>(file) || dynamic_cast<const Katalog::Audio*>(file) || dynamic_cast<const Katalog::Video*>(file))) {
        setMedia(file);
    } else {
        errorLabel->setText("Non ci sono file riproducibili");
    }
    previousButton->setDisabled(true);
    nextButton->setDisabled(true);
    playButton->setDisabled(false);
}

void VideoPlayer::setFolder(const FileList *filesVector)
{
    mediaPlayer->stop();
    mediaPlayer->setMedia(QMediaContent());
    files = filesVector;
    mediaIndex = 0;

    if(files){
        bool soloCartelle = true;
        for(unsigned int i = 0; i < files->size() && soloCartelle; ++i){
            if(dynamic_cast<Katalog::Photo*>((*files)[i].pointer()) || dynamic_cast<Katalog::Audio*>((*files)[i].pointer()) || dynamic_cast<Katalog::Video*>((*files)[i].pointer())){
                mediaIndex = i;
                soloCartelle = false;
            }
        }

        if(soloCartelle){
            errorLabel->setText("Non ci sono file riproducibili");
            playButton->setDisabled(true);
            nextButton->setDisabled(true);
            previousButton->setDisabled(true);
        } else {
            playButton->setDisabled(false);
            nextButton->setDisabled(false);
            previousButton->setDisabled(false);
            setMedia((*files)[mediaIndex].pointer());
        }
    } else {
        errorLabel->setText("Non ci sono file riproducibili");
        playButton->setDisabled(true);
        nextButton->setDisabled(true);
        previousButton->setDisabled(true);
    }
}

void VideoPlayer::playPause()
{
    if(mediaPlayer->state() == QMediaPlayer::PlayingState){
        mediaPlayer->pause();
    } else {
        mediaPlayer->play();
    }
}

void VideoPlayer::mediaStatusChanged(QMediaPlayer::MediaStatus state)
{
    if(state == QMediaPlayer::LoadedMedia){
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        mediaPlayer->play();
    } else if(state == QMediaPlayer::EndOfMedia){
        if(files != nullptr && dynamic_cast<Katalog::Photo*>((*files)[mediaIndex].pointer()) == nullptr){
            nextMedia();
        }
    }
}

void VideoPlayer::positionChanged(qint64 position)
{
    positionSlider->setValue(position);
}

void VideoPlayer::durationChanged(qint64 duration)
{
    positionSlider->setRange(0, duration);
}

void VideoPlayer::setPosition(int position)
{
    mediaPlayer->setPosition(position);
}

void VideoPlayer::handleError()
{
    playButton->setEnabled(false);
    const QString errorString = mediaPlayer->errorString();
    QString message = "Error: ";
    if (errorString.isEmpty())
        message += " #" + QString::number(int(mediaPlayer->error()));
    else
        message += errorString;
    errorLabel->setText(message);
}

void VideoPlayer::playerStateChanged(QMediaPlayer::State state)
{
    if(state == QMediaPlayer::PlayingState)
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    else if(state == QMediaPlayer::PausedState)
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

void VideoPlayer::triggerMuting()
{
    mediaPlayer->setMuted(!mediaPlayer->isMuted());
}

void VideoPlayer::muteHandler(bool isMute)
{
    if(isMute)
        volumeIcon->setIcon(QIcon(":/Icons/muted.svg"));
    else
        volumeIcon->setIcon(QIcon(":/Icons/volume.svg"));
}

void VideoPlayer::nextMedia()
{
    if(files) {
        if((++mediaIndex) == files->size()) mediaIndex = 0; //avanzo di un media file
        while(!dynamic_cast<Katalog::Photo*>((*files)[mediaIndex].pointer()) && !dynamic_cast<Katalog::Audio*>((*files)[mediaIndex].pointer()) && !dynamic_cast<Katalog::Video*>((*files)[mediaIndex].pointer()))
        {   //avanzo finchè non trovo un file adatto
            if((++mediaIndex) == files->size()) mediaIndex = 0;
        }
        setMedia((*files)[mediaIndex].pointer());
    }
}

void VideoPlayer::previousMedia()
{
    if(files){
        if(mediaIndex == 0) mediaIndex = files->size() - 1; //torno indietro di un file
        else --mediaIndex;
        while(!dynamic_cast<Katalog::Photo*>((*files)[mediaIndex].pointer()) && !dynamic_cast<Katalog::Audio*>((*files)[mediaIndex].pointer()) && !dynamic_cast<Katalog::Video*>((*files)[mediaIndex].pointer()))
        {   //torno indietro di un file finchè non ne trovo uno di riproducibile
            if(mediaIndex == 0) mediaIndex = files->size() - 1; //torno indietro di un file
            else --mediaIndex;
        }
        setMedia((*files)[mediaIndex].pointer());
    }
}

void VideoPlayer::setMedia(const Katalog::BaseNode *file)
{
    mediaPlayer->setMedia(QMediaContent());
    if(file && (dynamic_cast<const Katalog::Photo*>(file) || dynamic_cast<const Katalog::Audio*>(file) || dynamic_cast<const Katalog::Video*>(file))) {
        if(!dynamic_cast<const Katalog::Video*>(file)){
            //immagine
            if(image) delete image;
            if(!dynamic_cast<const Katalog::Audio*>(file))
            {
                playButton->setDisabled(true);
                image = new QImage(QString::fromStdString(file->getPath()));
            }
            else
            {
                playButton->setEnabled(true);
                image = new QImage(":/Icons/speaker.svg");
                mediaPlayer->setMedia(QUrl::fromLocalFile(QString::fromStdString(file->getPath())));
            }
            imageLabel->setPixmap(QPixmap::fromImage(image->scaled(std::min(width(), image->width()), std::min(height(), image->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            staked->setCurrentIndex(1);
        } else {
            //video o audio
            playButton->setEnabled(true);
            mediaPlayer->setMedia(QUrl::fromLocalFile(QString::fromStdString(file->getPath())));
            staked->setCurrentIndex(0);
        }
        errorLabel->setText(QString::fromStdString(file->getName()));
    }
    else
        errorLabel->setText("Non ci sono file riproducibili");
}

void VideoPlayer::buildWidget()
{
    playLayout = new QVBoxLayout(this);
    playLayout->setMargin(0);
    controlsLayout = new QHBoxLayout(this);
    controlsLayout->setMargin(0);
    addControls(controlsLayout);
    view = new QStackedLayout(this);

    errorLabel = new QLabel(this);
    errorLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    mediaPlayer = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    videoWidget = new QVideoWidget;
    mediaPlayer->setVideoOutput(videoWidget);
    sliderVolume->setValue(mediaPlayer->volume());
    imageView = new QLabel(this);
    imageView->setAlignment(Qt::AlignCenter);

    view->addWidget(videoWidget);
    view->addWidget(imageView);

    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    image = nullptr;
    staked = new QStackedLayout(this);
    staked->setMargin(0);
    staked->addWidget(videoWidget);
    staked->addWidget(imageLabel);
    staked->setCurrentIndex(0);

    playLayout->addLayout(staked);
    playLayout->addLayout(controlsLayout);
    playLayout->addWidget(errorLabel);

    connect(playButton, SIGNAL(clicked()), this, SLOT(playPause()));
    connect(previousButton, SIGNAL(clicked()), this, SLOT(previousMedia()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(nextMedia()));
    connect(volumeIcon, SIGNAL(clicked()), this, SLOT(triggerMuting()));
    connect(sliderVolume, SIGNAL(valueChanged(int)), mediaPlayer, SLOT(setVolume(int)));
    connect(positionSlider, SIGNAL(sliderMoved(int)), this, SLOT(setPosition(int)));
    connect(mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(playerStateChanged(QMediaPlayer::State)));
    connect(mediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(mediaPlayer, SIGNAL(mutedChanged(bool)), this, SLOT(muteHandler(bool)));

    connect(mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &VideoPlayer::handleError);

    setLayout(playLayout);
}

void VideoPlayer::addControls(QLayout *l)
{
    previousButton = new QPushButton(this);
    previousButton->setIcon(QIcon(":/Icons/arrow-left.svg"));
    nextButton = new QPushButton(this);
    nextButton->setIcon(QIcon(":/Icons/arrow-right.svg"));
    playButton = new QPushButton(this);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    volumeIcon = new QPushButton(this);
    volumeIcon->setIcon(QIcon(":/Icons/volume.svg"));
    positionSlider = new QSlider(Qt::Horizontal, this);
    positionSlider->setRange(0, 0);
    sliderVolume = new QSlider(Qt::Horizontal, this);
    sliderVolume->setRange(0, 100);
    l->addWidget(playButton);
    l->addWidget(previousButton);
    l->addWidget(nextButton);
    l->addWidget(positionSlider);
    l->addWidget(volumeIcon);
    l->addWidget(sliderVolume);
}

void VideoPlayer::setMedia(const Katalog::BaseNode* file)
{
    errorLabel->setText(QString::fromStdString(file->getName()));
    if(dynamic_cast<const Katalog::Photo*>(file)){
        mediaPlayer->setMedia(QMediaContent());
        view->setCurrentIndex(1);
        img = QImage(QString::fromStdString(file->getPath()));

        imageView->setPixmap(QPixmap::fromImage(img.scaled(std::min(width(), img.width()), std::min(height(), img.height()))));
    } else if(dynamic_cast<const Katalog::Audio*>(file)) {
        view->setCurrentIndex(1);
        img = QImage(":/Icons/speaker.svg");

        imageView->setPixmap(QPixmap::fromImage(img.scaled(width() / 2, height() / 2, Qt::KeepAspectRatio)));
        mediaPlayer->setMedia(QUrl::fromLocalFile(QString::fromStdString(file->getPath())));
    }else {
        view->setCurrentIndex(0);
        mediaPlayer->setMedia(QUrl::fromLocalFile(QString::fromStdString(file->getPath())));
    }
}

void VideoPlayer::closeEvent(QCloseEvent *event)
{
    if(mediaPlayer->state() == QMediaPlayer::PlayingState){
        mediaPlayer->stop();
        delete mediaPlayer;
        mediaPlayer = 0;
        delete videoWidget;
        videoWidget = 0;
    }
    QWidget::closeEvent(event);
}

void VideoPlayer::resizeEvent(QResizeEvent *event)
{
    imageView->setPixmap(QPixmap::fromImage(img.scaled(std::min(width(), img.width()), std::min(height(), img.height()))));
    QWidget::resizeEvent(event);
}

