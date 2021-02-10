#include "PreviewWindow.h"

//debug stuff
#include <iostream>
using std::cout;
using std::endl;
//end debut stuff

PreviewWindow::PreviewWindow(Katalog::BaseNode* sel_file, QWidget *parent) : QWidget(parent), defaultColor(QWidget::palette().color(QWidget::backgroundRole())), filePtr(sel_file), il(nullptr)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setMargin(10);

    icon = new QLabel(this);
    QLabel *namefile = new QLabel(QString::fromStdString(sel_file->getName()), this);

    icon->setStyleSheet("background-color: rgba(0,0,0,0);");
    namefile->setStyleSheet("background-color: rgba(0,0,0,0);");

    namefile->setMaximumWidth(75);
    namefile->setMaximumHeight(200);
    namefile->setAlignment(Qt::AlignLeft);

    if (sel_file == dynamic_cast<Katalog::Audio*>(sel_file))
    {
        QImage audioimg(":/Icons/speaker.svg");
        icon->setPixmap(QPixmap::fromImage(audioimg.scaled(75,200, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    }
    else if(sel_file == dynamic_cast<Katalog::Photo*>(sel_file))
    {
        QImage photoimg(":/Icons/image-gallery.svg");
        icon->setPixmap(QPixmap::fromImage(photoimg.scaled(75,200, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        il = new ImageLoader(this, QString::fromStdString(sel_file->getPath()), this);
        il->start(QThread::LowestPriority);
    }
    else if(sel_file == dynamic_cast<Katalog::Video*>(sel_file))
    {
        QImage videoimg(":/Icons/video.svg");
        icon->setPixmap(QPixmap::fromImage(videoimg.scaled(75,200, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    }
    else
    {
        QImage dirimg(":/Icons/folder.svg");
        icon->setPixmap(QPixmap::fromImage(dirimg.scaled(75,200, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    }
    mainLayout->layout()->addWidget(icon);
    mainLayout->layout()->addWidget(namefile);
    setLayout(mainLayout);
    setToolTip(QString::fromStdString(filePtr->getInfo()));
    setAttribute(Qt::WA_Hover, true);
    setAttribute(Qt::WA_DeleteOnClose, true);
}

PreviewWindow::~PreviewWindow()
{
    if(il != nullptr){
        if(il->isRunning())
            il->terminate();
        il->wait();
        delete il;
    }
}

void PreviewWindow::enterEvent(QEvent *event)
{
    std::stringstream ss;
    ss << "background-color: rgba(0, 126, 232, 0.60)";
    setStyleSheet(QString::fromStdString(ss.str()));
    QWidget::enterEvent(event);
}

void PreviewWindow::leaveEvent(QEvent *event)
{
    std::stringstream ss;
    ss << "background-color: rgba(0, 126, 232, 0)";
    setStyleSheet(QString::fromStdString(ss.str()));
    QWidget::enterEvent(event);
}

void PreviewWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void PreviewWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    QWidget::mouseDoubleClickEvent(event);
    if(event->button() == Qt::LeftButton)
        emit mouseDoubleClicked(filePtr);
}

ImageLoader::ImageLoader(PreviewWindow *w, QString file, QWidget *parent): QThread(parent), obj(w), path(file), img(nullptr) {}

ImageLoader::~ImageLoader()
{
    if(img) delete img;
}

void ImageLoader::run()
{
    if(img) delete img;
    img = new QImage(path);
    obj->icon->setPixmap(QPixmap::fromImage(img->scaled(75,200, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    delete img;
    img = nullptr;
}
