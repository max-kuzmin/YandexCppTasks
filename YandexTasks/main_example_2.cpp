//A+B


#include <iostream>

using namespace std;

int main2(int argc, char* argv[])
{
    string inp, as, bs;

    getline(cin, inp);
    int space = inp.find_first_of(' ');
    as = inp.substr(0, space);
    bs = inp.substr(space + 1, inp.size() - 1);

    cout << (stoi(as) + stoi(bs));
    return 0;
}
