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
// Helpful references (internal KB):
// - Topological Sorting (graph, array, dfs, topo)
//   • When to use: Use for graph or tree traversal, pathfinding, cycle detection, or topological sorting in DAGs. It's also suitable for exploring all states in a search space.
//   • Idea: DFS explores as far as possible along each branch before backtracking, typically using recursion or an explicit stack. Topological sort orders nodes in a DAG such that for every directed edge u -> v, u comes before v, achievable with DFS in O(V+E) time.
//   • Invariants: All nodes reachable from the current path have been explored or are in the recursion stack.; A node is marked 'visited' only after all its descendants have been fully explored.
//   • Tips: Use a visited set/array to prevent infinite loops in graphs and redundant computations.; Recursion is natural for DFS, but an explicit stack can avoid recursion depth limits.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect results.; Exceeding recursion depth limits for very deep graphs or trees.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortItems(int n, int m, int* group, int groupSize, int** beforeItems, int beforeItemsSize, int* beforeItemsColSize, int* returnSize) {
    // Create adjacency list for item dependencies
    int** itemAdj = (int**)malloc(n * sizeof(int*));
    int* itemInDegree = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        itemAdj[i] = (int*)malloc(n * sizeof(int));
        itemInDegree[i] = 0;
    }
    
    // Create adjacency list for group dependencies
    int groupCount = m;
    for (int i = 0; i < n; i++) {
        if (group[i] == -1) {
            group[i] = groupCount++;
        }
    }
    
    int** groupAdj = (int**)malloc(groupCount * sizeof(int*));
    int* groupInDegree = (int*)malloc(groupCount * sizeof(int));
    for (int i = 0; i < groupCount; i++) {
        groupAdj[i] = (int*)malloc(groupCount * sizeof(int));
        groupInDegree[i] = 0;
    }
    
    // Count edges for adjacency lists
    int* itemEdgeCount = (int*)malloc(n * sizeof(int));
    int* groupEdgeCount = (int*)malloc(groupCount * sizeof(int));
    for (int i = 0; i < n; i++) {
        itemEdgeCount[i] = 0;
    }
    for (int i = 0; i < groupCount; i++) {
        groupEdgeCount[i] = 0;
    }
    
    // Build graphs from beforeItems
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < beforeItemsColSize[i]; j++) {
            int beforeItem = beforeItems[i][j];
            int beforeGroup = group[beforeItem];
            int currentGroup = group[i];
            
            // Add item edge
            itemAdj[beforeItem][itemEdgeCount[beforeItem]++] = i;
            itemInDegree[i]++;
            
            // Add group edge if different groups
            if (beforeGroup != currentGroup) {
                // Check if edge already exists
                int found = 0;
                for (int k = 0; k < groupEdgeCount[beforeGroup]; k++) {
                    if (groupAdj[beforeGroup][k] == currentGroup) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    groupAdj[beforeGroup][groupEdgeCount[beforeGroup]++] = currentGroup;
                    groupInDegree[currentGroup]++;
                }
            }
        }
    }
    
    // Topological sort for groups using Kahn's algorithm
    int* groupQueue = (int*)malloc(groupCount * sizeof(int));
    int queueFront = 0, queueRear = 0;
    
    for (int i = 0; i < groupCount; i++) {
        if (groupInDegree[i] == 0) {
            groupQueue[queueRear++] = i;
        }
    }
    
    int* sortedGroups = (int*)malloc(groupCount * sizeof(int));
    int sortedGroupCount = 0;
    
    while (queueFront < queueRear) {
        int currentGroup = groupQueue[queueFront++];
        sortedGroups[sortedGroupCount++] = currentGroup;
        
        for (int i = 0; i < groupEdgeCount[currentGroup]; i++) {
            int nextGroup = groupAdj[currentGroup][i];
            groupInDegree[nextGroup]--;
            if (groupInDegree[nextGroup] == 0) {
                groupQueue[queueRear++] = nextGroup;
            }
        }
    }
    
    // Check if valid topological order exists for groups
    if (sortedGroupCount != groupCount) {
        *returnSize = 0;
        int* emptyResult = (int*)malloc(1 * sizeof(int));
        // Free memory
        for (int i = 0; i < n; i++) free(itemAdj[i]);
        free(itemAdj);
        free(itemInDegree);
        free(itemEdgeCount);
        for (int i = 0; i < groupCount; i++) free(groupAdj[i]);
        free(groupAdj);
        free(groupInDegree);
        free(groupEdgeCount);
        free(groupQueue);
        free(sortedGroups);
        return emptyResult;
    }
    
    // Topological sort for items within each group
    int* result = (int*)malloc(n * sizeof(int));
    int resultIndex = 0;
    
    for (int g = 0; g < sortedGroupCount; g++) {
        int currentGroup = sortedGroups[g];
        
        // Find all items in current group
        int* groupItems = (int*)malloc(n * sizeof(int));
        int groupItemCount = 0;
        
        for (int i = 0; i < n; i++) {
            if (group[i] == currentGroup) {
                groupItems[groupItemCount++] = i;
            }
        }
        
        // Topological sort items in this group
        int* itemQueue = (int*)malloc(groupItemCount * sizeof(int));
        int itemQueueFront = 0, itemQueueRear = 0;
        
        for (int i = 0; i < groupItemCount; i++) {
            int item = groupItems[i];
            if (itemInDegree[item] == 0) {
                itemQueue[itemQueueRear++] = item;
            }
        }
        
        int itemsAdded = 0;
        while (itemQueueFront < itemQueueRear) {
            int currentItem = itemQueue[itemQueueFront++];
            result[resultIndex++] = currentItem;
            itemsAdded++;
            
            for (int i = 0; i < itemEdgeCount[currentItem]; i++) {
                int nextItem = itemAdj[currentItem][i];
                // Only process items in current group
                if (group[nextItem] == currentGroup) {
                    itemInDegree[nextItem]--;
                    if (itemInDegree[nextItem] == 0) {
                        itemQueue[itemQueueRear++] = nextItem;
                    }
                }
            }
        }
        
        // Check if all items in group were processed
        if (itemsAdded != groupItemCount) {
            *returnSize = 0;
            int* emptyResult = (int*)malloc(1 * sizeof(int));
            // Free memory
            free(groupItems);
            free(itemQueue);
            for (int i = 0; i < n; i++) free(itemAdj[i]);
            free(itemAdj);
            free(itemInDegree);
            free(itemEdgeCount);
            for (int i = 0; i < groupCount; i++) free(groupAdj[i]);
            free(groupAdj);
            free(groupInDegree);
            free(groupEdgeCount);
            free(groupQueue);
            free(sortedGroups);
            return emptyResult;
        }
        
        free(groupItems);
        free(itemQueue);
    }
    
    *returnSize = resultIndex;
    
    // Free memory
    for (int i = 0; i < n; i++) free(itemAdj[i]);
    free(itemAdj);
    free(itemInDegree);
    free(itemEdgeCount);
    for (int i = 0; i < groupCount; i++) free(groupAdj[i]);
    free(groupAdj);
    free(groupInDegree);
    free(groupEdgeCount);
    free(groupQueue);
    free(sortedGroups);
    
    return result;  
}
