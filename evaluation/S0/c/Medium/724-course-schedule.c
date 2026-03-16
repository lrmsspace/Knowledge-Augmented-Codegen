// Source: https://leetcode.com/problems/course-schedule/   |   Difficulty: Medium
//
// Problem Description:
// There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
//
//
// 	For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
//
//
// Return true if you can finish all courses. Otherwise, return false.
//
// Example:
// Input: numCourses = 2, prerequisites = [[1,0]]
// Output: true
// Explanation: There are a total of 2 courses to take. 
// To take course 1 you should have finished course 0. So it is possible.
//
// Constraints:
// 1 <= numCourses <= 2000
// 	0 <= prerequisites.length <= 5000
// 	prerequisites[i].length == 2
// 	0 <= ai, bi < numCourses
// 	All the pairs prerequisites[i] are unique.
//

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize) {
    int indegree[numCourses];
    memset(indegree, 0, sizeof(indegree));
    
    // Build the indegree array
    for (int i = 0; i < prerequisitesSize; i++) {
        indegree[prerequisites[i][0]]++;
    }
    
    // Initialize the queue with courses having zero indegree
    int queue[numCourses];
    int front = 0, rear = 0;
    
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }
    
    int completedCourses = 0;
    
    while (front < rear) {
        int course = queue[front++];
        completedCourses++;
        
        // Decrease the indegree of neighboring courses
        for (int i = 0; i < prerequisitesSize; i++) {
            if (prerequisites[i][1] == course) {
                indegree[prerequisites[i][0]]--;
                if (indegree[prerequisites[i][0]] == 0) {
                    queue[rear++] = prerequisites[i][0];
                }
            }
        }
    }
    
    return completedCourses == numCourses;      
}
