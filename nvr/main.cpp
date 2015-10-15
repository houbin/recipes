#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>
#include <QTranslator>
#include <QFile>
#include "common.h"
#include "src/display_window.h"
#include <QAbstractTableModel>

Log4Qt::Logger *logger = NULL;
QSqlDatabase db;
DisplayWindow *w = NULL;

qint32 CreateAndInitConfigTable()
{
    bool r;
    QSqlQuery query;

    r = query.exec("create table ConfigTable(Key varchar(64), ValueInt INTEGER, ValueStr varchar(256), PRIMARY KEY(Key));");
    if (!r)
    {
        logger->error("query exec error, msg ", query.lastError().text());
        return -ERROR_SQL_EXEC;
    }

    r = query.exec("insert into ConfigTable values('DefaultLayout',  2, '');");
    if (!r)
    {
        logger->error("query exec error, msg ", query.lastError().text());
        return -ERROR_SQL_EXEC;
    }

    return 0;
}

qint32 CreateAndInitLayoutTable()
{
    bool r;
    QSqlQuery query;

    r = query.exec("create table LayoutTable(ID INTEGER AUTO_INCREMENT NOT NULL, Name VARCHAR(64), ViewType INTEGER NOT NULL, SplitType INTEGER NOT NULL, StreamIDs VARCHAR(1000) NOT NULL, PRIMARY KEY(ID ASC));");
    if (!r)
    {
        logger->error("query exec error, msg ", query.lastError().text());
        return -ERROR_SQL_EXEC;
    }

    query.prepare("insert into LayoutTable values(:ID, :Name, :IfDefault, :SplitType, :StreamIDs);");

    qint32 i = 1;
    QString temp;
    for (i; i <= MAX_BOX_COUNT; i++)
    {
        temp.append("-1,");
    }

    for (i = 1; i <= 4; i++)
    {
        query.bindValue(0, i);
        query.bindValue(1, "");
        query.bindValue(2, 0);
        query.bindValue(3, i * i);
        query.bindValue(4, temp);

        r = query.exec();
        if (!r)
        {
            logger->error("query exec error, msg ", query.lastError().text());
            return -ERROR_SQL_EXEC;
        }
    }

    return 0;
}

qint32 InitEmptyDB()
{
    qint32 ret = 0;

    ret = CreateAndInitConfigTable();
    if (ret != 0)
    {
        return ret;
    }

    ret = CreateAndInitLayoutTable();
    if (ret != 0)
    {
        return ret;
    }

    return 0;
}

qint32 InitYst()
{
    logger->debug("init yst");

#if defined(Q_OS_WIN32)
    bool ret;
#elif defined(Q_OS_LINUX)
    int ret;
#endif
    ret = JVC_InitSDK(-1);
    if (ret == 0)
    {
        logger->warn("init yst error");
        return -ERROR_INIT_YST;
    }

#if defined(Q_OS_WIN32)
    JVC_RegisterCallBack(YST_ClientConnectCallBack,
                         YST_ClientNormalDataCallBack,
                         YST_ClientCheckResultCallBack,
                         YST_ClientChatDataCallBack,
                         YST_ClientTextDataCallBack,
                         YST_ClientDownloadCallBack,
                         YST_ClientPlayDataCallBack);
#elif defined(Q_OS_LINUX)

#endif
    JVC_EnableLog(FALSE);
    JVC_SetLanguage(JVN_LANGUAGE_ENGLISH);

    return 0;
}

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(resource);

    QApplication a(argc, argv);

    // use chinese
    QTranslator t;
    t.load("chinese.qm");
    a.installTranslator(&t);

    // init logger
    Log4Qt::BasicConfigurator::configure();
    logger = Log4Qt::Logger::rootLogger();

    // check if program has already run
    QSharedMemory mem("VM");
    if (!mem.create(1))
    {
        QMessageBox::information(NULL, QObject::tr("NVR"), QObject::tr("You have run this program"), QMessageBox::Yes);
        return -1;
    }

    // init sqlite database
    bool if_empty_db = false;
    QFile f("nvr.db");
    if (!f.exists())
    {
        f.open(QIODevice::ReadWrite);
        f.close();
        if_empty_db = true;
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("nvr.db");
    if (!db.open())
    {
        QMessageBox::information(NULL, QObject::tr("NVR"), QObject::tr("Failed to open DataBase"), QMessageBox::Yes);
        return -1;
    }

    if (if_empty_db)
    {
        qint32 ret;
        ret = InitEmptyDB();
        if (ret != 0)
        {
            QMessageBox::information(NULL, QObject::tr("NVR"), QObject::tr("failed to init DataBase"), QMessageBox::Yes);
            return -1;
        }
    }

    InitYst();

    DisplayWindow main_window;
    w = &main_window;

    main_window.Init();
    main_window.show();

    return a.exec();
}
