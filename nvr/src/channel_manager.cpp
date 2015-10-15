#include "ui_channel_manager.h"
#include <QStandardItem>
#include <QLatin1String>
#include "common.h"

#if defined(Q_OS_WIN32)
#include <WS2tcpip.h>
#elif defined(Q_OS_LINUX)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

/*  device search model
 *
 *
*/
DeviceSearchModel::DeviceSearchModel()
{
    header_list_.append(tr("Device Name"));
    header_list_.append(tr("IP address"));
    header_list_.append(tr("Port"));
    header_list_.append(tr("Cloudsee ID"));
    header_list_.append(tr("Protocol"));
    header_list_.append(tr("Manufacture"));
}

DeviceSearchModel::~DeviceSearchModel()
{

}

int DeviceSearchModel::rowCount(const QModelIndex &parent) const
{
    return search_result_list_.count();
}

int DeviceSearchModel::columnCount(const QModelIndex &parent) const
{
    return header_list_.count();
}

QVariant DeviceSearchModel::data(const QModelIndex &index, int role) const
{
    QString yst_str;

    if (!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }
    else if (role == Qt::DisplayRole)
    {
        int row = index.row();
        int column = index.column();

        switch (column)
        {
            case 0:
                return search_result_list_[row]->name;

            case 1:
                return search_result_list_[row]->client_ip;

            case 2:
                return search_result_list_[row]->client_port;

            case 3:
                yst_str.append(search_result_list_[row]->group);
                yst_str.append(QString::number(search_result_list_[row]->yst_id));
                return yst_str;

            case 4:
                return search_result_list_[row]->protocol_type;

            case 5:
                return search_result_list_[row]->manufacture;

            default:
                return QVariant();
        }
    }

    return QVariant();
}

QVariant DeviceSearchModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }
    else if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Vertical)
        {
            return QVariant();
        }

        return header_list_[section];
    }

    return QVariant();
}

bool DeviceSearchModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);

    if (position == -1)
    {
        position = search_result_list_.size();
    }

    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; row++)
    {
        SearchResult *result = new SearchResult();
        search_result_list_.insert(position, result);
    }

    endInsertRows();

    return true;
}

bool DeviceSearchModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);

    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; row++)
    {
        search_result_list_.removeAt(position);
    }

    endRemoveRows();

    return true;
}

bool DeviceSearchModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int first_number;
    QString yst_str;
    QString yst_id_str;

    if (index.isValid() && role == Qt::EditRole)
    {
        int row = index.row();
        int column = index.column();

        SearchResult *result = search_result_list_.value(row);

        switch (column)
        {
            case 0:
                result->name = value.toString();
                break;

            case 1:
                result->client_ip = value.toString();
                break;

            case 2:
                result->client_port = value.toInt();
                break;

            case 3:
                yst_str = value.toString();
                first_number = yst_str.indexOf(QRegExp("[0-9]"));
                yst_id_str = yst_str.mid(first_number);
                result->group = yst_str.left(first_number);
                result->yst_id = yst_id_str.toInt();
                break;

            case 4:
                result->protocol_type = value.toString();
                break;

            case 5:
                result->manufacture = value.toString();
                break;

            default:
                return false;
        }

        emit(dataChanged(index, index));
        return true;
    }

    return false;
}

bool DeviceSearchModel::Contains(QString protocol, quint32 key)
{
    QList<SearchResult*>::iterator iter = search_result_list_.begin();
    for (iter; iter != search_result_list_.end(); iter++)
    {
        SearchResult *result = *iter;

        if (protocol == tr("cloudsee"))
        {
            if (key == result->yst_id)
            {
                return true;
            }
        }
    }

    return false;
}

