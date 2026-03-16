// Source: https://leetcode.com/problems/number-of-orders-in-the-backlog/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array orders, where each orders[i] = [pricei, amounti, orderTypei] denotes that amounti orders have been placed of type orderTypei at the price pricei. The orderTypei is:
//
//
// 	0 if it is a batch of buy orders, or
// 	1 if it is a batch of sell orders.
//
//
// Note that orders[i] represents a batch of amounti independent orders with the same price and order type. All orders represented by orders[i] will be placed before all orders represented by orders[i+1] for all valid i.
//
// There is a backlog that consists of orders that have not been executed. The backlog is initially empty. When an order is placed, the following happens:
//
//
// 	If the order is a buy order, you look at the sell order with the smallest price in the backlog. If that sell order's price is smaller than or equal to the current buy order's price, they will match and be executed, and that sell order will be removed from the backlog. Else, the buy order is added to the backlog.
// 	Vice versa, if the order is a sell order, you look at the buy order with the largest price in the backlog. If that buy order's price is larger than or equal to the current sell order's price, they will match and be executed, and that buy order will be removed from the backlog. Else, the sell order is added to the backlog.
//
//
// Return the total amount of orders in the backlog after placing all the orders from the input. Since this number can be large, return it modulo 109 + 7.
//
// Example:
// Input: orders = [[10,5,0],[15,2,1],[25,1,1],[30,4,0]]
// Output: 6
// Explanation: Here is what happens with the orders:
// - 5 orders of type buy with price 10 are placed. There are no sell orders, so the 5 orders are added to the backlog.
// - 2 orders of type sell with price 15 are placed. There are no buy orders with prices larger than or equal to 15, so the 2 orders are added to the backlog.
// - 1 order of type sell with price 25 is placed. There are no buy orders with prices larger than or equal to 25 in the backlog, so this order is added to the backlog.
// - 4 orders of type buy with price 30 are placed. The first 2 orders are matched with the 2 sell orders of the least price, which is 15 and these 2 sell orders are removed from the backlog. The 3rd order is matched with the sell order of the least price, which is 25 and this sell order is removed from the backlog. Then, there are no more sell orders in the backlog, so the 4th order is added to the backlog.
// Finally, the backlog has 5 buy orders with price 10, and 1 buy order with price 30. So the total number of orders in the backlog is 6.
//
// Constraints:
// 1 <= orders.length <= 105
// 	orders[i].length == 3
// 	1 <= pricei, amounti <= 109
// 	orderTypei is either 0 or 1.
//
// Helpful references (internal KB):
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
// - Discrete Logarithm (array, number, binary-search, mod-exp)
//   • When to use: Use when solving for the exponent 'x' in the modular equation a^x = b (mod m), especially when 'm' is large and a and m are coprime. It's suitable for finding a solution within O(sqrt(m) log m) time.
//   • Idea: This algorithm, also known as Baby-step Giant-step, finds the smallest non-negative integer 'x' satisfying a^x = b (mod m) using a meet-in-the-middle approach. It achieves a time complexity of O(sqrt(m) log m).
//   • Invariants: The map stores (a^q mod m, q) for all baby steps q in [0, n-1].; For each giant step p, a^(np) mod m is correctly computed.
//   • Tips: Choose 'n' as ceil(sqrt(m)) for balanced steps.; Use a hash map to store baby steps for O(1) average lookup.
//   • Pitfalls: Incorrect choice of 'n' can lead to suboptimal time complexity.; Failure to check if 'a' and 'm' are coprime may yield no solution or incorrect results.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int getNumberOfBacklogOrders(int[][] orders) {
        // Min-heap for sell orders (sorted by price ascending)
        PriorityQueue<int[]> sellOrders = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        // Max-heap for buy orders (sorted by price descending)
        PriorityQueue<int[]> buyOrders = new PriorityQueue<>((a, b) -> Integer.compare(b[0], a[0]));

        for (int[] order : orders) {
            int price = order[0];
            int amount = order[1];
            int orderType = order[2];

            if (orderType == 0) { // Buy order
                while (amount > 0 && !sellOrders.isEmpty() && sellOrders.peek()[0] <= price) {
                    int[] sellOrder = sellOrders.poll();
                    int sellPrice = sellOrder[0];
                    int sellAmount = sellOrder[1];

                    if (sellAmount > amount) {
                        sellOrders.offer(new int[]{sellPrice, sellAmount - amount});
                        amount = 0;
                    } else {
                        amount -= sellAmount;
                    }
                }
                if (amount > 0) {
                    buyOrders.offer(new int[]{price, amount});
                }
            } else { // Sell order
                while (amount > 0 && !buyOrders.isEmpty() && buyOrders.peek()[0] >= price) {
                    int[] buyOrder = buyOrders.poll();
                    int buyPrice = buyOrder[0];
                    int buyAmount = buyOrder[1];

                    if (buyAmount > amount) {
                        buyOrders.offer(new int[]{buyPrice, buyAmount - amount});
                        amount = 0;
                    } else {
                        amount -= buyAmount;
                    }
                }
                if (amount > 0) {
                    sellOrders.offer(new int[]{price, amount});
                }
            }
        }

        long backlogCount = 0;
        for (int[] buyOrder : buyOrders) {
            backlogCount += buyOrder[1];
        }
        for (int[] sellOrder : sellOrders) {
            backlogCount += sellOrder[1];
        }

        return (int)(backlogCount % 1000000007);            
    }
}
