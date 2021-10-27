#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string.h>


#define max_vertices 201
using namespace std;

 struct Dis {
    int to;
    int capacity;
};
typedef struct Dis Dis;
typedef vector<Dis> Edge;

Edge edges;
/**The vertix number maps to the edges' ids which outing of that vertix**/
map<int,vector<int>> trancitions;

int read_data() {
    int m,n;
    cin>>m>>n;
    for(int i=0;i<n;i++) {
        int from,to,cap;
        cin>>from>>to>>cap;

         if(from == to)
          continue;
      vector <int> temp = trancitions[from];
      temp.push_back(edges.size());
      trancitions[from]=temp;
      Dis temp2;
      temp2.to=to;
      temp2.capacity=cap;
      edges.push_back(temp2);

      temp = trancitions[to];
      temp.push_back(edges.size());
      trancitions[to]=temp;
      temp2.to=from;
      temp2.capacity=0;
      edges.push_back(temp2);

      }
return m;
}


int max_flow(int from, int to) {
    int flow = 0;
    bool test[edges.size()];
    memset(test,false,sizeof(test));
    /* your code goes here */
    queue<vector<int>>My_queue;
    queue <int>min_flow;

    vector<int> temp=trancitions[from];

     for(int i=0 ;i<temp.size(); i++) {
         int current_id=temp[i];
         if(edges[current_id].to==to && edges[current_id].capacity>0 ) {
             flow += edges[current_id].capacity;
             edges[current_id^1].capacity=edges[current_id].capacity;
             edges[current_id].capacity=0;
             i=-1;
             while (!My_queue.empty())
                My_queue.pop();
             while(!min_flow.empty())
                min_flow.pop();
         memset(test,false,sizeof(test));
             continue;
         }

        if(edges[current_id].capacity>0){
        test[current_id]=true;
        vector<int> t;
        t.push_back(current_id);
        My_queue.push(t);
        min_flow.push(edges[current_id].capacity);
        }
     }

    while(!My_queue.empty())  {
     int flow_min_value=min_flow.front();
     min_flow.pop();
     temp=My_queue.front();
     My_queue.pop();

     int current_id=temp[temp.size()-1];
     vector<int>temp2=trancitions[edges[current_id].to];
     for(int i=0; i<temp2.size(); i++) {

        current_id=temp2[i];
        if(test[current_id])
            continue;
        if(edges[current_id].to==to && edges[current_id].capacity>0) {
           flow_min_value=flow_min_value<edges[current_id].capacity?flow_min_value:edges[current_id].capacity;
           edges[current_id].capacity-=flow_min_value;
           edges[current_id^1].capacity+=flow_min_value;
           flow += flow_min_value;

           for(int i=0; i<temp.size(); i++) {
            current_id=temp[i];
            edges[current_id].capacity-=flow_min_value;
            edges[current_id^1].capacity+=flow_min_value;
           }
          while (!My_queue.empty()){
                My_queue.pop();
                min_flow.pop();
          }
          memset(test,false,sizeof(test));
     //////////////////////////
     temp=trancitions[from];
     for(int i=0 ;i<temp.size(); i++) {
         int current_id=temp[i];
     if(edges[current_id].capacity>0){
        vector<int> t;
        t.push_back(current_id);
        My_queue.push(t);
        min_flow.push(edges[current_id].capacity);
        test[current_id]=true;
        }
     }

        break;
        }

        else {
         if(edges[current_id].capacity<=0 || test[current_id] )
            continue;
         vector<int>temp3=temp;
         temp3.push_back(current_id);
         int min_=flow_min_value<edges[current_id].capacity?flow_min_value:edges[current_id].capacity;
         My_queue.push(temp3);
         min_flow.push(min_);
         test[current_id]=true;
        }
     }

    }

    return flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
   int distination = read_data();
    cout << max_flow(1,distination) << "\n";
    return 0;
}
