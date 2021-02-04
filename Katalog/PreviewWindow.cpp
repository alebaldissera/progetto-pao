#include "PreviewWindow.h"

//debug stuff
#include <iostream>
using std::cout;
using std::endl;
//end debut stuff

PreviewWindow::PreviewWindow(Katalog::BaseNode* sel_file, QWidget *parent) : QWidget(parent), defaultColor(QWidget::palette().color(QWidget::backgroundRole())), filePtr(sel_file)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setMargin(10);

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
        /*QImage photoimg(":/Icons/image-gallery.svg");
        icon->setPixmap(QPixmap::fromImage(photoimg.scaled(75,200, Qt::KeepAspectRatio, Qt::SmoothTransformation)));*/
        QImage photoimg(QString::fromStdString(sel_file->getPath()));
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
    setToolTip(QString::fromStdString(filePtr->getInfo()));
    setAttribute(Qt::WA_Hover, true);
    setAttribute(Qt::WA_DeleteOnClose, true);
}

void PreviewWindow::enterEvent(QEvent *event)
{
    std::stringstream ss;
    ss << "background-color: rgba(" << defaultColor.red() << ","  << defaultColor.green() * 1.50 << "," << defaultColor.blue() * 1.75 << "," << defaultColor.alpha() << ")";
    setStyleSheet(QString::fromStdString(ss.str()));
    QWidget::enterEvent(event);
}

void PreviewWindow::leaveEvent(QEvent *event)
{
    std::stringstream ss;
    ss << "background-color: rgba(" << defaultColor.red() << ","  << defaultColor.green() << "," << defaultColor.blue() << "," << defaultColor.alpha() << ")";
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
    if(event->button() == Qt::LeftButton)
        emit mouseDoubleClicked(filePtr);
    QWidget::mouseDoubleClickEvent(event);
}
