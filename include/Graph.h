#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream> 
#include "Stack.h"

class Graph
{
    public:
        Graph(int v): v{v}, e{0}
        {
            init();
        }

        Graph(std::istream& s)
        {
            int edges;
            s >> v;
            s >> edges;
            init();
            for(int i = 0; i < edges; i++)
            {
                int f;
                int t;
                s >> f;
                s >> t;
                add_edge(f, t);
            }
        }
        Graph(const Graph & other):Graph(other.v)
        {
            std::cout << "Graph cpy cnstr" << std::endl;
            for(int m = 0; m < this->v; m++)
            {
                for(auto& w: other.adj_list(m))
                {
                    this->add_edge(m, w);
                }
            }
        }
        /*
        Graph(Graph&& other)
        {
            std::cout << "Graph move cnstr" << std::endl;
        } 
        Graph& operator=(const Graph & other)
        {
            std::cout << "Graph cpy assigmt" << std::endl;
        }
        Graph& operator=(Graph&& other)
        {
            std::cout << "Graph move assigmt" << std::endl;
        }
        */
        ~Graph()
        {
            for(int i=0; i < v; i++)
                delete adj[i];
            delete [] adj;
        }

        int V() const { return v; }
        int E() const { return e; }
        void add_edge(int v, int w)
        {
            adj[v]->add(w);
            adj[w]->add(v);
            ++e;
        }

        Bag<int>& adj_list(int v) const
        {
            return *(adj[v]);
        }
    private:
        int v = 0;
        int e = 0;
        Bag<int>** adj;
        void init()
        {
            adj = new Bag<int>*[v];
            for(int i=0; i < v; i++)
            {
                adj[i] = new Bag<int>();
            }
        }
};

class Digraph
{
    public:
        Digraph(int v): v{v}, e{0}
        {
            init();
        }

        Digraph(std::istream& s)
        {
            int edges;
            s >> v;
            s >> edges;
            init();
            for(int i = 0; i < edges; i++)
            {
                int f;
                int t;
                s >> f;
                s >> t;
                add_edge(f, t);
            }
        }
        Digraph(const Digraph & other):Digraph(other.v)
        {
            std::cout << "Digraph cpy cnstr" << std::endl;
            for(int m = 0; m < this->v; m++)
            {
                for(auto& w: other.adj_list(m))
                {
                    this->add_edge(m, w);
                }
            }
        }
        ~Digraph()
        {
            for(int i=0; i < v; i++)
                delete adj[i];
            delete [] adj;
        }

        int V() const { return v; }
        int E() const { return e; }
        void add_edge(int v, int w)
        {
            adj[v]->add(w);
            ++e;
        }
        Bag<int>& adj_list(int v) const
        {
            return *(adj[v]);
        }
        
        Digraph reverse()
        {
            Digraph g(this->V());
            for(int m = 0; m < v; m++)
            {
                for(auto& w: this->adj_list(m))
                {
                    g.add_edge(m, w);
                }
            }
            return g;
        }
    private:
        int v = 0;
        int e = 0;
        Bag<int>** adj;
        void init()
        {
            adj = new Bag<int>*[v];
            for(int i=0; i < v; i++)
            {
                adj[i] = new Bag<int>();
            }
        }
};

template <typename G>
class DepthFirstSearch
{
    public:
        DepthFirstSearch(G & g, int s): s{s}
        {
            marked = new bool[g.V()];
            edgeTo = new int[g.V()];
            dfs(g, s);
        }

        ~DepthFirstSearch()
        {
            delete [] marked;
            delete [] edgeTo;
        }

        bool is_marked(int w)
        {
            return marked[w];
        }

        int get_count()
        {
            return count;
        }

        Stack<int> path_to(int v)
        {
            Stack<int> path;
            if(!marked[v]) return path;
            for(int x = v; x != s; x = edgeTo[x])
            {
                path.push(x);
            } 
            path.push(s);
            return path;
        }



    private:
        int s;
        bool* marked;
        int* edgeTo;
        int count = 0;
        void dfs(G & g, int v)
        {
            marked[v] = true;
            count++;
            for(auto& w: g.adj_list(v))
            {
                if(!marked[w])
                {
                    dfs(g, w);
                    edgeTo[w] = v;
                }
            }
        }
};

template <typename G>
class BreadthFirstSearch
{
    public:
        BreadthFirstSearch(G & g, int s): s{s}
        {
            marked = new bool[g.V()];
            edgeTo = new int[g.V()];
            marked[s] = true;
            queue.enqueue(s);
            count++;
            while(queue.size() > 0)
            {
                int v = queue.dequeue();
                for(auto& m: g.adj_list(v))
                {
                    if(!marked[m])
                    {
                        marked[m] = true;
                        edgeTo[m] = v;
                        queue.enqueue(m);
                        count++;
                    }
                }
            }
        }

        ~BreadthFirstSearch()
        {
            delete [] marked;
            delete [] edgeTo;
        }

        bool is_marked(int w)
        {
            return marked[w];
        }

        int get_count()
        {
            return count;
        }

        Stack<int> path_to(int v)
        {
            Stack<int> path;
            if(!marked[v]) return path;
            for(int x = v; x != s; x = edgeTo[x])
            {
                path.push(x);
            } 
            path.push(s);
            return path;
        }



    private:
        int s;
        bool* marked;
        int* edgeTo;
        Queue<int> queue;
        int count = 0;
};

class ConnectedComponent
{
    public:
        ConnectedComponent(Graph & g)
        {
            id = new int[g.V()];
            marked = new bool[g.V()];
            for(int v = 0; v < g.V(); v++)
            {
                if(!marked[v])
                {
                    dfs(g, v);
                    ++count;
                }
            }
        }
        ~ConnectedComponent()
        {
            delete [] marked;
        }
        bool is_connected(int v, int w)
        {
            return id[v] == id[w];
        }
        int get_count()
        {
            return count;
        }
        int get_id(int v)
        {
            return id[v];
        }
    private:
        bool *marked;
        int *id;
        int count = 0;
        void dfs(Graph & g, int v)
        {
            marked[v] = true;
            id[v] = count;
            for(auto& w: g.adj_list(v))
            {
                if(!marked[w])
                    dfs(g, w);
            }
        }
};

class DirectedCycle
{

};
#endif
