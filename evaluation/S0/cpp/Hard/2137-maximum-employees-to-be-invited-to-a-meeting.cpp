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
public:
    int maximumInvitations(vector<int>& favorite) {
        int n = favorite.size();
        vector<vector<int>> adj(n);
        vector<int> indeg(n, 0);
        
        for (int i = 0; i < n; i++) {
            adj[favorite[i]].push_back(i);
            indeg[favorite[i]]++;
        }
        
        queue<int> q;
        vector<int> depth(n, 0);
        
        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            int v = favorite[u];
            depth[v] = max(depth[v], depth[u] + 1);
            indeg[v]--;
            if (indeg[v] == 0) {
                q.push(v);
            }
        }
        
        int res = 0;
        vector<bool> visited(n, false);
        
        for (int i = 0; i < n; i++) {
            if (indeg[i] > 0 && !visited[i]) {
                int cycle_size = 0;
                int u = i;
                int pair_sum = 0;
                
                while (!visited[u]) {
                    visited[u] = true;
                    cycle_size++;
                    int v = favorite[u];
                    
                    if (favorite[v] == u) {
                        pair_sum += depth[u] + depth[v] + 2;
                    }
                    
                    u = v;
                }
                
                if (cycle_size == 2) {
                    res += pair_sum;
                } else {
                    res = max(res, cycle_size);
                }
            }
        }
        
        return res;         
    }
};
