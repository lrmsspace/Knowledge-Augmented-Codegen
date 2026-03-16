# Source: https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/   |   Difficulty: Hard
#
# Problem Description:
# There are n items each belonging to zero or one of m groups where group[i] is the group that the i-th item belongs to and it's equal to -1 if the i-th item belongs to no group. The items and the groups are zero indexed. A group can have no item belonging to it.
#
# Return a sorted list of the items such that:
#
#
# 	The items that belong to the same group are next to each other in the sorted list.
# 	There are some relations between these items where beforeItems[i] is a list containing all the items that should come before the i-th item in the sorted array (to the left of the i-th item).
#
#
# Return any solution if there is more than one solution and return an empty list if there is no solution.
#
# Example:
# Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
# Output: [6,3,4,1,5,2,0,7]
#
# Constraints:
# 1 <= m <= n <= 3 * 104
# 	group.length == beforeItems.length == n
# 	-1 <= group[i] <= m - 1
# 	0 <= beforeItems[i].length <= n - 1
# 	0 <= beforeItems[i][j] <= n - 1
# 	i != beforeItems[i][j]
# 	beforeItems[i] does not contain duplicates elements.
#

class Solution(object):
    def sortItems(self, n, m, group, beforeItems):
        """
        :type n: int
        :type m: int
        :type group: List[int]
        :type beforeItems: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        # Assign unique group IDs to items with no group
        for i in range(n):
            if group[i] == -1:
                group[i] = m
                m += 1

        # Build graphs
        item_graph = defaultdict(list)
        item_indegree = [0] * n
        group_graph = defaultdict(list)
        group_indegree = [0] * m

        for curr in range(n):
            for prev in beforeItems[curr]:
                item_graph[prev].append(curr)
                item_indegree[curr] += 1
                if group[prev] != group[curr]:
                    group_graph[group[prev]].append(group[curr])
                    group_indegree[group[curr]] += 1

        # Topological sort function
        def topological_sort(graph, indegree, total):
            queue = deque([i for i in range(total) if indegree[i] == 0])
            sorted_list = []

            while queue:
                node = queue.popleft()
                sorted_list.append(node)
                for neighbor in graph[node]:
                    indegree[neighbor] -= 1
                    if indegree[neighbor] == 0:
                        queue.append(neighbor)

            return sorted_list if len(sorted_list) == total else []

        # Sort items and groups
        sorted_items = topological_sort(item_graph, item_indegree, n)
        sorted_groups = topological_sort(group_graph, group_indegree, m)

        if not sorted_items or not sorted_groups:
            return []

        # Group items by their groups
        items_by_group = defaultdict(list)
        for item in sorted_items:
            items_by_group[group[item]].append(item)

        # Compile final result based on sorted groups
        result = []
        for grp in sorted_groups:
            result.extend(items_by_group[grp])

        return result