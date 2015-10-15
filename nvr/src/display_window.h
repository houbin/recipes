#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include "../common.h"
#include <QListWidgetItem>
#include "channel_manager.h"
#include "src/yst_usedef.h"
#include "src/player_box.h"
#include "src/main_menu.h"
#include "inc/JVNSDKDef.h"

typedef struct SplitScreenInfo_T
{
    qint32 id;
    QString name;
    qint32 split_type;
    QVector<qint32> stream_sequence;
}SplitScreenInfo;

class PlayerBox;
class MainMenu;

class DisplayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWindow(QWidget *parent = 0);
    ~DisplayWindow();

    qint32 Init();

    void SetMaxScreen();
    void SetFullScreen();

    qint32 GetDefaultLayoutId(qint32 &layout_id);
    qint32 SetDefaultLayoutId(qint32 layout_id);

    qint32 GetDefaultSplitScreenInfo(SplitScreenInfo &split_screen_info);
    qint32 SetDefaultSplitScreenInfo(SplitScreenInfo &split_screen_info);
    qint32 DecodeLayoutStr(QString layout_str, QVector<qint32> &stream_sequence);
    qint32 EncodeLayoutStr(QVector<qint32> stream_sequence, QString &layout_str);

    qint32 GetLayoutInfoById(qint32 layout_id);
    qint32 GetLayoutInfoByName(QString name);

    qint32 RemoveLayout();
    qint32 SplitScreen(qint32 box_number);

    void ShowChannelManager();

    // search return
    void SearchCallBack(SearchResult *result);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    qint32 InitRightButtonMenu();
    qint32 InitAllPlayerBox();
    qint32 ShowDefaultLayout();
    PlayerBox *CreatePlayerBox(qint32 id);

    qint32 HighlightBox(PlayerBox *box);

signals:
    void NewSearchResult(SearchResult *result);

private slots:
    void ShowMainMenu();
    void SplitOneScreen();
    void SplitFourScreen();
    void SplitNineScreen();
    void SplitSixteenScreen();
    void SetupChannel();

    // sub menu
    void ShowSubMenu(QListWidgetItem *item);

private:
    QGridLayout *layout_;

    // all player box
    QVector<PlayerBox*> player_box_vec_;

    PlayerBox *highlight_box_;

    // right button menu
    QMenu *main_window_right_button_menu_;
    QAction *show_main_menu_action_;
    QMenu *split_screen_menu_;
    QAction *split_screen_1_action_;
    QAction *split_screen_4_action_;
    QAction *split_screen_9_action_;
    QAction *split_screen_16_action_;
    QAction *setup_channel_action_;

    // main menu
    MainMenu *main_menu_;

    // sub menu
    // channel manager
    ChannelManager *channel_manager_;
};

#endif // DISPLAY_WINDOW_H
