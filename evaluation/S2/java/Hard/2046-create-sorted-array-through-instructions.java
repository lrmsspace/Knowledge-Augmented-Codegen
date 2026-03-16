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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int createSortedArray(int[] instructions) {
        int max = 0;
        for (int num : instructions) {
            max = Math.max(max, num);
        }
        FenwickTree fenwickTree = new FenwickTree(max);
        long cost = 0;
        for (int i = 0; i < instructions.length; i++) {
            int num = instructions[i];
            cost += Math.min(fenwickTree.query(num - 1), i - fenwickTree.query(num));
            fenwickTree.update(num, 1);
        }
        return (int) (cost % 1_000_000_007);            
    }
}
