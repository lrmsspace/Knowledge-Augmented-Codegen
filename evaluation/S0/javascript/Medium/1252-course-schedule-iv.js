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

/**
 * @param {number} numCourses
 * @param {number[][]} prerequisites
 * @param {number[][]} queries
 * @return {boolean[]}
 */
var checkIfPrerequisite = function(numCourses, prerequisites, queries) {
    const graph = Array.from({ length: numCourses }, () => []);
    const reachable = Array.from({ length: numCourses }, () => new Set());
    const result = [];
    for (const [pre, course] of prerequisites) {
        graph[pre].push(course);
    }
    const dfs = (course, start) => {
        for (const neighbor of graph[course]) {
            if (!reachable[start].has(neighbor)) {
                reachable[start].add(neighbor);
                dfs(neighbor, start);
            }
        }
    };
    for (let i = 0; i < numCourses; i++) {
        dfs(i, i);
    }
    for (const [u, v] of queries) {
        result.push(reachable[u].has(v));
    }
    return result;
        
};
