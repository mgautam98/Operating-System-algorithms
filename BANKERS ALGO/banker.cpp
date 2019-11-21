#include <bits/stdc++.h>
using namespace std;

bool SafetyAlgorithm(vector<vector<int>> AllocatedResources, vector<vector<int>> MaxResource, vector<vector<int>> NeedResources, vector<int> AvailableResources, vector<int> &SafeSequence, const int noOfProcesses, const int noOfResources)
{

    vector<bool> Finished(noOfProcesses, false);

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

    for (int i = 0; i < noOfProcesses; i++)
        if (SafeSequence[i] == -1)
            return false;
    return true;
}

int main()
{
    freopen("input.txt", "r", stdin);

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

    bool isSafe = SafetyAlgorithm(AllocatedResources, MaxResource, NeedResources, AvailableResources, SafeSequence, noOfProcesses, noOfResources);

    if (isSafe)
    {
        cout << "\nIt is in Safe State\n"
             << endl;
        for (auto i : SafeSequence)
        {
            cout << i << "->";
        }
        cout << "\b\b is one of safe sequence.";
    }
    else
    {
        cout << "\nIt is in Unsafe State\n";
        cout << "Processes ";
        for (int i = 0; i < noOfProcesses; i++)
        {
            if (SafeSequence[i] == -1)
            {
                cout << i << ", ";
            }
        }
        cout << "can cause deadlock.";
    }
    cout << "\n\n";

    char res = 'N';
    int p, r;

    while (1)
    {
        cout << "\t\tRequest Additional Resources (Y/N) :\n\n";
        cin >> res;

        if (res != 'Y' && res != 'y')
            break;

        cout << "Enter Process no. :\n";
        cin >> p;
        cout << "Enter Additional resource wanted e.g 1,0,2 :\n";
        for (int i = 0; i < noOfResources; i++)
        {
            cin >> r;
            MaxResource[p][i] += r;
        }

        for (int i = 0; i < noOfProcesses; i++)
            for (int j = 0; j < noOfResources; j++)
                NeedResources[i][j] = MaxResource[i][j] - AllocatedResources[i][j];

        for (int i = 0; i < noOfProcesses; i++)
            SafeSequence[i] = -1;



        bool isSafe = SafetyAlgorithm(AllocatedResources, MaxResource, NeedResources, AvailableResources, SafeSequence, noOfProcesses, noOfResources);
        if (isSafe)
        {
            cout << "\nYes, we can allocate and still be in safe state\n\n";
        }
        else
        {
            cout << "\nNo, we can not allocate\n\n";
        }
    }

    return 0;
}
