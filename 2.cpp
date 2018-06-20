//
// Created by 李安东 on 2018/6/12.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;


const int size = 9;
int w[size][size] = {0};


//返回两个数组相减,结果保存在第一个数组中返回
inline void mminus (vector <int> & w1, const int* w2)
{
    for(int i=0; i<size; i++)
    {
        w1[i] = (w1[i] - w2[i]+4)%4;
    }

}


//返回枚举的最小值
vector<int>  enumerate(int * initpos)
{
    vector <int> result; //记录最终的结果
    vector <int> weight(size, 0);
    int minnum = 1000;
    weight[0] = -1;
    int a =0;
    while(a<9)   //仅仅枚举前三条,后面的条的状态可以被前三条所确定
    {
        int c = 0;  //个位
        weight[c]++;
        while(weight[c] > 3)
        {
            weight[c] = 0;
            c++;
            weight[c]++;
        }

        vector <int> tmp(initpos, initpos+size);
        for(int i =0; i<3; i++)
        {
            for(int j =0; j<weight[i]; j++)
                mminus(tmp, w[i]);
        }
        weight[3] = tmp[0];
        weight[4] = tmp[1];
        weight[5] = tmp[2];
        for(int i =3; i<6; i++)
        {
            for(int j =0; j<weight[i]; j++)
                mminus(tmp, w[i]);
        }
        weight[6] = tmp[3];
        for(int j =0; j<weight[6]; j++)
            mminus(tmp, w[6]);
        weight[7] = tmp[6];
        weight[8] = tmp[5];
        for(int i =7; i<size; i++)
        {
            for(int j =0; j<weight[i]; j++)
                mminus(tmp, w[i]);
        }

        if(accumulate(tmp.begin(), tmp.end(), 0)== 0)
        {
            int num = accumulate(weight.begin(), weight.end(), 0);
            if (num < minnum)
            {
                minnum = num;
                result = weight;
            }
        }
        a = accumulate(weight.begin(),weight.begin()+3, 0);
    }
    return result;
}




int main()
{
    w[0][0] = 1;w[0][1] = 1;w[0][3] = 1; w[0][4] = 1;
    w[1][0] = 1;w[1][1] = 1;w[1][2] = 1;
    w[2][1] = 1;w[2][2] = 1;w[2][4] = 1;w[2][5] = 1;
    w[3][0] = 1;w[3][3] = 1;w[3][6] = 1;
    w[4][1] = 1;w[4][3] = 1;w[4][4] = 1;w[4][5] = 1;w[4][7] = 1;
    w[5][2] = 1;w[5][5] = 1;w[5][8] = 1;
    w[6][3] = 1;w[6][4] = 1;w[6][6] = 1;w[6][7] = 1;
    w[7][6] = 1;w[7][7] = 1;w[7][8] = 1;
    w[8][4] = 1;w[8][5] = 1;w[8][7] = 1;w[8][8] = 1;
    int initpos[9] = {0};
    for(int& i: initpos)
    {
        cin>>i;
    }
    for_each(initpos,initpos+9,[&](int& x){x=(4-x)%4;});
    vector<int> result = enumerate(initpos);
    for(int i =0; i<size; i++)
        for(int j =0; j<result[i]; j++)
        {
            cout<<(i+1)<<" ";
        }

    return 0;
}