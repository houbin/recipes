#ifndef UTIL_LOGGER_H_
#define UTIL_LOGGER_H_

#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include <pthread.h>
#include <stdarg.h>
#include <assert.h>
#include <boost/scoped_ptr.hpp>
#include "env.h"
#include "mutex.h"
#include "utime.h"
#include "clock.h"
#include "env_posix.h"

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

using namespace std;

namespace util {

enum LogLevel
{
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5,
    NUM_LOG_LEVELS,
};

class Logger
{
private:
    string log_file_;
    const static int kRollPerSeconds_ = 24 * 60 * 60;

    int count_;

    boost::scoped_ptr<PosixWritableFile> file_;

    time_t last_roll_;

    static LogLevel g_log_level;

    Mutex mutex_;

public:
    Logger(const string& log_file, bool threadsafe = true);

    ~Logger();

    void Logv(const char* format, va_list ap);
    void Append(const Slice &data);

    static string GetLogFileName(const string& log_file, time_t *now);
    bool RollFile();

    static LogLevel GetLogLevel();
    static int32_t SetLogLevel(LogLevel level);
};

int32_t NewLogger(const char* name, Logger **logger);
void LogFunc(Logger *info_log, const char* format, ...);

#define Log(info_log, format, ...) LogFunc(info_log, "[%s:%s:%d]: "format, __FILE__,  __func__, __LINE__, ##__VA_ARGS__)

#define LOG_TRACE(info_log, format, ...) if (util::Logger::GetLogLevel() <= TRACE) \
    LogFunc(info_log, "TRACE [%s:%s:%d]: "format, __FILE__,  __func__, __LINE__, ##__VA_ARGS__)

#define LOG_DEBUG(info_log, format, ...) if (util::Logger::GetLogLevel() <= DEBUG) \
    LogFunc(info_log, "DEBUG [%s:%s:%d]: "format, __FILE__,  __func__, __LINE__, ##__VA_ARGS__)

#define LOG_INFO(info_log, format, ...) if (util::Logger::GetLogLevel() <= INFO) \
    LogFunc(info_log, "INFO  [%s:%s:%d]: "format, __FILE__,  __func__, __LINE__, ##__VA_ARGS__)

#define LOG_WARN(info_log, format, ...) if (util::Logger::GetLogLevel() <= WARN) \
    LogFunc(info_log, "WARN  [%s:%s:%d]: "format, __FILE__,  __func__, __LINE__, ##__VA_ARGS__)

#define LOG_ERROR(info_log, format, ...) if (util::Logger::GetLogLevel() <= ERROR) \
    LogFunc(info_log, "ERROR [%s:%s:%d]: "format, __FILE__,  __func__, __LINE__, ##__VA_ARGS__)

#define LOG_FATAL(info_log, format, ...) if (util::Logger::GetLogLevel() <= FATAL) \
    LogFunc(info_log, "FATAL [%s:%s:%d]: "format, __FILE__,  __func__, __LINE__, ##__VA_ARGS__)
}


#endif
