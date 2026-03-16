// Source: https://leetcode.com/problems/array-of-doubled-pairs/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array of even length arr, return true if it is possible to reorder arr such that arr[2 * i + 1] = 2 * arr[2 * i] for every 0 <= i < len(arr) / 2, or false otherwise.
//
// Example:
// Input: arr = [3,1,3,6]
// Output: false
//
// Constraints:
// 2 <= arr.length <= 3 * 104
// 	arr.length is even.
// 	-105 <= arr[i] <= 105
//

bool canReorderDoubled(int* arr, int arrSize) {
    int count[200001] = {0};
    for (int i = 0; i < arrSize; i++) {
        count[arr[i] + 100000]++;
    }

    for (int i = -100000; i <= 100000; i++) {
        if (count[i + 100000] == 0) {
            continue;
        }
        if (i < 0) {
            if (i % 2 != 0 || count[i + 100000] > count[(i / 2) + 100000]) {
                return false;
            }
            count[(i / 2) + 100000] -= count[i + 100000];
        } else {
            if (count[i + 100000] > count[(2 * i) + 100000]) {
                return false;
            }
            count[(2 * i) + 100000] -= count[i + 100000];
        }
    }
    return true;        
}
