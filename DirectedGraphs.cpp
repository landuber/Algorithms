
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <memory>
#include <fstream>
#include "Stack.h"
#include "Graph.h"

using namespace std;


int main(int argc, char** argv)
{
    if(argc == 4)
    {
        ifstream inFile;
        inFile.open(argv[1]);
        if(!inFile)
        {
            cerr << "Unable to open file " << argv[1] << endl;
            exit(1);
        }
        Digraph g(inFile);
        DepthFirstSearch<Digraph> dfs(g, stoi(argv[2]));
        for(int v = 0; v < g.V(); v++)
        {
            if(dfs.is_marked(v))
                cout << v << " ";
        }
        cout << endl;
        auto stack = dfs.path_to(stoi(argv[3]));
        cout << "Path from " << argv[2] << " to " << argv[3] << endl;
        while(stack.size() > 0)
        {
            cout << stack.pop() << endl;
        }

        KosarajuConnectedComponent cc(g);
        cout << cc.get_count() << " strongly connected components" << endl;

        Topological top(g);
        cout << "Here";
        if(top.is_dag())
        {
            cout << "Topologically ordered" << endl;
            for(int v: top.get_order())
            {
                cout << v << endl;
            } 
        }
        cout << flush;
        inFile.close();
    }
    /*
    Stack<string> s;
    Queue<string> q;
    string input;
    getline(cin, input);
    while(!input.empty())
    {
        s.push(input);
        q.enqueue(input);
        getline(cin, input);
    }
    cout << "Stack: " << endl;
    */
    /*
    while(s.size() > 0)
    {
        cout << s.pop() << endl;
    }
    */
    /*
    for(auto it = s.begin(); it != s.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << "Queue: " << endl;
    */
    /*
    while(q.size() > 0)
    {
        cout << q.dequeue() << endl;
    }
    */
    /*
    for(auto it = q.begin(); it != q.end(); ++it)
    {
        cout << *it << endl;
    }
    */
    return 0;
}
