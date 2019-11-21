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
        totalCylinders = currentPosition + a[a.size()-1];
        for(int i=pos-1; i>=0; i--) cout<<a[i]<<" ";
        for(int i=pos; i<a.size(); i++) cout<<a[i]<<" ";
    }else{
        totalCylinders = (TRACKS - currentPosition) + (TRACKS - a[0]); 
        for(int i=pos; i<a.size(); i++) cout<<a[i]<<" ";
        for(int i=pos-1; i>=0; i--) cout<<a[i]<<" ";
    }
    cout<<"\nTotal Cylinders :"<<totalCylinders<<endl;
}