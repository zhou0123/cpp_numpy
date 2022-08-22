#include <math.h>
#include"array.h"
void Exp(ndarray & first)
{
    for (int i=0;i<first.shape.first;i++)
    {
        for (int j=0;j<first.shape.second;j++)
        {
            first.nums[i*first.shape.second+j] = exp(first.nums[i*first.shape.second+j]);
        }
    }
}
void Log(ndarray & first)
{
    for (int i=0;i<first.shape.first;i++)
    {
        for (int j=0;j<first.shape.second;j++)
        {
            first.nums[i*first.shape.second+j] = log(first.nums[i*first.shape.second+j]);
        }
    }
}

void Log10(ndarray & first)
{
    for (int i=0;i<first.shape.first;i++)
    {
        for (int j=0;j<first.shape.second;j++)
        {
            first.nums[i*first.shape.second+j] = log10(first.nums[i*first.shape.second+j]);
        }
    }
}
void Sqrt(ndarray & first)
{
    for (int i=0;i<first.shape.first;i++)
    {
        for (int j=0;j<first.shape.second;j++)
        {
            first.nums[i*first.shape.second+j] = sqrt(first.nums[i*first.shape.second+j]);
        }
    }
}

void Pow(ndarray & first,_Float32 num)
{
    for (int i=0;i<first.shape.first;i++)
    {
        for (int j=0;j<first.shape.second;j++)
        {
            first.nums[i*first.shape.second+j] = pow(first.nums[i*first.shape.second+j],num);
        }
    }
}

void Abs(ndarray & first)
{
    for (int i=0;i<first.shape.first;i++)
    {
        for (int j=0;j<first.shape.second;j++)
        {
            first.nums[i*first.shape.second+j] = fabs(first.nums[i*first.shape.second+j]);
        }
    }
}

void Cos(ndarray & first)
{
    for (int i=0;i<first.shape.first;i++)
    {
        for (int j=0;j<first.shape.second;j++)
        {
            first.nums[i*first.shape.second+j] = cos(first.nums[i*first.shape.second+j]);
        }
    }
}

void Sin(ndarray & first)
{
    for (int i=0;i<first.shape.first;i++)
    {
        for (int j=0;j<first.shape.second;j++)
        {
            first.nums[i*first.shape.second+j] = sin(first.nums[i*first.shape.second+j]);
        }
    }
}

void Tan(ndarray & first)
{
    for (int i=0;i<first.shape.first;i++)
    {
        for (int j=0;j<first.shape.second;j++)
        {
            first.nums[i*first.shape.second+j] = tan(first.nums[i*first.shape.second+j]);
        }
    }
}




