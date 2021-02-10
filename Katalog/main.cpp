#include <QApplication>
#include <MainWindow.h>
#include <Catalogo.h>
#include <Controller.h>

int main(int argc, char *argv[])
{
    QImage img(":/Icons/speaker.svg");
    QApplication a(argc, argv);
    MainWindow window;
    Katalog::Catalogo catalogo;
    Controller c(catalogo, window);
    return a.exec();
}
