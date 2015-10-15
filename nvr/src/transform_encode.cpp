#include "src/transform_encode.h"

QString gbk_2_utf8(const char *in)
{
    QTextCodec *gbk = QTextCodec::codecForName("gbk");

    return gbk->toUnicode(in);
}

QString gbk_2_utf8(const QString &in)
{
    QTextCodec *gbk = QTextCodec::codecForName("gbk");
    //QTextCodec *utf8 = QTextCodec::codecForName("uft8");

    return gbk->toUnicode(gbk->fromUnicode(in));
}
