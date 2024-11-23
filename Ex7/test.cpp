#include <iostream>
#include <cstring>

using namespace std;

const int MAX_PROCESSES = 50;
const int MAX_RESOURCES = 50;

typedef int ProcessArray[MAX_PROCESSES];
typedef int ResourceArray[MAX_RESOURCES];
typedef int AllocationArray[MAX_PROCESSES][MAX_RESOURCES];

struct SystemInfo {
	int n, m;
	ResourceArray Available;
	AllocationArray Max, Allocation;
};

// returns -1 if the system is deadlock free, or the LOWEST index of the processes in deadlock
bool check(const ResourceArray& Work, int Request_i[], int m) 
{
    for (int j=0;j<m;j++) 
    {
        if (Request_i[j]>Work[j]) 
        {
            return false;
        }
    }
    return true;
}

void release(ResourceArray& Work, const int Allocation_i[], int m) 
{
    for (int j=0;j<m;j++) 
    {
        Work[j] = Work[j] + Allocation_i[j];
    }

    return;
}

int findFirstDeadlockedProcess(const SystemInfo& s, AllocationArray Request) {
	// TODO: deadlock detection
	ResourceArray Work;
	bool Finish[s.n] = {false};

	for (int i=0;i<s.m;i++) 
	{
		Work[i] = s.Available[i];
	}
    
	for (int count=0; count<s.n;count++) 
	{
		for (int i=0; i<s.n;i++) 
		{
			if (!Finish[i] && (check(Work, Request[i], s.m))) 
            {
                Finish[i] = true;
                release(Work, s.Allocation[i], s.m);
            }
		}
	}

    for (int i=0;i<s.n;i++) 
    {
        if (!Finish[i]) return i;
    }

	return -1;
	// END TODO
}






template <typename T>
void assignArray(T* a, initializer_list<T> l) {
	size_t i = 0;
	for (auto li : l)
		a[i++] = li;
}

void assignAllocationArray(AllocationArray a, initializer_list<initializer_list<int>> l) {
	size_t i = 0;
	for (auto li : l)
		assignArray(a[i++], li);
}

void deadlockDetection(int argc, const char** argv) {
	SystemInfo s;
	AllocationArray Request;

	if (argc <= 1 || strcmp(argv[1], "-i") != 0) {
		s.n = 5;
		s.m = 3;
		assignArray(s.Available, {0, 0, 0});
		assignAllocationArray(s.Allocation, {
			{0, 1, 0},
			{2, 0, 0},
			{3, 0, 3},
			{2, 1, 1},
			{0, 0, 2}});
		
		assignAllocationArray(Request, {
			{0, 0, 0},
			{2, 0, 2},
			{0, 0, 0},
			{1, 0, 0},
			{0, 0, 2}});
        
	} else {
		cin >> s.n >> s.m;

		int i, j;
		for (i = 0; i < s.n; i++)
			cin >> s.Available[i];

		for (i = 0; i < s.n; i++)
			for (j = 0; j < s.m; j++)
				cin >> s.Allocation[i][j];

		for (i = 0; i < s.n; i++)
			for (j = 0; j < s.m; j++)
				cin >> Request[i][j];
	}

	cout << "Deadlock process: " << findFirstDeadlockedProcess(s, Request) << endl;
}


int main(int argc, const char** argv) {
	// TODO: gỡ chú thích một trong 2 dòng dưới đây tuỳ theo bài được giao:
	//deadlockAvoidance(argc, argv);
	deadlockDetection(argc, argv);
	// END TODO

    
	return 0;
}