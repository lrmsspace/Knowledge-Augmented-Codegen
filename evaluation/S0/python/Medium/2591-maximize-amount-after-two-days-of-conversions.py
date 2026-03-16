# Source: https://leetcode.com/problems/maximize-amount-after-two-days-of-conversions/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string initialCurrency, and you start with 1.0 of initialCurrency.
#
# You are also given four arrays with currency pairs (strings) and rates (real numbers):
#
#
# 	pairs1[i] = [startCurrencyi, targetCurrencyi] denotes that you can convert from startCurrencyi to targetCurrencyi at a rate of rates1[i] on day 1.
# 	pairs2[i] = [startCurrencyi, targetCurrencyi] denotes that you can convert from startCurrencyi to targetCurrencyi at a rate of rates2[i] on day 2.
# 	Also, each targetCurrency can be converted back to its corresponding startCurrency at a rate of 1 / rate.
#
#
# You can perform any number of conversions, including zero, using rates1 on day 1, followed by any number of additional conversions, including zero, using rates2 on day 2.
#
# Return the maximum amount of initialCurrency you can have after performing any number of conversions on both days in order.
#
# Note: Conversion rates are valid, and there will be no contradictions in the rates for either day. The rates for the days are independent of each other.
#
# Example:
# Input: initialCurrency = "EUR", pairs1 = [["EUR","USD"],["USD","JPY"]], rates1 = [2.0,3.0], pairs2 = [["JPY","USD"],["USD","CHF"],["CHF","EUR"]], rates2 = [4.0,5.0,6.0]
#
# Output: 720.00000
#
# Explanation:
#
# To get the maximum amount of EUR, starting with 1.0 EUR:
#
#
# 	On Day 1:
# 	
# 		Convert EUR to USD to get 2.0 USD.
# 		Convert USD to JPY to get 6.0 JPY.
# 	
# 	
# 	On Day 2:
# 	
# 		Convert JPY to USD to get 24.0 USD.
# 		Convert USD to CHF to get 120.0 CHF.
# 		Finally, convert CHF to EUR to get 720.0 EUR.
#
# Constraints:
# 1 <= initialCurrency.length <= 3
# 	initialCurrency consists only of uppercase English letters.
# 	1 <= n == pairs1.length <= 10
# 	1 <= m == pairs2.length <= 10
# 	pairs1[i] == [startCurrencyi, targetCurrencyi]
# 	pairs2[i] == [startCurrencyi, targetCurrencyi]
# 	1 <= startCurrencyi.length, targetCurrencyi.length <= 3
# 	startCurrencyi and targetCurrencyi consist only of uppercase English letters.
# 	rates1.length == n
# 	rates2.length == m
# 	1.0 <= rates1[i], rates2[i] <= 10.0
# 	The input is generated such that there are no contradictions or cycles in the conversion graphs for either day.
# 	The input is generated such that the output is at most 5 * 1010.
#

class Solution(object):
    def maxAmount(self, initialCurrency, pairs1, rates1, pairs2, rates2):
        """
        :type initialCurrency: str
        :type pairs1: List[List[str]]
        :type rates1: List[float]
        :type pairs2: List[List[str]]
        :type rates2: List[float]
        :rtype: float
        """
        from collections import defaultdict
        import heapq

        def build_graph(pairs, rates):
            graph = defaultdict(list)
            for (src, dst), rate in zip(pairs, rates):
                graph[src].append((dst, rate))
                graph[dst].append((src, 1 / rate))
            return graph

        def dijkstra(graph, start):
            max_amounts = defaultdict(float)
            max_amounts[start] = 1.0
            heap = [(-1.0, start)]

            while heap:
                curr_amount, curr_currency = heapq.heappop(heap)
                curr_amount = -curr_amount

                for neighbor, rate in graph[curr_currency]:
                    new_amount = curr_amount * rate
                    if new_amount > max_amounts[neighbor]:
                        max_amounts[neighbor] = new_amount
                        heapq.heappush(heap, (-new_amount, neighbor))

            return max_amounts

        graph1 = build_graph(pairs1, rates1)
        graph2 = build_graph(pairs2, rates2)

        day1_amounts = dijkstra(graph1, initialCurrency)

        max_final_amount = 0.0
        for currency, amount_after_day1 in day1_amounts.items():
            day2_amounts = dijkstra(graph2, currency)
            final_amount = day2_amounts.get(initialCurrency, 0.0) * amount_after_day1
            max_final_amount = max(max_final_amount, final_amount)

        return max_final_amount