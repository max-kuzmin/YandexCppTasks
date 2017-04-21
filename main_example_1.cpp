//A+B


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main1(int argc, char* argv[])
{
    ifstream ifile;
    ifile.open("input.txt");

    string inp, as, bs, sums;
    getline(ifile, inp);
    ifile.close();

    int space = inp.find_first_of(" ");
    as = inp.substr(0, space);
    bs = inp.substr(space + 1, inp.size() - 1);

    ofstream ofile;
    ofile.open("output.txt", ios_base::trunc);

    int a, b;
    a = stoi(as);
    b = stoi(bs);
    ofile << (a + b);

    ofile.close();
    return 0;
}

