// Source: https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/   |   Difficulty: Hard
//
// Problem Description:
// There are n items each belonging to zero or one of m groups where group[i] is the group that the i-th item belongs to and it's equal to -1 if the i-th item belongs to no group. The items and the groups are zero indexed. A group can have no item belonging to it.
//
// Return a sorted list of the items such that:
//
//
// 	The items that belong to the same group are next to each other in the sorted list.
// 	There are some relations between these items where beforeItems[i] is a list containing all the items that should come before the i-th item in the sorted array (to the left of the i-th item).
//
//
// Return any solution if there is more than one solution and return an empty list if there is no solution.
//
// Example:
// Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
// Output: [6,3,4,1,5,2,0,7]
//
// Constraints:
// 1 <= m <= n <= 3 * 104
// 	group.length == beforeItems.length == n
// 	-1 <= group[i] <= m - 1
// 	0 <= beforeItems[i].length <= n - 1
// 	0 <= beforeItems[i][j] <= n - 1
// 	i != beforeItems[i][j]
// 	beforeItems[i] does not contain duplicates elements.
//

class Solution {
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        // Assign unique groups to items with no group
        for (int i = 0; i < n; i++) {
            if (group[i] == -1) {
                group[i] = m++;
            }
        }
        
        // Build graphs
        vector<vector<int>> itemGraph(n);
        vector<int> itemIndegree(n, 0);
        vector<vector<int>> groupGraph(m);
        vector<int> groupIndegree(m, 0);
        
        for (int i = 0; i < n; i++) {
            for (int before : beforeItems[i]) {
                itemGraph[before].push_back(i);
                itemIndegree[i]++;
                
                if (group[before] != group[i]) {
                    groupGraph[group[before]].push_back(group[i]);
                    groupIndegree[group[i]]++;
                }
            }
        }
        
        // Topological sort for groups
        vector<int> groupOrder;
        queue<int> q;
        for (int i = 0; i < m; i++) {
            if (groupIndegree[i] == 0) {
                q.push(i);
            }
        }
        
        while (!q.empty()) {
            int g = q.front(); q.pop();
            groupOrder.push_back(g);
            
            for (int nei : groupGraph[g]) {
                if (--groupIndegree[nei] == 0) {
                    q.push(nei);
                }
            }
        }
        
        if (groupOrder.size() != m) return {};
        
        // Topological sort for items
        vector<int> itemOrder;
        q = queue<int>();
        for (int i = 0; i < n; i++) {
            if (itemIndegree[i] == 0) {
                q.push(i);
            }
        }
        
        while (!q.empty()) {
            int it = q.front(); q.pop();
            itemOrder.push_back(it);
            
            for (int nei : itemGraph[it]) {
                if (--itemIndegree[nei] == 0) {
                    q.push(nei);
                }
            }
        }
        
        if (itemOrder.size() != n) return {};
        
        // Group items by their groups in the order of itemOrder
        vector<vector<int>> itemsInGroup(m);
        for (int it : itemOrder) {
            itemsInGroup[group[it]].push_back(it);
        }   
        // Build final result based on group order
        vector<int> result;
        for (int g : groupOrder) {
            for (int it : itemsInGroup[g]) {
                result.push_back(it);
            }
        }
        return result;        
    }
};
