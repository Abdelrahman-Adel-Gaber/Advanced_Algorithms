#include <iostream>
#include <vector>

struct Vertex {
    int weight;
    std::vector <int> children;
};
typedef std::vector<Vertex> Graph;
typedef std::vector<int> Sum;

Graph ReadTree() {
    std::ios::sync_with_stdio(false);

    int vertices_count;
    std::cin >> vertices_count;

    Graph tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i)
        std::cin >> tree[i].weight;

    for (int i = 1; i < vertices_count; ++i) {
        int from, to;
        std::cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}

int dfs(const Graph &tree, int vertex,Sum &s, int parent) {
    // This is a template function for processing a tree using depth-first search.
    // Write your code here.
    // You may need to add more parameters to this function for child processing.

    if(s[vertex]==-1){
    if(tree[vertex].children.size()==1 && tree[vertex].children[0]==parent ) {
        s[vertex]=tree[vertex].weight;
    }
    else
    {
        int m1=tree[vertex].weight;
        for(auto u : tree[vertex].children)
        {
            if(u==parent)
              continue;

           for(auto w: tree[u].children)
             if(w!=vertex)
              {m1+=dfs(tree,w,s,u);
                }
        }
        int m2=0;
         for(auto u:tree[vertex].children)
        {
            if(u!=parent)
             {
              m2+=dfs(tree,u,s,vertex);
             }
        }
        s[vertex]=m1>m2?m1:m2;
    }
    }
return s[vertex]; }

int MaxWeightIndependentTreeSubset(const Graph &tree) {
    size_t size = tree.size();
    if (size == 0)
        return 0;
    // You must decide what to return.
    Sum s(tree.size(),-1);
    int result=dfs(tree, 0,s,-1);

    return result;
}

int main() {
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.

    // Here begins the solution
    Graph tree = ReadTree();
    int weight = MaxWeightIndependentTreeSubset(tree);
    std::cout << weight << std::endl;
    return 0;
}
