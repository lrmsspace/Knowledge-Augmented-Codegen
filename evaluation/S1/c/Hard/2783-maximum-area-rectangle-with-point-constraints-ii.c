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
// 	Has its edges parallel to the axes.
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
// 	0 <= xCoord[i], yCoord[i] <= 8 * 107
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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

#include <stdlib.h>

struct Point {
	int y;
	int xIdx;
};

static int cmp_int(const void* a, const void* b) {
	int va = *(const int*)a, vb = *(const int*)b;
	if (va == vb) return 0;
	return va < vb ? -1 : 1;
}

static int cmp_point(const void* a, const void* b) {
	const struct Point* pa = (const struct Point*)a;
	const struct Point* pb = (const struct Point*)b;
	if (pa->y != pb->y) return pa->y < pb->y ? -1 : 1;
	if (pa->xIdx == pb->xIdx) return 0;
	return pa->xIdx < pb->xIdx ? -1 : 1;
}

static int lower_bound_idx(const int* arr, int len, int target) {
	int l = 0, r = len;
	while (l < r) {
		int mid = l + ((r - l) >> 1);
		if (arr[mid] < target)
			l = mid + 1;
		else
			r = mid;
	}
	return l;
}

struct SegTree {
	int sizePow;
	int* data;
};

static struct SegTree seg_build(int n) {
	struct SegTree t;
	t.sizePow = 1;
	while (t.sizePow < n) t.sizePow <<= 1;
	t.data = (int*)malloc(sizeof(int) * (t.sizePow << 1));
	if (t.data) {
		for (int i = 0; i < (t.sizePow << 1); ++i) t.data[i] = -1;
	}
	return t;
}

static void seg_point_update(struct SegTree* t, int pos, int val) {
	pos += t->sizePow;
	t->data[pos] = val;
	for (pos >>= 1; pos > 0; pos >>= 1) {
		int lv = t->data[pos << 1];
		int rv = t->data[(pos << 1) | 1];
		t->data[pos] = lv > rv ? lv : rv;
	}
}

static int seg_range_max(const struct SegTree* t, int l, int r) {
	if (l > r) return -1;
	l += t->sizePow;
	r += t->sizePow;
	int res = -1;
	while (l <= r) {
		if (l & 1) {
			if (t->data[l] > res) res = t->data[l];
			++l;
		}
		if (!(r & 1)) {
			if (t->data[r] > res) res = t->data[r];
			--r;
		}
		l >>= 1;
		r >>= 1;
	}
	return res;
}

long long maxRectangleArea(int* xCoord, int xCoordSize, int* yCoord, int yCoordSize) {
	if (xCoordSize != yCoordSize || xCoordSize == 0) return -1;

	int n = xCoordSize;

	/* coordinate compression for x */
	int* xs = (int*)malloc(sizeof(int) * n);
	if (!xs) return -1;
	for (int i = 0; i < n; ++i) xs[i] = xCoord[i];
	qsort(xs, n, sizeof(int), cmp_int);
	int m = 0;
	for (int i = 0; i < n; ++i) {
		if (i == 0 || xs[i] != xs[i - 1]) xs[m++] = xs[i];
	}

	/* build points with compressed x */
	struct Point* pts = (struct Point*)malloc(sizeof(struct Point) * n);
	if (!pts) { free(xs); return -1; }
	for (int i = 0; i < n; ++i) {
		pts[i].y = yCoord[i];
		pts[i].xIdx = lower_bound_idx(xs, m, xCoord[i]);
	}
	qsort(pts, n, sizeof(struct Point), cmp_point);

	/* segment tree for range max of last seen y per x index */
	struct SegTree seg = seg_build(m);
	if (!seg.data) { free(xs); free(pts); return -1; }

	int* lastSeen = (int*)malloc(sizeof(int) * m);
	if (!lastSeen) { free(xs); free(pts); free(seg.data); return -1; }
	for (int i = 0; i < m; ++i) lastSeen[i] = -1;

	long long best = -1;

	int idx = 0;
	while (idx < n) {
		int y = pts[idx].y;
		int start = idx;
		while (idx < n && pts[idx].y == y) ++idx;
		int k = idx - start;
		int* rowX = (int*)malloc(sizeof(int) * k);
		if (!rowX) { free(xs); free(pts); free(seg); free(lastSeen); return -1; }
		for (int i = 0; i < k; ++i) rowX[i] = pts[start + i].xIdx;
		/* rowX already sorted by xIdx due to overall sort */

		for (int i = 0; i + 1 < k; ++i) {
			int l = rowX[i];
			int r = rowX[i + 1];
			int lb = lastSeen[l];
			int rb = lastSeen[r];
			if (lb == rb && lb != -1) {
				int insideMax = (l + 1 <= r - 1) ? seg_range_max(&seg, l + 1, r - 1) : -1;
				if (insideMax < lb) {
					long long area = (long long)(xs[r] - xs[l]) * (long long)(y - lb);
					if (area > best) best = area;
				}
			}
		}

		for (int i = 0; i < k; ++i) {
			int pos = rowX[i];
			lastSeen[pos] = y;
			seg_point_update(&seg, pos, y);
		}

		free(rowX);
	}

	free(xs);
	free(pts);
	free(seg.data);
	free(lastSeen);

	return best;
}
