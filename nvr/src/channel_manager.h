#ifndef CHANNEL_MANAGER_H
#define CHANNEL_MANAGER_H

#include <QtGlobal>
#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QAbstractTableModel>
#include <QLabel>
#include <QHBoxLayout>
#include <QVector>
#include <QList>
#include <QMap>
#include <QTableView>
#include <QPushButton>
#include "src/yst_usedef.h"
#include "src/device_discovery.h"

namespace Ui {
class ChannelManager;
}

class DeviceSearchModel : public QAbstractTableModel
{
public:
    DeviceSearchModel();
    ~DeviceSearchModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool insertRows(int position, int rows, const QModelIndex &index);
    bool removeRows(int position, int rows, const QModelIndex &index);
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    bool Contains(QString protocol, quint32 key);

private:
    QStringList header_list_;

    QList<SearchResult*> search_result_list_;
};

class ChannelManager : public QDialog
{
    Q_OBJECT

public:
    explicit ChannelManager(QWidget *parent = 0);
    ~ChannelManager();

    void Init();

public slots:
    void StartSearch(bool);
    void NewSearchResult(SearchResult *result);

private:
    Ui::ChannelManager *ui;

    QGridLayout *main_layout_;

    QLabel *search_label_;

    bool if_start_search_;
    DeviceSearchModel *search_model_;
    QTableView *search_table_;

    QPushButton *search_button_;

    QHBoxLayout *op_layout_;
    QPushButton *add_button_;
    QPushButton *del_button_;

    QLabel *added_label_;
    QTableView *added_table_;

    QVBoxLayout *button_layout_;
    QPushButton *manual_add_button_;
    QPushButton *one_key_set_ip_button_;

    QPushButton *quit_button_;

    DeviceDiscovery *device_discovery_;
};

#endif // CHANNEL_MANAGER_H
