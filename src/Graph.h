#ifndef GRAPHALGORITHMS_GRAPH_H
#define GRAPHALGORITHMS_GRAPH_H
#include <vector>
#include <unordered_map>
#include "GraphNode.h"
#include "GraphEdge.h"



using namespace std;
//Un-implemented yet AdjacencyList Representation. Need to build conversion to the underlying Edge representation.
typedef unordered_map<GraphNode* ,vector<GraphEdge*>> AdjacencyList;
//Implemented Conversion from AdjacencyMatrix required representation to the underlying Edge Representation.

class Graph {
    vector<GraphEdge*> edges;
    unordered_map<int,GraphNode*> vertices;
public:

    virtual ~Graph();
    Graph();
    Graph(const vector<int>& vertcie_list, const vector<tuple<int,int,int>>& edge_list);
    const unordered_map<int,GraphNode *> &getVertices() const;
    //vector<GraphEdge>* primAlgorithm(GraphNode* node);
    vector<vector<int>> dijkstraAlgorithm(GraphNode* node);
    GraphNode* addNode(int index);
    void addEdge(tuple<int, int, int> p_edge);
    void removeEdge(tuple<int,int> p_edge);
    void addEdges(const vector<tuple<int,int,int>>& edge_list);
    void removeEdges(const vector<tuple<int,int>>& edge_list);
    void addNodes(const vector<int>& vertcie_list);
    void removeNodes(const vector<int>& node_list);
private:
    GraphEdge addEdge(GraphNode* node1, GraphNode* node2, int weight);
    void createNodes(const vector<int>& vertcie_list);
    void createEdges(const vector<tuple<int,int,int>>& edge_list);
    void printParents(int index,int sourceIndex,int *parentVertices);
    void removeNode(int index);
    // To compare two edges
    class myComparator
    {
    public:
        int operator() (GraphEdge& edge1, GraphEdge& edge2);

    };
};
#endif //GRAPHALGORITHMS_GRAPH_H
