// Source: https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/   |   Difficulty: Hard
//
// Problem Description:
// A company is organizing a meeting and has a list of n employees, waiting to be invited. They have arranged for a large circular table, capable of seating any number of employees.
//
// The employees are numbered from 0 to n - 1. Each employee has a favorite person and they will attend the meeting only if they can sit next to their favorite person at the table. The favorite person of an employee is not themself.
//
// Given a 0-indexed integer array favorite, where favorite[i] denotes the favorite person of the ith employee, return the maximum number of employees that can be invited to the meeting.
//
// Example:
// Input: favorite = [2,2,1,2]
// Output: 3
// Explanation:
// The above figure shows how the company can invite employees 0, 1, and 2, and seat them at the round table.
// All employees cannot be invited because employee 2 cannot sit beside employees 0, 1, and 3, simultaneously.
// Note that the company can also invite employees 1, 2, and 3, and give them their desired seats.
// The maximum number of employees that can be invited to the meeting is 3.
//
// Constraints:
// n == favorite.length
// 	2 <= n <= 105
// 	0 <= favorite[i] <= n - 1
// 	favorite[i] != i
//

int maximumInvitations(int* favorite, int favoriteSize) {
    int n = favoriteSize;
    int *indegree = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        indegree[favorite[i]]++;
    }

    int *queue = (int*)malloc(n * sizeof(int));
    int front = 0, back = 0;
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            queue[back++] = i;
        }
    }

    int *depth = (int*)calloc(n, sizeof(int));
    while (front < back) {
        int u = queue[front++];
        int v = favorite[u];
        depth[v] = depth[u] + 1;
        indegree[v]--;
        if (indegree[v] == 0) {
            queue[back++] = v;
        }
    }

    int maxCycle = 0;
    int pairSum = 0;
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) continue;
        if (indegree[favorite[i]] == 1 && favorite[favorite[i]] == i) {
            pairSum += depth[i] + depth[favorite[i]] + 2;
            indegree[i] = 0;
            indegree[favorite[i]] = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) continue;
        int cycleLen = 0;
        int u = i;
        while (indegree[u] > 0) {
            indegree[u] = 0;
            u = favorite[u];
            cycleLen++;
        }
        if (cycleLen > maxCycle) {
            maxCycle = cycleLen;
        }
    }

    free(indegree);
    free(queue);
    free(depth);

    return (pairSum > maxCycle) ? pairSum : maxCycle;       
}
