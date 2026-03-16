// Source: https://leetcode.com/problems/find-the-minimum-amount-of-time-to-brew-potions/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays, skill and mana, of length n and m, respectively.
//
// In a laboratory, n wizards must brew m potions in order. Each potion has a mana capacity mana[j] and must pass through all the wizards sequentially to be brewed properly. The time taken by the ith wizard on the jth potion is timeij = skill[i] * mana[j].
//
// Since the brewing process is delicate, a potion must be passed to the next wizard immediately after the current wizard completes their work. This means the timing must be synchronized so that each wizard begins working on a potion exactly when it arrives. ​
//
// Return the minimum amount of time required for the potions to be brewed properly.
//
// Example:
// Input: skill = [1,5,2,4], mana = [5,1,4,2]
//
// Output: 110
//
// Explanation:
//
//
// 	
// 		
// 			Potion Number
// 			Start time
// 			Wizard 0 done by
// 			Wizard 1 done by
// 			Wizard 2 done by
// 			Wizard 3 done by
// 		
// 		
// 			0
// 			0
// 			5
// 			30
// 			40
// 			60
// 		
// 		
// 			1
// 			52
// 			53
// 			58
// 			60
// 			64
// 		
// 		
// 			2
// 			54
// 			58
// 			78
// 			86
// 			102
// 		
// 		
// 			3
// 			86
// 			88
// 			98
// 			102
// 			110
// 		
// 	
//
//
// As an example for why wizard 0 cannot start working on the 1st potion before time t = 52, consider the case where the wizards started preparing the 1st potion at time t = 50. At time t = 58, wizard 2 is done with the 1st potion, but wizard 3 will still be working on the 0th potion till time t = 60.
//
// Constraints:
// n == skill.length
// 	m == mana.length
// 	1 <= n, m <= 5000
// 	1 <= mana[i], skill[i] <= 5000
//
// Helpful references (internal KB):
// - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
//   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
//   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
//   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
//   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
//   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        int n = skill.size();
        int m = mana.size();
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));

        for (int j = 1; j <= m; ++j) {
            dp[0][j] = dp[0][j - 1] + skill[0] * mana[j - 1];
        }

        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= m; ++j) {
                dp[i][j] = dp[i - 1][j];
                long long timeAccum = 0;
                for (int k = j - 1; k >= 0; --k) {
                    timeAccum += skill[i] * mana[k];
                    long long candidate = dp[i - 1][k] + timeAccum;
                    if (candidate < dp[i][j]) {
                        dp[i][j] = candidate;
                    }
                }
            }
        }

        return dp[n - 1][m];            
    }
};
