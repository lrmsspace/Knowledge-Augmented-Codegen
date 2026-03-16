// Source: https://leetcode.com/problems/pacific-atlantic-water-flow/   |   Difficulty: Medium
//
// Problem Description:
// There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean. The Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the island's right and bottom edges.
//
// The island is partitioned into a grid of square cells. You are given an m x n integer matrix heights where heights[r][c] represents the height above sea level of the cell at coordinate (r, c).
//
// The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is less than or equal to the current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.
//
// Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.
//
// Example:
// Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
// Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
// Explanation: The following cells can flow to the Pacific and Atlantic oceans, as shown below:
// [0,4]: [0,4] -> Pacific Ocean 
//        [0,4] -> Atlantic Ocean
// [1,3]: [1,3] -> [0,3] -> Pacific Ocean 
//        [1,3] -> [1,4] -> Atlantic Ocean
// [1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean 
//        [1,4] -> Atlantic Ocean
// [2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean 
//        [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
// [3,0]: [3,0] -> Pacific Ocean 
//        [3,0] -> [4,0] -> Atlantic Ocean
// [3,1]: [3,1] -> [3,0] -> Pacific Ocean 
//        [3,1] -> [4,1] -> Atlantic Ocean
// [4,0]: [4,0] -> Pacific Ocean 
//        [4,0] -> Atlantic Ocean
// Note that there are other possible paths for these cells to flow to the Pacific and Atlantic oceans.
//
// Constraints:
// m == heights.length
// 	n == heights[r].length
// 	1 <= m, n <= 200
// 	0 <= heights[r][c] <= 105
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
// - Maximum flow - Push-relabel algorithm (graph, queue, simulation)
//   • When to use: Used for finding the maximum flow in a flow network. It is particularly efficient for dense graphs or when the Ford-Fulkerson method is too slow due to many augmenting paths.
//   • Idea: The Push-relabel algorithm computes maximum flow by maintaining a preflow and a height function, iteratively pushing excess flow from higher to lower nodes and relabeling nodes when flow cannot be pushed. It typically achieves a time complexity of O(V^2 * E) or O(V^3) with specific implementations.
//   • Invariants: For any edge (u, v) with positive residual capacity, h(u) <= h(v) + 1.; The source s always has h(s) = |V| and the sink t always has h(t) = 0.
//   • Tips: Initialize preflow by saturating edges from the source.; Initialize source height to |V| and others to 0.
//   • Pitfalls: Incorrectly handling residual capacities.; Not maintaining the height invariant during pushes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

#include <stdlib.h>

