#include <ios>
#include <iostream>
#include <vector>

using namespace std;


struct ConvertGSMNetworkProblemToSat {
    int numVertices;

    ConvertGSMNetworkProblemToSat(int n) :
        numVertices(n)
    {  }

    void printEquisatisfiableSatFormula(const vector<vector<int>>&vertices) {
        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.
     vector<vector<int>>clauses_variables(numVertices);
     int num_variables=1;
     vector<vector<int>> clauses;
     for(int i=0;i<numVertices;i++) {
         clauses_variables[i].push_back(num_variables);
         num_variables++;
         clauses_variables[i].push_back(num_variables);
          num_variables++;
         clauses_variables[i].push_back(num_variables);
         num_variables++;
     }
     for(int i=0;i<vertices.size();i++) {
        vector<int> temp(2);
         temp[0]=(-1*clauses_variables[i][0]);
         temp[1]=(-1*clauses_variables[i][1]);
         //temp[2]=(clauses_variables[i][2]);
         clauses.push_back(temp);

         temp[0]=(-1*clauses_variables[i][0]);
         temp[1]=(-1*clauses_variables[i][2]);
         //temp[2]=(-1*clauses_variables[i][2]);
         clauses.push_back(temp);

         temp[0]=(-1*clauses_variables[i][2]);
         temp[1]=(-1*clauses_variables[i][1]);
         //temp[2]=(-1*clauses_variables[i][2]);
         clauses.push_back(temp);
         temp.resize(3);
         temp[0]=clauses_variables[i][0];
         temp[1]=clauses_variables[i][1];
         temp[2]=clauses_variables[i][2];
         clauses.push_back(temp);
         
         if(vertices[i].size()==0)
          continue;
         vector<int>temp1(2);
         temp1[0]=(-1*clauses_variables[i][0]);
         for(int j=0; j<vertices[i].size(); j++) {
          temp1[1]=(-1*clauses_variables[vertices[i][j]][0]);
          clauses.push_back(temp1);

         }

         vector<int>temp2(2);
         temp2[0]=(-1*clauses_variables[i][1]);
         for(int j=0; j<vertices[i].size(); j++) {
          temp2[1]=(-1*clauses_variables[vertices[i][j]][1]);
          clauses.push_back(temp2);
         }

         vector<int>temp3(2);
         temp3[0]=(-1*clauses_variables[i][2]);
         for(int j=0; j<vertices[i].size(); j++) {
          temp3[1]=(-1*clauses_variables[vertices[i][j]][2]);
          clauses.push_back(temp3);
          }

          }
     cout<<clauses.size()<<" "<< (num_variables-1)<<"\n";
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
    ConvertGSMNetworkProblemToSat converter(n);
    vector<vector<int>>vertices(n);
    int x1,x2;
    for (int i = 0; i < m; ++i) {
        cin >>x1 >> x2;
        vertices[x1-1].push_back(x2-1);
        }

    converter.printEquisatisfiableSatFormula(vertices);

    return 0;
}
