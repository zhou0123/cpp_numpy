//  #include<initializer_list>
//  #include<iostream>
//  #include<thread>
//  using namespace std;
// int main()
// {
//     int count =0;

//     std::thread workers[8];

//     for (int i=0;i<8;i++)
//     {
//         workers[i] = std::thread([&]
//         {
//             count++;
//             cout<<"..."<<count<<"..."<<endl;
//         });
//     }

//     for (auto & worker :workers) worker.join();
//     cout<<count<<endl;
//     return 0 ;
// }
