/*
Uninformed (Blind) Search
ไม่รู้ข้อมูลล่วงหน้า ไม่มี heuristic (เดาไม่ได้ว่าทางไหนดีกว่า)

Iterative Deepening Search (IDS) หรือ Iterative Deepening Depth-First Search (IDDFS) ไปพร้อมกันเลย
อันนี้เป็นอัลกอริธึมที่ รวมข้อดีของ DFS และ BFS ไว้ด้วยกัน!

IDS คืออะไร?
IDS = DFS ที่วนทำหลายรอบ โดยจำกัดความลึกในแต่ละรอบให้เพิ่มขึ้นเรื่อย ๆ
(เรียกอีกชื่อว่า Iterative Deepening DFS หรือ IDDFS)

แนวคิด:
เริ่มจาก DFS ที่ลึกแค่ 0 → ถ้ายังไม่เจอ → ลึกขึ้นเป็น 1 → 2 → ... จนกว่าจะเจอ
เหมือน BFS ที่ไล่ระดับ (level-order) แต่ใช้ DFS ล้วน ๆ

| ปัญหา                                  | วิธีแก้                                     |
| -------------------------------------- | ------------------------------------------- |
| DFS อาจหลงไปทางลึกผิด ๆ → ไม่เจอทางออก | IDS ใช้ DFS แบบจำกัดความลึก (ไม่หลงลึกเกิน) |
| BFS ใช้ memory เยอะ (queue ใหญ่)       | IDS ใช้ memory แบบ DFS → **ประหยัดมาก**     |

*/

#include <iostream>
#include <vector>
using namespace std;

bool dls(int node, int target, int depth, const vector<vector<int>>& graph, vector<bool>& visited) {
    if (depth < 0) return false;
    if (node == target) {
        cout << "found target at node: " << node << endl;
        return true;
    }

    visited[node] = true;
    cout << "visited node: " << node << " (depth left: " << depth << ")" << endl;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            if (dls(neighbor, target, depth - 1, graph, visited)) {
                return true;
            }
        }
    }

    return false;
}

bool iddfs(int start, int target, int maxDepth, const vector<vector<int>>& graph) {
    for (int depth = 0; depth <= maxDepth; ++depth) {
        cout << "\nTry the depth = " << depth << endl;
        vector<bool> visited(graph.size(), false);
        if (dls(start, target, depth, graph, visited)) {
            return true;
        }
    }
    return false;
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

    int start = 0;
    int goal = 5;
    int maxDepth = 4;

    cout << "Iterative Deepening DFS from node " << start << " → " << goal << ":\n";
    if (!iddfs(start, goal, maxDepth, graph)) {
        cout << "not found target in depth = " << maxDepth << endl;
    }

    return 0;
}

// อธิบาย:
// iddfs(...) → ลอง DFS ด้วย depth ที่เพิ่มขึ้นทีละ 1
// dls(...) → DFS แบบจำกัดความลึก (Depth-Limited Search)
// เมื่อเจอ node เป้าหมาย → หยุดทันที

// สรุป: IDS (IDDFS)
// | รายการ        | รายละเอียด                                               |
// | ------------- | -------------------------------------------------------- |
// | ประเภท        | Uninformed Search                                        |
// | โครงสร้างหลัก | DFS + Loop ตาม depth                                     |
// | ทำงานอย่างไร  | DFS แบบจำกัดความลึก → เพิ่มลึกทีละรอบ                    |
// | ข้อดี         | ใช้ memory น้อย (เหมือน DFS) + หาทางสั้นสุด (เหมือน BFS) |
// | Time          | O(b^d) (*ซ้ำรอบเยอะหน่อย*)                               |
// | Space         | O(d) → **ประหยัดมาก!**                                   |

// | อัลกอริธึม | ใช้ Memory | หา path สั้นสุด | เสี่ยงหลง |
// | ---------- | ---------- | --------------- | --------- |
// | DFS        | น้อยมาก    | ❌               | ✅         |
// | BFS        | เยอะมาก    | ✅               | ❌         |
// | **IDS**    | ✅ ต่ำ      | ✅               | ❌         |
