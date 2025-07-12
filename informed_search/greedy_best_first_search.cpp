/*
 * GREEDY BEST-FIRST SEARCH ALGORITHM
 * 
 * Category: Informed Search (Heuristic Search)
 * Description: Pathfinding algorithm that uses only heuristic function to guide search
 * 
 * Key Characteristics:
 * - Uses only heuristic function h(n) for node selection
 * - Ignores actual path cost (g value)
 * - Always chooses node with lowest heuristic value
 * - Fast but may not find optimal path
 * - Similar to A* but without g(n) component
 * 
 * Time Complexity: O(E log V) - where V = vertices, E = edges
 * Space Complexity: O(V) - priority queue size
 * 
 * Best for: Quick pathfinding when optimality not required
 * Worst for: When optimal path is required
 */

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

// Edge structure: pair<destination, cost>
using Edge = pair<int, int>;

/**
 * Node structure for Greedy Best-First Search priority queue
 * Contains only node identifier and heuristic value
 */
struct Node {
    int id;  // Node identifier
    int h;   // Heuristic value h(n)

    // Priority queue comparator (min-heap based on h value)
    bool operator>(const Node& other) const {
        return h > other.h;
    }
};

/**
 * Greedy Best-First Search Algorithm
 * 
 * @param start - starting node
 * @param goal - target node to reach
 * @param graph - weighted graph represented as adjacency list
 * @param heuristic - heuristic function values for each node
 */
void greedyBestFirstSearch(int start, int goal,
                           const vector<vector<Edge>>& graph, const vector<int>& heuristic) {
    int n = graph.size();
    vector<bool> visited(n, false);           // Track visited nodes

    // Priority queue ordered by heuristic value only
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({start, heuristic[start]});       // Add start node with its heuristic

    while (!pq.empty()) {
        Node current = pq.top(); pq.pop();
        int node = current.id;

        if (visited[node]) continue;          // Skip if already visited
        visited[node] = true;                 // Mark as visited

        cout << "\nVisited node: " << node
             << " (h = " << heuristic[node] << ")\n";

        if (node == goal) {
            cout << "\nGoal reached at node " << node << "!\n";
            return;
        }

        // Explore all unvisited neighbors
        for (auto [neighbor, cost] : graph[node]) {
            if (!visited[neighbor]) {
                pq.push({neighbor, heuristic[neighbor]}); // Add with heuristic value
            }
        }
    }

    cout << "\nGoal cannot be reached\n";
}

int main() {
    int n = 6; // Number of nodes
    vector<vector<Edge>> graph(n);

    // Create weighted directed graph
    // Each edge: {destination, cost}
    graph[0] = {{1, 2}, {2, 4}};  // Node 0: to node 1 (cost=2), to node 2 (cost=4)
    graph[1] = {{3, 2}, {4, 3}};  // Node 1: to nodes 3,4
    graph[2] = {{4, 2}};          // Node 2: to node 4
    graph[3] = {{5, 1}};          // Node 3: to node 5
    graph[4] = {{5, 2}};          // Node 4: to node 5
    graph[5] = {};                 // Goal node (no outgoing edges)

    // Heuristic function h(n): estimated distance to goal (node 5)
    vector<int> heuristic = {
        7, // h(0) - estimated cost from node 0 to goal
        6, // h(1) - estimated cost from node 1 to goal
        2, // h(2) - estimated cost from node 2 to goal
        1, // h(3) - estimated cost from node 3 to goal
        3, // h(4) - estimated cost from node 4 to goal
        0  // h(5) - goal node (cost to itself is 0)
    };

    int start = 0;
    int goal = 5;

    cout << "\nGreedy Best-First Search from node " << start << " to " << goal << ":\n";
    greedyBestFirstSearch(start, goal, graph, heuristic);
    return 0;
}

/*
 * ALGORITHM ANALYSIS:
 * 
 * Key Features:
 * - Uses only heuristic function for node selection
 * - Ignores actual path cost (g value)
 * - Always chooses node with lowest heuristic value
 * - Fast but may not find optimal path
 * 
 * Data Structures Used:
 * - Priority Queue: Orders nodes by heuristic value only
 * - Vector<bool>: Tracks visited nodes
 * - Adjacency List: Weighted graph representation
 * 
 * Complexity Analysis:
 * - Time Complexity: O(E log V) - each edge processed once
 * - Space Complexity: O(V) - priority queue size
 * 
 * Advantages:
 * - Very fast execution
 * - Low memory usage
 * - Good for quick pathfinding
 * - Simple implementation
 * 
 * Disadvantages:
 * - May not find optimal path
 * - Can get stuck in local optima
 * - Quality depends heavily on heuristic
 * - No guarantee of completeness
 * 
 * Use Cases:
 * - Quick pathfinding in games
 * - Real-time navigation
 * - When optimality is not critical
 * - Prototype development
 * 
 * Comparison with A*:
 * | Aspect        | Greedy Best-First | A* Search        |
 * |---------------|-------------------|------------------|
 * | Node Selection| h(n) only         | f(n) = g(n) + h(n)|
 * | Optimality    | Not guaranteed    | Guaranteed       |
 * | Speed         | Very fast         | Fast             |
 * | Memory Usage  | Low               | Medium           |
 * | Completeness  | Not guaranteed    | Guaranteed       |
 * 
 * Note: Greedy Best-First is good for quick solutions when optimality is not required
 */
