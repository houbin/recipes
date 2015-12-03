#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QDialog>
#include <QList>
#include <QLabel>
#include <QtGlobal>
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QVector>
#include <QMenu>
#include <QAction>
#include "../common.h"
#include "src/stream_dev.h"
#include "src/main_menu.h"
#include "src/display_window.h"
#include "util/log4qt/logger.h"

namespace Ui {
class MainWindow;
}

#define MAX_DISPLAY_WINDOW_COUNT 16

class MainWindow : public QDialog
{
    Q_OBJECT

private:
    qint32 InitRightButtonMenu();

    qint32 SetChannelLayout(quint8 channel_counts, quint8 start_channel);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    qint32 Init();

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void SetFullScreen();
    void SetMaxScreen();

    void ShowMainMenu();
    void SplitOneScreen();
    void SplitFourScreen();
    void SplitNineScreen();
    void SplitSixteenScreen();
    void SetupChannel();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *main_layout_;

    // display window
    DisplayWindow *display_window_;
};

#endif // MAIN_WINDOW_H
