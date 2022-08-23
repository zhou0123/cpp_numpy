#include <stdarg.h>
#include <immintrin.h>
#include <xmmintrin.h>
#include<iostream>
#include<initializer_list>
#include <sched.h>
#include<thread>
#include<cstdlib>
#include <math.h>
#include<vector>
using namespace std;
class ndarray
{
private:
    /* data */
public:
    ndarray(initializer_list<initializer_list<_Float32>> il);
    ndarray(pair<int,int> shape_,bool is_num =false,float num =0.0);
    ~ndarray();
    pair<int,int> shape;
    _Float32 * nums;
    ndarray &operator [](vector<int> inds)
    {
        auto res = ndarray({inds.size(),shape.second},true);
        for (int i =0 ;i<inds.size();i++)
        {
            for (int j=0;j<shape.second;j++)
            {
                res.nums[i*res.shape.second+j] = nums[inds[i]*res.shape.second+j];
            }
        }
        return res;
    }
    ndarray &operator [](pair<char,int> coords)
    {
        auto res = ndarray({1,shape.first},true);
        if (coords.first != ':')
        {
            cout<<"ERROR!!!"<<endl;
            return res;
        }
        for (int i=0;i<shape.first;i++)
        {
            res.nums[i] = nums[shape.first*i+coords.second];
        }

        return res;
    }
    ndarray &operator [](pair<int,char> coords)
    {   
        auto res = ndarray({1,shape.second},true);
        if (coords.second != ':')
        {
            cout<<"ERROR!!!"<<endl;
            return res;
        }
        for (int i=0;i<shape.second;i++)
        {
            res.nums[i] = nums[shape.second*i+coords.first];
        }
        return res;
    }
    ndarray &operator [](vector<pair<int,int>> coords)
    {
        auto res = ndarray({1,coords.size()},true);
        for (int i=0;i<coords.size();i++)
        {
            auto [x,y] = coords[i];
            res.nums[i]= nums[x*shape.first+y];
        }
        return res;
    }
    ndarray &operator [](pair<int,int> coords)
    {
        auto res = ndarray({1,1},true);
        auto [x,y] = coords;
        res.nums[0] = nums[x*shape.second+y];
        return res;
    }
    ndarray &operator-(float x)
    {
        auto res = *this;
        for (int i=0;i<shape.first;i++)
        {
            for (int j=0;j<shape.second;j++)
            {
                res.nums[i*shape.second+j] = nums[i*shape.second+j]-x;
            }
        }
        return res;
    }
    ndarray &operator+(float x)
    {
        auto res = *this;
        for (int i=0;i<shape.first;i++)
        {
            for (int j=0;j<shape.second;j++)
            {
                res.nums[i*shape.second+j] = nums[i*shape.second+j]+x;
            }
        }
        return res;
    }
    ndarray &operator*(float x)
    {
        auto res = *this;
        for (int i=0;i<shape.first;i++)
        {
            for (int j=0;j<shape.second;j++)
            {
                res.nums[i*shape.second+j] = nums[i*shape.second+j]*x;
            }
        }
        return res;
    }
    ndarray &operator/(float x)
    {
        auto res = *this;
        for (int i=0;i<shape.first;i++)
        {
            for (int j=0;j<shape.second;j++)
            {
                res.nums[i*shape.second+j] = nums[i*shape.second+j]/x;
            }
        }
        return res;
    }
    void operator+=(float x)
    {
        for (int i=0;i<shape.first;i++)
        {
            for (int j=0;j<shape.second;j++)
            {
                nums[i*shape.second+j] = nums[i*shape.second+j]+x;
            }
        }
    }
    void operator-=(float x)
    {
        for (int i=0;i<shape.first;i++)
        {
            for (int j=0;j<shape.second;j++)
            {
                nums[i*shape.second+j] = nums[i*shape.second+j]-x;
            }
        }
    }
    void operator*=(float x)
    {
        for (int i=0;i<shape.first;i++)
        {
            for (int j=0;j<shape.second;j++)
            {
                nums[i*shape.second+j] = nums[i*shape.second+j]*x;
            }
        }
    }
    void operator/=(float x)
    {
        for (int i=0;i<shape.first;i++)
        {
            for (int j=0;j<shape.second;j++)
            {
                nums[i*shape.second+j] = nums[i*shape.second+j]/x;
            }
        }
    }
    //rand()
    // void randn(pair<int,int>);
    // 输出
    void print();
    //coord 
    // 矩乘
    //转置
    ndarray T();
    //sum
    vector<float> sum(int axis=-1);
};
ndarray ndarray::T()
{
    ndarray re = ndarray({shape.second , shape.first},true);
    for (int i=0;i<shape.first;i++)
    {
        for (int j=0;j<shape.second;j++)
        {

           re.nums[i+j*shape.first] = nums[shape.second*i+j];
        }
    }
    return re;
}
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
vector<float> ndarray::sum(int axis)
{
    vector<float> res;
    if (axis ==-1)
    {
        float  res_ =0;
        for (int i=0;i<shape.first;i++)
        {
            for (int j=0;j<shape.second;j++) res_ += nums[i*shape.second+j];
        }
        res.push_back(res_);
        return res;
    }
    if (axis ==1)
    {
        
        for (int i=0;i<shape.first;i++)
        {
            float  res_ =0;
            for (int j=0;j<shape.second;j++) res_ += nums[i*shape.second+j];
            res.push_back(res_);

        }
        return res;
    }
    if (axis ==0)
    {
        
        for (int i=0;i<shape.second;i++)
        {
            float  res_ =0;
            for (int j=0;j<shape.first;j++) res_ += nums[j*shape.second+i];
            res.push_back(res_);

        }
        return res;
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
ndarray::ndarray(pair<int,int> shape_,bool is_num,float num)
{
        shape.first = shape_.first;
        shape.second = shape_.second;
        nums = new _Float32[shape.first * shape.second];
         if (is_num)
        {
            for (int i=0;i<shape.first;i++)
            {
            for (int j=0;j<shape.second;j++)
            {
                nums [i*shape.second+j] =  num;
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