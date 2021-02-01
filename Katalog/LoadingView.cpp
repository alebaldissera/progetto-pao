#include "LoadingView.h"

LoadingView::LoadingView(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(300, 100);
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
    setWindowIcon(QIcon(":/Icons/katalog.svg"));
}
