// Source: https://leetcode.com/problems/construct-2d-grid-matching-graph-layout/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array edges representing an undirected graph having n nodes, where edges[i] = [ui, vi] denotes an edge between nodes ui and vi.
//
// Construct a 2D grid that satisfies these conditions:
//
//
// 	The grid contains all nodes from 0 to n - 1 in its cells, with each node appearing exactly once.
// 	Two nodes should be in adjacent grid cells (horizontally or vertically) if and only if there is an edge between them in edges.
//
//
// It is guaranteed that edges can form a 2D grid that satisfies the conditions.
//
// Return a 2D integer array satisfying the conditions above. If there are multiple solutions, return any of them.
//
// Example:
// Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]]
//
// Output: [[3,1],[2,0]]
//
// Explanation:
//
// Constraints:
// 2 <= n <= 5 * 104
// 	1 <= edges.length <= 105
// 	edges[i] = [ui, vi]
// 	0 <= ui < vi < n
// 	All the edges are distinct.
// 	The input is generated such that edges can form a 2D grid that satisfies the conditions.
//

class Solution {
    public int[][] constructGridLayout(int n, int[][] edges) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }

        int rows = 0, cols = 0;
        for (int i = 0; i < n; i++) {
            int degree = graph.get(i).size();
            if (degree > cols) {
                cols = degree;
            }
        }
        rows = n / cols;

        int[][] grid = new int[rows][cols];
        boolean[] visited = new boolean[n];
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(0);
        visited[0] = true;

        int r = 0, c = 0;
        while (!queue.isEmpty()) {
            int node = queue.poll();
            grid[r][c] = node;
            c++;
            if (c == cols) {
                c = 0;
                r++;
            }
            for (int neighbor : graph.get(node)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.offer(neighbor);
                }
            }
        }

        return grid;            
    }
}
