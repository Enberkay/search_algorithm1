/*
 * BINARY SEARCH ALGORITHM
 * 
 * Category: Uninformed Search (Blind Search)
 * Description: Efficient search in sorted arrays using divide-and-conquer approach
 * 
 * Key Characteristics:
 * - Requires sorted array as input
 * - Divides search space in half each iteration
 * - Much faster than Linear Search for large datasets
 * - Uses divide-and-conquer strategy
 * 
 * Time Complexity: O(log n) - logarithmic time
 * Space Complexity: O(1) - constant space
 * 
 * Best for: Large sorted arrays
 * Worst for: Unsorted arrays (must sort first)
 */

#include <iostream>
using namespace std;

/**
 * Binary Search Function
 * 
 * @param arr[] - sorted input array to search in
 * @param size - size of the array
 * @param target - value to search for
 * @return index of target if found, -1 if not found
 */
int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        // Calculate middle point (prevents integer overflow)
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid; // Found: return the index
        } else if (arr[mid] < target) {
            left = mid + 1; // Target is in right half
        } else {
            right = mid - 1; // Target is in left half
        }
    }

    return -1; // Not found: return -1
}

int main() {
    // Sample data array (MUST be sorted)
    int data[] = {10, 20, 30, 40, 50, 60};
    int size = sizeof(data) / sizeof(data[0]);

    int target;
    cout << "Enter value to search: ";
    cin >> target;

    int result = binarySearch(data, size, target);

    if (result != -1) {
        cout << "Found " << target << " at index " << result << endl;
    } else {
        cout << "Value not found in array" << endl;
    }

    return 0;
}

/*
 * ALGORITHM ANALYSIS:
 * 
 * Code Breakdown:
 * - int left = 0, right = size - 1 - initialize search boundaries
 * - int mid = left + (right - left) / 2 - calculate middle (prevents overflow)
 * - if (arr[mid] == target) - check if middle element is target
 * - else if (arr[mid] < target) - target is in right half
 * - else - target is in left half
 * 
 * Complexity Analysis:
 * - Best Case: O(1) - target found at middle position
 * - Average Case: O(log n) - target found after log n comparisons
 * - Worst Case: O(log n) - target not found or at boundaries
 * - Space Complexity: O(1) - constant extra space
 * 
 * Important Notes:
 * - Array MUST be sorted before using Binary Search
 * - If array is unsorted, use std::sort() from <algorithm> first
 * - Much more efficient than Linear Search for large datasets
 * 
 * Use Cases:
 * - Large sorted arrays
 * - When array is frequently searched
 * - Database queries on indexed data
 * 
 * Comparison with Linear Search:
 * - Unsorted array → Use Linear Search
 * - Sorted array (large size) → Use Binary Search (much faster!)
 */
