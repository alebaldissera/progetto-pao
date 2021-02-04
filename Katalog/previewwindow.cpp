#include "PreviewWindow.h"

PreviewWindow::PreviewWindow(Katalog::BaseNode* sel_file, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    QLabel *icon = new QLabel(this);
    QLabel *namefile = new QLabel(QString::fromStdString(sel_file->getName()), this);
    namefile->setAlignment(Qt::AlignHCenter);

    if (sel_file == dynamic_cast<Katalog::Audio*>(sel_file))
    {
        QImage audioimg(":/Icons/speaker.svg");
        icon->setPixmap(QPixmap::fromImage(audioimg.scaled(75,200, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    }
    else if(sel_file == dynamic_cast<Katalog::Photo*>(sel_file))
    {
        QImage photoimg(":/Icons/image-gallery.svg");
        icon->setPixmap(QPixmap::fromImage(photoimg.scaled(75,200, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
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

}