/*  channel manager
 *
 *
*/
ChannelManager::ChannelManager(QWidget *parent) :
    QDialog(parent),
    if_start_search_(false),
    ui(new Ui::ChannelManager)
{
    ui->setupUi(this);

    setWindowTitle(tr("channel manager"));
    resize(1150, 600);

    main_layout_ = new QGridLayout(this);

    setLayout(main_layout_);

    search_label_ = new QLabel(tr("searched device:"));

    search_model_ = new DeviceSearchModel();
    search_table_ = new QTableView(this);
    search_table_->setModel(search_model_);
    search_table_->verticalHeader()->hide();
    search_table_->setSelectionBehavior(QAbstractItemView::SelectRows);
    search_table_->setAutoScroll(true);
    search_table_->setSelectionMode(QAbstractItemView::SingleSelection);
    search_table_->setSelectionBehavior(QAbstractItemView::SelectRows);
    search_table_->setGridStyle(Qt::NoPen);
    search_table_->horizontalHeader()->setStretchLastSection(true);
    // set width of "ip address"
    search_table_->setColumnWidth(1, 160);

    search_button_ = new QPushButton(tr("search"), this);

    op_layout_ = new QHBoxLayout;
    add_button_ = new QPushButton(QIcon(":/images/up_arrow.png"), "", this);
    del_button_ = new QPushButton(QIcon(":/images/down_arrow.png"), "", this);
    op_layout_->addWidget(add_button_);
    op_layout_->addSpacing(200);
    op_layout_->addWidget(del_button_);

    added_label_ = new QLabel(tr("added device:"));
    added_table_ = new QTableView(this);

    button_layout_ = new QVBoxLayout;
    manual_add_button_ = new QPushButton(tr("manual add"), this);
    one_key_set_ip_button_ = new QPushButton(tr("quick set ip"), this);
    button_layout_->addWidget(manual_add_button_, 0);
    button_layout_->addWidget(one_key_set_ip_button_, 0);

    quit_button_ = new QPushButton(tr("quit"), this);

    main_layout_->addWidget(search_label_, 0, 0, Qt::AlignLeft);
    main_layout_->addWidget(search_table_, 1, 0);
    main_layout_->addWidget(search_button_, 1, 1, Qt::AlignTop);
    main_layout_->addLayout(op_layout_, 2, 0, Qt::AlignCenter);
    main_layout_->addWidget(added_label_, 3, 0);
    main_layout_->addWidget(added_table_, 4, 0);
    main_layout_->addLayout(button_layout_, 4, 1, Qt::AlignTop);
    main_layout_->addWidget(quit_button_, 5, 1, Qt::AlignTop);

    device_discovery_ = new DeviceDiscovery(this);
}

ChannelManager::~ChannelManager()
{
    delete ui;
}

void ChannelManager::Init()
{
    // init device discovery
    device_discovery_->Init();
    connect(search_button_, SIGNAL(clicked(bool)), this, SLOT(StartSearch(bool)));

    return;
}

void ChannelManager::StartSearch(bool)
{
    // clear old search result
    if (search_model_->rowCount(QModelIndex()) != 0)
    {
        search_model_->removeRows(0, search_model_->rowCount(QModelIndex()), QModelIndex());
    }

    device_discovery_->StartSearch();

    return;
}

void ChannelManager::NewSearchResult(SearchResult *result)
{
    logger->debug("search callback, name %1, ip %2", result->name, result->client_ip);

    if (!search_model_->Contains(result->protocol_type,result->yst_id))
    {
        search_model_->insertRows(0, 1, QModelIndex());

        // device name
        QModelIndex index = search_model_->index(0, 0, QModelIndex());
        search_model_->setData(index, result->name, Qt::EditRole);

        // ip
        index = search_model_->index(0, 1, QModelIndex());
        search_model_->setData(index, result->client_ip, Qt::EditRole);

        // port
        index = search_model_->index(0, 2, QModelIndex());
        search_model_->setData(index, result->client_port, Qt::EditRole);

        // yst str = group + yst id
        QString yst_str(result->group);
        yst_str.append(QString::number(result->yst_id));
        index = search_model_->index(0, 3, QModelIndex());
        search_model_->setData(index, yst_str, Qt::EditRole);

        // protocol
        index = search_model_->index(0, 4, QModelIndex());
        search_model_->setData(index, result->protocol_type, Qt::EditRole);

        // manufacture
        index = search_model_->index(0, 5, QModelIndex());
        search_model_->setData(index, result->manufacture, Qt::EditRole);
    }

    delete result;

    return;
}