static void bfsFromOcean(int** heights, int rows, int cols, unsigned char* reachable, int* queue, int isPacific) {
	int head = 0;
	int tail = 0;
	int r;
	int c;

	if (isPacific) {
		for (c = 0; c < cols; ++c) {
			int idxTop = c;
			if (!reachable[idxTop]) {
				reachable[idxTop] = 1;
				queue[tail++] = idxTop;
			}
		}
		for (r = 0; r < rows; ++r) {
			int idxLeft = r * cols;
			if (!reachable[idxLeft]) {
				reachable[idxLeft] = 1;
				queue[tail++] = idxLeft;
			}
		}
	} else {
		int lastRow = rows - 1;
		int lastCol = cols - 1;
		for (c = 0; c < cols; ++c) {
			int idxBottom = lastRow * cols + c;
			if (!reachable[idxBottom]) {
				reachable[idxBottom] = 1;
				queue[tail++] = idxBottom;
			}
		}
		for (r = 0; r < rows; ++r) {
			int idxRight = r * cols + lastCol;
			if (!reachable[idxRight]) {
				reachable[idxRight] = 1;
				queue[tail++] = idxRight;
			}
		}
	}

	while (head < tail) {
		int idx = queue[head++];
		int row = idx / cols;
		int col = idx % cols;
		int currentHeight = heights[row][col];

		if (row > 0) {
			int nidx = (row - 1) * cols + col;
			if (!reachable[nidx] && heights[row - 1][col] >= currentHeight) {
				reachable[nidx] = 1;
				queue[tail++] = nidx;
			}
		}
		if (row + 1 < rows) {
			int nidx = (row + 1) * cols + col;
			if (!reachable[nidx] && heights[row + 1][col] >= currentHeight) {
				reachable[nidx] = 1;
				queue[tail++] = nidx;
			}
		}
		if (col > 0) {
			int nidx = row * cols + (col - 1);
			if (!reachable[nidx] && heights[row][col - 1] >= currentHeight) {
				reachable[nidx] = 1;
				queue[tail++] = nidx;
			}
		}
		if (col + 1 < cols) {
			int nidx = row * cols + (col + 1);
			if (!reachable[nidx] && heights[row][col + 1] >= currentHeight) {
				reachable[nidx] = 1;
				queue[tail++] = nidx;
			}
		}
	}
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pacificAtlantic(int** heights, int heightsSize, int* heightsColSize, int* returnSize, int** returnColumnSizes) {
	int rows;
	int cols;
	int total;
	unsigned char* pacificReachable;
	unsigned char* atlanticReachable;
	int* queue;
	int count;
	int** result;
	int* colSizes;
	int r;
	int c;
	int writeIndex;

	*returnSize = 0;
	*returnColumnSizes = NULL;

	if (heights == NULL || heightsColSize == NULL || heightsSize <= 0 || heightsColSize[0] <= 0) {
		return NULL;
	}

	rows = heightsSize;
	cols = heightsColSize[0];
	total = rows * cols;

	pacificReachable = (unsigned char*)calloc((size_t)total, sizeof(unsigned char));
	atlanticReachable = (unsigned char*)calloc((size_t)total, sizeof(unsigned char));
	queue = (int*)malloc((size_t)total * sizeof(int));

	if (pacificReachable == NULL || atlanticReachable == NULL || queue == NULL) {
		free(pacificReachable);
		free(atlanticReachable);
		free(queue);
		return NULL;
	}

	bfsFromOcean(heights, rows, cols, pacificReachable, queue, 1);
	bfsFromOcean(heights, rows, cols, atlanticReachable, queue, 0);

	count = 0;
	for (r = 0; r < rows; ++r) {
		for (c = 0; c < cols; ++c) {
			int idx = r * cols + c;
			if (pacificReachable[idx] && atlanticReachable[idx]) {
				++count;
			}
		}
	}

	result = (int**)malloc((size_t)count * sizeof(int*));
	colSizes = (int*)malloc((size_t)count * sizeof(int));
	if ((count > 0 && (result == NULL || colSizes == NULL)) || (count == 0 && (result == NULL || colSizes == NULL))) {
		free(pacificReachable);
		free(atlanticReachable);
		free(queue);
		free(result);
		free(colSizes);
		return NULL;
	}

	writeIndex = 0;
	for (r = 0; r < rows; ++r) {
		for (c = 0; c < cols; ++c) {
			int idx = r * cols + c;
			if (pacificReachable[idx] && atlanticReachable[idx]) {
				int* point = (int*)malloc(2 * sizeof(int));
				if (point == NULL) {
					int i;
					for (i = 0; i < writeIndex; ++i) {
						free(result[i]);
					}
					free(result);
					free(colSizes);
					free(pacificReachable);
					free(atlanticReachable);
					free(queue);
					*returnSize = 0;
					*returnColumnSizes = NULL;
					return NULL;
				}
				point[0] = r;
				point[1] = c;
				result[writeIndex] = point;
				colSizes[writeIndex] = 2;
				++writeIndex;
			}
		}
	}

	free(pacificReachable);
	free(atlanticReachable);
	free(queue);

	*returnSize = count;
	*returnColumnSizes = colSizes;
	return result;
}
