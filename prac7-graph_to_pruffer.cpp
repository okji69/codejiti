#include<bits/stdc++.h>
using namespace std;
int main(){ 
    int n;
    cout<<"Enter number of vertices"<<endl;
    cin>>n;

    vector<set<int>>v(n+1);
    cout<<"enter "<<n-1<<" edges"<<endl;
    set<pair<int,int>>s;
    for(int i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        if(s.find({v[x].size(),x})!=s.end()){
            s.erase(s.find({v[x].size(),x}));
        }
        if(s.find({v[y].size(),y})!=s.end()){
            s.erase(s.find({v[y].size(),y}));
        }
        v[x].insert(y);
        v[y].insert(x);
        s.insert({v[x].size(),x});
        
        s.insert({v[y].size(),y});
    }
    while(s.size()>2){
        auto it=*s.begin();
        s.erase(s.find(it));
        int y=*v[it.second].begin();
        cout<<y <<" ";
        v[it.second].erase(v[it.second].begin());
        s.erase({v[y].size(),y});
        v[y].erase(v[y].find(it.second));
        s.insert({v[y].size(),y});
    }
}