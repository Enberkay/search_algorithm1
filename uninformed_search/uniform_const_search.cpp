/*
 * UNIFORM COST SEARCH (UCS) ALGORITHM
 * 
 * Category: Uninformed Search (Blind Search)
 * Description: BFS variant that finds shortest path in weighted graphs using priority queue
 * 
 * Key Characteristics:
 * - No heuristic or prior knowledge used
 * - Uses Priority Queue (min-heap) to select lowest cost node
 * - Works with weighted graphs (edges have costs)
 * - Guarantees optimal (shortest) path
 * - Similar to Dijkstra's algorithm but without specific goal
 * 
 * Time Complexity: O(E log V) - where V = vertices, E = edges
 * Space Complexity: O(V) - priority queue size
 * 
 * Best for: Shortest path in weighted graphs
 * Worst for: Unweighted graphs (use BFS instead)
 */

#include <iostream>
#include <vector>
#include <queue>
#include <utility> // for pair
using namespace std;

// Edge structure: pair<destination, cost>
using Edge = pair<int, int>;

/**
 * Uniform Cost Search Function
 * 
 * @param start - starting node for search
 * @param graph - weighted graph represented as adjacency list
 */
void ucs(int start, const vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);           // Track visited nodes
    vector<int> cost(n, INT_MAX);             // Store minimum cost to reach each node

    // Min-heap priority queue: orders by cost (lowest first)
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    cost[start] = 0;                          // Cost to start node is 0
    pq.push({0, start});                      // Add start node to priority queue

    while (!pq.empty()) {
        int currCost = pq.top().first;        // Get current cost
        int node = pq.top().second;           // Get current node
        pq.pop();                             // Remove from priority queue

        if (visited[node]) continue;          // Skip if already visited
        visited[node] = true;                 // Mark as visited

        cout << "Visited node: " << node << " with cost = " << currCost << endl;

        // Explore all neighbors of current node
        for (auto [neighbor, weight] : graph[node]) {
            int newCost = currCost + weight;  // Calculate new cost through current node
            if (newCost < cost[neighbor]) {   // If this path is better
                cost[neighbor] = newCost;     // Update minimum cost
                pq.push({newCost, neighbor}); // Add to priority queue
            }
        }
    }

    // Display results
    cout << "\nMinimum cost from node " << start << " to each node:\n";
    for (int i = 0; i < n; ++i) {
        cout << "To node " << i << ": cost = " << cost[i] << endl;
    }
}

int main() {
    int n = 6; // Number of nodes
    vector<vector<Edge>> graph(n);

    // Create weighted graph (directed)
    // Each edge: {destination, cost}
    graph[0] = {{1, 2}, {2, 4}};  // Node 0: to node 1 (cost=2), to node 2 (cost=4)
    graph[1] = {{0, 2}, {3, 7}, {4, 1}}; // Node 1: to nodes 0,3,4 with respective costs
    graph[2] = {{0, 4}, {4, 3}};  // Node 2: to nodes 0,4
    graph[3] = {{1, 7}, {5, 1}};  // Node 3: to nodes 1,5
    graph[4] = {{1, 1}, {2, 3}, {5, 5}}; // Node 4: to nodes 1,2,5
    graph[5] = {{3, 1}, {4, 5}};  // Node 5: to nodes 3,4

    cout << "Uniform Cost Search starting from node 0:\n";
    ucs(0, graph);

    return 0;
}

/*
 * ALGORITHM ANALYSIS:
 * 
 * Key Features:
 * - Uses Priority Queue (min-heap) for node selection
 * - Always explores lowest cost path first
 * - Guarantees optimal (shortest) path in weighted graphs
 * - Similar to Dijkstra's algorithm
 * 
 * Data Structures Used:
 * - Priority Queue: Orders nodes by cost (lowest first)
 * - Vector<bool>: Tracks visited nodes
 * - Vector<int>: Stores minimum cost to reach each node
 * - Adjacency List: Weighted graph representation
 * 
 * Complexity Analysis:
 * - Time Complexity: O(E log V) - each edge processed once, log V for priority queue
 * - Space Complexity: O(V) - priority queue size
 * 
 * Advantages:
 * - Guarantees optimal path in weighted graphs
 * - Works with any positive edge weights
 * - Systematic exploration
 * 
 * Disadvantages:
 * - Slower than BFS for unweighted graphs
 * - Higher memory usage than DFS
 * - Cannot handle negative edge weights
 * 
 * Use Cases:
 * - GPS navigation systems
 * - Network routing
 * - Game AI pathfinding
 * - Resource allocation problems
 * 
 * Comparison with BFS:
 * | Aspect        | BFS (Unweighted)        | UCS (Weighted)           |
 * |---------------|--------------------------|--------------------------|
 * | Queue Type    | Regular Queue (FIFO)    | Priority Queue (Min-Heap)|
 * | Node Selection| Level order             | Cost-based order         |
 * | Optimal Path  | Only for unweighted     | Always optimal           |
 * | Edge Weights  | Not considered          | Must be positive         |
 * | Time Complexity| O(V + E)               | O(E log V)               |
 * 
 * Note: UCS is essentially Dijkstra's algorithm without a specific goal node
 */
