// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-arrays-similar/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integer arrays nums and target, of the same length.
//
// In one operation, you can choose any two distinct indices i and j where 0 <= i, j < nums.length and:
//
//
// 	set nums[i] = nums[i] + 2 and
// 	set nums[j] = nums[j] - 2.
//
//
// Two arrays are considered to be similar if the frequency of each element is the same.
//
// Return the minimum number of operations required to make nums similar to target. The test cases are generated such that nums can always be similar to target.
//
// Example:
// Input: nums = [8,12,6], target = [2,14,10]
// Output: 2
// Explanation: It is possible to make nums similar to target in two operations:
// - Choose i = 0 and j = 2, nums = [10,12,4].
// - Choose i = 1 and j = 2, nums = [10,14,2].
// It can be shown that 2 is the minimum number of operations needed.
//
// Constraints:
// n == nums.length == target.length
// 	1 <= n <= 105
// 	1 <= nums[i], target[i] <= 106
// 	It is possible to make nums similar to target.
//
// Helpful references (internal KB):
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - Manhattan Distance (geometry, number, coordinate-compress)
//   • When to use: Use when calculating distance between two points on a grid where movement is restricted to horizontal and vertical directions. It is also useful for problems involving maximizing or minimizing sums of absolute coordinate differences, often transformable to Chebyshev distance.
//   • Idea: Manhattan distance measures the sum of absolute differences of Cartesian coordinates between two points. It can be transformed into a Chebyshev distance problem by rotating coordinates, enabling efficient O(N) max/min distance calculations.
//   • Invariants: For any two points P1=(x1, y1) and P2=(x2, y2), the Manhattan distance is always non-negative.; The transformed points P1'=(x1+y1, y1-x1) and P2'=(x2+y2, y2-x2) satisfy Chebyshev(P1', P2') == Manhattan(P1, P2).
//   • Tips: Consider transforming to Chebyshev distance for max/min distance problems.; The transformation involves rotating coordinates: (x, y) -> (x+y, y-x).
//   • Pitfalls: Confusing with Euclidean distance, which allows diagonal movement.; Incorrectly applying coordinate transformation (e.g., wrong signs).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long makeSimilar(int[] nums, int[] target) {
        long ans = 0;
        List<Integer> oddNums = new ArrayList<>();
        List<Integer> evenNums = new ArrayList<>();
        List<Integer> oddTarget = new ArrayList<>();
        List<Integer> evenTarget = new ArrayList<>();

        for (int i = 0; i < nums.length; i++) {
            if (nums[i] % 2 == 0) {
                evenNums.add(nums[i]);
            } else {
                oddNums.add(nums[i]);
            }

            if (target[i] % 2 == 0) {
                evenTarget.add(target[i]);
            } else {
                oddTarget.add(target[i]);
            }
        }

        Collections.sort(oddNums);
        Collections.sort(evenNums);
        Collections.sort(oddTarget);
        Collections.sort(evenTarget);

        for (int i = 0; i < oddNums.size(); i++) {
            ans += Math.abs(oddNums.get(i) - oddTarget.get(i)) / 2;
        }

        for (int i = 0; i < evenNums.size(); i++) {
            ans += Math.abs(evenNums.get(i) - evenTarget.get(i)) / 2;
        }

        return ans;         
    }
}
