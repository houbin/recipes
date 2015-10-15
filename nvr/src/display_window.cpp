#include "display_window.h"
#include "ui_display_window.h"

DisplayWindow::DisplayWindow(QWidget *parent) :
    QWidget(parent), highlight_box_(NULL)
{
    SetFullScreen();

    setContentsMargins(1, 1, 1, 1);

    layout_= new QGridLayout(this);
    layout_->setSpacing(0);
    layout_->setMargin(0);
    setLayout(layout_);

    // main menu
    main_menu_ = new MainMenu(this);
    main_window_right_button_menu_ = new QMenu(this);

    // sub menu
    channel_manager_ = new ChannelManager(this);
    qRegisterMetaType<SearchResult>("SearchResult");
    connect(this, SIGNAL(NewSearchResult(SearchResult*)),
            channel_manager_, SLOT(NewSearchResult(SearchResult*)));
}

DisplayWindow::~DisplayWindow()
{

}

qint32 DisplayWindow::Init()
{
    qint32 ret;

    ret = main_menu_->Init();
    if (ret != 0)
    {
        return ret;
    }

    channel_manager_->Init();

    // init right button menu
    ret = InitRightButtonMenu();
    if (ret != 0)
    {
        return ret;
    }

    // init all player box
    ret = InitAllPlayerBox();
    if (ret != 0)
    {
        return ret;
    }

    ret = ShowDefaultLayout();
    if (ret != 0)
    {
        return ret;
    }

    return 0;
}

qint32 DisplayWindow::InitRightButtonMenu()
{
    show_main_menu_action_ = new QAction(tr("main menu"), main_window_right_button_menu_);
    split_screen_menu_ = new QMenu(tr("split screen"), main_window_right_button_menu_);
    split_screen_1_action_ = new QAction(tr("one screens"), split_screen_menu_);
    split_screen_4_action_ = new QAction(tr("four screens"), split_screen_menu_);
    split_screen_9_action_ = new QAction(tr("nine screens"), split_screen_menu_);
    split_screen_16_action_ = new QAction(tr("sixteen screens"), split_screen_menu_);

    split_screen_menu_->addAction(split_screen_1_action_);
    main_window_right_button_menu_->addSeparator();
    split_screen_menu_->addAction(split_screen_4_action_);
    main_window_right_button_menu_->addSeparator();
    split_screen_menu_->addAction(split_screen_9_action_);
    main_window_right_button_menu_->addSeparator();
    split_screen_menu_->addAction(split_screen_16_action_);

    setup_channel_action_ = new QAction(tr("setup channel"), main_window_right_button_menu_);

    main_window_right_button_menu_->addAction(show_main_menu_action_);
    main_window_right_button_menu_->addSeparator();
    main_window_right_button_menu_->addMenu(split_screen_menu_);
    main_window_right_button_menu_->addSeparator();
    main_window_right_button_menu_->addAction(setup_channel_action_);

    connect(show_main_menu_action_, SIGNAL(triggered()), this, SLOT(ShowMainMenu()));
    connect(split_screen_1_action_, SIGNAL(triggered()), this, SLOT(SplitOneScreen()));
    connect(split_screen_4_action_, SIGNAL(triggered()), this, SLOT(SplitFourScreen()));
    connect(split_screen_9_action_, SIGNAL(triggered()), this, SLOT(SplitNineScreen()));
    connect(split_screen_16_action_,SIGNAL(triggered()), this, SLOT(SplitSixteenScreen()));
    connect(setup_channel_action_,  SIGNAL(triggered()), this, SLOT(SetupChannel()));

    return 0;
}

qint32 DisplayWindow::InitAllPlayerBox()
{
    qint32 i = 0;

    for (i; i < MAX_BOX_COUNT; i++)
    {
        PlayerBox *box = CreatePlayerBox(i);
        player_box_vec_.push_back(box);
    }

    return 0;
}


qint32 DisplayWindow::ShowDefaultLayout()
{
    qint32 ret = 0;
    qint32 layout_id = -1;

    // show default layout
    ret = GetDefaultLayoutId(layout_id);
    if (ret != 0)
    {
        return ret;
    }

    // standard output
    qint32 box_number = layout_id * layout_id;
    ret = SplitScreen(box_number);
    if (ret != 0)
    {
        return ret;
    }

    return 0;
}

void DisplayWindow::SetFullScreen()
{
    // erase titile bar
    setWindowFlags(Qt::Window);
    showFullScreen();

    return;
}

void DisplayWindow::SetMaxScreen()
{
    setWindowFlags(Qt::Window);
    showMaximized();

    return;
}

PlayerBox *DisplayWindow::CreatePlayerBox(qint32 id)
{
    PlayerBox *box = new PlayerBox(id, this);
    box->installEventFilter(this);

    return box;
}

