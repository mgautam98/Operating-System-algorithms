#include<bits/stdc++.h>
using namespace std;


int main(){

    string str = "12342156212376321236";
    int NoOfFrames = 3, faults=0;
    unordered_set<int> frames;
    queue<int> fifo_order;
    for(int i=0; i<str.size(); i++){
        int page = str[i] - '0';
        if(frames.size()<NoOfFrames){
            if(frames.find(page)==frames.end()){
                faults++;
                fifo_order.push(page);
                frames.insert(page);
            }
        }else{
            if(frames.find(page)==frames.end()){
                faults++;
                int val = fifo_order.front();
                fifo_order.pop();
                frames.erase(val);
                fifo_order.push(page);
                frames.insert(page);
            }
        }
        // for(auto i:frames) cout<<i<<" ";
        // cout<<endl;
    }
    cout<<"Total Faults are : "<<faults<<endl;

    return 0;
}