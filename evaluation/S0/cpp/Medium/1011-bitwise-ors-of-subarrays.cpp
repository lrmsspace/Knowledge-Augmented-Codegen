// Source: https://leetcode.com/problems/bitwise-ors-of-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr, return the number of distinct bitwise ORs of all the non-empty subarrays of arr.
//
// The bitwise OR of a subarray is the bitwise OR of each integer in the subarray. The bitwise OR of a subarray of one integer is that integer.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: arr = [0]
// Output: 1
// Explanation: There is only one possible result: 0.
//
// Constraints:
// 1 <= arr.length <= 5 * 104
// 	0 <= arr[i] <= 109
//

class Solution {
public:
    int subarrayBitwiseORs(vector<int>& arr) {
        unordered_set<int> resultSet;
        unordered_set<int> currentSet;

        for (int num : arr) {
            unordered_set<int> nextSet;
            nextSet.insert(num);
            for (int prev : currentSet) {
                nextSet.insert(prev | num);
            }
            currentSet = nextSet;
            resultSet.insert(currentSet.begin(), currentSet.end());
        }

        return resultSet.size();            
    }
};
