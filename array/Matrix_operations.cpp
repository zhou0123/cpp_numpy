#include"array.h"
#include<vector>
#include<string>
using namespace std;
/*
matmul
transpose
arange
trace
where
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
ndarray arange(int num)
{
    ndarray re = ndarray({1,num},true);
    for (int i=0;i<num;i++) re.nums[i] = i;
    return re;
}
// 迹
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


