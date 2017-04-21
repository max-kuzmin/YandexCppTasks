/*
В промежутках между занятиями по изучению теории графов Вася со своими друзьями играет в настольную игру под названием «Горки».
Поле для игры представляет из себя граф, состоящий из nn вершин, mm ориентированных обычных ребер, ll ориентированных ребер специального типа, называемых горками. Гарантируется, что из каждой вершины графа исходит не более одной горки. Все вершины графа пронумерованы целыми числами от 11 до nn.
У игрока имеется игровая фишка, изначально находящаяся в вершине с номером 11.
Игра состоит из последовательности ходов. В начале каждого хода игрок бросает стандартный игровой кубик, состоящий из 66 граней с написанными на них различными числами от 11 до 66.
Дальнейшие действия игрока в рамках одного хода состоят из двух этапов, которые определяются следующим образом:
Пусть на грани кубика выпало число x∈{1,2,3,4,5,6}x∈{1,2,3,4,5,6}.
На первом этапе игрок смещает свою фишку по xx произвольным обычным ребрам на выбор игрока.

Если в какой-то момент фишка оказывается в тупиковой вершине (то есть вершине, из которой не исходит ни одного обычного ребра), то игрок прекращает смещать свою фишку в рамках первого этапа.

Если после смещений в рамках первого этапа фишка игрока оказывается в вершине с номером nn, игрок признается победителем.

На втором этапе хода игрок смещает свою фишку по ребру-горке, если такое ребро исходит из вершины, в которой находится фишка игрока.
Вася, как очень любознательный программист, хочет по заданным параметрам настольной игры и последовательности из kk значений, которые выпали в процесс бросков его кубика, определить, через какое минимальное количество бросков он мог стать победителем игры.
Помогите Васе решить поставленную задачу.
Обратите внимание, в условии задачи не гарантируется, что, следуя последовательности значений, выпавших на грани кубика, Вася может стать победителем игры.
Формат ввода

В первой строке входных данных записано четыре целых числа — nn, mm, ll, kk ( 2≤n≤10002≤n≤1000, 0≤m≤50000≤m≤5000, 0≤l≤n0≤l≤n, 1≤k≤50001≤k≤5000) — количество вершин, количество обычных ребер, количество ребер-горок, количество бросков кубика Васи, разделенные одним пробелом.
В последующих mm строках задано описание обычных ребер.
В ii-й ( 1≤i≤m1≤i≤m) из этих строк записано два целых числа xixi, yiyi ( 1≤xi,yi≤n1≤xi,yi≤n, xi≠yixi≠yi) — номера начальной и конечной вершины обычного ребра соответственно, разделенные одним пробелом.
В последующих ll строках задано описание ребер-горок в формате, аналогичном формату описания обычных ребер.
Гарантируется, что из каждой вершины исходит не более одного ребра-горки. Каждая упорядоченная пара вершин соединена не более, чем одним ребром (обычным или ребром-горкой).
В последней строке входных данных записано kk целых чисел — a1,…,aka1,…,ak ( ai∈{1,2,3,4,5,6}ai∈{1,2,3,4,5,6}, 1≤i≤k1≤i≤k) — значения, выпавшие на грани кубика Васи, разделенные одним пробелом.
Формат вывода

Выведите в единственной строке выходных данных минимальное количество бросков, которое требуется совершить, чтобы стать победителем игры, если это возможно.
В противном случае в единственной строке выходных данных выведите −1−1.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>

using namespace std;

int* edgescount, ** edges, *hills, *cubes;
int n, m, k, l;

int go_vertex(int vertex, int steps, int cube);
int go_hill(int vertex, int cube);


int main(int argc, char* argv[])
{
    ifstream ifile;
    ifile.open("input.txt");

    ifile >> n >> m >> l >> k;

    //alloc edges
    edgescount = new int[n];
    edges = new int* [n];
    hills = new int[n];

    for (int i = 0; i < n; i++)
    {
        edges[i] = new int[n];
        edgescount[i] = 0;
        hills[i] = 0;
    }

    int x, y;
    //fill edges
    for (int i = 0; i < m; i++)
    {
        ifile >> x;
        ifile >> y;
        edgescount[x - 1]++;
        edges[x - 1][edgescount[x - 1] - 1] = y - 1; //add new edge to vertex x with endpoint y
    }

    //fill hills
    for (int i = 0; i < l; i++)
    {
        ifile >> x;
        ifile >> y;
        hills[x - 1] = y - 1; //add hill to vertex x with endpoint y
    }

    //fill cubes
    cubes = new int[k];
    for (int i = 0; i < k; i++)
    {
        ifile >> cubes[i];
    }

    ifile.close();

    //solve problem with recursion
    int outcube = go_vertex(0, cubes[0], 0);



    ofstream ofile;
    ofile.open("output.txt", ios_base::trunc);

    if (outcube < INT_MAX)
        ofile << (outcube + 1) << endl;
    else
        ofile << "-1" << endl;

    ofile.close();

    for (int i = 0; i < n; i++)
    {
        free(edges[i]);
    }

    free(edges);
    free(cubes);
    free(edgescount);
    free(hills);

    return 0;
}


//step 1
int go_vertex(int vertex, int steps, int cube)   //current vertex, not used steps, cube number
{
    //if there is no edges and no hill
    if (edgescount[vertex] == 0)
    {
        steps = 0;

        if (hills[vertex] == 0)
        {
            //if we are in last vertex then return cube
            if (vertex == (n - 1))
                return cube;
            //else error
            else
                return INT_MAX;
        }
    }


    //if there left some steps
    if (steps > 0)
    {
        steps--;

        //else go throught all edges with go_vertex
        int minresult = INT_MAX;
        for (int i = 0; i < edgescount[vertex]; i++)
        {
            minresult = min(minresult, go_vertex(edges[vertex][i], steps, cube));
        }
        //return min from returned values
        return minresult;

    }
    //if no steps
    else
    {
        //go through go_hill and return it
        return go_hill(vertex, cube);
    }

}

//step 2
int go_hill(int vertex, int cube)
{
    //if we are in last vertex then return cube
    if (vertex == (n - 1))
        return cube;

    //if it was last cube then return error
    if (cube == (k - 1))
        return INT_MAX;

    cube++;

    //go through hill with go_vertex if it exist
    if (hills[vertex] > 0)
        return go_vertex(hills[vertex], cubes[cube], cube);
    //else just go deeper
    else
        return go_vertex(vertex, cubes[cube], cube);
}


