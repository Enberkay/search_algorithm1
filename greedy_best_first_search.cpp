#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

using Edge = pair<int, int>; // pair<ปลายทาง, cost>

// โครงสร้าง node สำหรับ priority queue ตาม heuristic อย่างเดียว
struct Node {
    int id;  // หมายเลข node
    int h;   // heuristic h(n)

    bool operator>(const Node& other) const {
        return h > other.h; // min-heap ตาม h(n)
    }
};

void greedyBestFirstSearch(int start, int goal,
                           const vector<vector<Edge>>& graph, const vector<int>& heuristic) {
    int n = graph.size();
    vector<bool> visited(n, false);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({start, heuristic[start]});

    while (!pq.empty()) {
        Node current = pq.top(); pq.pop();
        int node = current.id;

        if (visited[node]) continue;
        visited[node] = true;

        cout << "\nเยี่ยม node: " << node
             << " (h = " << heuristic[node] << ")\n";

        if (node == goal) {
            cout << "\n\u2705 ถึงเป้าหมายที่ node " << node << " แล้ว!\n";
            return;
        }

        for (auto [neighbor, cost] : graph[node]) {
            if (!visited[neighbor]) {
                pq.push({neighbor, heuristic[neighbor]});
            }
        }
    }

    cout << "\n\u274C ไม่สามารถไปถึงเป้าหมายได้\n";
}

int main() {
    int n = 6;
    vector<vector<Edge>> graph(n);

    // กราฟแบบไม่มีลูป
    graph[0] = {{1, 2}, {2, 4}};
    graph[1] = {{3, 2}, {4, 3}};
    graph[2] = {{4, 2}};
    graph[3] = {{5, 1}};
    graph[4] = {{5, 2}};
    graph[5] = {};

    vector<int> heuristic = {
        7, // h(0)
        6, // h(1)
        2, // h(2)
        1, // h(3)
        3, // h(4)
        0  // h(5)
    };

    int start = 0;
    int goal = 5;

    cout << "\n\U0001F9E0 Greedy Best-First Search จาก node " << start << " \u2192 " << goal << ":\n";
    greedyBestFirstSearch(start, goal, graph, heuristic);
    return 0;
}
