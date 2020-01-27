#include <iostream>
using namespace std;

void change(int& bal)
{
    bal = 3;
}

int main()
{
    int bal = 5;
    cout<<bal;
    change(bal);
    cout<<bal;
}
