/*
 * A* SEARCH ALGORITHM
 * 
 * Category: Informed Search (Heuristic Search)
 * Description: Optimal pathfinding algorithm that uses heuristic function to guide search
 * 
 * Key Characteristics:
 * - Uses heuristic function h(n) to estimate distance to goal
 * - Combines actual cost g(n) with heuristic estimate h(n)
 * - Evaluation function: f(n) = g(n) + h(n)
 * - Guarantees optimal path when heuristic is admissible
 * - More efficient than Dijkstra's algorithm
 * 
 * Time Complexity: O(E log V) - where V = vertices, E = edges
 * Space Complexity: O(V) - priority queue size
 * 
 * Best for: Pathfinding in games, GPS navigation, AI planning
 * Worst for: When no good heuristic is available
 */

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
using namespace std;

// Edge structure: pair<destination node, cost>
using Edge = pair<int, int>;

/**
 * Node structure for A* priority queue
 * Contains node information and evaluation values
 */
struct Node {
    int id;     // Node identifier
    int g;      // Actual cost from start to this node
    int f;      // Evaluation function: f(n) = g(n) + h(n)

    // Priority queue comparator (min-heap based on f value)
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

/**
 * A* Search Algorithm
 * 
 * @param start - starting node
 * @param goal - target node to reach
 * @param graph - weighted graph represented as adjacency list
 * @param heuristic - heuristic function values for each node
 */
void aStar(int start, int goal, const vector<vector<Edge>>& graph, const vector<int>& heuristic) {
    int n = graph.size();
    vector<bool> visited(n, false);        // Track visited nodes
    vector<int> cost(n, INT_MAX);          // Store minimum g(n) values

    // Priority queue ordered by f(n) = g(n) + h(n)
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({start, 0, heuristic[start]}); // Start node: g=0, f=h(start)
    cost[start] = 0;

    while (!pq.empty()) {
        Node current = pq.top(); pq.pop();
        int node = current.id;

        // Skip if already visited
        if (visited[node]) continue;
        visited[node] = true;

        // Display current node information
        cout << "\nVisited node: " << node
             << " (g = " << current.g
             << ", h = " << heuristic[node]
             << ", f = " << current.f << ")\n";

        // Check if goal reached
        if (node == goal) {
            cout << "\nGoal reached at node " << node
                 << "! (Total cost: " << current.g << ")\n";
            return;
        }

        // Explore all neighbors
        for (auto [neighbor, weight] : graph[node]) {
            int newG = current.g + weight;             // New actual cost
            int newF = newG + heuristic[neighbor];     // New evaluation: f = g + h

            if (newG < cost[neighbor]) {               // If this path is better
                cost[neighbor] = newG;                 // Update minimum cost
                pq.push({neighbor, newG, newF});       // Add to priority queue
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
    // Should never overestimate the actual cost (admissible heuristic)
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

    cout << "\nA* Search from node " << start << " to " << goal << ":\n";
    aStar(start, goal, graph, heuristic);

    return 0;
}

/*
 * ALGORITHM ANALYSIS:
 * 
 * Key Features:
 * - Uses heuristic function to guide search
 * - Combines actual cost (g) with estimated cost (h)
 * - Evaluation function: f(n) = g(n) + h(n)
 * - Guarantees optimal path with admissible heuristic
 * 
 * Heuristic Requirements:
 * - Admissible: h(n) ≤ actual cost to goal (never overestimate)
 * - Consistent: h(n) ≤ cost(n,n') + h(n') for all neighbors
 * - Better heuristics lead to faster search
 * 
 * Data Structures Used:
 * - Priority Queue: Orders nodes by f(n) value
 * - Vector<bool>: Tracks visited nodes
 * - Vector<int>: Stores minimum g(n) values
 * - Adjacency List: Weighted graph representation
 * 
 * Complexity Analysis:
 * - Time Complexity: O(E log V) - each edge processed once
 * - Space Complexity: O(V) - priority queue size
 * 
 * Advantages:
 * - Guarantees optimal path with admissible heuristic
 * - More efficient than Dijkstra's algorithm
 * - Can handle large graphs with good heuristics
 * - Widely used in games and navigation
 * 
 * Disadvantages:
 * - Requires good heuristic function
 * - Memory usage can be high
 * - Performance depends on heuristic quality
 * 
 * Use Cases:
 * - Game AI pathfinding
 * - GPS navigation systems
 * - Robot navigation
 * - Network routing
 * - AI planning problems
 * 
 * Comparison with other algorithms:
 * | Algorithm | Optimal | Uses Heuristic | Memory Usage |
 * |-----------|---------|----------------|--------------|
 * | Dijkstra  | Yes     | No             | High         |
 * | A*        | Yes     | Yes            | Medium       |
 * | Greedy    | No      | Yes            | Low          |
 * 
 * Note: A* is often the best choice for pathfinding when a good heuristic is available
 */
