#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

int main03(int argc, char* argv[])
{
    ifstream ifile;
    ifile.open("input.txt");

    int n, m, k;
    ifile >> n >> m >> k;
    ifile.close();

    double cells = m * n;
    double p_one = 1.0 / cells;

    double mean = 0;

    for (int i = 0; i < k; i++)
    {
        mean = mean + p_one * (cells - mean);
    }

    ofstream ofile;
    ofile.open("output.txt", ios_base::trunc);
    ofile << std::setprecision(17) << mean << endl;
    ofile.close();
    return 0;
}

