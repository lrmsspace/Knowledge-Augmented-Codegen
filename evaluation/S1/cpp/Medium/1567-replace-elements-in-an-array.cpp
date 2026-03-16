// Source: https://leetcode.com/problems/replace-elements-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums that consists of n distinct positive integers. Apply m operations to this array, where in the ith operation you replace the number operations[i][0] with operations[i][1].
//
// It is guaranteed that in the ith operation:
//
//
// 	operations[i][0] exists in nums.
// 	operations[i][1] does not exist in nums.
//
//
// Return the array obtained after applying all the operations.
//
// Example:
// Input: nums = [1,2,4,6], operations = [[1,3],[4,7],[6,1]]
// Output: [3,2,7,1]
// Explanation: We perform the following operations on nums:
// - Replace the number 1 with 3. nums becomes [3,2,4,6].
// - Replace the number 4 with 7. nums becomes [3,2,7,6].
// - Replace the number 6 with 1. nums becomes [3,2,7,1].
// We return the final array [3,2,7,1].
//
// Constraints:
// n == nums.length
// 	m == operations.length
// 	1 <= n, m <= 105
// 	All the values of nums are distinct.
// 	operations[i].length == 2
// 	1 <= nums[i], operations[i][0], operations[i][1] <= 106
// 	operations[i][0] will exist in nums when applying the ith operation.
// 	operations[i][1] will not exist in nums when applying the ith operation.
//
// Helpful references (internal KB):
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when you need to perform many range queries on a static array, especially when the query operation is associative and idempotent, allowing for O(1) query time after O(N log N) precomputation.
//   • Idea: A Sparse Table is a data structure that precomputes answers for all possible range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like min/max/gcd and O(log N) for non-idempotent associative operations, after an O(N log N) build time.
//   • Invariants: After precomputation, dp[k][i] stores the result for the range [i, i + 2^k - 1].; For any k > 0, dp[k][i] is the result of combining dp[k-1][i] and dp[k-1][i + 2^(k-1)].
//   • Tips: Precompute log2 values for faster range length calculations.; Store dp[k][i] as the result for range [i, i + 2^k - 1].
//   • Pitfalls: Does not support updates to array elements efficiently.; Requires O(N log N) space, which can be significant for large N.
// - Gauss method for solving system of linea (bitset, matrix, simulation)
//   • When to use: Use when determining the number of solutions (zero, one, or infinite) for a system of linear equations, or to find the unique solution if it exists. It is suitable for solving systems represented as an augmented matrix.
//   • Idea: Gaussian elimination systematically transforms an augmented matrix into row echelon form using elementary row operations to solve a system of linear equations. It determines the existence and values of solutions in O(N^3) time for an N x N system.
//   • Invariants: The submatrix formed by rows 0 to current_row - 1 is in row echelon form.; For the current column, all elements below the pivot in previous columns are zero.
//   • Tips: Use a small epsilon for floating-point comparisons to handle precision issues.; Implement partial pivoting to enhance numerical stability by selecting the largest absolute value.
//   • Pitfalls: Failing to account for floating-point precision errors can lead to incorrect results.; Improper handling of free variables can misrepresent infinite solution sets.
// - Bit manipulation (number, simulation)
//   • When to use: Use when operations on individual bits of an integer are required, for optimizing arithmetic with powers of two, or for efficient management of boolean flags.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators and shifts. These operations typically have O(1) time complexity as they are hardware-level instructions.
//   • Invariants: The total number of bits representing the integer remains constant for fixed-width types.; Applying `n & (1 << k)` isolates the k-th bit, setting all other bits to zero.
//   • Tips: Use `&` with `(1 << k)` to check if the k-th bit is set.; Use `|` with `(1 << k)` to set the k-th bit.
//   • Pitfalls: Be aware of integer overflow when performing large left shifts.; Understand the difference between arithmetic and logical right shifts, especially for signed numbers.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> arrayChange(vector<int>& nums, vector<vector<int>>& operations) {
        unordered_map<int, int> val_to_idx;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            val_to_idx[nums[i]] = i;
        }

        for (const auto& op : operations) {
            int old_val = op[0];
            int new_val = op[1];
            int idx = val_to_idx[old_val];
            nums[idx] = new_val;
            val_to_idx.erase(old_val);
            val_to_idx[new_val] = idx;
        }

        return nums;            
    }
};
