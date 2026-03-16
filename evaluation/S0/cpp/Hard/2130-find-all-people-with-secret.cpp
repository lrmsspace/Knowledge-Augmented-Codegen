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

class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        // Union-Find data structure
        vector<int> parent(n);
        for (int i = 0; i < n; i++) parent[i] = i;
        
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };
        
        auto unite = [&](int x, int y) {
            int px = find(x);
            int py = find(y);
            if (px != py) {
                parent[py] = px;
            }
        };
        
        // Sort meetings by time
        sort(meetings.begin(), meetings.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });
        
        // Initially, person 0 and firstPerson know the secret
        unite(0, firstPerson);
        
        int m = meetings.size();
        int i = 0;
        
        while (i < m) {
            int time = meetings[i][2];
            vector<pair<int, int>> temp;
            
            // Collect all meetings at the same time
            while (i < m && meetings[i][2] == time) {
                int x = meetings[i][0];
                int y = meetings[i][1];
                temp.push_back({x, y});
                i++;
            }
            
            // Unite participants of the meetings at this time
            for (const auto& meeting : temp) {
                unite(meeting.first, meeting.second);
            }
            
            // Reset connections for those who don't know the secret
            for (const auto& meeting : temp) {
                int x = meeting.first;
                int y = meeting.second;
                if (find(x) != find(0)) {
                    parent[x] = x;
                }
                if (find(y) != find(0)) {
                    parent[y] = y;
                }
            }
        }
        
        // Collect all people who know the secret
        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (find(i) == find(0)) {
                result.push_back(i);
            }
        }
        
        return result;          
    }
};
