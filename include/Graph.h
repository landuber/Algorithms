#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream> 
#include <limits>
#include "Stack.h"
#include "PriorityQueue.h"
#include "UF.h"

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

        Digraph(Digraph && other): v(other.v), e(other.e), adj(other.adj)
        {
            other.v = 0;
            other.e = 0;
            other.adj = nullptr;
        }

        Digraph & operator=(Digraph && other)
        {
            v = other.v;
            e = other.e;
            adj = other.adj;
            other.v = 0;
            other.e = 0;
            other.adj = nullptr;
            return *this;
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
        
        Digraph reverse() const
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
        DepthFirstSearch(const G & g, int s): s{s}
        {
            marked = new bool[g.V()]();
            edgeTo = new int[g.V()]();
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
        void dfs(const G & g, int v)
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
        BreadthFirstSearch(const G & g, int s): s{s}
        {
            marked = new bool[g.V()]();
            edgeTo = new int[g.V()]();
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
        ConnectedComponent(const Graph & g)
        {
            id = new int[g.V()]();
            marked = new bool[g.V()]();
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
        void dfs(const Graph & g, int v)
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
    public:
        DirectedCycle(const Digraph & g)
        {
            marked = new bool[g.V()]();
            edgeTo = new int[g.V()]();
            onStack = new bool[g.V()]();
            for(int i = 0; i < g.V(); i++)
            {
                if(!marked[i])
                {
                    dfs(g, i);
                }
            }
        }
        ~DirectedCycle()
        {
            delete [] marked;
            delete [] edgeTo;
            delete [] onStack;
        }
        bool has_cycle()
        {
            return cycle.size() != 0;
        }
        Stack<int> get_cycle()
        {
            return cycle;
        }
    private:
        bool* marked;
        int* edgeTo;
        bool* onStack;
        Stack<int> cycle;
        void dfs(const Digraph & g, int v)
        {
            marked[v] = true;
            onStack[v] = true;
            for(auto& w: g.adj_list(v))
            {
                if(this->has_cycle()) return;
                else if(!marked[w])
                {
                    edgeTo[w] = v;
                    dfs(g, w);
                }
                else if(onStack[w])
                {
                    for(int m = v; m != w; m = edgeTo[m])
                    {
                        std::cout << "Navigating back" << std::endl;
                        cycle.push(m);
                    }
                    cycle.push(w);
                    cycle.push(v);
                }
            }
            onStack[v] = false;

        }
};

class DepthFirstOrder
{
    public:
        DepthFirstOrder(const Digraph & g)
        {
            marked = new bool[g.V()]();
            for(int v = 0; v < g.V(); v++)
                if(!marked[v]) dfs(g, v);

        }

        ~DepthFirstOrder()
        {
            delete [] marked;
        }
        
        Queue<int> get_preorder()
        {
            return pre;
        }

        Queue<int> get_postorder()
        {
            return pre;
        }

        Stack<int> get_reversepost()
        {
            return reversePost;
        }
    private:
        bool* marked;
        Queue<int> pre;
        Queue<int> post;
        Stack<int> reversePost;
        void dfs(const Digraph & g, int v)
        {
            pre.enqueue(v);
            marked[v] = true;
            for(auto& w: g.adj_list(v))
            {
                if(!marked[w])
                {
                    dfs(g, w);
                }
            }
            post.enqueue(v);
            reversePost.push(v);
        }
};

class Topological
{
    public:
        Topological(const Digraph & g)
        {
            std::cout << "In Topological" << std::endl;
            DirectedCycle cyclefinder(g);
            std::cout << "In Topological" << std::endl;
            if(!cyclefinder.has_cycle())
            {
                DepthFirstOrder dfs(g);
                order = dfs.get_reversepost();
            }
        }
        ~Topological()
        {}
        bool is_dag()
        {
            return order.size() != 0;
        }
        Stack<int> get_order()
        {
            return order;
        }
    private:
        Stack<int> order;
        
};

class KosarajuConnectedComponent
{
    public:
        KosarajuConnectedComponent(const Digraph & g)
        {
            id = new int[g.V()]();
            marked = new bool[g.V()]();
            DepthFirstOrder order(g.reverse());
            for(auto& w : order.get_reversepost())
            {
                if(!marked[w])
                {
                    dfs(g, w);
                    ++count;
                }
            }
        }
        ~KosarajuConnectedComponent()
        {
            delete [] marked;
        }
        bool is_strongly_connected(int v, int w)
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
        void dfs(const Digraph & g, int v)
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

class Edge
{
    public:
        Edge(int v, int w, double weight): v(v), w(w), weight(weight)
        {
        }
        double get_weight() const
        {
            return weight;
        }
        int get_either() const
        {
            return v;
        }
        int get_other(int vertex) const
        {
            if(vertex == v) return w;
            else if(vertex == w) return v;
            else 
            {
                throw "Inconsistent edge";
            }
        }
        bool operator<(const Edge& other) const
        {
            return this->weight < other.weight;
        }
    private:
        int v, w;
        double weight;
};

class EdgeWeightedGraph
{
    public:
        EdgeWeightedGraph(int v): v{v}, e{0}
        {
            init();
        }

        EdgeWeightedGraph(std::istream& s)
        {
            int edges;
            s >> v;
            s >> edges;
            init();
            for(int i = 0; i < edges; i++)
            {
                int f;
                int t;
                double  w;
                s >> f;
                s >> t;
                s >> w;
                Edge edge(f, t, w);
                add_edge(edge);
            }
        }
        EdgeWeightedGraph(const EdgeWeightedGraph & other):EdgeWeightedGraph(other.v)
        {
            for(int m = 0; m < this->v; m++)
            {
                for(auto& w: other.adj_list(m))
                {
                    this->add_edge(w);
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
        ~EdgeWeightedGraph()
        {
            for(int i=0; i < v; i++)
                delete adj[i];
            delete [] adj;
        }

        int V() const { return v; }

        int E() const { return e; }

        void add_edge(const Edge& edge)
        {
            int v = edge.get_either();
            int w = edge.get_other(v);
            adj[v]->add(edge);
            adj[w]->add(edge);
            ++e;
        }

        Bag<Edge>& adj_list(int v) const
        {
            return *(adj[v]);
        }

        Bag<Edge> get_edges() const
        {
            Bag<Edge> b;
            for(int i = 0; i < v; i++)
            {
                for(Edge& edge : *(adj[i]))
                {
                    if(edge.get_other(i) > i) 
                        b.add(edge);
                }
            }

            return b;
        }

    private:
        int v = 0;
        int e = 0;
        Bag<Edge>** adj;
        void init()
        {
            adj = new Bag<Edge>*[v];
            for(int i=0; i < v; i++)
            {
                adj[i] = new Bag<Edge>();
            }
        }

};

class LazyPrimMST
{
    public:
        LazyPrimMST(const EdgeWeightedGraph & g)
        {
            marked = new bool[g.V()]();
            pq = new MinPQ<Edge>(g.E());
            visit(g, 0);
            while(!pq->is_empty())
            {
                Edge e = pq->delMin();
                int v = e.get_either();
                int w = e.get_other(v);
                if(marked[v] && marked[w]) continue;
                mst.enqueue(e);
                if(!marked[v]) 
                    visit(g, v);
                if(!marked[w])
                    visit(g, w);
            }

        }
        ~LazyPrimMST()
        {
            delete [] marked;
            delete pq;
        }

        const Queue<Edge>& get_edges()
        {
            return mst;
        }
    private:
        bool* marked;
        Queue<Edge> mst;
        MinPQ<Edge>* pq;

        void visit(const EdgeWeightedGraph & g, int v)
        {
            marked[v] = true;
            for(Edge& e : g.adj_list(v))
            {
                if(!marked[e.get_other(v)]) 
                    pq->insert(e);
            }

        }

};

class EagerPrimMST
{
    public:
        EagerPrimMST(const EdgeWeightedGraph & g)
        {
            v = g.V();
            edgeTo = new Edge*[v]();
            distTo = new double[v]();
            marked = new bool[v]();
            for(int i = 0; i < v; i++)
            {
                distTo[i] = std::numeric_limits<double>::max();
            }
            pq = new IndexMinPQ<double>(v);
            distTo[0] = 0.0;
            pq->insert(0, 0.0);
            while(!pq->is_empty())
            {
                visit(g, pq->del_min());
            }
        }
        ~EagerPrimMST()
        {
            delete [] edgeTo;
            delete [] distTo;
            delete pq;
        }

        Bag<Edge> get_edges()
        {
            Bag<Edge> b;
            for(int i = 1; i < v; i++)
            {
                b.add(*edgeTo[i]);
            }
            return b;
        }
    private:
        Edge** edgeTo = nullptr;
        double* distTo = nullptr;
        bool* marked = nullptr;
        IndexMinPQ<double>* pq;
        int v = 0;
        void visit(const EdgeWeightedGraph & g, int v)
        {
            marked[v] = true;
            for(auto& edge: g.adj_list(v))
            {
                int w = edge.get_other(v);
                if(marked[w]) continue;
                if(edge.get_weight() < distTo[w])
                {
                    delete edgeTo[w];
                    edgeTo[w] = new Edge(edge);
                    distTo[w] = edge.get_weight();
                    if(!pq->contains(w))
                    {
                        pq->insert(w, distTo[w]);
                    }
                    else
                    {
                        pq->change_key(w, distTo[w]);
                    }
                }
            }
        }
};

class KruskalMST
{
    public:
        KruskalMST(const EdgeWeightedGraph & g)
        {
            MinPQ<Edge> pq(g.E());
            WeightedQuickJoinUF uf(g.V());
            for(auto& edge : g.get_edges())
            {
                pq.insert(edge);
            }
            while(!pq.is_empty() && mst.size() < g.V() - 1)
            {
                Edge e = pq.delMin();
                int v = e.get_either(), w = e.get_other(v);
                if(!uf.is_connected(v, w))
                {
                    mst.enqueue(e);
                    uf.join(v, w);
                }
                
            }
        }

        Queue<Edge> get_edges()
        {
            return mst;
        }
    private:
        Queue<Edge> mst;
};
#endif
