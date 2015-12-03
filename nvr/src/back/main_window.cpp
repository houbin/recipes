#include "main_window.h"
#include "ui_main_window.h"
#include <QDesktopWidget>
#include <QLayout>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QSize>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetFullScreen();
    //SetMaxScreen();

    setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);
    setPalette(palette);

    QMargins m(0, 0, 0, 0);
    main_layout_ = new QVBoxLayout;
    main_layout_->setContentsMargins(m);
    setLayout(main_layout_);

    // right button menu
    main_window_right_button_menu_ = new QMenu(this);

    // main menu
    main_menu_ = new MainMenu(this);

    // main display window
    display_window_ = new DisplayWindow(this);

    main_layout_->addWidget(display_window_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

qint32 MainWindow::Init()
{
    qint32 ret = 0;

    ret = InitRightButtonMenu();
    if (ret != 0)
    {
        return ret;
    }

    ret = main_menu_->Init();
    if (ret != 0)
    {
        return ret;
    }

    ret = display_window_->Init();
    if (ret != 0)
    {
        return ret;
    }

    return 0;
}

void MainWindow::ShowMainMenu()
{
    main_menu_->exec();

    return;
}

void MainWindow::SplitOneScreen()
{
    display_window_->SplitScreen(1);
    return;
}

void MainWindow::SplitFourScreen()
{
    display_window_->SplitScreen(4);
    return;
}

void MainWindow::SplitNineScreen()
{
    display_window_->SplitScreen(9);
    return;
}

void MainWindow::SplitSixteenScreen()
{
    display_window_->SplitScreen(16);
    return;
}

void MainWindow::SetupChannel()
{
    return;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        SetMaxScreen();
    }

    return;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        // show right button menu
        logger->debug("enter right button press of main window");
        main_window_right_button_menu_->exec(QCursor::pos());
    }

    return;
}

void MainWindow::SetFullScreen()
{
    // erase titile bar
    setWindowFlags(Qt::Window);
    showFullScreen();

    return;
}

void MainWindow::SetMaxScreen()
{
    setWindowFlags(Qt::Window);
    showMaximized();

    return;
}
