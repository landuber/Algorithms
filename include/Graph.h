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
        auto adj_list(int v)
        {
            return adj[v];
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
        auto adj_list(int v)
        {
            return adj[v];
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


class DepthFirstSearch
{
    public:
        DepthFirstSearch(Graph & g, int s): s{s}
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
        void dfs(Graph & g, int v)
        {
            marked[v] = true;
            count++;
            auto adj_list = g.adj_list(v);
            auto begin = adj_list->begin();
            auto end = adj_list->end();
            for(auto& it = begin; it != end; ++it)
            {
                int w = *it;
                if(!marked[w])
                {
                    dfs(g, w);
                    edgeTo[w] = v;
                }
            }
        }
};

class BreadthFirstSearch
{
    public:
        BreadthFirstSearch(Graph & g, int s): s{s}
        {
            marked = new bool[g.V()];
            edgeTo = new int[g.V()];
            marked[s] = true;
            queue.enqueue(s);
            count++;
            while(queue.size() > 0)
            {
                int v = queue.dequeue();
                auto adj_list = g.adj_list(v);
                auto begin = adj_list->begin();
                auto end = adj_list->end();
                for(auto& it = begin; it != end; ++it)
                {
                    int m = *it;
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

#endif
