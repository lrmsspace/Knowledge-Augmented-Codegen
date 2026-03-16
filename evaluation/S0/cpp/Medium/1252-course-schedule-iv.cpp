// Source: https://leetcode.com/problems/course-schedule-iv/   |   Difficulty: Medium
//
// Problem Description:
// There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course ai first if you want to take course bi.
//
//
// 	For example, the pair [0, 1] indicates that you have to take course 0 before you can take course 1.
//
//
// Prerequisites can also be indirect. If course a is a prerequisite of course b, and course b is a prerequisite of course c, then course a is a prerequisite of course c.
//
// You are also given an array queries where queries[j] = [uj, vj]. For the jth query, you should answer whether course uj is a prerequisite of course vj or not.
//
// Return a boolean array answer, where answer[j] is the answer to the jth query.
//
// Example:
// Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
// Output: [false,true]
// Explanation: The pair [1, 0] indicates that you have to take course 1 before you can take course 0.
// Course 0 is not a prerequisite of course 1, but the opposite is true.
//
// Constraints:
// 2 <= numCourses <= 100
// 	0 <= prerequisites.length <= (numCourses * (numCourses - 1) / 2)
// 	prerequisites[i].length == 2
// 	0 <= ai, bi <= numCourses - 1
// 	ai != bi
// 	All the pairs [ai, bi] are unique.
// 	The prerequisites graph has no cycles.
// 	1 <= queries.length <= 104
// 	0 <= ui, vi <= numCourses - 1
// 	ui != vi
//

class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<bool>> reach(numCourses, vector<bool>(numCourses, false));
        
        for (const auto& pre : prerequisites) {
            reach[pre[0]][pre[1]] = true;
        }
        
        for (int k = 0; k < numCourses; ++k) {
            for (int i = 0; i < numCourses; ++i) {
                for (int j = 0; j < numCourses; ++j) {
                    reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
                }
            }
        }
        
        vector<bool> result;
        for (const auto& query : queries) {
            result.push_back(reach[query[0]][query[1]]);
        }
        
        return result;          
    }
};
