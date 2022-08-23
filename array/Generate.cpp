#include"array.h"
#include <math.h>
using namespace std;
/*
这个主要是生成不同类型的矩阵
rand
zero
One
Init_mat 用一个数初始化矩阵
ones_like
zeros_like
*/
ndarray Rand(pair<int,int> coords)
{
    auto res = ndarray({coords.first,coords.second});
    return res;   
}
ndarray Zero(pair<int,int> coords)
{
    auto res = ndarray({coords.first,coords.second},true);
    return res;   
}
ndarray One(pair<int,int> coords)
{
    auto res = ndarray({coords.first,coords.second},true,1);
    return res;   
}
ndarray Init_mat(pair<int,int> coords,float num)
{
    auto res = ndarray({coords.first,coords.second},true,num);
    return res;   
}
ndarray ones_like(ndarray & first)
{
    auto res = ndarray({first.shape.first,first.shape.second},true,1);
    return res;   
}
ndarray zeros_like(ndarray & first)
{
    auto res = ndarray({first.shape.first,first.shape.second},true,0.0);
    return res;   
}
ndarray eye(int dim)
{
    auto res = ndarray({dim,dim},true);
    for (int i=0;i<res.shape.first;i++) res.nums[i+i*res.shape.second] =1;
    return res;
}