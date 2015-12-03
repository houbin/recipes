#include "menu_window.h"
#include "ui_menu_window.h"

MenuWindow::MenuWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);

    layout_ = new QHBoxLayout;
}

MenuWindow::~MenuWindow()
{
    delete ui;
}
