// Source: https://leetcode.com/problems/sliding-window-median/   |   Difficulty: Hard
//
// Problem Description:
// The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.
//
//
// 	For examples, if arr = [2,3,4], the median is 3.
// 	For examples, if arr = [1,2,3,4], the median is (2 + 3) / 2 = 2.5.
//
//
// You are given an integer array nums and an integer k. There is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
//
// Return the median array for each window in the original array. Answers within 10-5 of the actual value will be accepted.
//
// Example:
// Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
// Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
// Explanation: 
// Window position                Median
// ---------------                -----
// [1  3  -1] -3  5  3  6  7        1
//  1 [3  -1  -3] 5  3  6  7       -1
//  1  3 [-1  -3  5] 3  6  7       -1
//  1  3  -1 [-3  5  3] 6  7        3
//  1  3  -1  -3 [5  3  6] 7        5
//  1  3  -1  -3  5 [3  6  7]       6
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	-231 <= nums[i] <= 231 - 1
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
// - Minimum Spanning Trees (graph, heap, mst-kruskal)
//   • When to use: Use Kruskal's algorithm to find a subset of edges that connects all vertices in an edge-weighted graph with the minimum possible total edge weight. It is suitable for sparse graphs or when edges are easily sorted.
//   • Idea: Kruskal's algorithm is a greedy algorithm that builds a Minimum Spanning Tree (MST) by iteratively adding the cheapest available edge that does not form a cycle. It typically runs in O(E log E) time, dominated by sorting edges or Union-Find operations.
//   • Invariants: The set of edges chosen so far forms a forest, where each tree is a component of the MST.; All edges considered so far that do not form a cycle are part of the current forest.
//   • Tips: Sort all edges by their weights in non-decreasing order before processing.; Utilize a Union-Find data structure to efficiently track connected components and detect cycles.
//   • Pitfalls: Incorrectly implementing Union-Find can lead to performance bottlenecks or incorrect cycle detection.; Failing to sort edges correctly will result in a non-minimal spanning tree.
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
double* medianSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
	if (numsSize <= 0 || k <= 0 || k > numsSize) {
		*returnSize = 0;
		return NULL;
	}

	typedef long long ll;
	typedef struct { ll val; int idx; } Item;
	typedef struct {
		Item *a;
		int cap;
		int size;
		int isMin; // 0: max-heap, 1: min-heap
	} Heap;

	// heap helpers
	#define PARENT(i) ((i) >> 1)
	#define LEFT(i)  ((i) << 1)
	static void heapInit(Heap *h, int cap, int isMin) {
		h->a = (Item*)malloc(sizeof(Item) * (cap + 1));
		h->cap = cap;
		h->size = 0;
		h->isMin = isMin;
	}
	static void heapFree(Heap *h) { free(h->a); h->a = NULL; }
	static int heapCompare(Heap *h, Item *x, Item *y) {
		if (h->isMin) {
			if (x->val != y->val) return x->val < y->val;
			return x->idx < y->idx;
		} else {
			if (x->val != y->val) return x->val > y->val;
			return x->idx < y->idx;
		}
	}
	static void heapSwap(Item *a, Item *b) { Item t = *a; *a = *b; *b = t; }
	static void heapPush(Heap *h, Item it) {
		if (h->size + 1 > h->cap) return; // should not happen
		int i = ++h->size;
		h->a[i] = it;
		while (i > 1 && heapCompare(h, &h->a[i], &h->a[PARENT(i)])) {
			heapSwap(&h->a[i], &h->a[PARENT(i)]);
			i = PARENT(i);
		}
	}
	static Item heapTop(Heap *h) { return h->a[1]; }
	static int heapEmpty(Heap *h) { return h->size == 0; }
	static Item heapPop(Heap *h) {
		Item ret = h->a[1];
		h->a[1] = h->a[h->size--];
		int i = 1;
		while (1) {
			int l = LEFT(i), r = l + 1, best = i;
			if (l <= h->size && heapCompare(h, &h->a[l], &h->a[best])) best = l;
			if (r <= h->size && heapCompare(h, &h->a[r], &h->a[best])) best = r;
			if (best == i) break;
			heapSwap(&h->a[i], &h->a[best]);
			i = best;
		}
		return ret;
	}
	static void heapCleanTop(Heap *h, int valid_left) {
		while (h->size > 0 && h->a[1].idx < valid_left) {
			heapPop(h);
		}
	}

	Heap lower, upper; // lower: max-heap, upper: min-heap
	heapInit(&lower, numsSize, 0);
	heapInit(&upper, numsSize, 1);

	int lowerCount = 0, upperCount = 0;
	int outCount = numsSize - k + 1;
	double *res = (double*)malloc(sizeof(double) * outCount);
	int resPos = 0;

	for (int i = 0; i < numsSize; ++i) {
		int left = i - k + 1;
		// clean invalid tops (indices < left)
		heapCleanTop(&lower, left > 0 ? left : 0);
		heapCleanTop(&upper, left > 0 ? left : 0);

		Item it; it.val = (ll)nums[i]; it.idx = i;
		if (lower.size == 0 || it.val <= heapTop(&lower).val) {
			heapPush(&lower, it);
			lowerCount++;
		} else {
			heapPush(&upper, it);
			upperCount++;
		}

		// rebalance counts
		if (lowerCount > upperCount + 1) {
			heapCleanTop(&lower, left > 0 ? left : 0);
			if (!heapEmpty(&lower)) {
				Item mv = heapPop(&lower);
				heapPush(&upper, mv);
				lowerCount--; upperCount++;
			}
		} else if (lowerCount < upperCount) {
			heapCleanTop(&upper, left > 0 ? left : 0);
			if (!heapEmpty(&upper)) {
				Item mv = heapPop(&upper);
				heapPush(&lower, mv);
				upperCount--; lowerCount++;
			}
		}

		if (i >= k - 1) {
			int valid_left = i - k + 1;
			// ensure tops are valid
			heapCleanTop(&lower, valid_left);
			heapCleanTop(&upper, valid_left);

			// compute median
			double median;
			if (k & 1) {
				median = (double)heapTop(&lower).val;
			} else {
				ll a = heapTop(&lower).val;
				ll b;
				if (upper.size > 0) b = heapTop(&upper).val;
				else b = a; // fallback
				median = ((double)a + (double)b) / 2.0;
			}
			res[resPos++] = median;

			// remove outgoing element from counts (lazy deletion by index)
			int outIdx = valid_left;
			ll outVal = (ll)nums[outIdx];
			// ensure lower top is valid for comparison
			heapCleanTop(&lower, valid_left);
			if (lower.size > 0 && outVal <= heapTop(&lower).val) {
				lowerCount--;
			} else {
				upperCount--;
			}
			// actual removal will happen lazily when those items reach the top
		}
	}

	heapFree(&lower);
	heapFree(&upper);
	*returnSize = resPos;
	return res;
}
