/*
 * ITERATIVE DEEPENING A* (IDA*) SEARCH ALGORITHM
 * 
 * Category: Informed Search (Heuristic Search)
 * Description: Memory-efficient version of A* that uses iterative deepening with f-value limits
 * 
 * Key Characteristics:
 * - Combines A* heuristic guidance with IDS memory efficiency
 * - Uses f(n) = g(n) + h(n) as depth limit
 * - Runs multiple DFS iterations with increasing f-limits
 * - Guarantees optimal path with admissible heuristic
 * - Much lower memory usage than A*
 * 
 * Time Complexity: O(b^d) - where b = branching factor, d = depth
 * Space Complexity: O(d) - recursion stack depth
 * 
 * Best for: Memory-constrained environments requiring optimal paths
 * Worst for: Very deep graphs (repeated work)
 */

#include <iostream>
#include <vector>
#include <utility>
#include <limits>
using namespace std;

// Edge structure: pair<destination, cost>
using Edge = pair<int, int>;
const int INF = numeric_limits<int>::max();

/**
 * Depth-First Search with f-value limit (DLS for IDA*)
 * 
 * @param node - current node being visited
 * @param goal - target node to reach
 * @param g - actual cost from start to current node
 * @param limit - f-value limit for this iteration
 * @param graph - weighted graph represented as adjacency list
 * @param heuristic - heuristic function values for each node
 * @param visited - boolean array to track visited nodes
 * @param next_limit - reference to store next f-limit
 * @return true if goal found, false otherwise
 */
bool dfs(int node, int goal, int g, int limit,
         const vector<vector<Edge>>& graph, const vector<int>& heuristic,
         vector<bool>& visited, int& next_limit) {
    int f = g + heuristic[node]; // f(n) = g(n) + h(n)

    // If f exceeds limit, wait for next iteration
    if (f > limit) {
        next_limit = min(next_limit, f);
        return false;
    }

    // Display current node information
    cout << "Visited node: " << node
         << " (g = " << g
         << ", h = " << heuristic[node]
         << ", f = " << f << ")\n";

    if (node == goal) {
        cout << "\nGoal reached at node " << node << "! (cost: " << g << ")\n";
        return true;
    }

    visited[node] = true;

    // Explore all neighbors
    for (auto [neighbor, cost] : graph[node]) {
        if (!visited[neighbor]) {
            if (dfs(neighbor, goal, g + cost, limit, graph, heuristic, visited, next_limit)) {
                return true; // Goal found
            }
        }
    }

    visited[node] = false; // Backtrack to try other paths
    return false;
}

/**
 * IDA* Algorithm: Iterative deepening with f-value limits
 * 
 * @param start - starting node
 * @param goal - target node to reach
 * @param graph - weighted graph represented as adjacency list
 * @param heuristic - heuristic function values for each node
 */
void idaStar(int start, int goal,
             const vector<vector<Edge>>& graph, const vector<int>& heuristic) {
    int limit = heuristic[start]; // Start with h(start) as initial limit

    while (true) {
        cout << "\nNew iteration: limit = " << limit << "\n";
        vector<bool> visited(graph.size(), false);
        int next_limit = INF;

        // Run DFS with current f-limit
        if (dfs(start, goal, 0, limit, graph, heuristic, visited, next_limit)) {
            return; // Goal found
        }

        if (next_limit == INF) {
            cout << "\nGoal not found at any depth\n";
            return;
        }

        limit = next_limit; // Increase limit for next iteration
    }
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

    cout << "\nIDA* Search from node " << start << " to " << goal << ":\n";
    idaStar(start, goal, graph, heuristic);
    return 0;
}

/*
 * ALGORITHM ANALYSIS:
 * 
 * Key Features:
 * - Combines A* heuristic guidance with IDS memory efficiency
 * - Uses f(n) = g(n) + h(n) as depth limit instead of simple depth
 * - Runs multiple DFS iterations with increasing f-limits
 * - Guarantees optimal path with admissible heuristic
 * - Much lower memory usage than A*
 * 
 * How it works:
 * - Start with f-limit = h(start)
 * - Run DFS with current f-limit
 * - If goal not found, increase f-limit to minimum f-value that exceeded limit
 * - Repeat until goal found or no path exists
 * 
 * Data Structures Used:
 * - Recursion Stack: Implements DFS (LIFO)
 * - Vector<bool>: Tracks visited nodes
 * - Adjacency List: Weighted graph representation
 * 
 * Complexity Analysis:
 * - Time Complexity: O(b^d) - may repeat work at shallow levels
 * - Space Complexity: O(d) - recursion stack depth
 * 
 * Advantages:
 * - Guarantees optimal path with admissible heuristic
 * - Very low memory usage (like IDS)
 * - More efficient than IDS due to heuristic guidance
 * - Good for memory-constrained systems
 * 
 * Disadvantages:
 * - May repeat work at shallow levels
 * - Slower than A* for shallow goals
 * - Performance depends on heuristic quality
 * - Not suitable for infinite graphs
 * 
 * Use Cases:
 * - Memory-constrained pathfinding
 * - Game AI with limited memory
 * - Robot navigation systems
 * - AI planning problems
 * - Large-scale pathfinding
 * 
 * Comparison with A* and IDS:
 * | Algorithm | Optimal | Memory Usage | Uses Heuristic | Speed |
 * |-----------|---------|--------------|----------------|-------|
 * | A*        | Yes     | High         | Yes            | Fast  |
 * | IDS       | Yes     | Low          | No             | Slow  |
 * | IDA*      | Yes     | Low          | Yes            | Medium|
 * 
 * Note: IDA* is the best choice when you need optimal paths but have memory constraints
 */
