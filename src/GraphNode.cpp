#include "GraphNode.h"
GraphNode::GraphNode(int nodeIndex) {
    this->nodeIndex=nodeIndex;
}
GraphNode::~GraphNode() {
}
vector<GraphEdge *> &GraphNode::getEdges()  {
    return edges;
}

void GraphNode::setEdges(const vector<GraphEdge *> &p_edges) {
    GraphNode::edges = p_edges;
}

int GraphNode::getNodeIndex()  {
    return nodeIndex;
}




