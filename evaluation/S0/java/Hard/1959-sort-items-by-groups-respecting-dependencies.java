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
    public int[] sortItems(int n, int m, int[] group, List<List<Integer>> beforeItems) {
        // Step 1: Assign unique groups to ungrouped items
        for (int i = 0; i < n; i++) {
            if (group[i] == -1) {
                group[i] = m++;
            }
        }

        // Step 2: Build graphs for items and groups
        List<List<Integer>> itemGraph = new ArrayList<>();
        List<List<Integer>> groupGraph = new ArrayList<>();
        int[] itemIndegree = new int[n];
        int[] groupIndegree = new int[m];

        for (int i = 0; i < n; i++) {
            itemGraph.add(new ArrayList<>());
        }
        for (int i = 0; i < m; i++) {
            groupGraph.add(new ArrayList<>());
        }

        for (int curr = 0; curr < n; curr++) {
            for (int prev : beforeItems.get(curr)) {
                itemGraph.get(prev).add(curr);
                itemIndegree[curr]++;

                if (group[prev] != group[curr]) {
                    groupGraph.get(group[prev]).add(group[curr]);
                    groupIndegree[group[curr]]++;
                }
            }
        }

        // Step 3: Topological sort for items and groups
        List<Integer> itemOrder = topologicalSort(itemGraph, itemIndegree, n);
        if (itemOrder.isEmpty()) return new int[0];

        List<Integer> groupOrder = topologicalSort(groupGraph, groupIndegree, m);
        if (groupOrder.isEmpty()) return new int[0];

        // Step 4: Group items according to their groups
        Map<Integer, List<Integer>> groupedItems = new HashMap<>();
        for (int item : itemOrder) {
            groupedItems.computeIfAbsent(group[item], k -> new ArrayList<>()).add(item);
        }

        // Step 5: Construct final sorted order
        List<Integer> sortedItems = new ArrayList<>();
        for (int grp : groupOrder) {
            if (groupedItems.containsKey(grp)) {
                sortedItems.addAll(groupedItems.get(grp));
            }
        }

        return sortedItems.stream().mapToInt(i -> i).toArray();                 
    }
}
