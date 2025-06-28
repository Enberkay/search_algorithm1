/*
Uninformed (Blind) Search
ไม่รู้ข้อมูลล่วงหน้า ไม่มี heuristic (เดาไม่ได้ว่าทางไหนดีกว่า)

Depth-First Search (DFS) – ค้นหาแบบลึกก่อน
โครงสร้างที่ใช้:
ใช้ stack หรือ recursion
ใช้ visited[] เช่นเดียวกับ BFS
*/

#include <iostream>
#include <vector>
using namespace std;

void dfs(int node, const vector<vector<int>>& graph, vector<bool>& visited) {
    visited[node] = true;
    cout << "visited node: " << node << endl;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited);  // เรียกตัวเองซ้ำ → ลึกก่อน
        }
    }
}

int main() {
    int n = 6;
    vector<vector<int>> graph(n);
    graph[0] = {1, 2};
    graph[1] = {0, 3, 4};
    graph[2] = {0};
    graph[3] = {1};
    graph[4] = {1, 5};
    graph[5] = {4};

    vector<bool> visited(n, false);

    cout << "DFS start at node 0:\n";
    dfs(0, graph, visited);

    return 0;
}

// | จุดเด่น       | รายละเอียด                               |
// | ------------- | ---------------------------------------- |
// | ค้นหาแบบ      | "ลึกก่อน"                                |
// | โครงสร้างหลัก | Recursion หรือ Stack                     |
// | ใช้ได้กับ     | Tree, Graph                              |
// | เวลา (Time)   | O(V + E)                                 |
// | เหมาะกับ      | ตรวจสอบ connectivity, ตรวจ loop, เดินเกม |

// สรุปเปรียบเทียบ BFS vs DFS
// | หัวข้อ     | BFS                | DFS                        |
// | ---------- | ------------------ | -------------------------- |
// | โครงสร้าง  | Queue              | Stack หรือ Recursion       |
// | เดินทางแบบ | กว้างก่อน          | ลึกก่อน                    |
// | เหมาะกับ   | หาทางที่ใกล้ที่สุด | สำรวจทั้งหมด, หาทางซับซ้อน |
// | เวลา       | O(V + E)           | O(V + E)                   |
