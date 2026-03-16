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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double maxAmount(char* initialCurrency, char*** pairs1, int pairs1Size, int* pairs1ColSize, double* rates1, int rates1Size, char*** pairs2, int pairs2Size, int* pairs2ColSize, double* rates2, int rates2Size) {
    // Step 1: Create a mapping of currency to index for both days
    int maxCurrencies = 20; // Assuming a maximum of 20 unique currencies
    char* currencies[maxCurrencies];
    int currencyCount = 0;

    // Helper function to get or add currency index
    int getCurrencyIndex(char* currency) {
        for (int i = 0; i < currencyCount; i++) {
            if (strcmp(currencies[i], currency) == 0) {
                return i;
            }
        }
        currencies[currencyCount] = currency;
        return currencyCount++;
    }

    // Step 2: Build the conversion graphs for both days
    double graph1[maxCurrencies][maxCurrencies];
    double graph2[maxCurrencies][maxCurrencies];

    // Initialize graphs with -1 (indicating no direct conversion)
    for (int i = 0; i < maxCurrencies; i++) {
        for (int j = 0; j < maxCurrencies; j++) {
            graph1[i][j] = -1.0;
            graph2[i][j] = -1.0;
        }
    }

    // Fill graph1 with rates from pairs1
    for (int i = 0; i < pairs1Size; i++) {
        int startIdx = getCurrencyIndex(pairs1[i][0]);
        int targetIdx = getCurrencyIndex(pairs1[i][1]);
        graph1[startIdx][targetIdx] = rates1[i];
        graph1[targetIdx][startIdx] = 1.0 / rates1[i]; // Add reverse conversion
    }

    // Fill graph2 with rates from pairs2
    for (int i = 0; i < pairs2Size; i++) {
        int startIdx = getCurrencyIndex(pairs2[i][0]);
        int targetIdx = getCurrencyIndex(pairs2[i][1]);
        graph2[startIdx][targetIdx] = rates2[i];
        graph2[targetIdx][startIdx] = 1.0 / rates2[i]; // Add reverse conversion
    }

    // Step 3: Use Floyd-Warshall algorithm to find the best conversion rates for both days
    for (int k = 0; k < currencyCount; k++) {
        for (int i = 0; i < currencyCount; i++) {
            for (int j = 0; j < currencyCount; j++) {
                if (graph1[i][k] > 0 && graph1[k][j] > 0) {
                    graph1[i][j] = fmax(graph1[i][j], graph1[i][k] * graph1[k][j]);
                }
                if (graph2[i][k] > 0 && graph2[k][j] > 0) {
                    graph2[i][j] = fmax(graph2[i][j], graph2[i][k] * graph2[k][j]);
                }
            }
        }
    }
    
    // Find the maximum amount of money that can be obtained
    int initialCurrencyIndex = getCurrencyIndex(initialCurrency);
    double maxAmount = 0.0;
    
    for (int i = 0; i < currencyCount; i++) {
        if (graph1[initialCurrencyIndex][i] > 0 && graph2[i][initialCurrencyIndex] > 0) {
            double totalAmount = graph1[initialCurrencyIndex][i] * graph2[i][initialCurrencyIndex];
            maxAmount = fmax(maxAmount, totalAmount);
        }
    }
    
    return maxAmount;
}
