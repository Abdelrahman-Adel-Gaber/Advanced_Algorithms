#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <string.h>

#define MaxV 100
int cv[MaxV];
int Cu[MaxV];
bool mt[MaxV];

int num_left;
int num_right;

using namespace std;


  vector<vector<bool>> ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
    return adj_matrix;
  }
  /***********************************************************/
  int path(int u,const vector<vector<bool>> &adj_matrix) {
      for(int i=0; i<num_right; i++) {
         if(adj_matrix[u][i]&&mt[i]){
          mt[i]=false;
          if( cv[i] == -1 ) {
            cv[i]=u;
            Cu[u]=i;
            return 1;
          }
          else if (path(cv[i],adj_matrix)) {
            cv[i]=u;
            Cu[u]=i;
            return 1;
          }
        }
      }
      return 0;

  }
  /******************************************************/

  void WriteResponse() {
    for (int i = 0; i < num_left; ++i) {
      if (i > 0)
        cout << " ";
      if (Cu[i] == -1)
        cout << "-1";
      else
        cout << (Cu[i] + 1);
    }
    cout << "\n";
  }

   void FindMatching(const vector<vector<bool>>& adj_matrix) {
    // Replace this code with an algorithm that finds the maximum
    // matching correctly in all cases.
     num_left = adj_matrix.size();
     num_right = adj_matrix[0].size();
     memset(Cu,-1,num_left * sizeof(int) );
     memset(cv,-1,num_right * sizeof(int));

    for(int i=0; i<num_left; i++) {
       memset(mt,true,num_right*sizeof(bool));
       if(!path(i,adj_matrix))
         Cu[i]=-1;
    }

    }

int main() {
  std::ios_base::sync_with_stdio(false);
    vector<vector<bool>> adj_matrix = ReadData();
    FindMatching(adj_matrix);
    WriteResponse();


  return 0;
}
