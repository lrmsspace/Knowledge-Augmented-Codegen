// Source: https://leetcode.com/problems/find-the-minimum-number-of-fibonacci-numbers-whose-sum-is-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer k, return the minimum number of Fibonacci numbers whose sum is equal to k. The same Fibonacci number can be used multiple times.
//
// The Fibonacci numbers are defined as:
//
//
// 	F1 = 1
// 	F2 = 1
// 	Fn = Fn-1 + Fn-2 for n > 2.
//
// It is guaranteed that for the given constraints we can always find such Fibonacci numbers that sum up to k.
//
// Example:
// Input: k = 7
// Output: 2 
// Explanation: The Fibonacci numbers are: 1, 1, 2, 3, 5, 8, 13, ... 
// For k = 7 we can use 2 + 5 = 7.
//
// Constraints:
// 1 <= k <= 109
//

class Solution {
    public int findMinFibonacciNumbers(int k) {
        List<Integer> fibs = new ArrayList<>();
        fibs.add(1);
        fibs.add(1);
        int nextFib = 2;
        while (nextFib <= k) {
            fibs.add(nextFib);
            int size = fibs.size();
            nextFib = fibs.get(size - 1) + fibs.get(size - 2);
        }

        int count = 0;
        int index = fibs.size() - 1;
        while (k > 0) {
            if (fibs.get(index) <= k) {
                k -= fibs.get(index);
                count++;
            } else {
                index--;
            }
        }
        return count;           
    }
}
