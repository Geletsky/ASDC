#include <iostream>
#include <vector>
#include <queue>

struct GraphPeak {
    int value;
    std::vector<GraphPeak*> neighbours;
    bool visited;
};

void printValuesOfNeighbours(GraphPeak* node);
int calcSumOfNeighboursValues(GraphPeak* node);
void BFS(GraphPeak* node);
void DFS(GraphPeak* node);
void resetAttendance(std::vector<GraphPeak*>& nodeVector);

int main() {
    GraphPeak* n1 = new GraphPeak{ 1, {}, false };
    GraphPeak* n2 = new GraphPeak{ 2, {}, false };
    GraphPeak* n3 = new GraphPeak{ 3, {}, false };
    GraphPeak* n4 = new GraphPeak{ 4, {}, false };

    std::vector<GraphPeak*> nodeVector = { n1, n2, n3, n4 };

    n1->neighbours = { n2, n3, n4 };
    n2->neighbours = { n3 };
    n3->neighbours = { n4, n2 };
    n4->neighbours = {};

    printValuesOfNeighbours(n1);
    std::cout << "Sum of Neighbours of n1: " << calcSumOfNeighboursValues(n1) << std::endl;

    std::cout << "\nBFS: " << std::endl;
    BFS(n2);
    std::cout << std::endl;

    resetAttendance(nodeVector);

    std::cout << "DFS: " << std::endl;
    DFS(n3);
    std::cout << std::endl;

    // Deallocate memory
    for (auto node : nodeVector)
        delete node;

    return 0;
}

void printValuesOfNeighbours(GraphPeak* node) {
    for (auto neighbour : node->neighbours) {
        std::cout << "Neighbour value: " << neighbour->value << std::endl;
    }
}

int calcSumOfNeighboursValues(GraphPeak* node) {
    int sum = 0;
    for (auto neighbour : node->neighbours) {
        sum += neighbour->value;
    }
    return sum;
}

void BFS(GraphPeak* node) {
    if (node == nullptr) return;
    std::queue<GraphPeak*> queue;
    node->visited = true;
    queue.push(node);
    while (!queue.empty()) {
        GraphPeak* curNode = queue.front();
        std::cout << curNode->value << std::endl;
        queue.pop();
        for (auto neighbour : curNode->neighbours) {
            if (!neighbour->visited) {
                queue.push(neighbour);
                neighbour->visited = true;
            }
        }
    }
}

void resetAttendance(std::vector<GraphPeak*>& nodeVector) {
    for (auto node : nodeVector) {
        node->visited = false;
    }
}

void DFS(GraphPeak* node) {
    if (node->visited) return;
    node->visited = true;
    std::cout << node->value << std::endl;
    for (auto neighbour : node->neighbours) {
        DFS(neighbour);
    }
}
