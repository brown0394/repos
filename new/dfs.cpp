#include <iostream>
#include <vector>
#include <list>

class Edge
{
    friend class Graph;
    int src, dst;
public:
    Edge(int s=0, int d=0):src(s), dst(d){}
};
// list<int>  list<string>
class Graph
{
    int size;// #of node
    std::vector<std::list<int>> adjlist; //adjacency list
    std::vector<bool> visitlist;

public:
    Graph(int n, std::vector<Edge> &edges) : size(n)
    {
        adjlist.resize(n);
        visitlist.resize(n);
        visitlist.assign(n, false);
        for (Edge &e: edges)
        {
            adjlist[e.src].push_back(e.dst);
            adjlist[e.dst].push_back(e.src);
        }
    }
    std::ostream& Print(int start, std::ostream &out = std::cout)
    {
        if(!visitlist[start])
        {
            out << start << std::endl;
            visitlist[start] = true;
        }
        auto list = adjlist[start];
        for(auto p = list.begin(); p != list.end(); ++p)
        {
            if(!visitlist[*p])
            {
                Print(*p);
            }
        }
        return out;
    }
};

int main()
{
    int numV, numE, start;
    std::cin >> numV >> numE;
    std::vector<Edge> edges;
    int one, two;
    for(int i = 0; i < numE; ++i)
    {
        std::cin >> one >> two;
        Edge temp(one, two);
        edges.push_back(temp);
    }
    Graph g(numV, edges);
    std::cin >> start;
    g.Print(start);
}