qint32 DisplayWindow::GetDefaultLayoutId(qint32 &layout_id)
{
    bool r;
    QSqlQuery query;

    r = query.exec("select ValueInt from ConfigTable where Key = 'DefaultLayout';");
    if (!r)
    {
        logger->error("get default layout id error");
        return -ERROR_SQL_EXEC;
    }

    if (!query.next())
    {
        return -ERROR_SQL_EXEC;
    }

    qint32 layout_id_number = query.record().indexOf("ValueInt");
    layout_id = query.record().value(layout_id_number).toInt();

    return 0;
}

qint32 DisplayWindow::SetDefaultLayoutId(qint32 layout_id)
{
    bool r;
    QSqlQuery query;

    r = query.exec(QString("update ConfigTable set ValueInt=%1 where Key='DefaultLayout';").arg(layout_id));
    if (!r)
    {
        logger->error("set default layout id error");
        return -ERROR_SQL_EXEC;
    }

    return 0;
}

qint32 DisplayWindow::RemoveLayout()
{
    qint32 count = 0;

    count = layout_->count();
    logger->debug(QString("current box count %1").arg(count));
    while (count-- > 0)
    {
        QWidget *temp = layout_->itemAt(0)->widget();
        layout_->removeWidget(temp);
        PlayerBox *box = static_cast<PlayerBox*>(temp);
        box->setVisible(false);
    }

    return 0;
}

qint32 DisplayWindow::SplitScreen(qint32 box_number)
{
    qint32 ret = 0;
    qint32 i = 0;
    qint32 j = 0;
    qint32 layout_id = 0;
    qint32 row_count = 0;
    qint32 column_count = 0;

    logger->debug(QString("split screen, screen number %1").arg(box_number));

    layout_id = row_count = column_count = sqrt(box_number);
    ret = SetDefaultLayoutId(layout_id);
    if (ret != 0)
    {
        return ret;
    }

    ret = RemoveLayout();
    if (ret != 0)
    {
        return ret;
    }

    for (i = 0; i < row_count; i++)
    {
        for (j = 0; j < column_count; j++)
        {
            PlayerBox *box = player_box_vec_[i * row_count + j];
            layout_->addWidget(box, i, j, 1, 1);
            box->setVisible(true);
        }
    }

    if (highlight_box_)
    {
        if (layout_->indexOf(highlight_box_) == -1)
        {
            highlight_box_->UnHighlight();
        }
    }

    return 0;
}

void DisplayWindow::ShowMainMenu()
{
    main_menu_->exec();

    return;
}

void DisplayWindow::SplitOneScreen()
{
    SplitScreen(1);
    return;
}

void DisplayWindow::SplitFourScreen()
{
    SplitScreen(4);
    return;
}

void DisplayWindow::SplitNineScreen()
{
    SplitScreen(9);
    return;
}

void DisplayWindow::SplitSixteenScreen()
{
    SplitScreen(16);
    return;
}

void DisplayWindow::SetupChannel()
{
    return;
}

void DisplayWindow::ShowSubMenu(QListWidgetItem *item)
{
    QString text = item->text();

    if (text == tr("channel manager"))
    {
        ShowChannelManager();
    }
    else
    {
        logger->warn("this sub menu is not implement, and text of sub menu is %1", text);
    }

    return;
}

void DisplayWindow::ShowChannelManager()
{
    main_menu_->close();

    channel_manager_->exec();

    return;
}

/* override funcitons of parent class
*/

qint32 DisplayWindow::HighlightBox(PlayerBox *box)
{
    if (box == highlight_box_)
    {
        return 0;
    }

    if (highlight_box_ != NULL)
    {
        highlight_box_->UnHighlight();
    }

    box->Highlight();
    highlight_box_ = box;

    return 0;
}

bool DisplayWindow::eventFilter(QObject *obj, QEvent *event)
{
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);

    if (mouse_event->button() == Qt::RightButton
            && mouse_event->type() == QEvent::MouseButtonPress)
    {
        PlayerBox *box = static_cast<PlayerBox*>(obj);
        HighlightBox(box);

        main_window_right_button_menu_->exec(QCursor::pos());
        return true;
    }
    else if (mouse_event->button() == Qt::LeftButton
             && mouse_event->type() == QEvent::MouseButtonPress)
    {
        PlayerBox *box = static_cast<PlayerBox*>(obj);
        HighlightBox(box);
        return true;
    }

    return true;
}

void DisplayWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        SetMaxScreen();
    }

    return ;
}

// yst callback
void DisplayWindow::SearchCallBack(SearchResult *result)
{
    emit NewSearchResult(result);

    return;
}
