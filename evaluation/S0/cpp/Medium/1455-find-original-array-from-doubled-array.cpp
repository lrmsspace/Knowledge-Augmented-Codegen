// Source: https://leetcode.com/problems/find-original-array-from-doubled-array/   |   Difficulty: Medium
//
// Problem Description:
// An integer array original is transformed into a doubled array changed by appending twice the value of every element in original, and then randomly shuffling the resulting array.
//
// Given an array changed, return original if changed is a doubled array. If changed is not a doubled array, return an empty array. The elements in original may be returned in any order.
//
// Example:
// Input: changed = [1,3,4,2,6,8]
// Output: [1,3,4]
// Explanation: One possible original array could be [1,3,4]:
// - Twice the value of 1 is 1 * 2 = 2.
// - Twice the value of 3 is 3 * 2 = 6.
// - Twice the value of 4 is 4 * 2 = 8.
// Other original arrays could be [4,3,1] or [3,1,4].
//
// Constraints:
// 1 <= changed.length <= 105
// 	0 <= changed[i] <= 105
//

class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        int n = changed.size();
        if (n % 2 != 0) return {};

        sort(changed.begin(), changed.end());
        unordered_map<int, int> countMap;
        for (int num : changed) {
            countMap[num]++;
        }

        vector<int> original;
        for (int num : changed) {
            if (countMap[num] == 0) continue;

            if (num == 0) {
                if (countMap[num] < 2) return {};
                countMap[num] -= 2;
                original.push_back(num);
            } else {
                int doubleNum = num * 2;
                if (countMap[doubleNum] == 0) return {};
                countMap[num]--;
                countMap[doubleNum]--;
                original.push_back(num);
            }
        }

        return original;            
    }
};
