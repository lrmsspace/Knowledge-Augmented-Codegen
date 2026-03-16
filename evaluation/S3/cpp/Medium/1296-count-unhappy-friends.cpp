// Source: https://leetcode.com/problems/count-unhappy-friends/   |   Difficulty: Medium
//
// Problem Description:
// You are given a list of preferences for n friends, where n is always even.
//
// For each person i, preferences[i] contains a list of friends sorted in the order of preference. In other words, a friend earlier in the list is more preferred than a friend later in the list. Friends in each list are denoted by integers from 0 to n-1.
//
// All the friends are divided into pairs. The pairings are given in a list pairs, where pairs[i] = [xi, yi] denotes xi is paired with yi and yi is paired with xi.
//
// However, this pairing may cause some of the friends to be unhappy. A friend x is unhappy if x is paired with y and there exists a friend u who is paired with v but:
//
//
// 	x prefers u over y, and
// 	u prefers x over v.
//
//
// Return the number of unhappy friends.
//
// Example:
// Input: n = 4, preferences = [[1, 2, 3], [3, 2, 0], [3, 1, 0], [1, 2, 0]], pairs = [[0, 1], [2, 3]]
// Output: 2
// Explanation:
// Friend 1 is unhappy because:
// - 1 is paired with 0 but prefers 3 over 0, and
// - 3 prefers 1 over 2.
// Friend 3 is unhappy because:
// - 3 is paired with 2 but prefers 1 over 2, and
// - 1 prefers 3 over 0.
// Friends 0 and 2 are happy.
//
// Constraints:
// 2 <= n <= 500
// 	n is even.
// 	preferences.length == n
// 	preferences[i].length == n - 1
// 	0 <= preferences[i][j] <= n - 1
// 	preferences[i] does not contain i.
// 	All values in preferences[i] are unique.
// 	pairs.length == n/2
// 	pairs[i].length == 2
// 	xi != yi
// 	0 <= xi, yi <= n - 1
// 	Each person is contained in exactly one pair.
//
// Helpful references (internal KB):
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
//   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
//   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
//   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
//   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {
        vector<vector<int>> rank(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - 1; ++j) {
                rank[i][preferences[i][j]] = j;
            }
        }

        vector<int> pair(n);
        for (const auto& p : pairs) {
            pair[p[0]] = p[1];
            pair[p[1]] = p[0];
        }

        int unhappyCount = 0;
        for (int x = 0; x < n; ++x) {
            int y = pair[x];
            for (int u : preferences[x]) {
                if (u == y) {
                    break;
                }
                int v = pair[u];
                if (rank[u][x] < rank[u][v]) {
                    ++unhappyCount;
                    break;
                }
            }
        }

        return unhappyCount;            
    }
};
