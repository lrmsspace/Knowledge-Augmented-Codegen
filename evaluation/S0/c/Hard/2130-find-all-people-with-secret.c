// Source: https://leetcode.com/problems/find-all-people-with-secret/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n indicating there are n people numbered from 0 to n - 1. You are also given a 0-indexed 2D integer array meetings where meetings[i] = [xi, yi, timei] indicates that person xi and person yi have a meeting at timei. A person may attend multiple meetings at the same time. Finally, you are given an integer firstPerson.
//
// Person 0 has a secret and initially shares the secret with a person firstPerson at time 0. This secret is then shared every time a meeting takes place with a person that has the secret. More formally, for every meeting, if a person xi has the secret at timei, then they will share the secret with person yi, and vice versa.
//
// The secrets are shared instantaneously. That is, a person may receive the secret and share it with people in other meetings within the same time frame.
//
// Return a list of all the people that have the secret after all the meetings have taken place. You may return the answer in any order.
//
// Example:
// Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
// Output: [0,1,2,3,5]
// Explanation:
// At time 0, person 0 shares the secret with person 1.
// At time 5, person 1 shares the secret with person 2.
// At time 8, person 2 shares the secret with person 3.
// At time 10, person 1 shares the secret with person 5.​​​​
// Thus, people 0, 1, 2, 3, and 5 know the secret after all the meetings.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= meetings.length <= 105
// 	meetings[i].length == 3
// 	0 <= xi, yi <= n - 1
// 	xi != yi
// 	1 <= timei <= 105
// 	1 <= firstPerson <= n - 1
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAllPeople(int n, int** meetings, int meetingsSize, int* meetingsColSize, int firstPerson, int* returnSize) {
    // Sort meetings by time
    qsort(meetings, meetingsSize, sizeof(int*), [](const void* a, const void* b) {
        return (*(int**)a)[2] - (*(int**)b)[2];
    });

    // Union-Find data structure
    int* parent = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) parent[i] = i;

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSet(int x, int y) {
        parent[find(x)] = find(y);
    }

    // Initially, person 0 and firstPerson know the secret
    unionSet(0, firstPerson);

    int i = 0;
    while (i < meetingsSize) {
        int time = meetings[i][2];
        int j = i;

        // Process all meetings at the same time
        while (j < meetingsSize && meetings[j][2] == time) {
            unionSet(meetings[j][0], meetings[j][1]);
            j++;
        }

        // Reset connections for those who don't know the secret
        for (int k = i; k < j; k++) {
            if (find(meetings[k][0]) != find(0)) {
                parent[meetings[k][0]] = meetings[k][0];
            }
            if (find(meetings[k][1]) != find(0)) {
                parent[meetings[k][1]] = meetings[k][1];
            }
        }

        i = j;
    }

    // Collect all people who know the secret
    int* result = (int*)malloc(n * sizeof(int));
    *returnSize = 0;
    for (int k = 0; k < n; k++) {
        if (find(k) == find(0)) {
            result[(*returnSize)++] = k;
        }
    }

    free(parent);
    return result;
}
