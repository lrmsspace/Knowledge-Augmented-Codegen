// Source: https://leetcode.com/problems/course-schedule-ii/   |   Difficulty: Medium
//
// Problem Description:
// There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
//
//
// 	For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
//
//
// Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.
//
// Example:
// Input: numCourses = 2, prerequisites = [[1,0]]
// Output: [0,1]
// Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].
//
// Constraints:
// 1 <= numCourses <= 2000
// 	0 <= prerequisites.length <= numCourses * (numCourses - 1)
// 	prerequisites[i].length == 2
// 	0 <= ai, bi < numCourses
// 	ai != bi
// 	All the pairs [ai, bi] are distinct.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize) {
    int *indegree = (int *)calloc(numCourses, sizeof(int));
    int *result = (int *)malloc(numCourses * sizeof(int));
    int resultIndex = 0;

    // Build the adjacency list and indegree array
    int **adjList = (int **)malloc(numCourses * sizeof(int *));
    int *adjListSizes = (int *)calloc(numCourses, sizeof(int));
    for (int i = 0; i < numCourses; i++) {
        adjList[i] = (int *)malloc(numCourses * sizeof(int));
    }

    for (int i = 0; i < prerequisitesSize; i++) {
        int dest = prerequisites[i][0];
        int src = prerequisites[i][1];
        adjList[src][adjListSizes[src]++] = dest;
        indegree[dest]++;
    }

    // Initialize the queue with all courses having indegree of 0
    int *queue = (int *)malloc(numCourses * sizeof(int));
    int front = 0, back = 0;
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) {
            queue[back++] = i;
        }
    }

    // Process the queue
    while (front < back) {
        int course = queue[front++];
        result[resultIndex++] = course;

        for (int i = 0; i < adjListSizes[course]; i++) {
            int neighbor = adjList[course][i];
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                queue[back++] = neighbor;
            }
        }
    }

    // Check if we were able to take all courses
    if (resultIndex != numCourses) {
        free(result);
        result = NULL;
        *returnSize = 0;
    } else {
        *returnSize = resultIndex;
    }

    // Free allocated memory
    for (int i = 0; i < numCourses; i++) {
        free(adjList[i]);
    }
    free(adjList);
    free(adjListSizes);
    free(indegree);
    free(queue);

    return result;      
}
