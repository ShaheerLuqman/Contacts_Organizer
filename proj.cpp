#include <iostream>
#include <vector>
// #include <algorithm>
// #include <iterator>
using namespace std;

int main()
{
    vector<string> v = {"1", "2", "3", "4", "5"};
    int index = 2;
    v.erase(v.begin() + index);

    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }

    return 0;
}