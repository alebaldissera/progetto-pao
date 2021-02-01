#include <QApplication>
#include <MainWindow.h>
#include <LoadingView.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    LoadingView loading;
    loading.show();
    window.show();
    return a.exec();
}
