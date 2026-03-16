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

class Solution {
public:
    bool canReorderDoubled(vector<int>& arr) {
        unordered_map<int, int> count;
        for (int x : arr) {
            count[x]++;
        }

        vector<int> keys;
        for (const auto& [key, _] : count) {
            keys.push_back(key);
        }
        sort(keys.begin(), keys.end(), [](int a, int b) {
            return abs(a) < abs(b);
        });

        for (int x : keys) {
            if (count[2 * x] < count[x]) {
                return false;
            }
            count[2 * x] -= count[x];
        }

        return true;            
    }
};
