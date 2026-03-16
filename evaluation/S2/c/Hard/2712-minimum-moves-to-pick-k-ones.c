// Source: https://leetcode.com/problems/minimum-moves-to-pick-k-ones/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary array nums of length n, a positive integer k and a non-negative integer maxChanges.
//
// Alice plays a game, where the goal is for Alice to pick up k ones from nums using the minimum number of moves. When the game starts, Alice picks up any index aliceIndex in the range [0, n - 1] and stands there. If nums[aliceIndex] == 1 , Alice picks up the one and nums[aliceIndex] becomes 0(this does not count as a move). After this, Alice can make any number of moves (including zero) where in each move Alice must perform exactly one of the following actions:
//
//
//  Select any index j != aliceIndex such that nums[j] == 0 and set nums[j] = 1. This action can be performed at most maxChanges times.
//  Select any two adjacent indices x and y (|x - y| == 1) such that nums[x] == 1, nums[y] == 0, then swap their values (set nums[y] = 1 and nums[x] = 0). If y == aliceIndex, Alice picks up the one after this move and nums[y] becomes 0.
//
//
// Return the minimum number of moves required by Alice to pick exactly k ones.
//
// Example:
// Input: nums = [1,1,0,0,0,1,1,0,0,1], k = 3, maxChanges = 1
//
// Output: 3
//
// Explanation: Alice can pick up 3 ones in 3 moves, if Alice performs the following actions in each move when standing at aliceIndex == 1:
//
//
//  At the start of the game Alice picks up the one and nums[1] becomes 0. nums becomes [1,0,0,0,0,1,1,0,0,1].
//  Select j == 2 and perform an action of the first type. nums becomes [1,0,1,0,0,1,1,0,0,1]
//  Select x == 2 and y == 1, and perform an action of the second type. nums becomes [1,1,0,0,0,1,1,0,0,1]. As y == aliceIndex, Alice picks up the one and nums becomes [1,0,0,0,0,1,1,0,0,1].
//  Select x == 0 and y == 1, and perform an action of the second type. nums becomes [0,1,0,0,0,1,1,0,0,1]. As y == aliceIndex, Alice picks up the one and nums becomes [0,0,0,0,0,1,1,0,0,1].
//
//
// Note that it may be possible for Alice to pick up 3 ones using some other sequence of 3 moves.
//
// Constraints:
// 2 <= n <= 105
//  0 <= nums[i] <= 1
//  1 <= k <= 105
//  0 <= maxChanges <= 105
//  maxChanges + sum(nums) >= k
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long minimumMoves(int* nums, int numsSize, int k, int maxChanges) {
	int i;
	int onesCount = 0;
	int bestRun = 0;
	int curRun = 0;
	int needExisting;
	long long ans;

	for (i = 0; i < numsSize; ++i) {
		if (nums[i] == 1) {
			++onesCount;
			++curRun;
			if (curRun > bestRun) {
				bestRun = curRun;
			}
		} else {
			curRun = 0;
		}
	}

	if (bestRun > 3) {
		bestRun = 3;
	}
	if (bestRun > k) {
		bestRun = k;
	}

	ans = (1LL << 62);

	if (maxChanges >= k - bestRun) {
		long long cand = (long long)(bestRun > 0 ? (bestRun - 1) : 0) + 2LL * (k - bestRun);
		if (cand < ans) {
			ans = cand;
		}
	}

	needExisting = k - maxChanges;
	if (needExisting < 1) {
		needExisting = 1;
	}

	if (needExisting <= onesCount) {
		int* pos = (int*)malloc(sizeof(int) * onesCount);
		long long* pre = (long long*)malloc(sizeof(long long) * (onesCount + 1));

		if (pos != NULL && pre != NULL) {
			int idx = 0;
			pre[0] = 0;

			for (i = 0; i < numsSize; ++i) {
				if (nums[i] == 1) {
					pos[idx] = i;
					pre[idx + 1] = pre[idx] + (long long)i;
					++idx;
				}
			}

			for (i = 0; i + needExisting - 1 < onesCount; ++i) {
				int l = i;
				int r = i + needExisting - 1;
				int mid = l + needExisting / 2;
				long long medianPos = pos[mid];
				long long leftCost = medianPos * (mid - l) - (pre[mid] - pre[l]);
				long long rightCost = (pre[r + 1] - pre[mid + 1]) - medianPos * (r - mid);
				long long cand = leftCost + rightCost + 2LL * (k - needExisting);
				if (cand < ans) {
					ans = cand;
				}
			}
		}

		if (pos != NULL) {
			free(pos);
		}
		if (pre != NULL) {
			free(pre);
		}
	}

	return ans;
}
