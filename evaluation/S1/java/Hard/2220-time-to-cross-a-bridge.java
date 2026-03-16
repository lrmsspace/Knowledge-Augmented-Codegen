// Source: https://leetcode.com/problems/time-to-cross-a-bridge/   |   Difficulty: Hard
//
// Problem Description:
// There are k workers who want to move n boxes from the right (old) warehouse to the left (new) warehouse. You are given the two integers n and k, and a 2D integer array time of size k x 4 where time[i] = [righti, picki, lefti, puti].
//
// The warehouses are separated by a river and connected by a bridge. Initially, all k workers are waiting on the left side of the bridge. To move the boxes, the ith worker can do the following:
//
//
// 	Cross the bridge to the right side in righti minutes.
// 	Pick a box from the right warehouse in picki minutes.
// 	Cross the bridge to the left side in lefti minutes.
// 	Put the box into the left warehouse in puti minutes.
//
//
// The ith worker is less efficient than the jth worker if either condition is met:
//
//
// 	lefti + righti > leftj + rightj
// 	lefti + righti == leftj + rightj and i > j
//
//
// The following rules regulate the movement of the workers through the bridge:
//
//
// 	Only one worker can use the bridge at a time.
// 	When the bridge is unused prioritize the least efficient worker (who have picked up the box) on the right side to cross. If not, prioritize the least efficient worker on the left side to cross.
// 	If enough workers have already been dispatched from the left side to pick up all the remaining boxes, no more workers will be sent from the left side.
//
//
// Return the elapsed minutes at which the last box reaches the left side of the bridge.
//
// Example:
// Input: n = 1, k = 3, time = [[1,1,2,1],[1,1,3,1],[1,1,4,1]]
//
// Output: 6
//
// Explanation:
//
//
// From 0 to 1 minutes: worker 2 crosses the bridge to the right.
// From 1 to 2 minutes: worker 2 picks up a box from the right warehouse.
// From 2 to 6 minutes: worker 2 crosses the bridge to the left.
// From 6 to 7 minutes: worker 2 puts a box at the left warehouse.
// The whole process ends after 7 minutes. We return 6 because the problem asks for the instance of time at which the last worker reaches the left side of the bridge.
//
// Constraints:
// 1 <= n, k <= 104
// 	time.length == k
// 	time[i].length == 4
// 	1 <= lefti, picki, righti, puti <= 1000
//
// Helpful references (internal KB):
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - Simulated Annealing (array, number, randomized, simulation)
//   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
//   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
//   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
//   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
//   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
// - Finding bridges in a graph in O(N+M) (graph, dfs)
//   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
//   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
//   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
//   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
//   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    static class Worker {
        int id;
        int efficiency;
        int[] time;
        Worker(int id, int efficiency, int[] time) {
            this.id = id;
            this.efficiency = efficiency;
            this.time = time;
        }
    }
    static class Event {
        int time;
        Worker worker;
        boolean toLeft;
        Event(int time, Worker worker, boolean toLeft) {
            this.time = time;
            this.worker = worker;
            this.toLeft = toLeft;
        }
    }
    
    public int findCrossingTime(int n, int k, int[][] time) {
        PriorityQueue<Worker> left = new PriorityQueue<>((a, b) -> a.efficiency != b.efficiency ? b.efficiency - a.efficiency : b.id - a.id);
        PriorityQueue<Worker> right = new PriorityQueue<>((a, b) -> a.efficiency != b.efficiency ? b.efficiency - a.efficiency : b.id - a.id);
        PriorityQueue<Event> events = new PriorityQueue<>((a, b) -> a.time != b.time ? a.time - b.time : a.worker.id - b.worker.id);

        for (int i = 0; i < k; i++) {
            left.offer(new Worker(i, time[i][0] + time[i][2], time[i]));
        }

        int currTime = 0;
        int boxesLeft = n;

        while (boxesLeft > 0 || !right.isEmpty() || !events.isEmpty()) {
            while (!events.isEmpty() && events.peek().time <= currTime) {
                Event event = events.poll();
                if (event.toLeft) {
                    left.offer(event.worker);
                } else {
                    right.offer(event.worker);
                }
            }

            if (!right.isEmpty()) {
                Worker worker = right.poll();
                currTime += worker.time[2];
                events.offer(new Event(currTime + worker.time[3], worker, true));
            } else if (boxesLeft > 0 && !left.isEmpty()) {
                Worker worker = left.poll();
                currTime += worker.time[0];
                events.offer(new Event(currTime + worker.time[1], worker, false));
                boxesLeft--;
            } else if (!events.isEmpty()) {
                currTime = events.peek().time;
            }
        }

        return currTime;            
    }
}
