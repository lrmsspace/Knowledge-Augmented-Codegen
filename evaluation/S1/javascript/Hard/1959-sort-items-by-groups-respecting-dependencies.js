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
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number} m
 * @param {number[]} group
 * @param {number[][]} beforeItems
 * @return {number[]}
 */
var sortItems = function(n, m, group, beforeItems) {
	let groupCount = m;
	const itemGroup = group.slice();
	for (let i = 0; i < n; i += 1) {
		if (itemGroup[i] === -1) {
			itemGroup[i] = groupCount;
			groupCount += 1;
		}
	}

	const itemGraph = Array.from({ length: n }, () => []);
	const itemIndeg = new Array(n).fill(0);
	const groupGraph = Array.from({ length: groupCount }, () => []);
	const groupIndeg = new Array(groupCount).fill(0);

	for (let i = 0; i < n; i += 1) {
		for (const prev of beforeItems[i]) {
			itemGraph[prev].push(i);
			itemIndeg[i] += 1;
			const gFrom = itemGroup[prev];
			const gTo = itemGroup[i];
			if (gFrom !== gTo) {
				groupGraph[gFrom].push(gTo);
				groupIndeg[gTo] += 1;
			}
		}
	}

	const topo = (graph, indeg) => {
		const queue = [];
		for (let i = 0; i < indeg.length; i += 1) {
			if (indeg[i] === 0) {
				queue.push(i);
			}
		}
		const order = [];
		let head = 0;
		while (head < queue.length) {
			const node = queue[head];
			head += 1;
			order.push(node);
			for (const next of graph[node]) {
				indeg[next] -= 1;
				if (indeg[next] === 0) {
					queue.push(next);
				}
			}
		}
		return order.length === indeg.length ? order : [];
	};

	const groupOrder = topo(groupGraph, groupIndeg);
	if (groupOrder.length === 0) {
		return [];
	}
	const itemOrder = topo(itemGraph, itemIndeg);
	if (itemOrder.length === 0) {
		return [];
	}

	const itemsByGroup = Array.from({ length: groupCount }, () => []);
	for (const item of itemOrder) {
		itemsByGroup[itemGroup[item]].push(item);
	}

	const result = [];
	for (const g of groupOrder) {
		for (const item of itemsByGroup[g]) {
			result.push(item);
		}
	}
	return result;
};
