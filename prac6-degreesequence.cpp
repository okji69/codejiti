#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cout<<"enter the size of degree sequence"<<endl;
    cin>>n;
    cout<<"enter the degree sequence code ";
    multiset<int,greater<int>>s;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        s.insert(x);
    }
    while(!s.empty()){
        int x=*s.begin();
        s.erase(s.begin());
        if(x>s.size()){
            cout<<"NOT POSSIBLE"<<endl;
            return 0;
        }
        vector<int>v;
        for(auto it:s){
            x--;
            v.push_back(it);
            if(x==0){break;}
        }
        for(auto it:v){
            s.erase(s.find(it));
            if(it-1>0){s.insert(it-1);}
        }

    }
    cout<<"POSSIBLE"<<endl;
}