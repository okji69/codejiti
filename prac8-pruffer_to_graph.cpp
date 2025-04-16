#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    set<int>s;
    multiset<int>ini;
    for(int i=1;i<=n;i++){
        s.insert(i);
    }
    vector<int>v(n-2);
    for(int i=0;i<n-2;i++){
        cin>>v[i];
        if(s.find(v[i])!=s.end()){
            s.erase(v[i]);
        }
        ini.insert(v[i]);
    }
    for(int i=0;i<n-2;i++){
        int x=*s.begin();
        cout<<v[i]<<" "<<x<<endl;
        s.erase(s.begin());
        ini.erase(ini.find(v[i]));
        if(ini.find(v[i])==ini.end()){
            s.insert(v[i]);
        }
    }
    auto it=s.begin();
    int x=*it;
    it++;
    int y=*it;
    cout<<x<<" "<<y<<endl;
    return 0;
}