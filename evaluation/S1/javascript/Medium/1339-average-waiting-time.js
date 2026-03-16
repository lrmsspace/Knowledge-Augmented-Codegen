// Source: https://leetcode.com/problems/average-waiting-time/   |   Difficulty: Medium
//
// Problem Description:
// There is a restaurant with a single chef. You are given an array customers, where customers[i] = [arrivali, timei]:
//
//
// 	arrivali is the arrival time of the ith customer. The arrival times are sorted in non-decreasing order.
// 	timei is the time needed to prepare the order of the ith customer.
//
//
// When a customer arrives, he gives the chef his order, and the chef starts preparing it once he is idle. The customer waits till the chef finishes preparing his order. The chef does not prepare food for more than one customer at a time. The chef prepares food for customers in the order they were given in the input.
//
// Return the average waiting time of all customers. Solutions within 10-5 from the actual answer are considered accepted.
//
// Example:
// Input: customers = [[1,2],[2,5],[4,3]]
// Output: 5.00000
// Explanation:
// 1) The first customer arrives at time 1, the chef takes his order and starts preparing it immediately at time 1, and finishes at time 3, so the waiting time of the first customer is 3 - 1 = 2.
// 2) The second customer arrives at time 2, the chef takes his order and starts preparing it at time 3, and finishes at time 8, so the waiting time of the second customer is 8 - 2 = 6.
// 3) The third customer arrives at time 4, the chef takes his order and starts preparing it at time 8, and finishes at time 11, so the waiting time of the third customer is 11 - 4 = 7.
// So the average waiting time = (2 + 6 + 7) / 3 = 5.
//
// Constraints:
// 1 <= customers.length <= 105
// 	1 <= arrivali, timei <= 104
// 	arrivali <= arrivali+1
//
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
// - Rejection Sampling in Artificial Intelligence (number, rejection-sampling, randomized)
//   • When to use: When you need to sample from a complex target probability distribution that is difficult to sample directly, especially when its probability density function is known up to a normalizing constant.
//   • Idea: Rejection sampling is a Monte Carlo method that generates samples from a target distribution by drawing from a simpler proposal distribution and accepting or rejecting based on a probability ratio. Its average time complexity is O(M * sample_cost_q) per accepted sample, where M bounds the ratio of target to proposal PDFs.
//   • Invariants: The generated sample x is always within the domain of the target distribution.; The constant M always satisfies p(x) <= M * q(x) for all x.
//   • Tips: Choose a proposal distribution that is easy to sample from.; Ensure the proposal distribution closely resembles the target distribution.
//   • Pitfalls: High rejection rate if proposal distribution is poorly chosen.; Difficulty in finding an optimal M for complex or high-dimensional distributions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} customers
 * @return {number}
 */
var averageWaitingTime = function(customers) {
	let totalWaitingTime = 0;
	let currentTime = 0;

	for (const [arrival, time] of customers) {
		// If the chef is idle before the customer arrives, start at the customer's arrival time
		currentTime = Math.max(currentTime, arrival);
		// Calculate waiting time for the current customer
		totalWaitingTime += (currentTime - arrival + time);
		// Update current time after preparing the order
		currentTime += time;
	}

	return totalWaitingTime / customers.length;
};
