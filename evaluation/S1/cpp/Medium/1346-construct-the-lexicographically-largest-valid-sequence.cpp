// Source: https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, find a sequence with elements in the range [1, n] that satisfies all of the following:
//
//
// 	The integer 1 occurs once in the sequence.
// 	Each integer between 2 and n occurs twice in the sequence.
// 	For every integer i between 2 and n, the distance between the two occurrences of i is exactly i.
//
//
// The distance between two numbers on the sequence, a[i] and a[j], is the absolute difference of their indices, |j - i|.
//
// Return the lexicographically largest sequence. It is guaranteed that under the given constraints, there is always a solution. 
//
// A sequence a is lexicographically larger than a sequence b (of the same length) if in the first position where a and b differ, sequence a has a number greater than the corresponding number in b. For example, [0,1,9,0] is lexicographically larger than [0,1,5,6] because the first position they differ is at the third number, and 9 is greater than 5.
//
// Example:
// Input: n = 3
// Output: [3,1,2,3,2]
// Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the lexicographically largest valid sequence.
//
// Constraints:
// 1 <= n <= 20
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
//   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
//   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
//   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
// - Fibonacci Numbers (number, greedy, enumeration)
//   • When to use: When you need a unique, non-ambiguous binary representation of positive integers based on Fibonacci numbers, ensuring no two consecutive Fibonacci numbers are used in the sum.
//   • Idea: This algorithm encodes a positive integer into a unique binary string by greedily finding its Zeckendorf representation (sum of non-consecutive Fibonacci numbers). The encoding process typically involves iterating through Fibonacci numbers, resulting in a logarithmic time complexity relative to the input number's magnitude.
//   • Invariants: The remaining value 'n' to be encoded is always non-negative.; The partial binary code constructed so far represents a valid Zeckendorf sum of non-consecutive Fibonacci numbers.
//   • Tips: Precompute Fibonacci numbers up to a certain limit to optimize lookups.; Always start with the largest Fibonacci number less than or equal to the target value.
//   • Pitfalls: Incorrectly handling the base cases for small numbers like 1 or 2.; Forgetting to append the mandatory final '1' bit to the codeword.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> constructDistancedSequence(int n) {
        vector<int> res(2 * n - 1, 0);
        vector<bool> used(n + 1, false);

        function<bool(int)> backtrack = [&](int pos) -> bool {
            if (pos >= res.size()) return true;
            if (res[pos] != 0) return backtrack(pos + 1);

            for (int num = n; num >= 1; --num) {
                if (used[num]) continue;

                if (num == 1) {
                    res[pos] = 1;
                    used[1] = true;
                    if (backtrack(pos + 1)) return true;
                    res[pos] = 0;
                    used[1] = false;
                } else {
                    int secondPos = pos + num;
                    if (secondPos < res.size() && res[secondPos] == 0) {
                        res[pos] = num;
                        res[secondPos] = num;
                        used[num] = true;
                        if (backtrack(pos + 1)) return true;
                        res[pos] = 0;
                        res[secondPos] = 0;
                        used[num] = false;
                    }
                }
            }
            return false;
        };

        backtrack(0);
        return res;         
    }
};
