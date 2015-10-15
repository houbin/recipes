#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <../common.h>
#include <QDialog>
#include <QToolButton>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QVector>
#include <QString>
#include <QIcon>
#include <QListWidget>
#include <QModelIndex>

namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

    qint32 Init();

private:
    Ui::MainMenu *ui;

    QVBoxLayout *main_layout_;
    QListWidget *main_list_widget_;
    //QGridLayout *menu_layout_;
    QHBoxLayout *bottom_layout_;

    QPushButton *quit_button_;
};

#endif // MAIN_MENU_H
