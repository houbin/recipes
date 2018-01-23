#include <iostream>
#include <stdio.h>
#include <leveldb/options.h>
#include <leveldb/slice.h>
#include <leveldb/db.h>
#include <leveldb/options.h>
#include <leveldb/status.h>
#include <leveldb/iterator.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;
using namespace leveldb;

static string db_name = NULL;
static string command = NULL;

void usage()
{
    printf("Usage: leveldb_tool -p [db_path] -c [command] -t [threads]\n");
    printf("Command: list    - list all <key, value> in db\n");
    printf("         clear   - clear all <key, value> in db\n");
    printf("         fillseq - write <key, value> in sequential key order\n");
    printf("threads: just use in fillseq \n");

    return;
}

class BenchMark
{
    public:
        BenchMark():
        void Open()
        {
            Options options;
            options.create_if_missing = true;
            options.compression = kSnappyCompression;

            DB::Open(

        }
        void Run()
        {
            Open();

    
        }
    
        void Open();
    private:
        DB db_;

}

void *thread_func(void *arg)
{
	Options options;
	Status status;

	options.write_buffer_size = 128 *1024 * 1024;

	DB *db = NULL;

	status = DB::Open(options, "/houbin/test_leveldb/delete_leveldb/10_million_test", &db);
	if (!status.ok())
	{
		cout << "open db error: " << status.ToString() << endl;
		return NULL;
	}

	int loop = 0;
	while (1)
	{
		Iterator *iter = db->NewIterator(ReadOptions());
		iter->SeekToFirst();
		if (iter->Valid())
		{
			Slice key = iter->key();
			Slice value = iter->value();
			cout << "	seq " << loop << ": key " << key.data() << ", value: " << value.data() << endl;
			db->Delete(WriteOptions(), key);
			loop++;
		}
		else
		{
			cout << "======= delete db to end , loop [ " << loop << " ] ==========="  << endl;
			break;
		}
	}

	return NULL;

}

int main(int argc, char *argv[])
{
    int c;
    int threads = 1;
    bool has_command = false;
    char db_path[128] = {0};
    char op[32] = {0};

    while ( (c = getopt(argc, argv, "p:c:t:h")) != -1)
    {
        switch (c)
        {
            case 'p':
                db_name = optarg;
                break;
            case 't':
                threads = atoi(optarg);
                break;

            case 'c':
                has_command = true;
                command = optarg;
                break;
            case 'h':
            default:
                usage();
                return 0;
        }
    }

    if (!has_command)
    {
        usage();
        return 0;
    }

    if (db_name.empty())
    {
        db_name = "test_db";
    }
    cout << "db name is " << db_name << endl;
    cout << "command name is " << command << endl;


	return 0;
}

