#include <iostream>
#include <string>
#include <utility>

using namespace std;

int main()
{
    string houbin = "houbin";
    string wangjing = "wangjing";

    cout << "before move：address of houbin is " << &houbin << ", wangjing is " << &wangjing << endl;
    houbin = std::move(wangjing);

    cout << "houbin is " << houbin << ", wangjing is " << wangjing << endl;
    cout << "after move: address of houbin is " << &houbin << ", wangjing is " << &wangjing << endl;

    return 0;
}
