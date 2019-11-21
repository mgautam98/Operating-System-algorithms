#include <bits/stdc++.h>
using namespace std;

bool SafetyAlgorithm(vector<vector<int>> AllocatedResources, vector<vector<int>> MaxResource, vector<vector<int>> NeedResources, vector<int> AvailableResources, vector<bool> &Finished, vector<int> &SafeSequence, const int noOfProcesses, const int noOfResources)
{

    int safeSequenceCounter = 0;

    for (int i = 0; i < noOfProcesses; i++)
    {
        for (int j = 0; j < noOfProcesses; j++)
        {
            if (!Finished[j])
            {
                bool isGoodToGo = true;
                for (int r = 0; r < noOfResources; r++)
                {
                    if (NeedResources[j][r] > AvailableResources[r])
                    {
                        isGoodToGo = false;
                        break;
                    }
                }

                if (isGoodToGo)
                {
                    SafeSequence[safeSequenceCounter++] = j;

                    for (int r = 0; r < noOfResources; r++)
                    {
                        AvailableResources[r] += AllocatedResources[j][r];
                        Finished[j] = true;
                    }
                }
            }
        }
    }

    // for(int i=0; i<noOfProcesses; i++){
    //     if(!Finished[i]) cout<<i<<" NF\n";
    //     else cout<<i<<" F\n";
    // }

    for (int i = 0; i < noOfProcesses; i++)
        if (SafeSequence[i] == -1)
            return false;
    return true;
}

void RemoveAndCheckDeadlock(vector<vector<int>> AllocatedResources, vector<vector<int>> MaxResource, vector<int> AvailableResources, vector<bool> &Finished, vector<int> &SafeSequence, const int noOfProcesses, const int noOfResources, vector<int> InDeadlock)
{

    cout << "Processes in Deadlock : ";
    for (auto i : InDeadlock)
    {
        cout << i << ",";
    }
    cout << endl;

    for (int i = 0; i < InDeadlock.size(); i++)
    {
        int PID = InDeadlock[i];
        for (int j = 0; j < noOfResources; j++)
        {
            AvailableResources[j] += AllocatedResources[PID][j];
            AllocatedResources[PID][j] = 0;
            MaxResource[PID][j] = 0;
        }

        cout << "\nAvailable ";
        for (auto i : AvailableResources)
            cout << i << " ";
        cout << endl;

        vector<vector<int>> NeedResources(noOfProcesses, vector<int>(noOfResources));
        for (int k = 0; k < noOfProcesses; k++)
            for (int j = 0; j < noOfResources; j++)
                NeedResources[k][j] = MaxResource[k][j] - AllocatedResources[k][j];

        vector<bool> Finished(noOfProcesses, false);

        bool notInDeadlock = SafetyAlgorithm(AllocatedResources, MaxResource, NeedResources, AvailableResources, Finished, SafeSequence, noOfProcesses, noOfResources);
        cout<<"IN DEADLOCK "<<notInDeadlock<<endl;
        if (notInDeadlock)
        {
            cout << "Deadlock Recovery: Remove Process IDs : ";
            for (int j = 0; j <= i; j++)
            {
                cout << InDeadlock[j] << ", ";
            }
            cout << endl;
            return;
        }
    }
    cout << "Deadlock Recovery: Remove Process IDs : ";
    for (int j = 0; j <= InDeadlock.size(); j++)
    {
        cout << InDeadlock[j] << ", ";
    }
    cout << endl;
    return;
}

int main()
{
    freopen("input2.txt", "r", stdin);

    int noOfProcesses = 5, noOfResources = 3;

    vector<vector<int>> AllocatedResources(noOfProcesses, vector<int>(noOfResources));
    vector<vector<int>> MaxResource(noOfProcesses, vector<int>(noOfResources));
    vector<int> AvailableResources(noOfResources);
    vector<vector<int>> NeedResources(noOfProcesses, vector<int>(noOfResources));

    cin >> noOfProcesses >> noOfResources;

    for (int i = 0; i < noOfProcesses; i++)
        for (int j = 0; j < noOfResources; j++)
            cin >> AllocatedResources[i][j];

    for (int i = 0; i < noOfProcesses; i++)
        for (int j = 0; j < noOfResources; j++)
            cin >> MaxResource[i][j];

    for (int i = 0; i < noOfResources; i++)
        cin >> AvailableResources[i];

    for (int i = 0; i < noOfProcesses; i++)
        for (int j = 0; j < noOfResources; j++)
            NeedResources[i][j] = MaxResource[i][j] - AllocatedResources[i][j];

    vector<int> SafeSequence(noOfProcesses, -1);
    vector<bool> Finished(noOfProcesses, false);

    bool isSafe = SafetyAlgorithm(AllocatedResources, MaxResource, NeedResources, AvailableResources, Finished, SafeSequence, noOfProcesses, noOfResources);

    vector<int> InDeadlock;

    if (isSafe)
    {
        cout << "\nIt is not in Deadlock\n"
             << endl;
        return 0;
    }

    for (int i = 0; i < noOfProcesses; i++)
    {
        if (!Finished[i])
        {
            InDeadlock.push_back(i);
        }
        else
        {
            int PID = i;
            for (int j = 0; j < noOfResources; j++)
            {
                AvailableResources[j] += AllocatedResources[PID][j];
                AllocatedResources[PID][j] = 0;
                MaxResource[PID][j] = 0;
            }
        }
    }

    RemoveAndCheckDeadlock(AllocatedResources, MaxResource, AvailableResources, Finished, SafeSequence, noOfProcesses, noOfResources, InDeadlock);
    return 0;
}
