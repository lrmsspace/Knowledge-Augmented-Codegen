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

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> countMap;
        for (int num : arr) {
            countMap[num]++;
        }

        unordered_set<int> occurrences;
        for (const auto& pair : countMap) {
            if (!occurrences.insert(pair.second).second) {
                return false; // Duplicate occurrence found
            }
        }

        return true; // All occurrences are unique          
    }
};
