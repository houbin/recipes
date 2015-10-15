#include "main_menu.h"
#include "ui_main_menu.h"
#include <QSize>


MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    resize(880, 520);

    {
        main_list_widget_ = new QListWidget(this);
        main_list_widget_->setViewMode(QListView::IconMode);
        main_list_widget_->setIconSize(QSize(120, 105));
        main_list_widget_->setMovement(QListView::Static);
        main_list_widget_->setSpacing(50);
        main_list_widget_->setResizeMode(QListView::Adjust);
        main_list_widget_->setWordWrap(true);
        main_list_widget_->setMouseTracking(true);

        QVector<QString> button_name;
        QVector<QString> button_text_name;
        button_name << "channel manager" << "replay record" << "record setting";
        button_text_name << tr("channel manager") << tr("replay record") << tr("record setting");

        int count = button_name.size();
        for(int i = 0; i < count; i++)
        {
            QString name = button_name[i];
            QString text_name = button_text_name[i];

            QString pic_path(":/images/");
            pic_path.append(name.replace(" ", "_"));
            pic_path.append(".png");

            QListWidgetItem *item = new QListWidgetItem(QIcon(pic_path), text_name);
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

            main_list_widget_->addItem(item);
        }
    }

    connect(main_list_widget_, SIGNAL(itemClicked(QListWidgetItem*)),
            this->parent(), SLOT(ShowSubMenu(QListWidgetItem*)));

    // create quit button
    {
        quit_button_ = new QPushButton(tr("quit"), this);
        connect(quit_button_, SIGNAL(clicked(bool)), this, SLOT(close()));

        // bottom layout
        bottom_layout_ = new QHBoxLayout;
        bottom_layout_->addStretch(1);
        bottom_layout_->addWidget(quit_button_);
        bottom_layout_->setSizeConstraint(QLayout::SetFixedSize);
        bottom_layout_->setContentsMargins(0, 0, 50, 40);
    }

    // main layout
    main_layout_ = new QVBoxLayout;
    main_layout_->setContentsMargins(0, 0, 0, 0);
    main_layout_->addWidget(main_list_widget_);
    main_layout_->addLayout(bottom_layout_);
    setLayout(main_layout_);
}

MainMenu::~MainMenu()
{
    delete ui;
}

qint32 MainMenu::Init()
{
    setWindowTitle(tr("main menu"));

    return 0;
}
