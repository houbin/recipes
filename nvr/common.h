#ifndef COMMON
#define COMMON

#include <QtGlobal>
#include <QDebug>
#include <QGridLayout>
#include <QtSql/QSqlDatabase>
#include "util/log4qt/logger.h"
#include <QPalette>
#include <QMutex>
#include <QVector>
#include <QtSql/QSql>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QTextCodec>
#include "util/log4qt/basicconfigurator.h"
#include "error_code.h"
#include "src/display_window.h"

extern Log4Qt::Logger *logger;
extern QSqlDatabase db;

class DisplayWindow;
extern DisplayWindow *w;
#pragma comment(lib, "lib/win/JvClient.lib")

#define MAX_BOX_COUNT 64

#endif // COMMON

