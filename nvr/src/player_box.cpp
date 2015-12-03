#include "player_box.h"

PlayerBox::PlayerBox(qint32 id, QWidget *parent)
    : QLabel(parent), id_(id)
{
    setAutoFillBackground(true);
    setAlignment(Qt::AlignCenter);

    setVisible(true);
    setStyleSheet("QLabel{border: 1px solid white; color: white; background-color: black;}");
    setTextFormat(Qt::PlainText);
    setText(QString("label number: %1").arg(id_));
    setVisible(false);
}

qint32 PlayerBox::Highlight()
{
    setStyleSheet("QLabel{border: 2px solid red; color: white; background-color: black;}");

    return 0;
}

qint32 PlayerBox::UnHighlight()
{
    setStyleSheet("QLabel{border: 1px solid white; color: white; background-color: black;}");

    return 0;
}
