#include "../util/logger.h"

using namespace util;

int main()
{
    Logger *logger = NULL;
    NewLogger("./", &logger);

    for (int i = 0; i < 10000; i++)
    {
        char buffer[64] = {0};
        LOG_INFO(logger, "seq is %d, pad pad pad pad pad", i);
        sleep(1);
    }

    return 0;
}
