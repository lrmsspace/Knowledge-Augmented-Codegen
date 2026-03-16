// Source: https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-ii/   |   Difficulty: Hard
//
// Problem Description:
// There are n points on an infinite plane. You are given two integer arrays xCoord and yCoord where (xCoord[i], yCoord[i]) represents the coordinates of the ith point.
//
// Your task is to find the maximum area of a rectangle that:
//
//
// 	Can be formed using four of these points as its corners.
// 	Does not contain any other point inside or on its border.
// 	Has its edges parallel to the axes.
//
//
// Return the maximum area that you can obtain or -1 if no such rectangle is possible.
//
// Example:
// Input: xCoord = [1,1,3,3], yCoord = [1,3,1,3]
//
// Output: 4
//
// Explanation:
//
//
//
// We can make a rectangle with these 4 points as corners and there is no other point that lies inside or on the border. Hence, the maximum possible area would be 4.
//
// Constraints:
// 1 <= xCoord.length == yCoord.length <= 2 * 105
// 	0 <= xCoord[i], yCoord[i] <= 8 * 107
// 	All the given points are unique.
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, divide-and-conquer)
//   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
//   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
//   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
//   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
// - Point location in O(logn) (geometry, ds, simulation)
//   • When to use: Use when needing to efficiently determine which region (face or edge) of a planar subdivision a given query point lies within, especially for multiple online queries.
//   • Idea: This algorithm preprocesses a planar subdivision to answer point location queries in logarithmic time. It typically involves building a specialized data structure, possibly persistent, to quickly identify the containing face or edge for any given point.
//   • Invariants: The search process always maintains the invariant that the query point is within the current candidate region.; After each step, the search space for the point's location is reduced by a constant factor.
//   • Tips: Use a suitable geometric data structure like a trapezoidal map or persistent segment tree.; Carefully handle points lying exactly on edges or vertices.
//   • Pitfalls: Degenerate cases (vertical edges, collinear points) require careful handling.; Floating-point precision errors can lead to incorrect classifications.
// - Lattice points inside non-lattice polygon (geometry, number, counting, recursion)
//   • When to use: Use this when you need to count integer coordinate points strictly inside a polygon whose vertices are not restricted to integer coordinates. It's suitable for problems requiring precise geometric counting with non-lattice boundaries.
//   • Idea: This algorithm counts lattice points within a polygon with arbitrary vertices by summing signed contributions from each edge. It reduces the problem to evaluating sums of floor functions, sum(floor(kx+b)), which is solved recursively, typically achieving logarithmic complexity per edge.
//   • Invariants: The sum sum(floor(kx+b)) correctly accumulates points below the current edge segment.; After coordinate transformations, the problem reduces to a sum over a non-negative range with non-negative k and b.
//   • Tips: Decompose the polygon into signed areas under each edge, similar to the shoelace formula.; Handle edge cases where k or b are negative by appropriate transformations.
//   • Pitfalls: Floating point precision issues when calculating k and b or during transformations.; Incorrectly handling boundary points (points on edges or vertices).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        int n = xCoord.size();
        if (n != yCoord.size() || n == 0) return -1;

        // Coordinate compression for x
        vector<int> xs = xCoord;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        // Build points with compressed x
        struct Point {
            int y;
            int xIdx;
        };
        vector<Point> pts(n);
        for (int i = 0; i < n; ++i) {
            pts[i].y = yCoord[i];
            pts[i].xIdx = lower_bound(xs.begin(), xs.end(), xCoord[i]) - xs.begin();
        }
        sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
            return a.y == b.y ? a.xIdx < b.xIdx : a.y < b.y;
        });

        // Segment tree for range max of last seen y per x index
        struct SegTree {
            int size;
            vector<int> data;

            SegTree(int n) : size(n), data(4 * n, -1) {}

            void update(int idx, int val, int node, int nodeL, int nodeR) {
                if (nodeL == nodeR) {
                    data[node] = val;
                    return;
                }
                int mid = (nodeL + nodeR) / 2;
                if (idx <= mid) update(idx, val, 2 * node + 1, nodeL, mid);
                else update(idx, val, 2 * node + 2, mid + 1, nodeR);
                data[node] = max(data[2 * node + 1], data[2 * node + 2]);
            }

            int rangeMax(int l, int r, int node, int nodeL, int nodeR) {
                if (r < nodeL || l > nodeR) return -1;
                if (l <= nodeL && nodeR <= r) return data[node];
                int mid = (nodeL + nodeR) / 2;
                return max(rangeMax(l, r, 2 * node + 1, nodeL, mid),
                           rangeMax(l, r, 2 * node + 2, mid + 1, nodeR));
            }

            void update(int idx, int val) {
                update(idx, val, 0, 0, size - 1);
            }   
            int rangeMax(int l, int r) {
                return rangeMax(l, r, 0, 0, size - 1);
            }   
        };
        SegTree segTree(xs.size());
        long long maxArea = -1;
        for (const auto& pt : pts) {
            int lastY = segTree.rangeMax(pt.xIdx, pt.xIdx);
            if (lastY != -1) {
                long long area = static_cast<long long>(xs[pt.xIdx + 1] - xs[pt.xIdx]) * (pt.y - lastY);
                maxArea = max(maxArea, area);
            }
            segTree.update(pt.xIdx, pt.y);
        }
        return maxArea;  
    }
};
