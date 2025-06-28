// Uninformed (Blind) Search
// ไม่รู้ข้อมูลล่วงหน้า ไม่มี heuristic (เดาไม่ได้ว่าทางไหนดีกว่า)

// Binary Search คือการค้นหาใน array ที่เรียงลำดับแล้วเท่านั้น (sorted)
// โดยการแบ่งครึ่งซ้าย–ขวา ไปเรื่อย ๆ เพื่อหาค่าที่ต้องการ
// เร็วกว่า Linear Search มาก (เวลา O(log n))

#include <iostream>
using namespace std;

// ฟังก์ชันค้นหาแบบ Binary Search
int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; // หาจุดกึ่งกลาง

        if (arr[mid] == target) {
            return mid; // เจอ
        } else if (arr[mid] < target) {
            left = mid + 1; // ค่าที่หาอยู่ด้านขวา
        } else {
            right = mid - 1; // ค่าที่หาอยู่ด้านซ้าย
        }
    }

    return -1; // ไม่เจอ
}

int main() {
    // ต้องเรียงลำดับแล้ว
    int data[] = {10, 20, 30, 40, 50, 60};
    int size = sizeof(data) / sizeof(data[0]);

    int target;
    cout << "ป้อนค่าที่ต้องการค้นหา: ";
    cin >> target;

    int result = binarySearch(data, size, target);

    if (result != -1) {
        cout << "เจอค่า " << target << " ที่ตำแหน่ง index " << result << endl;
    } else {
        cout << "ไม่พบค่าที่ต้องการค้นหาใน array" << endl;
    }

    return 0;
}

// | บรรทัด                                 | ความหมาย                 |
// | -------------------------------------- | ------------------------ |
// | `int left = 0, right = size - 1;`      | เริ่มค้นหาที่หัว–ท้าย    |
// | `int mid = left + (right - left) / 2;` | หาค่ากลางแบบไม่ overflow |
// | `if (arr[mid] == target)`              | ถ้าเจอเลย                |
// | `else if (arr[mid] < target)`          | ถ้าค่าที่หาอยู่ด้านขวา   |
// | `else`                                 | ถ้าอยู่ด้านซ้าย          |

// | กรณี  | เวลา                        |
// | ----- | --------------------------- |
// | Best  | O(1) → ถ้าเจอที่กลางเลย     |
// | Worst | O(log n) → หารครึ่งเรื่อย ๆ |
// | Space | O(1)                        |

// ข้อควรระวัง:
// ใช้ได้เฉพาะ array ที่เรียงลำดับแล้ว

// ถ้า array ไม่เรียง ให้ใช้ std::sort() จาก <algorithm> ก่อน


// | อย่างไหนดีกว่า?                                        |
// | ------------------------------------------------------ |
// | Array ไม่เรียง → ใช้ Linear                            |
// | Array เรียงแล้ว และ size ใหญ่ → ใช้ Binary (เร็วกว่า!) |
