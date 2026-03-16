// Source: https://leetcode.com/problems/parallel-courses-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given an array relations where relations[i] = [prevCoursei, nextCoursei], representing a prerequisite relationship between course prevCoursei and course nextCoursei: course prevCoursei has to be taken before course nextCoursei. Also, you are given the integer k.
//
// In one semester, you can take at most k courses as long as you have taken all the prerequisites in the previous semesters for the courses you are taking.
//
// Return the minimum number of semesters needed to take all courses. The testcases will be generated such that it is possible to take every course.
//
// Example:
// Input: n = 4, relations = [[2,1],[3,1],[1,4]], k = 2
// Output: 3
// Explanation: The figure above represents the given graph.
// In the first semester, you can take courses 2 and 3.
// In the second semester, you can take course 1.
// In the third semester, you can take course 4.
//
// Constraints:
// 1 <= n <= 15
// 	1 <= k <= n
// 	0 <= relations.length <= n * (n-1) / 2
// 	relations[i].length == 2
// 	1 <= prevCoursei, nextCoursei <= n
// 	prevCoursei != nextCoursei
// 	All the pairs [prevCoursei, nextCoursei] are unique.
// 	The given graph is a directed acyclic graph.
//

class Solution {
    public int minNumberOfSemesters(int n, int[][] relations, int k) {
        int[] pre = new int[n];
        for (int[] relation : relations) {
            pre[relation[1] - 1] |= 1 << (relation[0] - 1);
        }

        int size = 1 << n;
        int[] dp = new int[size];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;

        for (int mask = 0; mask < size; mask++) {
            int canTake = 0;
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0 && (pre[i] & mask) == pre[i]) {
                    canTake |= 1 << i;
                }
            }

            for (int sub = canTake; sub > 0; sub = (sub - 1) & canTake) {
                if (Integer.bitCount(sub) <= k) {
                    dp[mask | sub] = Math.min(dp[mask | sub], dp[mask] + 1);
                }
            }
        }

        return dp[size - 1];                    
    }
}
