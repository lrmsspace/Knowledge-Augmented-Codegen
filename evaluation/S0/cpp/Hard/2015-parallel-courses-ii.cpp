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
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        vector<int> prereq(n, 0);
        for (const auto& rel : relations) {
            prereq[rel[1] - 1] |= (1 << (rel[0] - 1));
        }
        
        int totalStates = 1 << n;
        vector<int> dp(totalStates, n + 1);
        dp[0] = 0;
        
        for (int state = 0; state < totalStates; ++state) {
            int canTake = 0;
            for (int course = 0; course < n; ++course) {
                if ((state & (1 << course)) == 0 && (prereq[course] & state) == prereq[course]) {
                    canTake |= (1 << course);
                }
            }
            
            for (int subset = canTake; subset > 0; subset = (subset - 1) & canTake) {
                if (__builtin_popcount(subset) <= k) {
                    dp[state | subset] = min(dp[state | subset], dp[state] + 1);
                }
            }
        }
        
        return dp[totalStates - 1];         
    }
};
