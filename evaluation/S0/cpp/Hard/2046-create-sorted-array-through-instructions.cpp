// Source: https://leetcode.com/problems/create-sorted-array-through-instructions/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array instructions, you are asked to create a sorted array from the elements in instructions. You start with an empty container nums. For each element from left to right in instructions, insert it into nums. The cost of each insertion is the minimum of the following:
//
//
// 	The number of elements currently in nums that are strictly less than instructions[i].
// 	The number of elements currently in nums that are strictly greater than instructions[i].
//
//
// For example, if inserting element 3 into nums = [1,2,3,5], the cost of insertion is min(2, 1) (elements 1 and 2 are less than 3, element 5 is greater than 3) and nums will become [1,2,3,3,5].
//
// Return the total cost to insert all elements from instructions into nums. Since the answer may be large, return it modulo 109 + 7
//
// Example:
// Input: instructions = [1,5,6,2]
// Output: 1
// Explanation: Begin with nums = [].
// Insert 1 with cost min(0, 0) = 0, now nums = [1].
// Insert 5 with cost min(1, 0) = 0, now nums = [1,5].
// Insert 6 with cost min(2, 0) = 0, now nums = [1,5,6].
// Insert 2 with cost min(1, 2) = 1, now nums = [1,2,5,6].
// The total cost is 0 + 0 + 0 + 1 = 1.
//
// Constraints:
// 1 <= instructions.length <= 105
// 	1 <= instructions[i] <= 105
//

class Solution {
public:
    int createSortedArray(vector<int>& instructions) {
        const int MOD = 1e9 + 7;
        const int MAX_VAL = 100000;
        
        // Fenwick Tree (Binary Indexed Tree) for counting
        vector<int> fenwLess(MAX_VAL + 1, 0);
        vector<int> fenwGreater(MAX_VAL + 1, 0);
        
        auto fenwUpdate = [&](vector<int>& fenw, int idx, int delta) {
            while (idx <= MAX_VAL) {
                fenw[idx] += delta;
                idx += idx & -idx;
            }
        };
        
        auto fenwQuery = [&](vector<int>& fenw, int idx) {
            int sum = 0;
            while (idx > 0) {
                sum += fenw[idx];
                idx -= idx & -idx;
            }
            return sum;
        };
        
        long long totalCost = 0;
        
        for (int num : instructions) {
            int lessCount = fenwQuery(fenwLess, num - 1);
            int greaterCount = fenwQuery(fenwGreater, MAX_VAL) - fenwQuery(fenwGreater, num);
            
            totalCost = (totalCost + min(lessCount, greaterCount)) % MOD;
            
            fenwUpdate(fenwLess, num, 1);
            fenwUpdate(fenwGreater, num, 1);
        }
        
        return (int)totalCost;          
    }
};
