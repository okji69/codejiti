#include<bits/stdc++.h>
using namespace std;

map<string,multiset<string>>g;
vector<string>ans;
void dfs(string i){
    while(!g[i].empty()){
        string x= *g[i].begin();
        g[i].erase(g[i].begin());
        dfs(x);
    }
    ans.push_back(i);
}

void findItinerary(vector<vector<string>>& tickets) {
    ans.clear();
    g.clear();
    for(int i=0;i<tickets.size();i++){
        g[tickets[i][0]].insert(tickets[i][1]);
    }
    dfs("JFK");
    reverse(ans.begin(),ans.end());

}

int main(){
    int n;
    cout<<"enter number of edges"<<endl;
    cin>>n;
    vector<vector<string>>tickets(n);
    for(int i=0;i<n;i++){
        string a,b;
        cin>>a>>b;
        tickets[i].push_back(a);
        tickets[i].push_back(b);
    }
    
}