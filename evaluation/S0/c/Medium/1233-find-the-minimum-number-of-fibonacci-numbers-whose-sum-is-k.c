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

int findMinFibonacciNumbers(int k) {
    int fib[45];
    fib[0] = 1;
    fib[1] = 1;
    int count = 2;
    while (1) {
        fib[count] = fib[count - 1] + fib[count - 2];
        if (fib[count] > k) {
            break;
        }
        count++;
    }
    int result = 0;
    for (int i = count - 1; i >= 0 && k > 0; i--) {
        if (fib[i] <= k) {
            k -= fib[i];
            result++;
        }
    }
    return result;      
}
