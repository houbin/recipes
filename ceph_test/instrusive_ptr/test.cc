#include "test.h"

int main()
{
	{
	
	TestRef houbin(new Test("houbin"));

	cout << "copy houbin to houbin_2" << endl;
	TestRef houbin_2(houbin);

	cout << "define wangjing" << endl;
	TestRef wangjing(new Test("wangjing"));

	}
	return 0;
};
