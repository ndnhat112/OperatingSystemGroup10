#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

struct shm 
{
    int x,y,z;
    int ready=0;
};

mutex mt;
condition_variable cond;
shm shared;

void parent_func() 
{
    {
        lock_guard<mutex> lock(mt);
        cout << "Nhap gia tri x: " ; cin >> shared.x; 
        cout << "Nhap gia tri y: " ; cin >> shared.y;
        shared.ready = 1;
    }
    cond.notify_one();

    {
        unique_lock<mutex> lock(mt);
        cond.wait(lock, [] {return shared.ready==0;});
    }

    {
        lock_guard<mutex> lock(mt);
        cout << "Gia tri cua z: " << shared.z << "\n";
    }

    return; 
}

void child_func() 
{
    {
        unique_lock<mutex> lock(mt);
        cond.wait(lock, [] {return shared.ready==1;});
    }

    {
        lock_guard<mutex> lock(mt);
        shared.z = shared.x + shared.y;
        shared.ready = 0;
    }
    cond.notify_one();
    
    return;
}

int main() 
{
    thread p_thread(parent_func), c_thread(child_func);
    p_thread.join();
    c_thread.join();

    return 0;
}