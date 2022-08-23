#include"array.h"
#include <math.h>
using namespace std;
/*
这个主要是对array进行shape的操作
resize
reshape
*/
void Resize(ndarray & first,pair<int,int>shapes)
{
    if (shapes.first*shapes.second != first.shape.first*first.shape.second)
    {
        cout<<"shape not matching!!!"<<endl;
        return;
    }
    first.shape.first =  shapes.first;
    first.shape.second = shapes.second;
    return;
}
void Reshape(ndarray & first,pair<int,int>shapes)
{
    if (shapes.first*shapes.second != first.shape.first*first.shape.second)
    {
        cout<<"shape not matching!!!"<<endl;
        return;
    }
    first.shape.first =  shapes.first;
    first.shape.second = shapes.second;
    return;
}