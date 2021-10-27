#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using std::vector;
using std::cin;
using std::cout;


bool sort_(const vector<int>&A, const vector<int>B) {
return A.size()<B.size();}


vector<int> ReadData() {
     int num_left, num_right;
     cin>>num_left>>num_right;
     vector<int> flight_options(num_left,0);
     vector<vector<int>> crew(num_right);
     int temp;
     for(int i=0; i<num_left; i++) {
         for(int j=0;j<num_right; j++)
         {
             cin>>temp;
             if(temp){
             crew[j].push_back(i);
             flight_options[i]++;
            }
         }
     }

     for(int i=0; i<num_right; i++)
        crew[i].push_back(i);

     sort(crew.begin(),crew.end(),sort_);
     vector<bool>taken(num_left,false);
     vector<int>matching(num_left,-1);


     for(int i=0,m=0; i<num_right&& m<num_left; i++) {
        if(crew[i].size()>1) {
          int flight_with_min_option=crew[i][0];
          for(int j=0; j<crew[i].size()-2; j++) {
              while(taken[flight_with_min_option] && (j<crew[i].size()-2)) {
                  j++;
                  flight_with_min_option=crew[i][j];
              }
              if(flight_options[flight_with_min_option]==1)
                break;
              if(!taken[crew[i][j+1]] && flight_options[flight_with_min_option]>flight_options[crew[i][j+1]]){
                flight_options[flight_with_min_option]--;
                flight_with_min_option=crew[i][j+1];
              }
              else if(!taken[crew[i][j+1]]) {
                 flight_options[crew[i][j+1]]--;
              }
         }

        m++;
        if(!taken[flight_with_min_option])
        matching[flight_with_min_option]=crew[i][crew[i].size()-1];
        taken[flight_with_min_option]=true;
      }
     }

    return matching;
  }

void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i] + 1);
    }
    cout << "\n";
  }


void Solve() {
    vector<int> matching = ReadData();
    WriteResponse(matching);
  }



int main() {
  std::ios_base::sync_with_stdio(false);
  Solve();
  return 0;
}
