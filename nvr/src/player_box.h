#ifndef PLAYERBOX_H
#define PLAYERBOX_H

#include <QtGlobal>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QMenu>
#include "main_menu.h"
#include "common.h"

enum STREAM_PLAY_TYPE
{
    STREAM_PLAY_RECORD,
    STREAM_PLAY_PREVIEW,

    STREAM_PLAY_TYPE_MAX
};

enum STREAM_CONNECT_TYPE
{
    STREAM_CONNECT_OK,
    STREAM_CONNECT_FAILED,
    STREAM_CONNECT_NOT_EXIST,

    STREAM_CONNECT_TYPE_MAX
};

class DisplayWindow;
class PlayerBox : public QLabel
{
    Q_OBJECT
public:
    explicit PlayerBox(qint32 id, QWidget *parent = 0);

    qint32 Highlight();
    qint32 UnHighlight();

private:
    qint32 id_;

    qint32 channel_id_;
    STREAM_CONNECT_TYPE connect_type_;
    STREAM_PLAY_TYPE play_type_;
};

#endif // PLAYERBOX_H
