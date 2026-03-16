// Source: https://leetcode.com/problems/maximum-product-after-k-increments/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of non-negative integers nums and an integer k. In one operation, you may choose any element from nums and increment it by 1.
//
// Return the maximum product of nums after at most k operations. Since the answer may be very large, return it modulo 109 + 7. Note that you should maximize the product before taking the modulo.
//
// Example:
// Input: nums = [0,4], k = 5
// Output: 20
// Explanation: Increment the first number 5 times.
// Now nums = [5, 4], with a product of 5 * 4 = 20.
// It can be shown that 20 is maximum product possible, so we return 20.
// Note that there may be other ways to increment nums to have the maximum product.
//
// Constraints:
// 1 <= nums.length, k <= 105
// 	0 <= nums[i] <= 106
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Montgomery Multiplication (number, mod-exp)
//   • When to use: Use when performing many modular multiplications or exponentiations with a large modulus, especially in cryptographic applications. It optimizes repeated modular operations by transforming numbers into a special residue system.
//   • Idea: Montgomery multiplication is an algorithm for performing modular multiplication without explicit division by the modulus, which is often a slow operation. It transforms numbers into a Montgomery residue domain, performs multiplications, and then transforms back, achieving O(log N) or O(k^2) complexity for k-bit numbers.
//   • Invariants: The current product T remains within a manageable range, typically 0 <= T < N*R.; After each step, the intermediate result T is congruent to (A * B * R_inv) mod N.
//   • Tips: Precompute the Montgomery constant R and its inverse R_inv, and N' (N-prime).; Ensure the modulus N is odd for the standard algorithm to apply.
//   • Pitfalls: Incorrectly calculating N' or R_inv can lead to wrong results.; The modulus N must be odd for the standard algorithm to work correctly.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maximumProduct(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int num : nums) {
            minHeap.push(num);
        }

        while (k-- > 0) {
            int smallest = minHeap.top();
            minHeap.pop();
            minHeap.push(smallest + 1);
        }

        long long product = 1;
        while (!minHeap.empty()) {
            product = (product * minHeap.top()) % MOD;
            minHeap.pop();
        }

        return (int)product;            
    }
};
