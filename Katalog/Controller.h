#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QMessageBox>

#include <MainWindow.h>
#include <Catalogo.h>
#include <Vector.h>
#include <DeepPtr.h>
#include <BaseNode.h>
#include <Photo.h>
#include <Audio.h>
#include <Video.h>
#include <IOManager.h>
#include <LoadingView.h>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(Katalog::Catalogo &cat, MainWindow &mw, QObject *parent = nullptr);

signals:

public slots:
    void addFile(Katalog::BaseNode *file, std::string destination);
    void saveCatalog();
    void openDirectory(QTreeWidgetItem *node);
    void closeDirectory(QTreeWidgetItem *node);

private:
    Katalog::Catalogo &catalogo;
    MainWindow &mainwindow;
    static std::string getItemPath(QTreeWidgetItem* item);

};

#endif // CONTROLLER_H
