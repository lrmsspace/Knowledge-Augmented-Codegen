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
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
// - Hungarian algorithm for solving the assignment problem (matrix, graph, array, greedy, bfs, enumeration)
//   • When to use: Use when finding a minimum cost perfect matching in a bipartite graph, typically represented as an N x N cost matrix, where each row must be assigned to exactly one column.
//   • Idea: The Hungarian algorithm finds a minimum weight perfect matching in a bipartite graph, solving the assignment problem for an N x N cost matrix. It iteratively finds augmenting paths in an equality graph and adjusts potentials, achieving O(N^3) time complexity.
//   • Invariants: For all i, j, u[i] + v[j] <= A[i][j] (potential condition).; The current matching is always valid (each row/column used at most once).
//   • Tips: Understand the concept of potentials and their role in maintaining the equality graph.; The algorithm can be adapted for maximum profit problems by negating costs.
//   • Pitfalls: Incorrectly updating potentials can lead to non-optimal solutions or infinite loops.; Handling non-square matrices requires careful padding with dummy values.
// - Linked-list implementations of collections (linked-list, stack, simulation)
//   • When to use: Use when a Last-In, First-Out (LIFO) data structure is required, and dynamic size with efficient O(1) push and pop operations is crucial, especially without a fixed capacity.
//   • Idea: This describes implementing a stack using a singly linked list, where elements are added and removed from the head of the list. Both push and pop operations achieve O(1) time complexity.
//   • Invariants: The 'first' pointer always points to the top element of the stack, or is null if the stack is empty.; Each node's 'next' pointer correctly links to the subsequent element in the stack, maintaining the LIFO order.
//   • Tips: Maintain a 'first' pointer to the head of the linked list, representing the stack's top.; Push operation involves creating a new node, linking it to the current 'first', then updating 'first'.
//   • Pitfalls: Forgetting to handle the empty stack case for pop, leading to `NoSuchElementException`.; Incorrectly updating the 'first' pointer during push or pop, which can break the list structure.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        const int MOD = 1e9 + 7;
        // Min-heap for sell orders (price, amount)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> sellHeap;
        // Max-heap for buy orders (price, amount)
        priority_queue<pair<int, int>> buyHeap;

        for (const auto& order : orders) {
            int price = order[0];
            int amount = order[1];
            int orderType = order[2];

            if (orderType == 0) { // Buy order
                while (amount > 0 && !sellHeap.empty() && sellHeap.top().first <= price) {
                    auto [sellPrice, sellAmount] = sellHeap.top();
                    sellHeap.pop();
                    int executed = min(amount, sellAmount);
                    amount -= executed;
                    sellAmount -= executed;
                    if (sellAmount > 0) {
                        sellHeap.push({sellPrice, sellAmount});
                    }
                }
                if (amount > 0) {
                    buyHeap.push({price, amount});
                }
            } else { // Sell order
                while (amount > 0 && !buyHeap.empty() && buyHeap.top().first >= price) {
                    auto [buyPrice, buyAmount] = buyHeap.top();
                    buyHeap.pop();
                    int executed = min(amount, buyAmount);
                    amount -= executed;
                    buyAmount -= executed;
                    if (buyAmount > 0) {
                        buyHeap.push({buyPrice, buyAmount});
                    }
                }
                if (amount > 0) {
                    sellHeap.push({price, amount});
                }
            }
        }

        long long totalOrders = 0;
        while (!buyHeap.empty()) {
            totalOrders = (totalOrders + buyHeap.top().second) % MOD;
            buyHeap.pop();
        }
        while (!sellHeap.empty()) {
            totalOrders = (totalOrders + sellHeap.top().second) % MOD;
            sellHeap.pop();
        }

        return static_cast<int>(totalOrders);           
    }
};
