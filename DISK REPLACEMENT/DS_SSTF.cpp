#include<bits/stdc++.h>
using namespace std;
#define TRACKS 199 //total 200 0-199

int closest(set<int> a, int currentPosition){
    int mn = INT_MAX, mnVal = -1;
    for(auto i:a){
        int tp = abs(i-currentPosition);
        if(mn>tp){
            mn = tp;
            mnVal = i;
        }
    }
    return mnVal;
}

int main(){
    freopen("input.txt", "r", stdin);
    int currentPosition = 53, t, n;
    set<int> a; 
    cin>>currentPosition>>n;
    for(int i=0; i<n; i++){
        cin>>t;
        a.insert(t);
    }
    int totalCylinders = 0;
    cout<<"Sequence is :\n";
    while(a.size()>0){
        int toSeek = closest(a, currentPosition);
        cout<<toSeek<<" ";
        totalCylinders += abs(toSeek - currentPosition);
        currentPosition = toSeek;
        a.erase(toSeek);
    }
    cout<<"\nTotal Cylinders :"<<totalCylinders<<endl;
}