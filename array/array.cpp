
#include <stdarg.h>
#include <immintrin.h>
#include<iostream>
 #include<initializer_list>
using namespace std;

template <class T>
int len(T &array)
{
    return  sizeof(array)/(array[0]);
}
class  array
{
private:
    int *shape;
    int num{0};//元素个数
    float *nums;//储存元素
    int len_shape;//shape的len
    float* sum_dim_x ();
    float* sum_dim_0();
    float* sum_dim_1();
public:
     array(initializer_list<int> il);
    ~ array();
    void put_out();
    void construct(initializer_list<float> il);
    float *sum(int dim =-1);
    int len();

    array &operator+=(float x)
    {
        #pragma omp simd
        for (int i=0;i<num;i++)
        {
            nums[i]+=x;
        }

        return *this;
    }
    array &operator+ (float x)
    {
        #pragma omp simd 
        for(int i=0;i<num;i++)
        {
            nums[i]+=x;
        }
        return *this;
    }
    array &operator-=(float x)
    {
        #pragma omp simd
        for (int i=0;i<num;i++)
        {
            nums[i]-=x;
        }

        return *this;

    }
    array &operator -(float x)
    {
        #pragma omp simd 
        for(int i=0;i<num;i++)
        {
            nums[i]-=x;
        }
        return *this;
    }
    array &operator*=(float x)
    {
        #pragma omp simd
        for (int i=0;i<num;i++)
        {
            nums[i]*=x;
        }

        return *this;

    }
    array &operator *(float x)
    {
        #pragma omp simd 
        for(int i=0;i<num;i++)
        {
            nums[i]*=x;
        }
        return *this;
    }
    array &operator/=(float x)
    {
        #pragma omp simd
        for (int i=0;i<num;i++)
        {
            nums[i]-=x;
        }

        return *this;

    }
    array &operator /(float x)
    {
        #pragma omp simd 
        for(int i=0;i<num;i++)
        {
            nums[i]-=x;
        }
        return *this;
    }
};
int array::len()
{
    return len_shape;
}
 array:: array(initializer_list<int> il)
{
    int size_ = il.size();
    shape = new int[size_];
    len_shape =size_;
    int i=0;
    for (auto tmp = il.begin();tmp!=il.end();tmp++)
    {
        shape[i] = *tmp;
        i++;
    }
}
void array::construct(initializer_list<float> il)
{
    
    nums = new float[il.size()];
    int i=0;
    #pragma omp simd
    for (auto tmp = il.begin();tmp!=il.end();tmp++)
    {
        nums[i] =*tmp;
        i++;
        num+=1;
    }
}
float* array::sum_dim_x()
{
     float *result =new float();
        if (num >=4)
        {
            __m128 res = _mm_set_ps1(0.f);
            __m128 temp;
            float *res_ptr;
            res_ptr = new float[4];
            
            for (int i=0;i<num-4;i+=4)
            {
                temp =_mm_load_ps(nums+i);
                res = _mm_add_ps(res,temp);
                // cout<<i<<endl;
            }
            _mm_store1_ps(res_ptr,res);

            for (int i=0;i<4;i++)
            {
                *result += res[i];
            }

        }
        for (int i=((num)/4)*4;i<num;i++)*result += nums[i];
        return result;
}
float* array::sum_dim_0()
{
    float * result = new float[shape[1]]();
    if (shape[1]<4)
    {
        for (int i=0;i<shape[1];i++)
        {
            for (int j=0;j<shape[0];j++)
            {
                result[i]+=nums[j*shape[1]+i];
            }
        }

        return result;
    }
    for (int j=0;j<shape[1];j+=4)
    {
        __m128 res = _mm_set_ps1(0.f);
        __m128 temp = _mm_set_ps1(0.f);
        for (int i=0;i<shape[0]-1;i++)
        {
            _mm_prefetch(nums+4*j+shape[1]*(i+1),_MM_HINT_ET0);
            temp = _mm_load_ps(nums+4*j+shape[1]*i);
            res = _mm_add_ps(res,temp);
        }
        temp = _mm_load_ps(nums+4*j+shape[1]*(shape[0]-1));
        res  = _mm_add_ps(res,temp);
        _mm_stream_ps(result+4*j,res);
    }
    int j =(shape[1]/4)*4;
    for (int i=0;i<shape[0]-1;i++)
    {
        _mm_prefetch(nums+j+shape[1]*(i+1),_MM_HINT_ET0);
        for ( j;j<shape[1];j++)
        {
            result[j] += nums[j];
        }
    }
    return result;
}
float* array::sum_dim_1()
{
    float * result = new float[shape[0]]();

    for (int i=0;i<shape[0];i++)
    {
        #pragma omp simd
        for (int j=0;j<shape[1];j++)
        {
            result[i]+=nums[shape[0]*i+j];
        }
    }
    return result;
}
float* array::sum(int dim)
{
    if (dim ==-1)
    {
         return sum_dim_x();
    }

    else if (dim ==0)
    {
        if (len_shape ==1) return sum_dim_x();
        return sum_dim_0();
    }
    else
    {
        if (len_shape==1) return sum_dim_x();
        return sum_dim_1();
    }
    
}
// float* dot(array& other)
// {
    
// }
void array::put_out()
{
    for(int i=0;i<shape[1];i++)
    {
        for (int j=0;j<shape[0];j++)cout<<nums[i*shape[0]+j]<<" ";
        cout<<endl;
    
    }
}
 array::~ array()
{
}


int main()
{
    array nu={2,2};
    nu.construct({1,2,3,4});
    float *a = new float[4];
    a = nu.sum(1);
    cout<<a[1]<<endl;
    return 0;
}