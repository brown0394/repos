#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Edge
{
    friend class Graph;
    int src, dst;
};
// list<int>  list<string>
class Graph
{
    int size;// #of node
    std::vector<std::list<int>> adjlist; //adjacency list

public:
    Graph(int n, std::vector<Edge> &edges) : size(n)
    {
        for (Edge &e: edges)
        {
            adjlist[e.src].push_back(e.dst);
            adjlist[e.dst].push_back(e.src);
        }
    }
    std::ostream& print(std::ostream &out = std::cout)
    {
        for (int i = 0; i < size; ++i)
        {
            auto list = adjlist[i];
            out << i << ": ";
            for(auto p = list.begin(); p != list.end(); ++p)
            {
                out << *p << "->";
            }
            out << "//" << std::endl;
        }
        return out;
    }
};

int main()
{
    int numV, numE, start;
    std::cin >> numV >> numE;
    std::vector<Edge> edges(numV, numE);
    int one, two;
    for(int i = 0; i < numE; ++i)
    {
        std::cin >> one >> two;
        edges[one].push_back(two); 
    }
    Graph g(n, edges);
    g.print();
}