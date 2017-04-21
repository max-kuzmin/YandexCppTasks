#include <iostream>
#include <fstream>

using namespace std;

int main0005(int argc, char* argv[])
{
    ifstream ifile;
    ifile.open("input.txt");

    int n, m;
    ifile >> n >> m;

    int** blocks = new int* [m];

    for (int i = 0; i < m; i++)
    {
        blocks[i] = new int[5]; //0=start,1=left,2=right,3=end,4=flag,5=maximal block at this time
        ifile >> blocks[i][0] >> blocks[i][1] >> blocks[i][2] >> blocks[i][3];
        blocks[i][3]+=blocks[i][0]; //end of block
        blocks[i][4] = 1; //flag, block accepted or not
    }

    ifile.close();

    string output = "";


    int *cur, *next, j;

    for (int i=0; i<m; i++) {

        cur = blocks[i];

        if (cur[4]==1) output+= "Yes\n";
        else
        {
            output+= "No\n";
            continue; //skip if cur block declined
        }

        for (j=i+1; j<m && blocks[j][0]<cur[3]; j++) { //for all blocks with start time up to cur end time

            next = blocks[j];

            if (next[4]==1) { //if next block accepted
                //if next block resources intersects curent then decline next block
                if (!((cur[1] < next[1] && cur[2]<next[1]) || (cur[1] > next[2] && cur[2]>next[2])))
                    next[4] = 0;
            }
        }
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

    return 0;
}
