// Source: https://leetcode.com/problems/parallel-courses-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given a 2D integer array relations where relations[j] = [prevCoursej, nextCoursej] denotes that course prevCoursej has to be completed before course nextCoursej (prerequisite relationship). Furthermore, you are given a 0-indexed integer array time where time[i] denotes how many months it takes to complete the (i+1)th course.
//
// You must find the minimum number of months needed to complete all the courses following these rules:
//
//
// 	You may start taking a course at any time if the prerequisites are met.
// 	Any number of courses can be taken at the same time.
//
//
// Return the minimum number of months needed to complete all the courses.
//
// Note: The test cases are generated such that it is possible to complete every course (i.e., the graph is a directed acyclic graph).
//
// Example:
// Input: n = 3, relations = [[1,3],[2,3]], time = [3,2,5]
// Output: 8
// Explanation: The figure above represents the given graph and the time required to complete each course. 
// We start course 1 and course 2 simultaneously at month 0.
// Course 1 takes 3 months and course 2 takes 2 months to complete respectively.
// Thus, the earliest time we can start course 3 is at month 3, and the total time required is 3 + 5 = 8 months.
//
// Constraints:
// 1 <= n <= 5 * 104
// 	0 <= relations.length <= min(n * (n - 1) / 2, 5 * 104)
// 	relations[j].length == 2
// 	1 <= prevCoursej, nextCoursej <= n
// 	prevCoursej != nextCoursej
// 	All the pairs [prevCoursej, nextCoursej] are unique.
// 	time.length == n
// 	1 <= time[i] <= 104
// 	The given graph is a directed acyclic graph.
//

int minimumTime(int n, int** relations, int relationsSize, int* relationsColSize, int* time, int timeSize) {
    int *indegree = (int*)calloc(n, sizeof(int));
    int **adj = (int**)calloc(n, sizeof(int*));
    int *adjSizes = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < relationsSize; ++i) {
        int u = relations[i][0] - 1;
        int v = relations[i][1] - 1;
        indegree[v]++;
        adj[u] = (int*)realloc(adj[u], (adjSizes[u] + 1) * sizeof(int));
        adj[u][adjSizes[u]++] = v;
    }

    int *dp = (int*)calloc(n, sizeof(int));
    int *queue = (int*)calloc(n, sizeof(int));
    int front = 0, back = 0;
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            queue[back++] = i;
            dp[i] = time[i];
        }
    }

    while (front < back) {
        int u = queue[front++];
        for (int i = 0; i < adjSizes[u]; ++i) {
            int v = adj[u][i];
            if (dp[v] < dp[u] + time[v]) {
                dp[v] = dp[u] + time[v];
            }
            indegree[v]--;
            if (indegree[v] == 0) {
                queue[back++] = v;
            }
        }
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
        if (dp[i] > result) {
            result = dp[i];
        }
    }

    free(indegree);
    for (int i = 0; i < n; ++i) {
        free(adj[i]);
    }
    free(adj);
    free(adjSizes);
    free(dp);
    free(queue);

    return result;      
}
