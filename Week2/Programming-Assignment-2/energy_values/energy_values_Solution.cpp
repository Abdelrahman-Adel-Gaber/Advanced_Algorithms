#include <cmath>
#include <iostream>
#include <vector>
#include <string.h>
#include <iomanip>

using namespace std;
const double EPS = 1e-6;
const int PRECISION = 20;

vector< vector<double> >equation;

 void ReadEquation() {
     int size_;
     double temp;
     cin >> size_;
     if(size_<=0)
        return;
     equation.resize(size_);
     for(int i=0; i<size_; i++)
      for(int j=0; j<=size_; j++){
       cin>>temp;
       equation[i].push_back(temp);
       }
 }

  void swap_lines(int first, int second) {
      swap(equation[first],equation[second]);
  }

void SolveEquation() {
    int size_rows=equation.size();
    int size_columns=size_rows+1;
    if(size_rows==0)
        return;

    for(int i=0; i<size_rows-1 ; i++) {
       int temp =i;
        while(equation[temp][i]==0 && i<size_rows-1 )
            temp++;
        if(temp>size_rows-1)
            continue;
        if(temp != i)
            swap_lines(i,temp);
        vector<double>t1=equation[i];

        for(int j=i+1; j<size_rows ;j++) {
           if(equation[j][i]==0)
            continue;
           double temp1=equation[j][i]/equation[i][i] * -1.0;
           for(int z=i; z<size_columns; z++) {
            equation[j][z] += (equation[i][z] * temp1);
           }
        }

    }
    equation[size_rows-1][size_columns-1]=equation[size_rows-1][size_columns-1]/equation[size_rows-1][size_columns-2];
    equation[size_rows-1][size_columns-2]=1;

    for(int i=size_rows-2; i>=0; i--) {
        for(int j=i; j>=0; j--) {
            int t;
            t=-(equation[j][i+1]) ;
            equation[j][i+1] +=t;
            equation[j][i+2] += (t*equation[i+1][i+2]);
        }
    }
}
void PrintColumn() {
int s= equation.size();
 cout<<"\n";

 for(int i=0; i<s ; i++)
 {
     cout<<fixed<<setprecision(6)<<equation[i][s]/equation[i][i]<<" ";
 }
}
int main() {
    ReadEquation();
    SolveEquation();
    PrintColumn();
    return 0;
}
