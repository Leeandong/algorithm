//
// Created by 李安东 on 2018/6/12.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;


const int size = 9;
vector <int> sequence;


//返回两个数组相减,结果保存在第一个数组中返回
void mminus (int* w1, int* w2)
{
    for(int i=0; i<size; i++)
    {
        w1[i] = (w1[i] - w2[i]+4)%4;
    }

}

//int mminus(int* w1, int* w2)


void search(int* pos, int (*w)[size])
{
    int num = accumulate(pos, pos+size, 0, [=](int x, int y){return (x+y);});
    int difference = 0;
    int j;
    int result[size] = {0};
    for(int i=0;i<size;i++)
    {
        memcpy(result, pos, sizeof(int)*size);
        mminus(result, w[i]);
        int result_num = accumulate(result, result+size, 0, [=](int x, int y){return (x+y);});
        if ((num-result_num)>difference)
        {
            difference =  num-result_num;
            j=i;
        }
    }
    if(difference>0)
    {
        mminus(pos, w[j]);
        sequence.push_back(j);
        search(pos, w);
    }

}




int main()
{
    int w[size][size] = {0};
    w[0][0] = 1;w[0][1] = 1;w[0][3] = 1; w[0][4] = 1;
    w[1][0] = 1;w[1][1] = 1;w[1][2] = 1;
    w[2][1] = 1;w[2][2] = 1;w[2][4] = 1;w[2][5] = 1;
    w[3][0] = 1;w[3][3] = 1;w[3][6] = 1;
    w[4][1] = 1;w[4][3] = 1;w[4][4] = 1;w[4][5] = 1;w[4][7] = 1;
    w[5][2] = 1;w[5][5] = 1;w[5][8] = 1;
    w[6][3] = 1;w[6][4] = 1;w[6][6] = 1;w[6][7] = 1;
    w[7][6] = 1;w[7][7] = 1;w[7][8] = 1;
    w[8][4] = 1;w[8][5] = 1;w[8][7] = 1;w[8][8] = 1;
//    for(int i =0; i<size; i++)
//    {
//        for(int j=0; j<size; j++)
//            cout<<w[i][j];
//        cout<<endl;
//    }
    int sum[9] = {4, 5, 3, 5, 6, 4, 3, 4, 3};
    int initpos[9] = {3, 3, 0, 2, 2, 2, 2, 1, 2};
    for_each(initpos,initpos+9,[&](int& x){x=(4-x)%4;});
//    for(int i=0; i<size; i++)
//        cout<<initpos[i];
    search(initpos, w);
    sort(sequence.begin(),sequence.end());
    ostream_iterator <int> oit(cout,"");
    copy(sequence.begin(),sequence.end(),oit);


    return 0;
}