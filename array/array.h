#include <stdarg.h>
#include <immintrin.h>
#include <xmmintrin.h>
#include<iostream>
#include<initializer_list>
#include <sched.h>
#include<thread>
#include<cstdlib>
#include <math.h>
using namespace std;
class ndarray
{
private:
    /* data */
public:
    ndarray(initializer_list<initializer_list<_Float32>> il);
    ndarray(pair<int,int> shape_,bool is_zero =false);
    ~ndarray();
    pair<int,int> shape;
    _Float32 * nums;
    //rand()
    // void randn(pair<int,int>);
    // 输出
    void print();
    // 矩乘
};
void ndarray::print()
{
    for (int i=0;i<shape.first;i++)
    {
        for (int j=0;j<shape.second;j++)
        {
            cout<<nums[i*shape.second + j]<<"  ";
        }
        cout<<endl;
    }
}
ndarray::ndarray(initializer_list<initializer_list<_Float32>> il)
{  
    shape.first = il.size();
    shape.second = (*(il.begin())).size();    
    nums = new _Float32[shape.second*shape.first]();
    int i=0,j;
    for (auto itor2 = il.begin();itor2!=il.end();itor2++)
    {
        j=0;
        for (auto itor1 = (*itor2).begin();itor1!=(*itor2).end();itor1++)
        {
            nums[j+i*shape.second] = *itor1;
            j++;
        }
        i++;
    }
}
ndarray::ndarray(pair<int,int> shape_,bool is_zero)
{
        shape.first = shape_.first;
        shape.second = shape_.second;
        nums = new _Float32[shape.first * shape.second];
         if (is_zero)
        {
            for (int i=0;i<shape.first;i++)
            {
            for (int j=0;j<shape.second;j++)
            {
                nums [i*shape.second+j] =  0;
            }
            }
        }
        else 
        {
            for (int i=0;i<shape.first;i++)
            {
            for (int j=0;j<shape.second;j++)
            {
                nums [i*shape.second+j] =  (_Float32)rand()/(_Float32)RAND_MAX;
            }
            }
        }
}
ndarray::~ndarray()
{
}