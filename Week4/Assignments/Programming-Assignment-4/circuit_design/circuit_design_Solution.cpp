#include<iostream>
#include <list>
#include <stack>
#define NIL -1
using namespace std;
#include <bits/stdc++.h>
#define NIL -1
using namespace std;


struct Slover_2SAT {
  struct util {
      util()
       :id(-1),LowLink(-1),OnStack(false)
       {}
      int id;
      int LowLink;
      bool OnStack;
      vector<int>edges;
   };

 Slover_2SAT(unordered_map<int,util>A,int n):Adj(move(A)),num_var(n),id(1)
 {}
 bool process_vertix(int u,vector<int>&result) {
  Adj[u].id=id;
  Adj[u].LowLink=id;
  Adj[u].OnStack=true;
  st.push(u);
  id++;
  for(int i=0;i<Adj[u].edges.size(); i++) {
    int v=Adj[u].edges[i];
     if(Adj[v].id==-1) {
       process_vertix(v,result);
       Adj[u].LowLink=min(Adj[u].LowLink,Adj[v].LowLink);
     }
     else if(Adj[v].OnStack)
     {
       Adj[u].LowLink=min(Adj[u].LowLink,Adj[v].id);
     }

  }
     int w=0;
     vector<int>temp1;
    if(Adj[u].LowLink == Adj[u].id ) {
      while (st.top()!=u)
       {
            w= st.top();
            st.pop();
            if(Adj[w].LowLink==Adj[-w].LowLink)
                return false;
             result[abs(w)-1]=w<0?1:0;
            temp1.push_back(w);
            Adj[w].OnStack=false;
          }
        w= st.top();
        st.pop();
        if(Adj[w].LowLink==Adj[-w].LowLink)
            return false;
        temp1.push_back(w);
        result[abs(w)-1]=w<0?1:0;
        SCC.push_back(temp1);
        Adj[w].OnStack=false;

    }
return true; }
bool solve(vector<int>&result) {
   for(int i=-num_var; i<=num_var ; i++ ) {
     if(i==0)
        continue;
     if(Adj[i].id==-1 ) {
      bool x= process_vertix(i,result);
      if(!x)
        return false;
     }
   }

 return true;}

  unordered_map<int,util>Adj;
  int num_var;
  int id;
  stack<int>st;
  vector<vector<int>>SCC;
   };
int main() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;

    unordered_map<int,Slover_2SAT::util>Adj;
    for(int i=0, x,y; i<m ; i++) {
        cin>>x>>y;
        Adj[-x].edges.push_back(y);
        Adj[-y].edges.push_back(x);
    }
    Slover_2SAT Sol(move(Adj),n);

    vector<int> result(n);
    if (Sol.solve(result)) {
        cout << "SATISFIABLE" << endl;
        for (int i = 1; i <= n; ++i) {
            if (!result[i-1]) {
                cout << -i;
            } else {
                cout << i;
            }
            if (i < n) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
    } else {
        cout << "UNSATISFIABLE" << endl;
    }
 return 0;
}
