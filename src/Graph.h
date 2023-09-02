#ifndef GRAPHALGORITHMS_GRAPH_H
#define GRAPHALGORITHMS_GRAPH_H
#include <vector>
#include <unordered_map>
#include "GraphNode.h"
#include "GraphEdge.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/global_constants.hpp>

using godot::TypedArray;
using godot::Vector3i;
using godot::Vector2i;

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
    Graph(const TypedArray<int>& vertcie_list, const TypedArray<Vector3i>& edge_list);
    const unordered_map<int,GraphNode *> &getVertices() const;
    //vector<GraphEdge>* primAlgorithm(GraphNode* node);
    vector<vector<int>> dijkstraAlgorithm(GraphNode* node);
    GraphNode* addNode(int index);
    void addEdge(Vector3i p_edge);
    void removeEdge(Vector2i p_edge);
    void addEdges(const TypedArray<Vector3i>& edge_list);
    void removeEdges(const TypedArray<Vector2i>& edge_list);
    void addNodes(const TypedArray<int>& vertcie_list);
    void removeNodes(const TypedArray<int>& node_list);
private:
    GraphEdge addEdge(GraphNode* node1, GraphNode* node2, int weight);
    void createNodes(const TypedArray<int>& vertcie_list);
    void createEdges(const TypedArray<Vector3i>& edge_list);
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
