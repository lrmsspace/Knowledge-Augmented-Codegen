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

class Solution {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        auto cmpBuy = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first < b.first; // Max-heap for buy orders
        };
        auto cmpSell = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first > b.first; // Min-heap for sell orders
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmpBuy)> buyOrders(cmpBuy);
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmpSell)> sellOrders(cmpSell);

        for (const auto& order : orders) {
            int price = order[0];
            int amount = order[1];
            int orderType = order[2];

            if (orderType == 0) { // Buy order
                while (amount > 0 && !sellOrders.empty() && sellOrders.top().first <= price) {
                    auto [sellPrice, sellAmount] = sellOrders.top();
                    sellOrders.pop();
                    int executed = min(amount, sellAmount);
                    amount -= executed;
                    sellAmount -= executed;
                    if (sellAmount > 0) {
                        sellOrders.push({sellPrice, sellAmount});
                    }
                }
                if (amount > 0) {
                    buyOrders.push({price, amount});
                }
            } else { // Sell order
                while (amount > 0 && !buyOrders.empty() && buyOrders.top().first >= price) {
                    auto [buyPrice, buyAmount] = buyOrders.top();
                    buyOrders.pop();
                    int executed = min(amount, buyAmount);
                    amount -= executed;
                    buyAmount -= executed;
                    if (buyAmount > 0) {
                        buyOrders.push({buyPrice, buyAmount});
                    }
                }
                if (amount > 0) {
                    sellOrders.push({price, amount});
                }
            }
        }

        const int MOD = 1e9 + 7;
        long long totalBacklog = 0;

        while (!buyOrders.empty()) {
            totalBacklog = (totalBacklog + buyOrders.top().second) % MOD;
            buyOrders.pop();
        }

        while (!sellOrders.empty()) {
            totalBacklog = (totalBacklog + sellOrders.top().second) % MOD;
            sellOrders.pop();
        }
        return static_cast<int>(totalBacklog);
    }
};
