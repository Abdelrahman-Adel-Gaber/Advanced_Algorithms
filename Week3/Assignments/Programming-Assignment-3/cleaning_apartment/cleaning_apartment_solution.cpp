#include <ios>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <set>
using namespace std;


struct ConvertHampathToSat {
    int numVertices;
    int numEdges;
    ConvertHampathToSat(int n,int m) :
        numVertices(n),
        numEdges(m)
    {  }

    void printEquisatisfiableSatFormula(const vector<vector<bool>>& Vertices) {
        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.
       int num_of_variables=1;
       vector<vector<int>>num_clauses(numVertices,vector<int>(numVertices));
        for(int i=0; i<numVertices ;i++) {
            for(int j=0; j<numVertices; j++) {
                num_clauses[i][j]=num_of_variables;
                num_of_variables++;
            }
        }

        /*************************************************/
        /* each vartix should occupy only one place*/
        /*there should not be empty palce*/
        vector<vector<int>>clauses;
        for(int i=0; i<numVertices ;i++) {
            vector<int>temp1(numVertices);
            for(int j=0; j<numVertices; j++)
            { temp1[j]=num_clauses[j][i];

             }
             clauses.push_back(temp1);
        }

        for(int i=0;i<numVertices; i++) {
          for(int j=0; j<numVertices; j++) {
              vector<int>temp(2);
              temp[0]=-1*num_clauses[j][i];
              for(int z=j+1; z< numVertices; z++) {
               temp[1]=-1*num_clauses[z][i];
               clauses.push_back(temp);
              }
          }
        }
      /**********************************************************/
      /*the order should be occupied by only one vertix***********/
       for(int z=0; z<numVertices; z++) {
           for(int i=0; i<numVertices ;i++) {
             vector<int>temp(2);
             temp[0]=-1*num_clauses[z][i];
             for(int j=i+1; j<numVertices; j++) {
                 temp[1]=-1*num_clauses[z][j];
                 clauses.push_back(temp);
             }
            }

       }
      /*********************************************************/
     /*Vertices conneced with edges Edges should be sucissive*/
     for(int i=0; i<numVertices; i++) {
        for(int j=0; j<numVertices; j++) {
          if(!Vertices[i][j]){
              for(int x=0; x<numVertices-1 ;x++) {
                  vector<int>temp(2);
                  temp[0]=-1*num_clauses[i][x];
                  temp[1]=-1*num_clauses[j][x+1];
                  clauses.push_back(temp);
               }
          }

        }

    }

    /*****************print the out put******************/
    cout<<clauses.size()<<" "<< (num_of_variables-1)<<"\n";
     for(int i=0; i<clauses.size() ; i++) {
        for(int j=0; j<clauses[i].size(); j++) {
            cout<<clauses[i][j]<<" ";
        }
        int z=0;
        cout<<z<<"\n";
     }

    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertHampathToSat converter(n, m);
    vector<vector<bool>>Vertices(n,vector<bool>(n,false));
    for (int i = 0; i < m; ++i) {
        int x1,x2;
        cin >> x1 >> x2;
        Vertices[x1-1][x2-1]=true;
        Vertices[x2-1][x1-1]=true;
    }

    converter.printEquisatisfiableSatFormula(Vertices);

    return 0;
}
