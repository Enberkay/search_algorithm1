/*
Uninformed (Blind) Search
ไม่รู้ข้อมูลล่วงหน้า ไม่มี heuristic (เดาไม่ได้ว่าทางไหนดีกว่า)

Uniform Cost Search (UCS)
โครงสร้างที่ใช้:
Priority Queue (min-heap) เพื่อเลือก node ที่มี cost น้อยที่สุดก่อน
ใช้ใน Graph ที่มีน้ำหนัก edge (weighted graph)

UCS (Uniform Cost Search) คือ BFS ที่รองรับ edge ที่มีน้ำหนัก (weight)
แต่ ต่างกันเล็กน้อยในวิธีเลือก node ถัดไป
*/
#include <iostream>
#include <vector>
#include <queue>
#include <utility> // for pair
using namespace std;

// โครงสร้าง edge: pair<ปลายทาง, cost>
using Edge = pair<int, int>;

// ใช้ pair<cost, node> ใน priority queue เพื่อจัดลำดับตาม cost
void ucs(int start, const vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> cost(n, INT_MAX); // เก็บระยะทางต่ำสุดที่เจอ

    // Min-heap: priority queue เรียงจาก cost น้อย → มาก
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    cost[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int currCost = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (visited[node]) continue;
        visited[node] = true;

        cout << "visited node: " << node << " with cost = " << currCost << endl;

        for (auto [neighbor, weight] : graph[node]) {
            int newCost = currCost + weight;
            if (newCost < cost[neighbor]) {
                cost[neighbor] = newCost;
                pq.push({newCost, neighbor});
            }
        }
    }

    // แสดงผลลัพธ์
    cout << "\nCost minimum from node " << start << " go to each node:\n";
    for (int i = 0; i < n; ++i) {
        cout << "go to node " << i << " : cost = " << cost[i] << endl;
    }
}

int main() {
    int n = 6;
    vector<vector<Edge>> graph(n);

    // ใส่ edge แบบมีน้ำหนัก
    graph[0] = {{1, 2}, {2, 4}};
    graph[1] = {{0, 2}, {3, 7}, {4, 1}};
    graph[2] = {{0, 4}, {4, 3}};
    graph[3] = {{1, 7}, {5, 1}};
    graph[4] = {{1, 1}, {2, 3}, {5, 5}};
    graph[5] = {{3, 1}, {4, 5}};

    cout << "Uniform Cost Search start at node 0:\n";
    ucs(0, graph);

    return 0;
}

// | บรรทัด                         | ความหมาย                               |
// | ------------------------------ | -------------------------------------- |
// | `priority_queue<...>`          | คิวลำดับความสำคัญ (ตาม cost ต่ำสุด)    |
// | `cost[]`                       | เก็บค่าระยะทางต่ำสุดที่ไปถึงแต่ละ node |
// | `visited[]`                    | ป้องกันการวนลูป                        |
// | `pq.push({newCost, neighbor})` | เพิ่มเส้นทางใหม่ที่ดีกว่า              |

// สรุป UCS
// | รายการ        | รายละเอียด                                                          |
// | ------------- | ------------------------------------------------------------------- |
// | ประเภท        | Uninformed Search                                                   |
// | โครงสร้างหลัก | Priority Queue (Min-Heap)                                           |
// | เหมาะสำหรับ   | หาทางที่มี **ต้นทุนต่ำสุด**                                         |
// | เงื่อนไข edge | ต้องมีน้ำหนัก ≥ 0                                                   |
// | เวลา (Time)   | O(E log V)                                                          |
// | ความคล้ายกับ  | Dijkstra’s Algorithm (จริง ๆ แล้ว UCS = Dijkstra ที่ไม่รู้เป้าหมาย) |


// เปรียบเทียบ BFS vs UCS
// | หัวข้อ                  | BFS (ไม่มี cost)                      | UCS (มี cost)    |
// | ----------------------- | ------------------------------------- | ---------------- |
// | ใช้ Queue แบบ           | ธรรมดา                                | Priority Queue   |
// | เลือก node ตาม          | ระยะทาง (level)                       | ค่าต้นทุน (cost) |
// | หา shortest path ได้ไหม | ได้เฉพาะกรณีทุก edge มีน้ำหนักเท่ากัน | ได้ทุกกรณี       |
