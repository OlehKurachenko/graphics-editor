#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent), scene(new MyGraphicsScene(0,0,600, 600)), view(new QGraphicsView){

    scene->currentDrawingState = scene->DrawingState::Default;

    view->setScene(scene);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setRenderHints(QPainter::Antialiasing
                         | QPainter::TextAntialiasing);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);
    setCentralWidget(view);

    createActions();
    createMenus();
    createToolBars();

    this->setWindowTitle(tr("Graphics Editor"));
}

MainWindow::~MainWindow(){
    delete scene;
    delete view;
    delete fileMenu;
    delete editMenu;
    delete helpMenu;
    delete quickAcessToolBar;
    delete saveAsAction;
    delete exitAction;
    delete selectionAction;
    delete addLineAction;
    delete addCircleAction;
    delete addRectAction;
    delete removeAction;
    delete helpBrowserAction;
    delete helpBrowser;
}

void MainWindow::createActions(){

    this->saveAsAction = new QAction(tr("Save as..."), this);
    saveAsAction->setShortcut(tr("Ctrl+S"));
    saveAsAction->setIcon(QIcon(":/resources/icons/save.png"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    this->exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setIcon(QIcon(":/resources/icons/exit.png"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    this->selectionAction = new QAction(tr("Go to Selection mode"), this);
    selectionAction->setIcon(QIcon(":/resources/icons/selection.png"));
    connect(selectionAction, SIGNAL(triggered()), scene, SLOT(selection()));

    addLineAction = new QAction(tr("Draw new Line"), this);
    addLineAction->setIcon(QIcon(":/resources/icons/addLine.png"));
    connect(addLineAction, SIGNAL(triggered()), scene, SLOT(addLine()));

    addCircleAction = new QAction(tr("Draw new Circle"), this);
    addCircleAction->setIcon(QIcon(":/resources/icons/addCircle.png"));
    connect(addCircleAction, SIGNAL(triggered()), scene, SLOT(addCircle()));

    addRectAction = new QAction(tr("Draw new Rect"), this);
    addRectAction->setIcon(QIcon(":/resources/icons/addRect.png"));
    connect(addRectAction, SIGNAL(triggered()), scene, SLOT(addRect()));

    removeAction = new QAction(tr("Remove selected elements"), this);
    removeAction->setIcon(QIcon(":/resources/icons/delete.png"));
    connect(removeAction, SIGNAL(triggered()), scene, SLOT(removeSelected()));

    helpBrowserAction = new QAction(tr("Open Help menu"), this);
    helpBrowserAction->setShortcut(tr("Ctrl+H"));
    helpBrowserAction->setIcon(QIcon(":/resources/icons/help.png"));
    connect(helpBrowserAction, SIGNAL(triggered()), this, SLOT(getSomeHelp()));

}

void MainWindow::createMenus(){
    fileMenu = this->menuBar()->addMenu(tr("File"));
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(exitAction);

    editMenu = this->menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(selectionAction);
    editMenu->addAction(addLineAction);
    editMenu->addAction(addCircleAction);
    editMenu->addAction(addRectAction);
    editMenu->addAction(removeAction);

    helpMenu = this->menuBar()->addMenu("Help");
    helpMenu->addAction(helpBrowserAction);
}

void MainWindow::createToolBars(){
    quickAcessToolBar = addToolBar(tr("Quick Access Menu"));
    quickAcessToolBar->addAction(saveAsAction);
    quickAcessToolBar->addSeparator();
    quickAcessToolBar->addAction(selectionAction);
    quickAcessToolBar->addAction(addLineAction);
    quickAcessToolBar->addAction(addCircleAction);
    quickAcessToolBar->addAction(addRectAction);
    quickAcessToolBar->addAction(removeAction);
}

void MainWindow::saveAs(){
    QString outName = QFileDialog::getSaveFileName(this, "Output file", tr("C:/Users/User/Desktop"), "Image (*.png)");
    QPixmap pixmap = QPixmap::grabWidget(view);
    pixmap.save(outName);
}

void MainWindow::getSomeHelp(){
    helpBrowser->resize(400, 300);
    helpBrowser->show();
}




