#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGui>
#include <QColorDialog>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

#include "mygraphicsscene.h"
#include "HelpBrowser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void saveAs();

    void getSomeHelp();

private:
    void createActions();
    void createMenus();
    void createToolBars();

    MyGraphicsScene* scene;
    QGraphicsView* view;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QToolBar *quickAcessToolBar;

    QAction *saveAsAction;
    QAction *exitAction;

    QAction *selectionAction;
    QAction *addLineAction;
    QAction *addCircleAction;
    QAction *addRectAction;
    QAction *removeAction;

    QAction *helpBrowserAction;

    HelpBrowser *helpBrowser = new HelpBrowser("../HW4_GraphicsEditor/resources/html", "index.html");
};

#endif // MAINWINDOW_H
