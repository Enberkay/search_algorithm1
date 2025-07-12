#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
using namespace std;

// Edge = pair<destination node, cost>
using Edge = pair<int, int>;

// โครงสร้าง node สำหรับ priority queue
struct Node {
    int id;     // หมายเลข node
    int g;      // cost จริงจากต้นทางถึง node นี้
    int f;      // f(n) = g(n) + h(n)

    // ให้ priority queue จัดลำดับจาก f น้อยไปมาก (min-heap)
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

// A* Algorithm
void aStar(int start, int goal, const vector<vector<Edge>>& graph, const vector<int>& heuristic) {
    int n = graph.size();
    vector<bool> visited(n, false);        // เก็บว่า node ไหนเยี่ยมแล้ว
    vector<int> cost(n, INT_MAX);          // เก็บค่า g(n) ต่ำสุดที่เคยเจอ

    // Priority queue เรียงตาม f(n) = g(n) + h(n)
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({start, 0, heuristic[start]}); // node แรกมี g = 0, f = h(start)
    cost[start] = 0;

    while (!pq.empty()) {
        Node current = pq.top(); pq.pop();
        int node = current.id;

        // ถ้าเคยเยี่ยมแล้วข้ามเลย
        if (visited[node]) continue;
        visited[node] = true;

        // แสดงสถานะปัจจุบัน
        cout << "\nเยี่ยม node: " << node
             << " (g = " << current.g
             << ", h = " << heuristic[node]
             << ", f = " << current.f << ")\n";

        // ถ้าถึงเป้าหมาย
        if (node == goal) {
            cout << "\n\u2705 ถึงเป้าหมายที่ node " << node
                 << " แล้ว! (cost ทั้งหมด: " << current.g << ")\n";
            return;
        }

        // ตรวจสอบเพื่อนบ้าน
        for (auto [neighbor, weight] : graph[node]) {
            int newG = current.g + weight;             // ค่า g ใหม่
            int newF = newG + heuristic[neighbor];     // ค่า f = g + h

            if (newG < cost[neighbor]) {
                cost[neighbor] = newG;
                pq.push({neighbor, newG, newF});
            }
        }
    }

    cout << "\n\u274C ไม่สามารถไปถึงเป้าหมายได้\n";
}

int main() {
    int n = 6; // จำนวน node
    vector<vector<Edge>> graph(n);

    // กราฟแบบ weighted (ไม่มี loop)
    // node 0 เชื่อมไป node 1 (cost=2) และ node 2 (cost=4)
    graph[0] = {{1, 2}, {2, 4}};
    graph[1] = {{3, 2}, {4, 3}};
    graph[2] = {{4, 2}};
    graph[3] = {{5, 1}};
    graph[4] = {{5, 2}};
    graph[5] = {}; // ปลายทางไม่มีอะไรต่อ

    // heuristic (h(n)) = ค่าคาดเดาระยะห่างถึง goal = node 5
    vector<int> heuristic = {
        7, // h(0)
        6, // h(1)
        2, // h(2)
        1, // h(3)
        3, // h(4)
        0  // h(5) = goal
    };

    int start = 0;
    int goal = 5;

    cout << "\n\U0001F9E0 A* Search จาก node " << start << " \u2192 " << goal << ":\n";
    aStar(start, goal, graph, heuristic);

    return 0;
}
