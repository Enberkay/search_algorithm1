/*
 * ITERATIVE DEEPENING DEPTH-FIRST SEARCH (IDS/IDDFS) ALGORITHM
 * 
 * Category: Uninformed Search (Blind Search)
 * Description: Combines benefits of DFS and BFS by running DFS with increasing depth limits
 * 
 * Key Characteristics:
 * - No heuristic or prior knowledge used
 * - Combines DFS memory efficiency with BFS completeness
 * - Runs DFS multiple times with increasing depth limits
 * - Guarantees shortest path (like BFS) with low memory usage (like DFS)
 * - Also known as Iterative Deepening DFS (IDDFS)
 * 
 * Time Complexity: O(b^d) - where b = branching factor, d = depth
 * Space Complexity: O(d) - recursion stack depth
 * 
 * Best for: Memory-constrained environments requiring optimal paths
 * Worst for: Very deep graphs (repeated work)
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * Depth-Limited Search (DLS) - DFS with depth limit
 * 
 * @param node - current node being visited
 * @param target - goal node to find
 * @param depth - remaining depth limit
 * @param graph - adjacency list representation of graph
 * @param visited - boolean array to track visited nodes
 * @return true if target found, false otherwise
 */
bool dls(int node, int target, int depth, const vector<vector<int>>& graph, vector<bool>& visited) {
    if (depth < 0) return false;              // Depth limit exceeded
    
    if (node == target) {
        cout << "Found target at node: " << node << endl;
        return true;                           // Target found
    }

    visited[node] = true;                     // Mark current node as visited
    cout << "Visited node: " << node << " (depth left: " << depth << ")" << endl;

    // Explore all neighbors within depth limit
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            if (dls(neighbor, target, depth - 1, graph, visited)) {
                return true;                   // Target found in subtree
            }
        }
    }

    return false;                             // Target not found in this branch
}

/**
 * Iterative Deepening DFS Function
 * 
 * @param start - starting node for search
 * @param target - goal node to find
 * @param maxDepth - maximum depth to search
 * @param graph - adjacency list representation of graph
 * @return true if target found, false otherwise
 */
bool iddfs(int start, int target, int maxDepth, const vector<vector<int>>& graph) {
    // Try DFS with increasing depth limits
    for (int depth = 0; depth <= maxDepth; ++depth) {
        cout << "\nTrying depth limit = " << depth << endl;
        vector<bool> visited(graph.size(), false);
        
        if (dls(start, target, depth, graph, visited)) {
            return true;                       // Target found at this depth
        }
    }
    return false;                             // Target not found within maxDepth
}

int main() {
    int n = 6; // Number of nodes
    vector<vector<int>> graph(n);
    
    // Create undirected graph using adjacency list
    graph[0] = {1, 2};  // Node 0 connects to nodes 1 and 2
    graph[1] = {0, 3, 4}; // Node 1 connects to nodes 0, 3, and 4
    graph[2] = {0};      // Node 2 connects to node 0
    graph[3] = {1};      // Node 3 connects to node 1
    graph[4] = {1, 5};   // Node 4 connects to nodes 1 and 5
    graph[5] = {4};      // Node 5 connects to node 4

    int start = 0;
    int goal = 5;
    int maxDepth = 4;

    cout << "Iterative Deepening DFS from node " << start << " to " << goal << ":\n";
    if (!iddfs(start, goal, maxDepth, graph)) {
        cout << "Target not found within depth limit " << maxDepth << endl;
    }

    return 0;
}

/*
 * ALGORITHM ANALYSIS:
 * 
 * Key Features:
 * - Combines DFS and BFS advantages
 * - Uses DFS with increasing depth limits
 * - Guarantees shortest path (like BFS)
 * - Low memory usage (like DFS)
 * - Systematic exploration
 * 
 * How it works:
 * - Start with depth limit 0
 * - Run DFS with current depth limit
 * - If target not found, increase depth limit by 1
 * - Repeat until target found or max depth reached
 * 
 * Data Structures Used:
 * - Recursion Stack: Implements DFS (LIFO)
 * - Vector<bool>: Tracks visited nodes
 * - Adjacency List: Graph representation
 * 
 * Complexity Analysis:
 * - Time Complexity: O(b^d) - may repeat work at shallow levels
 * - Space Complexity: O(d) - recursion stack depth
 * 
 * Advantages:
 * - Guarantees shortest path (like BFS)
 * - Low memory usage (like DFS)
 * - Complete search within depth limit
 * - Good for memory-constrained systems
 * 
 * Disadvantages:
 * - May repeat work at shallow levels
 * - Slower than pure BFS for shallow targets
 * - Not suitable for infinite graphs
 * 
 * Use Cases:
 * - Game tree search (chess, checkers)
 * - AI planning problems
 * - Memory-constrained pathfinding
 * - Puzzle solving
 * 
 * Comparison with BFS and DFS:
 * | Algorithm | Memory Usage | Finds Shortest Path | Complete Search |
 * |-----------|--------------|---------------------|-----------------|
 * | DFS       | Very Low     | No                  | Yes             |
 * | BFS       | Very High    | Yes                 | Yes             |
 * | IDS       | Low          | Yes                 | Yes             |
 * 
 * Note: IDS is the best choice when you need shortest path but have memory constraints
 */
