#include <queue>
#include <algorithm>
#include <iostream>
#include "Graph.h"
//defined a random high value integer as INF value.
#define  INF 99999
//Graph Object Constructor supporting Adjacency matrix representation interface.
Graph::Graph(int numberOfVertices, AdjacencyMatrix adjacencyMatrix) {
    this->numberOfVertices = numberOfVertices;
    this->adjacencyMatrix = adjacencyMatrix;
    //These methods is for Accommodating the adjacency matrix representation inserted to our Edge underlying representation.
    createNodes();
    createEdges();
}
//Insert GraphNode Object to the Graph Object.
GraphNode *Graph::addNode(int index) {
    auto *node = new GraphNode(index);
    //add this node to the vertices arrayList.
    vertices.push_back(node);
    //Set the edges arrayList for this node.
    auto *t_edges = new vector<GraphEdge *>;
    node->setEdges(*t_edges);
    return node;
}
//Insert GraphEdge Object to the Graph Object.
GraphEdge Graph::addEdge(GraphNode *node1, GraphNode *node2, int weight) {
    auto *edge = new GraphEdge(weight, node1, node2);
    //add this edge to the edges arrayList.
    edges.push_back(edge);
    //add this edge to the source node's edges arrayList.
    node1->getEdges().push_back(edge);
    return *edge;
}
//Prim's Algorithm Method to find Minimum Spanning Tree.
vector<GraphEdge> *Graph::primAlgorithm(GraphNode *node) {
    auto *distance = new int[numberOfVertices];
    priority_queue<GraphEdge, vector<GraphEdge>, myComparator> priorityQueue;
    auto *MST = new vector<GraphEdge>;
    distance[0] = 0;
    for (int i = 1; i < numberOfVertices; ++i) {
        distance[i] = INF;
    }
    for (auto &&edge :node->getEdges())
        priorityQueue.push(*edge);
    while (!priorityQueue.empty()) {
        GraphEdge minEdge = priorityQueue.top();
        priorityQueue.pop();
        if (minEdge.getWeight() < distance[minEdge.getNode2()->getNodeIndex()]) {
            distance[minEdge.getNode2()->getNodeIndex()] = minEdge.getWeight();
            for (auto &&edge: minEdge.getNode2()->getEdges()) {
                if (!(minEdge == edge)) {
                    priorityQueue.push(*edge);
                }
            }
            MST->push_back(minEdge);
        }


    }
    return MST;
}
//Dijkstra Algorithm Method to find the shortest path.
vector<vector<int>> Graph::dijkstraAlgorithm(GraphNode *node) {
    int* distanceFromSource = new int[numberOfVertices];
    auto *parentVertices = new int[numberOfVertices];
    priority_queue<GraphEdge, vector<GraphEdge>, myComparator> priorityQueue;
    distanceFromSource[node->getNodeIndex()] = 0;
    for (int i = 0; i < numberOfVertices; ++i) {
        if (i != node->getNodeIndex())
            distanceFromSource[i] = INF;
            parentVertices[i] = -1;
    }
    for (auto &&edge :node->getEdges()) {
        priorityQueue.push(*edge);
    }
    parentVertices[node->getNodeIndex()] = node->getNodeIndex();
    while (!priorityQueue.empty()) {
        GraphEdge minEdge = priorityQueue.top();
        priorityQueue.pop();
        int sum = minEdge.getWeight() + distanceFromSource[minEdge.getNode1()->getNodeIndex()];
        if (sum < distanceFromSource[minEdge.getNode2()->getNodeIndex()]) {
            distanceFromSource[minEdge.getNode2()->getNodeIndex()] = sum;
            parentVertices[minEdge.getNode2()->getNodeIndex()] = minEdge.getNode1()->getNodeIndex();
            for (auto &&edge: minEdge.getNode2()->getEdges()) {
                if (!(minEdge == edge)) {
                    priorityQueue.push(*edge);
                }
            }

        }
    }
    vector<vector<int>> to_e;
    for (int j = 0; j < numberOfVertices; ++j) {
        vector<int> from_e;
        if (j != node->getNodeIndex()) {
            int k = j;
            while (k != node->getNodeIndex()) {
                from_e.push_back(k);
                if (k == -1) {
                    break;
                }
                k = parentVertices[k];
            }
            from_e.push_back(distanceFromSource[j]);
            to_e.push_back(from_e);
        }
        else {
            from_e.push_back(distanceFromSource[j]);
            to_e.push_back(from_e);
        }
    }
    delete[](distanceFromSource);
    delete[](parentVertices);
    return to_e;
}
//Recursive Helper method for Dijkstra Algorithm to print the output edges.
void Graph::printParents(int index, int sourceIndex, int *parentVertices) {
    if (index != sourceIndex) {
        printParents(parentVertices[index], sourceIndex, parentVertices);
        cout<<" -> ";
    }
    cout << index ;

}
//Insert nodes using the number of vertices input.
void Graph::createNodes() {
    for (int i = 0; i < numberOfVertices; ++i) {
        addNode(i);
    }
}
//Insert edges using the adjacency matrix input.
void Graph::createEdges() {
    for (int i = 0; i < numberOfVertices; ++i) {
        for (int j = 0; j < numberOfVertices; ++j) {
            if (adjacencyMatrix[i][j] != 0)
                addEdge(vertices.at((unsigned long) i), vertices.at((unsigned long) j), adjacencyMatrix[i][j]);
        }

    }
}
//Method to return the vertices from the graph.
const vector<GraphNode *> &Graph::getVertices() const {
    return vertices;
}
//De-constructor of Graph Object to avoid memory leak by deleting the used pointers.
Graph::~Graph() {
    for (auto &&item :edges)
        delete (item);
    for (auto&& item : vertices)
        delete (item);
}
//Comparator class operator method helper for Prim's Algorithm, input for priority queue.
int Graph::myComparator::operator()(GraphEdge &edge1, GraphEdge &edge2) {
    return edge1.getWeight() > edge2.getWeight();
}
