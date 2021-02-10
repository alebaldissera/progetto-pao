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
    void catalogUpdated();

public slots:
    void addFile(Katalog::BaseNode *file, std::string destination);
    void saveCatalog();
    void openDirectory(QTreeWidgetItem *node);
    void closeDirectory(QTreeWidgetItem *node);
    void treeItemClicked(QTreeWidgetItem*,int);
    void treeItemDoubleClicked(QTreeWidgetItem*, int);
    void viewGridOnRoot();
    void copyFile(std::string);
    void cutFile(std::string);
    void pasteFile(std::string);
    void removeFile(std::string);
    void renameFile(std::string, std::string);
    void pathTextChanged();
    void requestForGridView();
    void requestForPlayView();

private:
    Katalog::Catalogo &catalogo;
    MainWindow &mainwindow;
    static std::string getItemPath(QTreeWidgetItem* item);

    std::string clip;
    bool operation; //true copia, false taglia
};


#endif // CONTROLLER_H
