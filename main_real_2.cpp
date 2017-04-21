/*
Размышляя о прекрасном, Вася осознал, что в его жизни не хватает порядка, поэтому он решил привести к красивому виду все записи в своем электронном дневнике.
Вася не любит знаки пунктуации и цифры, поэтому его записи состоят только из символов английского алфавита нижнего или верхнего регистров ( a,…,z,A,…,Za,…,z,A,…,Z), пробелов и точек.
Вася считает, что запись не теряет информационной значимости, если к ней любое количество раз применяются следующие операции:
Изменение регистра символа английского алфавита в некоторой позиции записи.
Удаление пробела в начале/конце строки или некоторой позиции pp, если хотя бы один соседний относительно позиции pp символ не является символом английского алфавита.
Вставка пробела в некоторую позицию pp, если хотя бы один соседний относительно позиции pp символ не является символом английского алфавита.
Вася считает, что запись является красивой, если выполнены следующие условия:
Запись состоит из непустой последовательности подряд идущих предложений, разделенных ровно одним пробелом.
Каждое предложение состоит из непустой последовательности слов, разделенных ровно одним пробелом, заканчивающейся точкой.
Каждое слово состоит из одного или более подряд идущих символов английского алфавита.
Первый символ первого слова каждого предложения является символом верхнего регистра. Остальные символы всех слов всех предложения являются символами нижнего регистра.
Помогите Васе преобразовать запись из его электронного дневника к красивому виду или сообщите, что такое преобразование невозможно.
Формат ввода

В единственной строке входных данных содержится запись ss из электронного дневника Васи ( 1≤|s|≤1000001≤|s|≤100000).
Формат вывода

Если не существует преобразования записи Васи к красивому виду, то выведите в единственной строке выходных данных число −1−1.
В противном случае выведите в единственной строке выходных данных результат преобразования записи ss к красивому виду. Если существует несколько возможных результатов, выведите любой.
Пример 1

Ввод	Вывод
hellOWOrLD.hELLOWORLD.
Helloworld. Helloworld.
Пример 2

Ввод	Вывод
A.B.A.C.A.B.A.
A. B. A. C. A. B. A.
*/



#include <iostream>
#include <fstream>

using namespace std;


int word(string* inp, string* outp)
{

    for (int i = 0; i < inp->size(); i++)
    {
        //if not letter then erro
        if (inp->at(i) < 'A' || (inp->at(i) > 'Z' && inp->at(i) < 'a') || inp->at(i) > 'z')
            return -1;
        //if upper case
        else if (inp->at(i) <= 'Z')
            (*outp) += tolower(inp->at(i));
        //else just copy
        else (*outp) += inp->at(i);
    }
    return 0;
}



int word1(string* inp, string* outp)
{
    //if not letter then error
    if (inp->at(0) < 'A' || (inp->at(0) > 'Z' && inp->at(0) < 'a') || inp->at(0) > 'z')
        return -1;
    //if lower case
    else if (inp->at(0) >= 'a')
        (*outp) += toupper(inp->at(0));
    //else just copy
    else (*outp) += inp->at(0);

    //if there is more letters
    if (inp->size() > 1)
    {
        string subs = inp->substr(1, inp->size() - 1);
        return word(&subs, outp);
    }
    else
        return 0;
}



int sentense(string* inp, string* outp)
{
    //remove dot
    (*inp) = inp->substr(0, inp->size() - 1);

    //trim spaces
    while (inp->size() > 0 && inp->at(0) == ' ')
        (*inp) = inp->substr(1, inp->size() - 1);
    while (inp->size() > 0 && inp->at(inp->size() - 1) == ' ')
        (*inp) = inp->substr(0, inp->size() - 1);

    //if empty input then error
    if (inp->size() == 0)
        return -1;

    int space = inp->find_first_of(' ');
    //if there only one word
    if (space == -1)
        return word1(inp, outp);
    //else get first word
    else
    {
        string subs = inp->substr(0, space);
        if (word1(&subs, outp) == -1)
            return -1;
    }

    int spacenew = inp->find_first_of(' ', space + 1);

    //while there is words
    while (space != -1)
    {
        (*outp) += ' ';

        //skip spaces
        while ((space + 1) == spacenew || space == spacenew)
        {
            space = spacenew;
            spacenew = inp->find_first_of(' ', space + 1);
        }

        string subs;
        //if its last word
        if (spacenew == -1)
            subs = inp->substr(space + 1, inp->size() - (space + 1));
        //if not last word
        else
            subs = inp->substr(space + 1, spacenew - space - 1);

        if (word(&subs, outp) == -1)
            return -1;

        space = spacenew;
    }

    return 0;
}



int record(string* inp, string* outp)
{

    int dot = inp->find_first_of('.');

    //if no dot = error
    if (dot == -1)
        return -1;
    //if dot is last symbol there only one sentence
    else if (dot == (inp->size() - 1))
    {
        int err = sentense(inp, outp);
        (*outp) += ".";
        return err;
    }

    int dotnew=dot;
    dot=-1;

    //while there is sentences
    while (dotnew != -1)
    {
        string subs = inp->substr(dot + 1, dotnew - dot);

        if (sentense(&subs, outp) == -1)
            return -1;

        (*outp) += ". ";

        dot = dotnew;
        dotnew = inp->find_first_of('.', dot + 1);
    }

    //if last sentence without dot
    if (dot!= inp->size()-1) return -1;

    outp->resize(outp->size()-1);

    return 0;
}



int main02(int argc, char* argv[])
{
    ifstream ifile;
    ifile.open("input.txt");

    string input;
    getline(ifile, input);
    ifile.close();

    ofstream ofile;
    ofile.open("output.txt", ios_base::trunc);

    //trim spaces
    while (input[0] == ' ')
        input = input.substr(1, input.size() - 1);
    while (input[input.size() - 1] == ' ')
        input = input.substr(0, input.size() - 1);

    if (input == "")
        ofile << -1 << endl;
    else
    {
        string result;
        int err = record(&input, &result);

        if (err == 0)
            ofile << result << endl;
        else
            ofile << err << endl;
    }

    ofile.close();

    return 0;
}
