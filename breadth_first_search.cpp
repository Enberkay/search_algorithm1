/*
Uninformed (Blind) Search
ไม่รู้ข้อมูลล่วงหน้า ไม่มี heuristic (เดาไม่ได้ว่าทางไหนดีกว่า)

Breadth-First Search (BFS) – ค้นหาแบบกว้างก่อน
โครงสร้างที่ใช้:
Graph แบบใช้ adjacency list
ใช้ queue เพื่อค้นหาแบบกว้างก่อน
ใช้ visited[] ป้องกันการเยี่ยมซ้ำ
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(int start, const vector<vector<int>>& graph, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << "visited node: " << node << endl;

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                q.push(neighbor);          // เพิ่มเพื่อนบ้านเข้า queue
                visited[neighbor] = true;  // mark ว่าเคยเยี่ยมแล้ว
            }
        }
    }
}

int main() {
    int n = 6; // จำนวน node
    vector<vector<int>> graph(n);
    // เพิ่ม edge แบบไม่ถ่วงน้ำหนัก (undirected)
    graph[0] = {1, 2};
    graph[1] = {0, 3, 4};
    graph[2] = {0};
    graph[3] = {1};
    graph[4] = {1, 5};
    graph[5] = {4};

    vector<bool> visited(n, false);

    cout << "BFS start at node 0:\n";
    bfs(0, graph, visited);

    return 0;
}

// | จุดเด่น       | รายละเอียด                                            |
// | ------------- | ----------------------------------------------------- |
// | ค้นหาแบบ      | "กว้างก่อน"                                           |
// | โครงสร้างหลัก | Queue                                                 |
// | ใช้ได้กับ     | Tree, Graph                                           |
// | เวลา (Time)   | O(V + E)                                              |
// | เหมาะกับ      | หาคำตอบที่ใกล้ที่สุด, shortest path (ถ้าไม่มี weight) |
