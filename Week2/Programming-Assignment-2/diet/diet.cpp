#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;


const double EPS = 1e-6;
const int PRECISION = 20;

typedef std::vector<double> Column;
typedef std::vector<double> Row;
typedef std::vector<Row> Matrix;


struct Equation {
    Equation(const Matrix &a, const Column &b):
        a(a),
        b(b)
    {}

    Matrix a;
    Column b;
};

struct Position {
    Position(int column, int row):
        column(column),
        row(row)
    {}

    int column;
    int row;
};
/************************************************************************************************************/
Equation ReadEquation() {
    int size;
    std::cin >> size;
    Matrix a(size, std::vector <double> (size, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column)
            std::cin >> a[row][column];
        std::cin >> b[row];
    }
    return Equation(a, b);
}

/********************************************************************************************************/
Matrix  Transpose(const Matrix &A) {
  Matrix m(A.size());
      for(int i=0; i<A.size(); i++) {
        m[i].resize(A[0].size());
       for(int j=0;j<A[i].size(); j++)
         m[i][j]=A[j][i];
       }

return m;}
/*********************************************************************************************************/
Position SelectPivotElement(
  int column_turn,
  const Matrix &a,
  std::vector <bool> &used_rows,
  std::vector <bool> &used_columns) {
    // This algorithm selects the first free element.
    // You'll need to improve it to pass the problem.
    Position pivot_element(0, 0);
    while (used_rows[pivot_element.row]||a[pivot_element.row][column_turn]==0.0)
       {
        ++pivot_element.row;
        if(pivot_element.row==used_rows.size())
          break;
        }
    return pivot_element;
}

/*************************************************************************************************/
void SwapLines(Matrix &a, Column &b, std::vector <bool> &used_rows, Position &pivot_element) {
    std::swap(a[pivot_element.column], a[pivot_element.row]);
    std::swap(b[pivot_element.column], b[pivot_element.row]);
    std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
    pivot_element.row = pivot_element.column;
}


/******************************************************************************************/

void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element) {
    // Write your code here
    int size_=a.size();
    double temp =a[pivot_element.row][pivot_element.column];
    for(int i=pivot_element.column; i<size_; i++)
     a[pivot_element.row][i] /= temp;

     b[pivot_element.row] /=temp;
    for(int i=pivot_element.row+1; i<size_; i++ ) {
       temp = -a[i][pivot_element.column];
       if(temp == 0)
        continue;
       for(int j=pivot_element.column; j<size_; j++) {
           double temp2= temp * a[pivot_element.row][j];
           a[i][j] += temp2;
       }
       b[i] += b[pivot_element.row]*temp;

    }
}

void MarkPivotElementUsed(const Position &pivot_element, std::vector <bool> &used_rows, std::vector <bool> &used_columns) {
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
}

/*********************************************************/
pair<int , Column > SolveEquation(Equation equation) {
    Matrix &a = equation.a;
    Column &b = equation.b;
    int size = a.size();
    int y=0;
    std::vector <bool> used_columns(size, false);
    std::vector <bool> used_rows(size, false);
    for (int step = 0; step < size; ++step) {
        Position pivot_element = SelectPivotElement(step,a, used_rows, used_columns);
         if(pivot_element.row >= size) {
          y=-1;
          break;
           }
        pivot_element.column=step;
        SwapLines(a, b, used_rows, pivot_element);
        ProcessPivotElement(a, b, pivot_element);
        MarkPivotElementUsed(pivot_element, used_rows, used_columns);


     }

     if(y!=0)
     return make_pair(y,b);

    for(int i = size-2; i >=0  ; i--)
    {

     double temp=b[i+1];

     if(temp!=0.0)
     for(int j=i; j>=0 ; j--)
       b[j]-= temp*a[j][i+1];

    }

    return make_pair(y,b);
}
/***********************************************************************************************************/
bool check_solution(const Matrix &a, const vector<double>& solution, const vector<double>&b) {
 for(int i=0; i<a.size(); i++) {
   double temp=0;
   for(int j=0 ;j<a[i].size(); j++)
    temp += solution[j]*a[i][j];

   if(temp<=b[i]){
     //satisfied the constraint
   }
   else
   return false;

 }
return true;
}

/**********************************************************************************************************/
pair<int, vector<double>> solve_diet_problem(
    int n,
    int m,
    Matrix A,
    vector<double> b,
    vector<double> c) {

  // Write your code here
  if (m==n) {
      Equation e(Transpose(A),c);
      pair <int , Column> solution =SolveEquation(e);
      if(solution.first == -1)
        return {-1, vector<double>(m, 0)};
      else if (solution.first == 1)
        return {1, vector<double>(m, 0)};
      else {
        e.a=A;
        e.b=b;
        vector<double> t=solution.second;
        solution = SolveEquation(e);
           if(solution.first == -1)
           return {-1, vector<double>(m, 0)};
           else if (solution.first == 1)
           return {1, vector<double>(m, 0)};
           else {
             for(int i=0; i<solution.second.size(); i++ )
             { if(solution.second[i]<0)
               solution.second[i]=0.0;
               if(t[i]<0)
                 solution.second[i]=-0.0;
             }
             if(check_solution(A,solution.second,b))
              return  {0 , solution.second};
             else
              return  {-1 , vector<double>(1,0)};
           }

      }

   }
   else if(n>m)
   {
     
   }
   else 
   {

   }
   

  return {0, vector<double>(m, 0)};
}


int main(){
  int n, m;
  cin >> n >> m;
  Matrix A(n, vector<double>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }
  vector<double> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<double> c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  pair<int, vector<double>> ans = solve_diet_problem(n, m, A, b, c);

  switch (ans.first) {
    case -1:
      printf("No solution\n");
      break;
    case 0:
      printf("Bounded solution\n");
      for (int i = 0; i < m; i++) {
        printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;
  }
  return 0;
}
