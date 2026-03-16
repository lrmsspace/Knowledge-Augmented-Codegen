// Source: https://leetcode.com/problems/unique-number-of-occurrences/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers arr, return true if the number of occurrences of each value in the array is unique or false otherwise.
//
// Example:
// Input: arr = [1,2,2,1,1,3]
// Output: true
// Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.
//
// Constraints:
// 1 <= arr.length <= 1000
// 	-1000 <= arr[i] <= 1000
//

bool uniqueOccurrences(int* arr, int arrSize) {
    int count[2001] = {0};
    int occurrences[1001] = {0};

    for (int i = 0; i < arrSize; i++) {
        count[arr[i] + 1000]++;
    }

    for (int i = 0; i < 2001; i++) {
        if (count[i] > 0) {
            occurrences[count[i]]++;
            if (occurrences[count[i]] > 1) {
                return false;
            }
        }
    }

    return true;        
}
