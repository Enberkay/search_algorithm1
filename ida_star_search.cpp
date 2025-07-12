#include <iostream>
#include <vector>
#include <utility>
#include <limits>
using namespace std;

using Edge = pair<int, int>; // pair<ปลายทาง, ค่าระยะทาง>
const int INF = numeric_limits<int>::max();

// ฟังก์ชัน DFS แบบมีการจำกัด f(n)
bool dfs(int node, int goal, int g, int limit,
         const vector<vector<Edge>>& graph, const vector<int>& heuristic,
         vector<bool>& visited, int& next_limit) {
    int f = g + heuristic[node]; // f(n) = g(n) + h(n)

    // ถ้า f เกิน limit → รอรอบถัดไป
    if (f > limit) {
        next_limit = min(next_limit, f);
        return false;
    }

    // แสดงสถานะปัจจุบัน
    cout << "เยี่ยม node: " << node
         << " (g = " << g
         << ", h = " << heuristic[node]
         << ", f = " << f << ")\n";

    if (node == goal) {
        cout << "\n\u2705 ถึงเป้าหมายที่ node " << node << " แล้ว! (cost: " << g << ")\n";
        return true;
    }

    visited[node] = true;

    // ลองเดินไปเพื่อนบ้านแต่ละ node
    for (auto [neighbor, cost] : graph[node]) {
        if (!visited[neighbor]) {
            if (dfs(neighbor, goal, g + cost, limit, graph, heuristic, visited, next_limit)) {
                return true; // เจอเป้าหมาย
            }
        }
    }

    visited[node] = false; // ถอยกลับเพื่อลองทางอื่น
    return false;
}

// IDA* Algorithm: วนหลายรอบ เพิ่ม limit ตาม f(n)
void idaStar(int start, int goal,
             const vector<vector<Edge>>& graph, const vector<int>& heuristic) {
    int limit = heuristic[start]; // เริ่มต้นด้วย h(start)

    while (true) {
        cout << "\n\U0001F504 รอบใหม่: limit = " << limit << "\n";
        vector<bool> visited(graph.size(), false);
        int next_limit = INF;

        // DFS ในรอบนี้
        if (dfs(start, goal, 0, limit, graph, heuristic, visited, next_limit)) {
            return; // เจอแล้ว
        }

        if (next_limit == INF) {
            cout << "\n\u274C ไม่เจอเป้าหมายในทุกความลึก\n";
            return;
        }

        limit = next_limit; // เพิ่ม limit เพื่อวนรอบใหม่
    }
}

int main() {
    int n = 6;
    vector<vector<Edge>> graph(n);

    // โครงสร้างกราฟ: กำหนดปลายทางและ cost
    graph[0] = {{1, 2}, {2, 4}};
    graph[1] = {{3, 2}, {4, 3}};
    graph[2] = {{4, 2}};
    graph[3] = {{5, 1}};
    graph[4] = {{5, 2}};
    graph[5] = {}; // goal

    // heuristic (h(n)): ค่าคาดการณ์ระยะห่างถึง goal (node 5)
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

    cout << "\n\U0001F9E0 IDA* Search จาก node " << start << " \u2192 " << goal << ":\n";
    idaStar(start, goal, graph, heuristic);
    return 0;
}
