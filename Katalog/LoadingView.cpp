#include "LoadingView.h"

LoadingView::LoadingView(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QProgressBar *progress = new QProgressBar(this);

    progress->setRange(0,0);
    progress->setValue(0);

    QLabel *label = new QLabel("Caricamento del catalogo in corso...", this);

    label->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(progress);
    mainLayout->addWidget(label);

    mainLayout->setAlignment(Qt::AlignCenter);

    setLayout(mainLayout);

    setMinimumSize(300, 100);
    setMaximumSize(300, 100);
    resize(300, 100);
    setWindowIcon(QIcon(":/Icons/katalog.svg"));
    setWindowTitle("Katalog");
    move(QGuiApplication::screens().at(0)->availableGeometry().center() - frameGeometry().center());
    setAttribute(Qt::WA_DeleteOnClose);
}
