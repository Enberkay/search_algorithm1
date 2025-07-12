/*
 * BIDIRECTIONAL SEARCH ALGORITHM
 * 
 * Category: Informed Search (Heuristic Search)
 * Description: Search algorithm that explores from both start and goal simultaneously
 * 
 * Key Characteristics:
 * - Searches from both start and goal nodes
 * - Uses two BFS queues running simultaneously
 * - Stops when search frontiers meet
 * - Reduces search space significantly
 * - Guarantees shortest path in unweighted graphs
 * 
 * Time Complexity: O(b^(d/2)) - where b = branching factor, d = depth
 * Space Complexity: O(b^(d/2)) - two queues instead of one
 * 
 * Best for: Large graphs where start and goal are far apart
 * Worst for: Small graphs or when start/goal are close
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

/**
 * Print the complete path from start to goal
 * Combines paths from both forward and backward searches
 * 
 * @param meet - meeting point where searches intersect
 * @param parent_fwd - parent pointers from forward search
 * @param parent_bwd - parent pointers from backward search
 */
void printPath(int meet,
               unordered_map<int, int>& parent_fwd,
               unordered_map<int, int>& parent_bwd) {
    vector<int> path;

    // Trace back from meeting point to start
    int node = meet;
    while (parent_fwd.count(node)) {
        path.push_back(node);
        node = parent_fwd[node];
    }
    path.push_back(node); // Add start node
    reverse(path.begin(), path.end());

    // Trace forward from meeting point to goal
    node = meet;
    while (parent_bwd.count(node)) {
        node = parent_bwd[node];
        path.push_back(node);
    }

    // Display complete path
    cout << "\nPath found: ";
    for (int n : path) cout << n << " ";
    cout << endl;
}

/**
 * Bidirectional BFS Algorithm
 * 
 * @param graph - unweighted graph represented as adjacency list
 * @param start - starting node
 * @param goal - target node to reach
 * @return true if path found, false otherwise
 */
bool bidirectionalBFS(const vector<vector<int>>& graph, int start, int goal) {
    int n = graph.size();
    vector<bool> visited_fwd(n, false), visited_bwd(n, false); // Track visited nodes for each direction
    unordered_map<int, int> parent_fwd, parent_bwd;             // Parent pointers for path reconstruction

    queue<int> q_fwd, q_bwd; // Queues for forward and backward searches
    q_fwd.push(start); visited_fwd[start] = true;  // Start forward search
    q_bwd.push(goal);  visited_bwd[goal] = true;   // Start backward search

    while (!q_fwd.empty() && !q_bwd.empty()) {
        // Forward search (from start)
        int size_f = q_fwd.size();
        while (size_f--) {
            int current = q_fwd.front(); q_fwd.pop();
            for (int neighbor : graph[current]) {
                if (!visited_fwd[neighbor]) {
                    visited_fwd[neighbor] = true;
                    parent_fwd[neighbor] = current;
                    q_fwd.push(neighbor);

                    // Check if backward search has visited this node
                    if (visited_bwd[neighbor]) {
                        cout << "\nSearch frontiers meet at node: " << neighbor << endl;
                        printPath(neighbor, parent_fwd, parent_bwd);
                        return true;
                    }
                }
            }
        }

        // Backward search (from goal)
        int size_b = q_bwd.size();
        while (size_b--) {
            int current = q_bwd.front(); q_bwd.pop();
            for (int neighbor : graph[current]) {
                if (!visited_bwd[neighbor]) {
                    visited_bwd[neighbor] = true;
                    parent_bwd[neighbor] = current;
                    q_bwd.push(neighbor);

                    // Check if forward search has visited this node
                    if (visited_fwd[neighbor]) {
                        cout << "\nSearch frontiers meet at node: " << neighbor << endl;
                        printPath(neighbor, parent_fwd, parent_bwd);
                        return true;
                    }
                }
            }
        }
    }

    cout << "\nNo path found from " << start << " to " << goal << endl;
    return false;
}

int main() {
    int n = 7; // Number of nodes
    vector<vector<int>> graph(n);

    // Create undirected unweighted graph
    // Each vector contains neighbors of that node
    graph[0] = {1, 2};  // Node 0 connects to nodes 1 and 2
    graph[1] = {0, 3};  // Node 1 connects to nodes 0 and 3
    graph[2] = {0, 4};  // Node 2 connects to nodes 0 and 4
    graph[3] = {1, 5};  // Node 3 connects to nodes 1 and 5
    graph[4] = {2, 5};  // Node 4 connects to nodes 2 and 5
    graph[5] = {3, 4, 6}; // Node 5 connects to nodes 3, 4, and 6
    graph[6] = {5};      // Node 6 connects to node 5

    int start = 0;
    int goal = 6;

    cout << "\nBidirectional BFS Search from " << start << " to " << goal << ":\n";
    bidirectionalBFS(graph, start, goal);
    return 0;
}

/*
 * ALGORITHM ANALYSIS:
 * 
 * Key Features:
 * - Two simultaneous BFS searches
 * - Forward search from start node
 * - Backward search from goal node
 * - Stops when search frontiers meet
 * - Guarantees shortest path in unweighted graphs
 * 
 * How it works:
 * - Start two BFS queues simultaneously
 * - Forward queue explores from start
 * - Backward queue explores from goal
 * - When a node is visited by both searches, path is found
 * - Combine paths from both directions
 * 
 * Data Structures Used:
 * - Two Queues: Forward and backward BFS
 * - Two Vector<bool>: Track visited nodes for each direction
 * - Two Unordered Maps: Store parent pointers for path reconstruction
 * - Adjacency List: Graph representation
 * 
 * Complexity Analysis:
 * - Time Complexity: O(b^(d/2)) - searches meet halfway
 * - Space Complexity: O(b^(d/2)) - two queues instead of one
 * 
 * Advantages:
 * - Much faster than unidirectional search
 * - Reduces search space significantly
 * - Guarantees shortest path
 * - Good for large graphs
 * 
 * Disadvantages:
 * - More complex implementation
 * - Requires bidirectional graph
 * - Memory usage can be high
 * - Not suitable for weighted graphs
 * 
 * Use Cases:
 * - Large social networks
 * - Web crawling
 * - Network routing
 * - Game AI pathfinding
 * - Database queries
 * 
 * Comparison with unidirectional BFS:
 * | Aspect        | Unidirectional BFS | Bidirectional BFS |
 * |---------------|-------------------|-------------------|
 * | Search Space  | O(b^d)            | O(b^(d/2))        |
 * | Time          | O(b^d)            | O(b^(d/2))        |
 * | Memory        | O(b^d)            | O(b^(d/2))        |
 * | Complexity    | Simple            | More complex       |
 * | Applicability | Any graph         | Bidirectional only |
 * 
 * Note: Bidirectional search is most effective when start and goal are far apart
 */
