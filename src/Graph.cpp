#include <queue>
#include <algorithm>
#include <iostream>
#include "Graph.h"
//defined a random high value integer as INF value.
#define  INF 99999
//Graph Object Constructor supporting Adjacency matrix representation interface.
Graph::Graph() {
    
}

Graph::Graph(const TypedArray<int>& vertcie_list, const TypedArray<Vector3i>& edge_list){
    createNodes(vertcie_list);
    createEdges(edge_list);
}
//Insert GraphNode Object to the Graph Object.
GraphNode *Graph::addNode(int index) {
    auto *node = new GraphNode(index);
    //add this node to the vertices arrayList.
    vertices.insert(make_pair(index, node));
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
//vector<GraphEdge> *Graph::primAlgorithm(GraphNode *node) {
//    auto *distance = new int[numberOfVertices];
//    priority_queue<GraphEdge, vector<GraphEdge>, myComparator> priorityQueue;
//    auto *MST = new vector<GraphEdge>;
//    distance[0] = 0;
//    for (int i = 1; i < numberOfVertices; ++i) {
//        distance[i] = INF;
//    }
//    for (auto &&edge :node->getEdges())
//        priorityQueue.push(*edge);
//    while (!priorityQueue.empty()) {
//        GraphEdge minEdge = priorityQueue.top();
//        priorityQueue.pop();
//        if (minEdge.getWeight() < distance[minEdge.getNode2()->getNodeIndex()]) {
//            distance[minEdge.getNode2()->getNodeIndex()] = minEdge.getWeight();
//            for (auto &&edge: minEdge.getNode2()->getEdges()) {
//                if (!(minEdge == edge)) {
//                    priorityQueue.push(*edge);
//                }
//            }
//            MST->push_back(minEdge);
//        }
//
//
//    }
//    return MST;
//}
//Dijkstra Algorithm Method to find the shortest path.
vector<vector<int>> Graph::dijkstraAlgorithm(GraphNode *node) {
    size_t numberOfVertices = vertices.size();
    unordered_map<int, int> vIndexMap(numberOfVertices);
    unordered_map<int, int> vIndexReverseMap(numberOfVertices);
    int p = 0;
    for (auto it = vertices.begin(); it != vertices.end(); ++it,++p) {
        vIndexMap[it->first] = p;
        vIndexReverseMap[p] = it->first;
    }
    int* distanceFromSource = new int[numberOfVertices];
    auto *parentVertices = new int[numberOfVertices];
    priority_queue<GraphEdge, vector<GraphEdge>, myComparator> priorityQueue;
    distanceFromSource[vIndexMap[node->getNodeIndex()]] = 0;
    for (int i = 0; i < numberOfVertices; ++i) {
        if (i != vIndexMap[node->getNodeIndex()])
            distanceFromSource[i] = INF;
            parentVertices[i] = -1;
    }
    for (auto &&edge :node->getEdges()) {
        priorityQueue.push(*edge);
    }
    parentVertices[vIndexMap[node->getNodeIndex()]] = vIndexMap[node->getNodeIndex()];
    while (!priorityQueue.empty()) {
        GraphEdge minEdge = priorityQueue.top();
        priorityQueue.pop();
        int sum = minEdge.getWeight() + distanceFromSource[vIndexMap[minEdge.getNode1()->getNodeIndex()]];
        if (sum < distanceFromSource[vIndexMap[minEdge.getNode2()->getNodeIndex()]]) {
            distanceFromSource[vIndexMap[minEdge.getNode2()->getNodeIndex()]] = sum;
            parentVertices[vIndexMap[minEdge.getNode2()->getNodeIndex()]] = vIndexMap[minEdge.getNode1()->getNodeIndex()];
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
        if (j != vIndexMap[node->getNodeIndex()]) {
            int k = j;
            while (k != vIndexMap[node->getNodeIndex()]) {
                from_e.push_back(vIndexReverseMap[k]);
                if (k == -1) {
                    from_e.clear();
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
void Graph::createNodes(const TypedArray<int>& vertcie_list) {
    for (int i = 0; i < vertcie_list.size(); i++) {
        addNode(vertcie_list[i]);
    }
}
//Insert edges using the adjacency matrix input.
void Graph::createEdges(const TypedArray<Vector3i>& edge_list) {
    for (int i = 0; i < edge_list.size(); i++) {
        Vector3i ce = edge_list[i];
        addEdge(vertices[ce.x], vertices[ce.y], ce.z);
    }
}
//Method to return the vertices from the graph.
const unordered_map<int, GraphNode*>& Graph::getVertices() const {
    return vertices;
}
//De-constructor of Graph Object to avoid memory leak by deleting the used pointers.
Graph::~Graph() {
    for (auto &&item :edges)
        delete (item);
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        delete(it->second);
    }
}
//Comparator class operator method helper for Prim's Algorithm, input for priority queue.
int Graph::myComparator::operator()(GraphEdge &edge1, GraphEdge &edge2) {
    return edge1.getWeight() > edge2.getWeight();
}

void Graph::addEdge(Vector3i p_edge) {
    auto it_e = find_if(edges.begin(), edges.end(), [p_edge](GraphEdge* x)->bool {
        return x->getNode1()->getNodeIndex() == p_edge.x && x->getNode2()->getNodeIndex() == p_edge.y;
        });
    if (it_e != edges.end()) {
        (*it_e)->setWeight(p_edge.z);
    }
    auto it1 = vertices.find(p_edge.x);
    auto it2 = vertices.find(p_edge.y);
    if (it1 != vertices.end() && it2 != vertices.end()) {
        addEdge(it1->second, it2->second, p_edge.z);
    }
}

void Graph::removeEdge(Vector2i p_edge) {
    auto it1 = vertices.find(p_edge.x);
    auto it2 = vertices.find(p_edge.y);
    if (it1 != vertices.end() && it2 != vertices.end()) {
        vector<GraphEdge*> tve = it1->second->getEdges();
        auto it_e = find_if(tve.begin(), tve.end(), [p_edge](GraphEdge* x)->bool {
            return x->getNode1()->getNodeIndex() == p_edge.x && x->getNode2()->getNodeIndex() == p_edge.y;
            });
        if (it_e != tve.end()) {
            GraphEdge* edge_to_delete = *it_e;
            it1->second->getEdges().erase(it_e);
            auto it_e2 = find_if(edges.begin(), edges.end(), [edge_to_delete](GraphEdge* x)->bool {
                return x == edge_to_delete;
                });
            edges.erase(it_e2);
            delete(edge_to_delete);
        }
    }
}
void Graph::addEdges(const TypedArray<Vector3i>& edge_list) {
    for (int i = 0; i < edge_list.size(); i++) {
        addEdge(edge_list[i]);
    }
}
void Graph::removeEdges(const TypedArray<Vector2i>& edge_list) {
    for (int i = 0; i < edge_list.size(); i++) {
        removeEdge(edge_list[i]);
    }
}
void Graph::removeNode(int index) {
    auto it1 = vertices.find(index);
    if (it1 != vertices.end()) {
        GraphNode* tNode = it1->second;
        // 1.1 find all edges directed to node target
        // 1.2 find all nodes in 1.1 start node and delete edge themself from that node
        // 1.3 delete all edges from graph edges in 1.1
        for (auto&& it = edges.begin(); it != edges.end(); it++) {
            if ((*it)->getNode2()->getNodeIndex() == index) {
                GraphEdge* r = *it;
                edges.erase(it);
                auto tve = &(r->getNode1()->getEdges());
                auto find_e = find_if(tve->begin(), tve->end(), [r](GraphEdge* e)->bool {
                    return e == r;
                    });
                tve->erase(find_e);
                delete(r);
            }
            // 2.3 delete all edges from graph edges in 2.1
            if ((*it)->getNode1()->getNodeIndex() == index) {
                edges.erase(it);
            }
        }
        // 2.1 find all edges from node target(direct from node edges)
        // 2.2 delete all edges from node edges in 2.1
        auto tve = &(it1->second->getEdges());
        for (auto&& it = tve->begin(); it != tve->end(); it++) {
            GraphEdge* r = *it;
            tve->erase(it);
            delete(r);
        }
        vertices.erase(it1);
        delete(tNode);
    }
}
void Graph::addNodes(const TypedArray<int>& vertcie_list) {
    for (int i = 0; i < vertcie_list.size(); i++) {
        addNode(vertcie_list[i]);
    }
}
void Graph::removeNodes(const TypedArray<int>& node_list) {
    for (int i = 0; i < node_list.size(); i++) {
        removeNode(node_list[i]);
    }
}