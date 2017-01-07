#include "obj_move.h"
#include <vector>

using namespace std;

int main()
{
	obj o(123);

	vector<obj> obj_vec;

	obj_vec.push_back(std::move(o));

	return 0;
}

