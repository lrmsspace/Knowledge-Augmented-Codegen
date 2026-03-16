// Source: https://leetcode.com/problems/minimum-space-wasted-from-packaging/   |   Difficulty: Hard
//
// Problem Description:
// You have n packages that you are trying to place in boxes, one package in each box. There are m suppliers that each produce boxes of different sizes (with infinite supply). A package can be placed in a box if the size of the package is less than or equal to the size of the box.
//
// The package sizes are given as an integer array packages, where packages[i] is the size of the ith package. The suppliers are given as a 2D integer array boxes, where boxes[j] is an array of box sizes that the jth supplier produces.
//
// You want to choose a single supplier and use boxes from them such that the total wasted space is minimized. For each package in a box, we define the space wasted to be size of the box - size of the package. The total wasted space is the sum of the space wasted in all the boxes.
//
//
// 	For example, if you have to fit packages with sizes [2,3,5] and the supplier offers boxes of sizes [4,8], you can fit the packages of size-2 and size-3 into two boxes of size-4 and the package with size-5 into a box of size-8. This would result in a waste of (4-2) + (4-3) + (8-5) = 6.
//
//
// Return the minimum total wasted space by choosing the box supplier optimally, or -1 if it is impossible to fit all the packages inside boxes. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: packages = [2,3,5], boxes = [[4,8],[2,8]]
// Output: 6
// Explanation: It is optimal to choose the first supplier, using two size-4 boxes and one size-8 box.
// The total waste is (4-2) + (4-3) + (8-5) = 6.
//
// Constraints:
// n == packages.length
// 	m == boxes.length
// 	1 <= n <= 105
// 	1 <= m <= 105
// 	1 <= packages[i] <= 105
// 	1 <= boxes[j].length <= 105
// 	1 <= boxes[j][k] <= 105
// 	sum(boxes[j].length) <= 105
// 	The elements in boxes[j] are distinct.
//
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when tasks with associated processing times and costs need to be sequenced on a single machine to minimize a total objective function, typically involving weighted completion times or penalties. The optimal sequence is found by a greedy sort.
//   • Idea: This method finds an optimal schedule for jobs on a single machine by sorting them according to a greedy criterion derived from an exchange argument. It achieves an optimal solution with O(N log N) time complexity, dominated by the sorting step.
//   • Invariants: The relative order of any two jobs i and j in the sorted sequence is consistent with the greedy comparison rule.; Any prefix of the sorted schedule represents an optimal ordering for the jobs within that prefix.
//   • Tips: Clearly define the objective function to be minimized.; Formulate the greedy sorting rule using an exchange argument for any two adjacent jobs.
//   • Pitfalls: Incorrectly deriving the greedy comparison criterion.; Applying this method to problems with multiple machines or complex precedence constraints without adaptation.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minWastedSpace(int[] packages, int[][] boxes) {
        int mod = 1_000_000_007;
        long totalPackageSize = 0;
        for (int pkg : packages) {
            totalPackageSize += pkg;
        }
        Arrays.sort(packages);

        long minWaste = Long.MAX_VALUE;
        for (int[] supplierBoxes : boxes) {
            Arrays.sort(supplierBoxes);
            if (supplierBoxes[supplierBoxes.length - 1] < packages[packages.length - 1]) {
                continue; // This supplier cannot fit the largest package
            }

            long waste = 0;
            int boxIndex = 0;
            for (int pkg : packages) {
                while (boxIndex < supplierBoxes.length && supplierBoxes[boxIndex] < pkg) {
                    boxIndex++;
                }
                waste += supplierBoxes[boxIndex] - pkg;
            }
            minWaste = Math.min(minWaste, waste);
        }

        return minWaste == Long.MAX_VALUE ? -1 : (int)(minWaste % mod);         
    }
}
