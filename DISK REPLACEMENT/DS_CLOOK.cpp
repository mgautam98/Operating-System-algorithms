#include<bits/stdc++.h>
using namespace std;
#define TRACKS 199 //total 200 0-199


int main(){
    freopen("input_SCAN.txt", "r", stdin);
    int currentPosition = 53, t, n;
    char direction;
    cin>>currentPosition>>direction>>n;
    vector<int> a; 
    for(int i=0; i<n; i++){
        cin>>t;
        a.push_back(t);
    }
    sort(a.begin(), a.end());
    int totalCylinders;

    //INDEX of currenPostion 
    int pos = lower_bound(a.begin(), a.end(), currentPosition) - a.begin();
    cout<<"Sequence is :\n";
    if(direction=='L'){
        totalCylinders = (currentPosition - a[0]) + (a[a.size()-1] - a[pos]) + (a[a.size()-1] - a[0]);
        for(int i=pos-1; i>=0; i--) cout<<a[i]<<" ";
        for(int i=a.size()-1; i>=pos; i--) cout<<a[i]<<" ";
    }else{
        totalCylinders = (a[a.size()-1] - currentPosition) + (a[pos-1] - a[0]) + a[a.size()-1] - a[0]; 
        for(int i=pos; i<a.size(); i++) cout<<a[i]<<" ";
        for(int i=0; i<=pos-1; i++) cout<<a[i]<<" ";
    }
    cout<<"\nTotal Cylinders :"<<totalCylinders<<endl;
}