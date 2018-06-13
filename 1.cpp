#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

// 返回需要变换的次数，如果为-1则表明无法进行调换；
int guess(const vector <vector <int> >& puzzle, vector <vector <int> >& press, int size)
{
    int num = 0;
    for (int i = 2; i <= size; i++)   //计算出所需要的puzzle矩阵
        for (int j = 1; j <= size; j++)
        {
            press[i][j] = 1-((puzzle[i-2][j-1] + press[i-1][j] + press[i-1][j-1]
                              + press[i-1][j+1] + press[i-2][j])%2);
            if(press[i][j]==1)
                num++;
        }

    for (int i = 0; i < size; i++)
    {
        if((puzzle[size-1][i]+press[size][i+1]+ press[size][i]
                + press[size][i+2] + press[size-1][i+1])%2 == 0)
            return -1;
    }
    for(int i = 0; i < size; i++)
    {
        if(press[1][i+1] == 1)
            num++;
    }
    return num;

}


// 返回最小的次数，如果是10000000则表明无法寻找到解；
int enumerate(const vector <vector <int> >& puzzle, vector <vector <int> >& press, int size)
{
    int num ;  //计算所需要的调换次数
    int min_num = 10000000; //计算所需要的最大调换次数
    int times = pow(2,size);  //计算枚举的最大次数
    press[1][1] = -1;
    while(0 < times--)
    {
        int c = 1;
        press[1][c]++;
        while(press[1][c]>1)
        {
            press[1][c] = 0;
            c++;
            press[1][c]++;
        }
        num = guess(puzzle, press, size);
        if(num>=0)
            min_num = (num < min_num) ? num : min_num;

    }
    return min_num;

}

int main() {

    int times;
    cin >> times;
    int size;
    while(0 < times--)
    {
        cin >> size;
        cin.ignore();
        vector <vector <int> > puzzle(size, vector<int>(size,0) );
        vector <vector <int> > press(size+1, vector<int>(size+2,0) );
        char a;
        for (int i = 0; i < size; i++)
        {
            for(int j = 0; j<size; j++)
            {
                a = cin.get();
                if(a == 'y')
                    puzzle[i][j] = 1;
            }
            cin.ignore();
        }
        int tmp = enumerate(puzzle, press, size);
        if(tmp == 10000000)
            cout << "inf"<<endl;
        else
            cout << tmp<<endl;

    }
    return 0;
}