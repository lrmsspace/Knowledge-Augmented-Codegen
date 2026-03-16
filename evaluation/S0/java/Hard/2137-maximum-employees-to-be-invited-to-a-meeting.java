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

class Solution {
    public int maximumInvitations(int[] favorite) {
        int n = favorite.length;
        boolean[] visited = new boolean[n];
        boolean[] inStack = new boolean[n];
        int maxCycleLength = 0;
        int sumOfChains = 0;

        List<List<Integer>> reverseGraph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            reverseGraph.add(new ArrayList<>());
        }
        for (int i = 0; i < n; i++) {
            reverseGraph.get(favorite[i]).add(i);
        }

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int cycleLength = dfsCycleDetection(i, favorite, visited, inStack);
                if (cycleLength > 0) {
                    maxCycleLength = Math.max(maxCycleLength, cycleLength);
                }
            }
        }

        visited = new boolean[n];
        for (int i = 0; i < n; i++) {
            if (favorite[favorite[i]] == i && i < favorite[i]) {
                int chainLength1 = dfsChainLength(i, favorite, reverseGraph, visited);
                int chainLength2 = dfsChainLength(favorite[i], favorite, reverseGraph, visited);
                sumOfChains += chainLength1 + chainLength2;
            }
        }

        return Math.max(maxCycleLength, sumOfChains);           
    }
}
