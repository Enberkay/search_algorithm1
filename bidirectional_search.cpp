#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

// แสดงเส้นทางจาก start ถึง goal โดยรวม path จากทั้ง 2 ฝั่ง
void printPath(int meet,
               unordered_map<int, int>& parent_fwd,
               unordered_map<int, int>& parent_bwd) {
    vector<int> path;

    // ไล่ย้อนกลับจากจุดเจอ → start
    int node = meet;
    while (parent_fwd.count(node)) {
        path.push_back(node);
        node = parent_fwd[node];
    }
    path.push_back(node); // start
    reverse(path.begin(), path.end());

    // ไล่ต่อจากจุดเจอ → goal
    node = meet;
    while (parent_bwd.count(node)) {
        node = parent_bwd[node];
        path.push_back(node);
    }

    // แสดงผลลัพธ์
    cout << "\n\u2705 Path: ";
    for (int n : path) cout << n << " ";
    cout << endl;
}

// Bidirectional BFS สำหรับกราฟไม่มีน้ำหนัก
bool bidirectionalBFS(const vector<vector<int>>& graph, int start, int goal) {
    int n = graph.size();
    vector<bool> visited_fwd(n, false), visited_bwd(n, false); // เยี่ยมแล้วฝั่งต้น/ปลาย
    unordered_map<int, int> parent_fwd, parent_bwd;             // ทางย้อนกลับ

    queue<int> q_fwd, q_bwd; // คิวของแต่ละฝั่ง
    q_fwd.push(start); visited_fwd[start] = true;
    q_bwd.push(goal);  visited_bwd[goal] = true;

    while (!q_fwd.empty() && !q_bwd.empty()) {
        // ฝั่งต้นทาง
        int size_f = q_fwd.size();
        while (size_f--) {
            int current = q_fwd.front(); q_fwd.pop();
            for (int neighbor : graph[current]) {
                if (!visited_fwd[neighbor]) {
                    visited_fwd[neighbor] = true;
                    parent_fwd[neighbor] = current;
                    q_fwd.push(neighbor);

                    // ถ้าอีกฝั่งเคยเยี่ยม node นี้ → เจอกัน!
                    if (visited_bwd[neighbor]) {
                        cout << "\n\U0001F3AF เจอกันที่ node: " << neighbor << endl;
                        printPath(neighbor, parent_fwd, parent_bwd);
                        return true;
                    }
                }
            }
        }

        // ฝั่งปลายทาง
        int size_b = q_bwd.size();
        while (size_b--) {
            int current = q_bwd.front(); q_bwd.pop();
            for (int neighbor : graph[current]) {
                if (!visited_bwd[neighbor]) {
                    visited_bwd[neighbor] = true;
                    parent_bwd[neighbor] = current;
                    q_bwd.push(neighbor);

                    if (visited_fwd[neighbor]) {
                        cout << "\n\U0001F3AF เจอกันที่ node: " << neighbor << endl;
                        printPath(neighbor, parent_fwd, parent_bwd);
                        return true;
                    }
                }
            }
        }
    }

    cout << "\n\u274C ไม่พบเส้นทางเชื่อมจาก " << start << " ถึง " << goal << endl;
    return false;
}

int main() {
    int n = 7;
    vector<vector<int>> graph(n);

    // สร้างกราฟแบบไม่มีน้ำหนัก (undirected)
    graph[0] = {1, 2};
    graph[1] = {0, 3};
    graph[2] = {0, 4};
    graph[3] = {1, 5};
    graph[4] = {2, 5};
    graph[5] = {3, 4, 6};
    graph[6] = {5};

    int start = 0;
    int goal = 6;

    cout << "\n\U0001F504 Bidirectional BFS Search จาก " << start << " \u2192 " << goal << ":\n";
    bidirectionalBFS(graph, start, goal);
    return 0;
}
