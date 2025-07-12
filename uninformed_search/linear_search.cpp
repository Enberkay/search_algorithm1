/*
 * LINEAR SEARCH ALGORITHM
 * 
 * Category: Uninformed Search (Blind Search)
 * Description: Sequential search through array elements from left to right
 * 
 * Key Characteristics:
 * - No prior knowledge or heuristic used
 * - Searches element by element sequentially
 * - Stops immediately when target is found
 * - Returns -1 if target not found
 * 
 * Time Complexity: O(n) - linear time
 * Space Complexity: O(1) - constant space
 * 
 * Best for: Unsorted arrays, small datasets
 * Worst for: Large sorted arrays (use Binary Search instead)
 */

#include <iostream>
using namespace std;

/**
 * Linear Search Function
 * 
 * @param arr[] - input array to search in
 * @param size - size of the array
 * @param target - value to search for
 * @return index of target if found, -1 if not found
 */
int linearSearch(int arr[], int size, int target) {
    // Iterate through each element in the array
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // Found: return the index of target
        }
    }
    return -1; // Not found: return -1
}

int main() {
    // Sample data array (unsorted)
    int data[] = {10, 25, 30, 45, 50};
    int size = sizeof(data) / sizeof(data[0]);
    
    int target;
    cout << "Enter value to search: ";
    cin >> target;

    int result = linearSearch(data, size, target);

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
 * - for (int i = 0; i < size; i++) - iterate through each element
 * - if (arr[i] == target) - check if current element matches target
 * - return i - return index when found
 * - return -1 - return -1 when not found
 * 
 * Complexity Analysis:
 * - Best Case: O(1) - target found at first position
 * - Average Case: O(n/2) - target found in middle
 * - Worst Case: O(n) - target at end or not found
 * - Space Complexity: O(1) - constant extra space
 * 
 * Use Cases:
 * - Small unsorted arrays
 * - When simplicity is preferred over efficiency
 * - When array is rarely searched
 */

