#include <bits/stdc++.h>
using namespace std;

int main()
{

    string str = "7012030423032";
    int NoOfFrames = 4, faults = 0;
    unordered_map<int, int> frames;

    for (int i = 0; i < str.size(); i++)
    {
        int page = str[i] - '0';
        if (frames.size() < NoOfFrames)
        {
            if (frames.find(page) == frames.end())
            { //FRAME NOT FOUND
                faults++;
            }
            //Increment all frames by 1
            for (auto &i : frames)
            {
                i.second++;
            }
            frames[page] = 0;
        }
        else
        {
            if (frames.find(page) == frames.end())
            {
                faults++;
                //search for max value key
                int key = -1, mxkey = -1;
                for (auto i : frames)
                {
                    if (mxkey < i.second)
                    {
                        key = i.first;
                        mxkey = i.second;
                    }
                }
                frames.erase(key);
                //Increment all frames by 1
                for (auto &i : frames)
                {
                    i.second++;
                }
                frames[page] = 0;
            }else{
                //Increment all frames by 1
                for (auto &i : frames)
                {
                    i.second++;
                }
                frames[page] = 0;
            }
        }
    }

    cout << "Total Faults are : " << faults << endl;

    return 0;
}