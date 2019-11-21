#include <bits/stdc++.h>
using namespace std;

int findFarthest(unordered_set<int> frames, string str, int i){
    map<int, int> m;

    for(auto k:frames){
        int index = INT_MAX;
        for(int p = str.length(); p>i; p--){
            int temp = str[p] - '0';
            if(k==temp){
                index = p;
            }
        }
        m[index] = k;
    }
    int mx = -1, mxVal = -1;
    for(auto p:m){
        if(mx<=p.first){
            mx = p.first;
            mxVal = p.second;
        }
    }
    return mxVal;
}

int main()
{

    string str = "70120304230321201701";
    int NoOfFrames = 3, faults = 0;
    unordered_set<int> frames;

    for (int i = 0; i < str.size(); i++)
    {
        int page = str[i] - '0';
        if (frames.size() < NoOfFrames)
        {
            if (frames.find(page) == frames.end())
            {
                faults++;
                frames.insert(page);
            }
        }
        else
        {
            if (frames.find(page) == frames.end())
            {
                faults++;
                int toReplace = findFarthest(frames, str, i);
                frames.erase(toReplace);
                frames.insert(page);
            }
        }
        for(auto k:frames) cout<<k<<" ";
        cout<<endl;
    }
    cout << "Total Faults are : " << faults << endl;

    return 0;
}