/*
Изучив стандартные виды блокировок ресурсов в различных системах, Вася решил закрепить свои знания, потренировавшись на абстрактном примере.
Вася расположил перед собой nn абстрактных ресурсов, пронумеровав их слева направо целыми числами от 11 до nn. Каждый ресурс в конкретный момент времени может находиться либо в занятом, либо в свободном состоянии. Изначально (в момент времени 00) все ресурсы находятся в свободном состоянии.
Блокировка с порядковым номером ii в примере Васи представляет из себя четверку чисел ( sisi, lili, riri, didi), обозначающих соответственно время старта ( si≥1si≥1), левую и правую границы индексов ресурсов ( 1≤li≤ri≤n1≤li≤ri≤n), продолжительность ( di≥1di≥1) блокировки.
Вася называет блокировку ii принятой, если на момент времени sisi все ресурсы с индексами в диапазоне [ li…rili…ri] находятся в свободном состоянии. Принятая блокировка ii переводит все ресурсы с индексами в диапазоне [ li…rili…ri] в занятое состояние для всех моментов времени t∈[si,si+di)t∈[si,si+di).
После того, как Вася определился с правилами, он задумался о возможности построения алгоритма, эффективно моделирующего данную логику. Помогите Васе с реализацией этого алгоритма.
Формат ввода

В первой строке входных данных записано два числа — nn, mm ( 1≤n,m≤1000001≤n,m≤100000), разделенных одним пробелом.
В последующих mm строках задано описание блокировок в примере Васи. В ii-й из этих строк записано четыре числа — sisi, lili, riri, didi ( 1≤si≤1091≤si≤109, 1≤li≤ri≤n1≤li≤ri≤n, 1≤di≤1091≤di≤109), разделенных одним пробелом.
Гарантируется, что все sisi в примере Васи различны. Блокировки следуют в порядке возрастания величины sisi.
Формат вывода

В ii-й ( 1≤i≤m1≤i≤m) строке выходных данных Вам необходимо вывести результат обработки ii-й блокировки в порядке следования во входных данных: если ii-я блокировка является принятой, выведите YesYes, иначе выведите NoNo.
Пример 1

Ввод	Вывод
4 2
1 1 2 1
2 3 4 1
Yes
Yes
Пример 2

Ввод	Вывод
6 6
1 1 3 5
2 4 6 2
3 4 6 2
4 4 6 2
5 1 5 1
10 1 5 1
Yes
Yes
No
Yes
No
Yes
*/

#include <iostream>
#include <fstream>

using namespace std;

int main005(int argc, char* argv[])
{
    ifstream ifile;
    ifile.open("input.txt");

    int n, m;
    ifile >> n >> m;

    //0=start,1=left,2=right,3=end,4=flag,5=maximal block at this time
    int *blocks = new int[6*m];

    for (int i = 0; i < m; i++)
    {
        ifile >> blocks[i*6+0] >> blocks[i*6+1] >> blocks[i*6+2] >> blocks[i*6+3];
        blocks[i*6+3]+=blocks[i*6+0]; //end of block
        blocks[i*6+4] = 1; //flag, block accepted or not
    }

    ifile.close();

    string output = "Yes\n";
    blocks[0*6+5] = blocks[0*6+3]; //maximal block at this time, for optimisation


    for (int i=1; i<m; i++) {

        int* cur = &(blocks[i*6]);

        cur[5] = max(cur[3], blocks[(i-1)*6+5]); //set cur 'max block' as maximum of cur 'end time' and prev 'max block'

        for (int j=i-1; j>=0; j--) {

            int* prev = &(blocks[j*6]);

            if (prev[5]<cur[0])
                break; //if prev max block less then current time

            if (prev[4]==1 && cur[0] < prev[3]) //if prev block accepted and cur 'start time' less then prev 'end time'
                //if there is intersection between resources
                if (!((cur[1] < prev[1] && cur[2]<prev[1]) || (cur[1] > prev[2] && cur[2]>prev[2]))) {
                    cur[4]=0;
                    break;
                }
        }

        if (cur[4]==1) output+= "Yes\n";
        else output+= "No\n";
    }



    ofstream ofile;
    ofile.open("output.txt", ios_base::trunc);
    ofile << output;
    ofile.close();

    free(blocks);

    return 0;
}
