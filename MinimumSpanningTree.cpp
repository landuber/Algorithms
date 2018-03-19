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
    if(argc == 2)
    {
        ifstream inFile;
        inFile.open(argv[1]);
        if(!inFile)
        {
            cerr << "Unable to open file " << argv[1] << endl;
            exit(1);
        }
        EdgeWeightedGraph g(inFile);
        LazyPrimMST mst(g);
        for(Edge& e: mst.get_edges())
        {
            int v = e.get_either(), w = e.get_other(v);
            cout << v << "-" << w << " " << e.get_weight() << endl;
        }
        cout << flush;
        inFile.close();
    }
    return 0;
}
