// Uninformed (Blind) Search
// ไม่รู้ข้อมูลล่วงหน้า ไม่มี heuristic (เดาไม่ได้ว่าทางไหนดีกว่า)

// Linear Search คืออะไร?
// เป็นการค้นหาข้อมูลใน array ทีละตัวจากซ้ายไปขวา
// ถ้าพบค่าที่ต้องการก็หยุดทันที
// หากไม่พบเลย ก็คืนค่าที่บอกว่า "ไม่เจอ"

#include <iostream>
using namespace std;

// ฟังก์ชันค้นหาแบบ Linear Search
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // เจอ: คืนตำแหน่งของค่าที่หาเจอ
        }
    }
    return -1; // ไม่เจอ
}

int main() {
    int data[] = {10, 25, 30, 45, 50};
    int size = sizeof(data) / sizeof(data[0]);
    
    int target;
    cout << "fill in what u want to search: ";
    cin >> target;

    int result = linearSearch(data, size, target);

    if (result != -1) {
        cout << "found " << target << " at index " << result << endl;
    } else {
        cout << "Not found value in array" << endl;
    }

    return 0;
}

// | ส่วน                             | ความหมาย               |
// | -------------------------------- | ---------------------- |
// | `for (int i = 0; i < size; i++)` | วน loop ทุกตัวใน array |
// | `if (arr[i] == target)`          | ถ้าตรงกับค่าที่ต้องการ |
// | `return i`                       | ส่ง index กลับเมื่อเจอ |
// | `return -1`                      | ส่ง -1 ถ้าไม่เจอเลย    |

// เวลาในการทำงาน (Time Complexity)
// Best case: O(1) → ถ้าเจอที่ index 0
// Worst case: O(n) → ถ้าเจอท้ายสุด หรือไม่เจอเลย
// Space: O(1)

