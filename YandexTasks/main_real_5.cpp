#include <iostream>
#include <fstream>

using namespace std;

int main05(int argc, char* argv[])
{
    ifstream ifile;
    ifile.open("input.txt");

    int n, m;
    ifile >> n >> m;

    int* resources = new int[n];
    int** blocks = new int* [m];

    for (int i = 0; i < m; i++)
    {
        blocks[i] = new int[4];
        ifile >> blocks[i][0] >> blocks[i][1] >> blocks[i][2] >> blocks[i][3];
    }

    for (int i = 0; i < n; i++)
    {
        resources[i] = 0;
    }

    ifile.close();

    int prevstart = 0;
    bool isfree;
    string output;

    for (int i = 0; i < m; i++)
    {
        int start = blocks[i][0];
        int left = blocks[i][1];
        int right = blocks[i][2];
        int duration = blocks[i][3];

        for (int k = 0; k < n; k++)
        {
            resources[k] -= (start - prevstart);
            if (resources[k] < 0)
                resources[k] = 0;
        }

        isfree = true;
        for (int x = left - 1; x < right; x++)
        {
            if (resources[x] != 0)
            {
                isfree = false;
                break;
            }
        }

        if (isfree)
        {
            output += "Yes\n";
            for (int x = left - 1; x < right; x++)
            {
                resources[x] += duration;
            }
        }
        else
            output += "No\n";

        prevstart = start;

    }

    ofstream ofile;
    ofile.open("output.txt", ios_base::trunc);
    ofile << output;
    ofile.close();

    for (int i = 0; i < m; i++)
    {
        free(blocks[i]);
    }

    free(blocks);
    free(resources);

    return 0;

}
