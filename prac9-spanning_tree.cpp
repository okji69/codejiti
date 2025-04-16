#include<bits/stdc++.h>
#define pb push_back
using namespace std;

vector<vector<vector<int>>>allgraphs;

void generateSubgraphs(int n,int m,vector<pair<int,int>>&edges)
{
  int total=(1<<m);
  for(int i=0;i<total;i++)
  {
    vector<vector<int>>graph(n);
    for(int j=0;j<m;j++)
    {
      if(i&(1<<j))
      {
        int u=edges[j].first;
        int v=edges[j].second;
        graph[u].pb(v);
        graph[v].pb(u);
      }
    }
    allgraphs.pb(graph);
  }
}
bool check(int n,vector<vector<int>>&graph)
{
  int nc=0,ec=0,start=-1;
  for(int i=0;i<n;i++)
  {
    if(!graph[i].empty())
    {
      start=i;
      break;
    }
  }
  if(start==-1)
  {
    return false;
  }
  queue<int>q;
  vector<bool>vis(n,false);
  q.push(start);
  vis[start]=true;
  nc++;
  while(!q.empty())
  {
    int node=q.front();
    q.pop();
    for(int v:graph[node])
    {
      ec++;
      if(!vis[v])
      {
      vis[v]=true;
      q.push(v);
      nc++;
      }
    }
  }
  ec/=2;
  for(int i=0;i<n;i++)
  {
    if(!graph[i].empty() && !vis[i])
    {
      return false;
    }
  }
  return(nc==n && ec==n-1);
}
void solve()
{
  int n,m;
  cin>>n>>m;
  vector<pair<int,int>>edges(m);
  for(int i=0;i<m;i++)
  {
  int x,y;
  cin>>x>>y;
  edges[i]={x-1,y-1};
  }
  generateSubgraphs(n,m,edges);
  int cnt=0;
  cout<<"Total Subgraphs:"<<allgraphs.size()<<"\n";
  for(int i=0;i<allgraphs.size();i++)
  {
    cout<<"Subgraph "<<i+1<<":\n";
    for(int u=0;u<n;u++)
    {
      if(!allgraphs[i][u].empty())
      {
        cout<<"Node "<<u+1<<" -> ";
        for(int v:allgraphs[i][u])
        {
          cout<<v+1<<" ";
        }
        cout<<"\n";
      }
    }
    if(check(n,allgraphs[i]))
    {
      cnt++;
      cout<<"YES\n";
    }
    else
    {
      cout<<"NO\n";
    }
    cout<<"------------------\n";
  }
  cout<<cnt<<endl;
}
signed main(){
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);
int t=1;
while(t--){
solve();
}
}
