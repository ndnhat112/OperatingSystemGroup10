#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define ENDL '\n'

using namespace std;

string filename = "output.txt";
fstream file;

struct Process 
{
    int pid;
    int at; // arrival time (ms)
    int bt; // burst time (ms)

    Process(int pid, int at, int bt): pid(pid), at(at), bt(bt) {}
};

void init(vector<Process> &processes) 
{   
    ios_base::openmode file_mode = fstream::app;
    file.open(filename, file_mode);

    int n; cin >> n; // Nhap tong so process
    for (int i=1;i<=n;i++) 
    {
        int pid, at, bt; cin >> at >> bt;
        processes.push_back(Process(i,at,bt));
    }

    return;
}

int check_arrival(int time, vector<Process> processes) 
{
    for (int i=0;i<processes.size();i++) 
    {
        if (processes[i].at == time)  
        {
            return i;
        }
    }

    return -1;
}

void srt(vector<Process> processes) 
{
    file << "Time (ms)" << " " << "Process" << " " << "Execution time (ms)" << ENDL;

    cout << "Time (ms)" << " " << "Process" << " " << "Execution time (ms)" << ENDL;
    
    int time = 0, start = 0;

    priority_queue<pair<pair<int,int>, int>, vector<pair<pair<int,int>, int>>, greater<pair<pair<int,int>, int>> > pq;
    Process first_arrived = processes[check_arrival(time, processes)];
    pq.push(make_pair(make_pair(first_arrived.bt, first_arrived.at), first_arrived.pid));

    int tmp_pid = first_arrived.pid; //pre-process id 
    int et = 0; // execution time (ms)

    while (!pq.empty()) 
    {
        pair<pair<int,int>, int> curr_p = pq.top(); pq.pop();
    
        time+=1;

        if (check_arrival((time),processes) != -1) 
        {
            int tmp_index = check_arrival((time),processes);
            pq.push(make_pair(make_pair(processes[tmp_index].bt, processes[tmp_index].at), processes[tmp_index].pid));
        }

        if (curr_p.second == tmp_pid) 
        {
            et+=1;
            if ((curr_p.first.first-1) > 0) 
            {
                pq.push(make_pair(make_pair(curr_p.first.first-1, curr_p.first.second), curr_p.second));
            }
        }

        
        if ((curr_p.second != pq.top().second) || pq.empty()) 
        {
            cout << start << " " << curr_p.second << " " << et << ENDL;
            file << start << " " << curr_p.second << " " << et << ENDL;
            et = 0;
            tmp_pid = pq.top().second;
            start = time;
        }
    }

    cout << "Finish: " << time << " (ms)" <<ENDL;
    file.close();
    return;
}

int main() 
{
    vector<Process> processes;
    init(processes);
    srt(processes);

    return 0;
}