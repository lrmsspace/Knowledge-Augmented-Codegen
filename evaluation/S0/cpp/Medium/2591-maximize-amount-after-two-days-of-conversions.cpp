// Source: https://leetcode.com/problems/maximize-amount-after-two-days-of-conversions/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string initialCurrency, and you start with 1.0 of initialCurrency.
//
// You are also given four arrays with currency pairs (strings) and rates (real numbers):
//
//
// 	pairs1[i] = [startCurrencyi, targetCurrencyi] denotes that you can convert from startCurrencyi to targetCurrencyi at a rate of rates1[i] on day 1.
// 	pairs2[i] = [startCurrencyi, targetCurrencyi] denotes that you can convert from startCurrencyi to targetCurrencyi at a rate of rates2[i] on day 2.
// 	Also, each targetCurrency can be converted back to its corresponding startCurrency at a rate of 1 / rate.
//
//
// You can perform any number of conversions, including zero, using rates1 on day 1, followed by any number of additional conversions, including zero, using rates2 on day 2.
//
// Return the maximum amount of initialCurrency you can have after performing any number of conversions on both days in order.
//
// Note: Conversion rates are valid, and there will be no contradictions in the rates for either day. The rates for the days are independent of each other.
//
// Example:
// Input: initialCurrency = "EUR", pairs1 = [["EUR","USD"],["USD","JPY"]], rates1 = [2.0,3.0], pairs2 = [["JPY","USD"],["USD","CHF"],["CHF","EUR"]], rates2 = [4.0,5.0,6.0]
//
// Output: 720.00000
//
// Explanation:
//
// To get the maximum amount of EUR, starting with 1.0 EUR:
//
//
// 	On Day 1:
// 	
// 		Convert EUR to USD to get 2.0 USD.
// 		Convert USD to JPY to get 6.0 JPY.
// 	
// 	
// 	On Day 2:
// 	
// 		Convert JPY to USD to get 24.0 USD.
// 		Convert USD to CHF to get 120.0 CHF.
// 		Finally, convert CHF to EUR to get 720.0 EUR.
//
// Constraints:
// 1 <= initialCurrency.length <= 3
// 	initialCurrency consists only of uppercase English letters.
// 	1 <= n == pairs1.length <= 10
// 	1 <= m == pairs2.length <= 10
// 	pairs1[i] == [startCurrencyi, targetCurrencyi]
// 	pairs2[i] == [startCurrencyi, targetCurrencyi]
// 	1 <= startCurrencyi.length, targetCurrencyi.length <= 3
// 	startCurrencyi and targetCurrencyi consist only of uppercase English letters.
// 	rates1.length == n
// 	rates2.length == m
// 	1.0 <= rates1[i], rates2[i] <= 10.0
// 	The input is generated such that there are no contradictions or cycles in the conversion graphs for either day.
// 	The input is generated such that the output is at most 5 * 1010.
//

class Solution {
public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        unordered_map<string, vector<pair<string, double>>> graph1, graph2;

        // Build graphs for both days
        for (int i = 0; i < pairs1.size(); ++i) {
            graph1[pairs1[i][0]].emplace_back(pairs1[i][1], rates1[i]);
            graph1[pairs1[i][1]].emplace_back(pairs1[i][0], 1.0 / rates1[i]);
        }
        for (int i = 0; i < pairs2.size(); ++i) {
            graph2[pairs2[i][0]].emplace_back(pairs2[i][1], rates2[i]);
            graph2[pairs2[i][1]].emplace_back(pairs2[i][0], 1.0 / rates2[i]);
        }

        // DFS to find max conversion for a given day
        auto dfs = [&](const string& startCurrency, const unordered_map<string, vector<pair<string, double>>>& graph) {
            unordered_map<string, double> maxAmountMap;
            function<void(const string&, double)> dfsHelper = [&](const string& currency, double amount) {
                if (amount <= maxAmountMap[currency]) return;
                maxAmountMap[currency] = amount;
                for (const auto& [nextCurrency, rate] : graph.at(currency)) {
                    dfsHelper(nextCurrency, amount * rate);
                }
            };
            dfsHelper(startCurrency, 1.0);
            return maxAmountMap;
        };

        // Get max amounts after day 1
        auto day1Amounts = dfs(initialCurrency, graph1);

        double maxFinalAmount = 0.0;

        // For each currency obtained after day 1, perform day 2 conversions
        for (const auto& [currency, amountAfterDay1] : day1Amounts) {
            auto day2Amounts = dfs(currency, graph2);
            if (day2Amounts.find(initialCurrency) != day2Amounts.end()) {
                maxFinalAmount = max(maxFinalAmount, amountAfterDay1 * day2Amounts[initialCurrency]);
            }
        }

        return maxFinalAmount;          
    }
};
