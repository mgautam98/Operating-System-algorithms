#include<bits/stdc++.h>
using namespace std;
#define TRACKS 199 //total 200 0-199


int main(){
    freopen("input.txt", "r", stdin);
    int currentPosition = 53, t, n;
    queue<int> q; 
    cin>>currentPosition>>n;
    for(int i=0; i<n; i++){
        cin>>t;
        q.push(t);
    }
    int totalCylinders = 0;
    cout<<"Sequence is :\n";
    while(!q.empty()){
        int a = q.front();
        q.pop();
        cout<<a<<" ";
        totalCylinders += abs(a-currentPosition);
        currentPosition = a;
    }
    cout<<"\nTotal Cylinders :"<<totalCylinders<<endl;
}