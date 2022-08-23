#include"array.h"
#include<vector>
#include<string>
// #include<opm.h>
#include<thread>
using namespace std;
/*
matmul  | 普通cpp | cuda 加速 | 多线程 + simd ？
transpose
arange
trace
where
argmax
argmin
*/
ndarray Matmul(ndarray & first ,ndarray &second)
{
    ndarray re = ndarray({first.shape.first , second.shape.second},true);
    if (first.shape.second != second.shape.first) 
    {
        cout <<"the shape is not matching!"<<endl;
    }
    for (int i=0;i<first.shape.first;i++)
    {

        for (int j=0;j<second.shape.second;j++)
        {

            for (int k = 0;k<first.shape.second;k++)
            {
                re.nums[i*second.shape.second+j] += first.nums[first.shape.second*i + k]*second.nums[k*second.shape.second+j];
            }
        }
    }
    return re;
}
ndarray Matmul_MP(ndarray & first ,ndarray &second)
{
    ndarray re = ndarray({first.shape.first , second.shape.second},true);
    if (first.shape.second != second.shape.first) 
    {
        cout <<"the shape is not matching!"<<endl;
    }
    #pragma opm parallel for schedule (dynamic)
    for (int i=0;i<first.shape.first;i++)
    {

        for (int j=0;j<second.shape.second;j++)
        {

            for (int k = 0;k<first.shape.second;k++)
            {
                re.nums[i*second.shape.second+j] += first.nums[first.shape.second*i + k]*second.nums[k*second.shape.second+j];
            }
        }
    }
    return re;
}
ndarray transpose(ndarray & first)
{
    ndarray re = ndarray({first.shape.second , first.shape.first},true);
    for (int i=0;i<first.shape.first;i++)
    {
        for (int j=0;j<first.shape.second;j++)
        {

           re.nums[i+j*first.shape.first] = first.nums[first.shape.second*i+j];
        }
    }
    return re;
}
ndarray transpose_MP(ndarray & first)
{
    ndarray re = ndarray({first.shape.second , first.shape.first},true);
    #pragma opm parallel for schedule (dynamic)
    for (int i=0;i<first.shape.first;i++)
    {
        for (int j=0;j<first.shape.second;j++)
        {

           re.nums[i+j*first.shape.first] = first.nums[first.shape.second*i+j];
        }
    }
    return re;
}
ndarray arange(int num)
{
    ndarray re = ndarray({1,num},true);
    for (int i=0;i<num;i++) re.nums[i] = i;
    return re;
}
ndarray arange_MP(int num)
{
    ndarray re = ndarray({1,num},true);
    #pragma opm parallel for schedule (dynamic)
    for (int i=0;i<num;i++) re.nums[i] = i;
    return re;
}
_Float32 trace(ndarray & first)
{
    _Float32 sum =0;
     if (first.shape.first != first.shape.second) return 0;
     for (int i=0;i<first.shape.first;i++)sum += first.nums[i+first.shape.second*i];
     return sum;
}
vector<pair<int,int>> where(ndarray & first,string cmp,_Float32 num)
{
    vector<pair<int,int>> res;
    if (cmp.compare("<")==0)
    {
        for (int i=0;i<first.shape.first;i++)
        {
            for (int j=0;j<first.shape.second;j++)
            {
                if (first.nums[i*first.shape.second+j]<num) res.push_back({i,j});
            }
        }
        return res;
    }
    else if (cmp.compare("<=") ==0)
    {
        for (int i=0;i<first.shape.first;i++)
        {
            for (int j=0;j<first.shape.second;j++)
            {
                if (first.nums[i*first.shape.second+j]<=num) res.push_back({i,j});
            }
        }
        return res;
    }
    else if (cmp.compare("==") ==0)
    {
        for (int i=0;i<first.shape.first;i++)
        {
            for (int j=0;j<first.shape.second;j++)
            {
                if (first.nums[i*first.shape.second+j]==num) res.push_back({i,j});
            }
        }
        return res;
    }
    else if (cmp.compare(">=") ==0)
    {
        for (int i=0;i<first.shape.first;i++)
        {
            for (int j=0;j<first.shape.second;j++)
            {
                if (first.nums[i*first.shape.second+j]>=num) res.push_back({i,j});
            }
        }
        return res;
    }
    else if (cmp.compare(">") ==0)
    {
        for (int i=0;i<first.shape.first;i++)
        {
            for (int j=0;j<first.shape.second;j++)
            {
                if (first.nums[i*first.shape.second+j]>num) res.push_back({i,j});
            }
        }
        return res;
    }

    return res;
}
vector<int> argmax(ndarray & first,int axis = 0)
{
    
    vector<int> res;
    if (axis ==0)
    {
        for (int i=0;i<first.shape.second;i++)
        {
            int index =0;
            float max_ = first.nums[i+0*first.shape.second];
            for (int j=0;j<first.shape.first;j++)
            {
                if (first.nums[i+j*first.shape.second]>max_)
                {
                    max_ = first.nums[i+j*first.shape.second];
                    index = j;
                }
            }
            res.push_back(index);
        }
        return res;
    }
    else if (axis==1)
    {
        for (int i=0;i<first.shape.first;i++)
        {
            int index = 0;
            float max_ = first.nums[i*first.shape.second+0];
            for (int j=0;j<first.shape.second;j++)
            {
                if (max_<first.nums[i*first.shape.second+j])
                {
                    max_ = first.nums[i*first.shape.second+j];
                    index = j;
                }
            }
            
            res.push_back(index);
        }
        return res;
    }
}
vector<int> argmin(ndarray & first,int axis = 0)
{
    vector<int> res;
    if (axis ==0)
    {
        for (int i=0;i<first.shape.second;i++)
        {
            int index =0;
            float min_ = first.nums[i+0*first.shape.second];
            for (int j=0;j<first.shape.first;j++)
            {
                if (first.nums[i+j*first.shape.second]<min_)
                {
                    min_ = first.nums[i+j*first.shape.second];
                    index = j;
                }
            }
            res.push_back(index);
        }
        return res;
    }
    else if (axis==1)
    {
        for (int i=0;i<first.shape.first;i++)
        {
            int index = 0;
            float min_ = first.nums[i*first.shape.second+0];
            for (int j=0;j<first.shape.second;j++)
            {
                if (min_>first.nums[i*first.shape.second+j])
                {
                    min_ = first.nums[i*first.shape.second+j];
                    index = j;
                }
            }
            res.push_back(index);
        }
        return res;
    }
}
