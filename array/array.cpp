
#include <stdarg.h>
#include <immintrin.h>
#include <xmmintrin.h>
#include<iostream>
#include<initializer_list>
#include <sched.h>
#include<thread>
using namespace std;

template <class T>
int len(T &array)
{
    return  sizeof(array)/(array[0]);
}
class  ndarray
{

private:
    int num{0};//元素个数
    int len_shape;//shape的len
    float* sum_dim_x ();
    float* sum_dim_0();
    float* sum_dim_1();
public:
    int *shape;
    float *nums;//储存元素
     ndarray(initializer_list<int> il);
    ~ ndarray();
    void put_out();
    void construct(initializer_list<float> il);
    void transpose();
    float *sum(int dim =-1);
    int len();
    void dot(ndarray &other);
    
    ndarray &operator+=(float x)
    {
        #pragma omp simd
        for (int i=0;i<num;i++)
        {
            nums[i]+=x;
        }

        return *this;
    }
    ndarray &operator+ (float x)
    {
        #pragma omp simd 
        for(int i=0;i<num;i++)
        {
            nums[i]+=x;
        }
        return *this;
    }
    ndarray &operator-=(float x)
    {
        #pragma omp simd
        for (int i=0;i<num;i++)
        {
            nums[i]-=x;
        }

        return *this;

    }
    ndarray &operator -(float x)
    {
        #pragma omp simd 
        for(int i=0;i<num;i++)
        {
            nums[i]-=x;
        }
        return *this;
    }
    ndarray &operator*=(float x)
    {
        #pragma omp simd
        for (int i=0;i<num;i++)
        {
            nums[i]*=x;
        }

        return *this;

    }
    ndarray &operator *(float x)
    {
        #pragma omp simd 
        for(int i=0;i<num;i++)
        {
            nums[i]*=x;
        }
        return *this;
    }
    ndarray &operator/=(float x)
    {
        #pragma omp simd
        for (int i=0;i<num;i++)
        {
            nums[i]-=x;
        }

        return *this;

    }
    ndarray &operator /(float x)
    {
        #pragma omp simd 
        for(int i=0;i<num;i++)
        {
            nums[i]-=x;
        }
        return *this;
    }
    float* &operator [](initializer_list<int> il)
    {
        int size_ = il.size();
        if (size_>2)
        {
            cout<<"error"<<endl;
            return;
        }
        
        else if(size_ ==1) 
        {
            

            int loc = *il.begin();
            if (len_shape ==1) 
            {
                float* res =new float[size_];
                res[0] = nums[loc];
                return res;
            }
            else if (len_shape ==2)
            {
                float* res =new float[shape[1]];
                #pragma omp simd
                for (int i=0;i<shape[1];i++)
                {
                    res[i] = nums[i+loc*shape[1]];
                }

                return res;
            }
        }
        else if(size_ ==2)
        {
            int i=0;
            int second;
            for (auto itor = il.begin();itor!=il.end();itor++)
            {
                if (*itor >=shape[i])
                {
                    cout<<"error"<<endl;
                    return ;
                }
                second = *itor;
                i++;
            }

            float * res = new float();

            *res = nums[shape[0]**((il.begin()))+second];
            return res;
        } 
    }
};
int ndarray::len()
{
    return len_shape;
}
 ndarray:: ndarray(initializer_list<int> il)
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
void ndarray::construct(initializer_list<float> il)
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
float* ndarray::sum_dim_x()
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
float* ndarray::sum_dim_0()
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
float* ndarray::sum_dim_1()
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
float* ndarray::sum(int dim)
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
void ndarray::dot(ndarray& other)
{
    int * other_shape;
    other_shape = other.shape;
    int num_tmp = shape[0]*other_shape[1];
    float* res = new float[num_tmp]();

    #pragma omp simd
    int core_num =8;
    std::thread workers[8];
    // std::thread workers[other_shape[1]];
    int base_size = other_shape[1]/8;
    int remain = other_shape[1]%8;
    for (int num_thread=0;num_thread<8;num_thread++)
    {
        // if (remain!=0)
        // {
        //     int start =num_thread*base_size;
        //     int end = (num_thread+1)*base_size+1;
        //     remain--;
        // }
        workers[num_thread] = std::thread(
            [&]{
                
                for (int j=num_thread*base_size;j<(num_thread+1)*base_size;j++)
                {
                    for (int i=0;i<shape[0];i++)
                    {
                        for (int k=0;k<shape[1];k++)res[j+shape[0]*i] += nums[i*shape[0]+k]*other.nums[k*other_shape[0]+j];
                    }
                }
                
            }

        );
        //绑core
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(num_thread, &cpuset);
        int rc = pthread_setaffinity_np(workers[num_thread].native_handle(), sizeof(cpu_set_t), &cpuset);
    }
    for (auto & worker : workers) worker.join();

    if (remain !=0)
    {
        #pragma omp parallal num_threads(remain)
        {
            #pragma omp for
            {
                for (int j=8*base_size;j<other_shape[1];j++)
                {
                    for (int i=0;i<shape[0];i++)
                    {
                        for (int k=0;k<shape[1];k++)res[j+shape[0]*i] += nums[i*shape[0]+k]*other.nums[k*other_shape[0]+j];
                    }
                }

            } 
        }
    }
}
void ndarray::put_out()
{
    for(int i=0;i<shape[1];i++)
    {
        for (int j=0;j<shape[0];j++)cout<<nums[i*shape[0]+j]<<" ";
        cout<<endl;
    
    }
}
 ndarray::~ ndarray()
{
}
void ndarray::transpose()
{
    float * nums_ = new float[num];
    #pragma omp parallal for 
    for(int i=0;i<shape[0];i++)
    {
        for (int j=0;j<shape[1];j++)
        {
            nums_[i+shape[1]*j] = nums[i*shape[0]+j];
        }
    }

    delete nums;
    nums = nums_;
    int tmp=shape[1];
    shape[1] = shape[0];
    shape[0] = shape[1];
}
int main()
{
    ndarray nu={2,2};
    nu.construct({1,2,3,4});
    float *a = new float[4];
    a = nu.sum(1);
    cout<<a[1]<<endl;
    return 0;
}