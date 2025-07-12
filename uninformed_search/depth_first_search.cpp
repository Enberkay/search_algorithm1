/*
 * DEPTH-FIRST SEARCH (DFS) ALGORITHM
 * 
 * Category: Uninformed Search (Blind Search)
 * Description: Graph traversal algorithm that explores as far as possible along each branch before backtracking
 * 
 * Key Characteristics:
 * - No heuristic or prior knowledge used
 * - Explores deep paths first (depth-first)
 * - Uses Stack data structure (LIFO) or recursion
 * - May not find shortest path
 * - Explores one complete path before backtracking
 * 
 * Time Complexity: O(V + E) - where V = vertices, E = edges
 * Space Complexity: O(V) - recursion stack depth in worst case
 * 
 * Best for: Complete exploration, cycle detection, maze solving
 * Worst for: Finding shortest path (use BFS instead)
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * Depth-First Search Function (Recursive Implementation)
 * 
 * @param node - current node being visited
 * @param graph - adjacency list representation of graph
 * @param visited - boolean array to track visited nodes
 */
void dfs(int node, const vector<vector<int>>& graph, vector<bool>& visited) {
    visited[node] = true;                    // Mark current node as visited
    cout << "Visited node: " << node << endl;

    // Explore all neighbors of current node
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited);   // Recursive call - go deep first
        }
    }
}

int main() {
    int n = 6; // Number of nodes in graph
    vector<vector<int>> graph(n);
    
    // Create undirected graph using adjacency list
    graph[0] = {1, 2};  // Node 0 connects to nodes 1 and 2
    graph[1] = {0, 3, 4}; // Node 1 connects to nodes 0, 3, and 4
    graph[2] = {0};      // Node 2 connects to node 0
    graph[3] = {1};      // Node 3 connects to node 1
    graph[4] = {1, 5};   // Node 4 connects to nodes 1 and 5
    graph[5] = {4};      // Node 5 connects to node 4

    vector<bool> visited(n, false);  // Track visited nodes

    cout << "DFS traversal starting from node 0:\n";
    dfs(0, graph, visited);

    return 0;
}

/*
 * ALGORITHM ANALYSIS:
 * 
 * Key Features:
 * - Deep exploration before backtracking
 * - Uses Stack data structure (LIFO principle) or recursion
 * - Explores one complete path before trying alternatives
 * - Memory efficient for deep graphs
 * 
 * Data Structures Used:
 * - Stack (implicit in recursion): Stores nodes to be visited (LIFO)
 * - Vector<bool>: Tracks visited nodes to avoid cycles
 * - Adjacency List: Graph representation
 * 
 * Complexity Analysis:
 * - Time Complexity: O(V + E) - visit each node and edge once
 * - Space Complexity: O(V) - recursion stack depth in worst case
 * 
 * Advantages:
 * - Memory efficient for deep graphs
 * - Good for complete exploration
 * - Natural for recursive problems
 * - Can detect cycles easily
 * 
 * Disadvantages:
 * - May not find shortest path
 * - Can get stuck in deep paths
 * - Stack overflow for very deep graphs
 * 
 * Use Cases:
 * - Maze solving
 * - Topological sorting
 * - Cycle detection
 * - Game tree exploration
 * - Web crawling (alternative to BFS)
 * 
 * BFS vs DFS Comparison:
 * | Aspect        | BFS                    | DFS                    |
 * |---------------|------------------------|------------------------|
 * | Data Structure| Queue (FIFO)          | Stack/Recursion (LIFO) |
 * | Exploration   | Level by level         | Deep paths first       |
 * | Shortest Path| Guaranteed (unweighted)| Not guaranteed         |
 * | Memory Usage  | High for wide graphs   | Low for deep graphs    |
 * | Best For      | Shortest path          | Complete exploration   |
 */
