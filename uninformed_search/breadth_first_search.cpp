/*
 * BREADTH-FIRST SEARCH (BFS) ALGORITHM
 * 
 * Category: Uninformed Search (Blind Search)
 * Description: Graph traversal algorithm that explores all neighbors at current depth before moving to next level
 * 
 * Key Characteristics:
 * - No heuristic or prior knowledge used
 * - Explores level by level (breadth-first)
 * - Uses Queue data structure (FIFO)
 * - Guarantees shortest path in unweighted graphs
 * - Visits all nodes at current level before going deeper
 * 
 * Time Complexity: O(V + E) - where V = vertices, E = edges
 * Space Complexity: O(V) - queue size in worst case
 * 
 * Best for: Shortest path in unweighted graphs, level-order traversal
 * Worst for: Deep graphs with many levels (high memory usage)
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/**
 * Breadth-First Search Function
 * 
 * @param start - starting node for traversal
 * @param graph - adjacency list representation of graph
 * @param visited - boolean array to track visited nodes
 */
void bfs(int start, const vector<vector<int>>& graph, vector<bool>& visited) {
    queue<int> q;                    // Queue for BFS traversal
    q.push(start);                   // Add starting node to queue
    visited[start] = true;           // Mark starting node as visited

    while (!q.empty()) {
        int node = q.front();        // Get front node from queue
        q.pop();                     // Remove front node from queue
        cout << "Visited node: " << node << endl;

        // Explore all neighbors of current node
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                q.push(neighbor);          // Add unvisited neighbor to queue
                visited[neighbor] = true;  // Mark neighbor as visited
            }
        }
    }
}

int main() {
    int n = 6; // Number of nodes in graph
    vector<vector<int>> graph(n);
    
    // Create undirected graph using adjacency list
    // Each vector contains neighbors of that node
    graph[0] = {1, 2};  // Node 0 connects to nodes 1 and 2
    graph[1] = {0, 3, 4}; // Node 1 connects to nodes 0, 3, and 4
    graph[2] = {0};      // Node 2 connects to node 0
    graph[3] = {1};      // Node 3 connects to node 1
    graph[4] = {1, 5};   // Node 4 connects to nodes 1 and 5
    graph[5] = {4};      // Node 5 connects to node 4

    vector<bool> visited(n, false);  // Track visited nodes

    cout << "BFS traversal starting from node 0:\n";
    bfs(0, graph, visited);

    return 0;
}

/*
 * ALGORITHM ANALYSIS:
 * 
 * Key Features:
 * - Level-by-level exploration (breadth-first)
 * - Uses Queue data structure (FIFO principle)
 * - Visits all neighbors before going deeper
 * - Guarantees shortest path in unweighted graphs
 * 
 * Data Structures Used:
 * - Queue: Stores nodes to be visited (FIFO)
 * - Vector<bool>: Tracks visited nodes to avoid cycles
 * - Adjacency List: Graph representation
 * 
 * Complexity Analysis:
 * - Time Complexity: O(V + E) - visit each node and edge once
 * - Space Complexity: O(V) - queue size in worst case
 * 
 * Advantages:
 * - Guarantees shortest path in unweighted graphs
 * - Complete traversal of connected components
 * - Good for level-order processing
 * 
 * Disadvantages:
 * - High memory usage for wide graphs
 * - May not be optimal for deep graphs
 * - Cannot handle infinite graphs
 * 
 * Use Cases:
 * - Web crawling
 * - Social network analysis
 * - GPS navigation (unweighted)
 * - Level-order tree traversal
 * - Finding shortest path in unweighted graphs
 */
