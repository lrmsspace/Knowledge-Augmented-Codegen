// Source: https://leetcode.com/problems/contains-duplicate-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers indexDiff and valueDiff.
//
// Find a pair of indices (i, j) such that:
//
//
// 	i != j,
// 	abs(i - j) <= indexDiff.
// 	abs(nums[i] - nums[j]) <= valueDiff, and
//
//
// Return true if such pair exists or false otherwise.
//
// Example:
// Input: nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
// Output: true
// Explanation: We can choose (i, j) = (0, 3).
// We satisfy the three conditions:
// i != j --> 0 != 3
// abs(i - j) <= indexDiff --> abs(0 - 3) <= 3
// abs(nums[i] - nums[j]) <= valueDiff --> abs(1 - 1) <= 0
//
// Constraints:
// 2 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	1 <= indexDiff <= nums.length
// 	0 <= valueDiff <= 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

#include <stdbool.h>
#include <stdlib.h>

static long long getBucketId(long long x, long long width) {
	if (x >= 0) {
		return x / width;
	}
	return ((x + 1) / width) - 1;
}

static int hashIndex(long long key, int cap) {
	unsigned long long x = (unsigned long long)key;
	x ^= x >> 33;
	x *= 0xff51afd7ed558ccdULL;
	x ^= x >> 33;
	x *= 0xc4ceb9fe1a85ec53ULL;
	x ^= x >> 33;
	return (int)(x & (unsigned long long)(cap - 1));
}

static int mapFind(long long* keys, int* state, int cap, long long key) {
	int idx = hashIndex(key, cap);
	while (state[idx] != 0) {
		if (state[idx] == 1 && keys[idx] == key) {
			return idx;
		}
		idx = (idx + 1) & (cap - 1);
	}
	return -1;
}

static int mapFindInsertPos(long long* keys, int* state, int cap, long long key) {
	int idx = hashIndex(key, cap);
	int firstDeleted = -1;
	while (state[idx] != 0) {
		if (state[idx] == 1 && keys[idx] == key) {
			return idx;
		}
		if (state[idx] == 2 && firstDeleted == -1) {
			firstDeleted = idx;
		}
		idx = (idx + 1) & (cap - 1);
	}
	return (firstDeleted == -1) ? idx : firstDeleted;
}

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int indexDiff, int valueDiff) {
	int i;
	int cap;
	long long width;
	long long* keys;
	long long* vals;
	int* state;

	if (nums == NULL || numsSize <= 1 || indexDiff <= 0 || valueDiff < 0) {
		return false;
	}

	width = (long long)valueDiff + 1LL;

	cap = 1;
	while (cap < (indexDiff + 1) * 4 && cap < (1 << 29)) {
		cap <<= 1;
	}

	keys = (long long*)malloc((size_t)cap * sizeof(long long));
	vals = (long long*)malloc((size_t)cap * sizeof(long long));
	state = (int*)malloc((size_t)cap * sizeof(int));
	if (keys == NULL || vals == NULL || state == NULL) {
		free(keys);
		free(vals);
		free(state);
		return false;
	}

	for (i = 0; i < cap; i++) {
		state[i] = 0;
	}

	for (i = 0; i < numsSize; i++) {
		long long x = (long long)nums[i];
		long long id = getBucketId(x, width);
		int pos;

		pos = mapFind(keys, state, cap, id);
		if (pos != -1) {
			free(keys);
			free(vals);
			free(state);
			return true;
		}

		pos = mapFind(keys, state, cap, id - 1);
		if (pos != -1) {
			long long diff = x - vals[pos];
			if (diff < 0) {
				diff = -diff;
			}
			if (diff <= (long long)valueDiff) {
				free(keys);
				free(vals);
				free(state);
				return true;
			}
		}

		pos = mapFind(keys, state, cap, id + 1);
		if (pos != -1) {
			long long diff = x - vals[pos];
			if (diff < 0) {
				diff = -diff;
			}
			if (diff <= (long long)valueDiff) {
				free(keys);
				free(vals);
				free(state);
				return true;
			}
		}

		pos = mapFindInsertPos(keys, state, cap, id);
		keys[pos] = id;
		vals[pos] = x;
		state[pos] = 1;

		if (i >= indexDiff) {
			long long oldX = (long long)nums[i - indexDiff];
			long long oldId = getBucketId(oldX, width);
			int oldPos = mapFind(keys, state, cap, oldId);
			if (oldPos != -1) {
				state[oldPos] = 2;
			}
		}
	}

	free(keys);
	free(vals);
	free(state);
	return false;
}
