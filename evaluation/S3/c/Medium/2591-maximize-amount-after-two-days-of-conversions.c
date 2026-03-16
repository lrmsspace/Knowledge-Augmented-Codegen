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
// - Floyd-Warshall Algorithm (number, simulation)
//   • When to use: When you need to find the shortest paths between all possible pairs of vertices in a graph. It is particularly suitable for dense graphs or when negative edge weights are present, as long as no negative cycles are reachable.
//   • Idea: Floyd-Warshall is a dynamic programming algorithm that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path distances, achieving an O(V^3) time complexity.
//   • Invariants: After the k-th iteration, dist[i][j] contains the shortest path from i to j considering only vertices 0 to k-1 as intermediate nodes.; For any pair (i, j), dist[i][j] is always greater than or equal to the true shortest path distance from i to j (or infinity if unreachable).
//   • Tips: Initialize distances: direct edge weights, infinity for no direct edge, zero for self-loops.; The outermost loop must iterate through intermediate vertices (k).
//   • Pitfalls: Incorrect loop order (k not outermost) leads to incorrect results.; Integer overflow with large path sums if not using appropriate data types.
// - Floyd-Warshall Algorithm (graph, matrix, floyd-warshall, dp-2d)
//   • When to use: Use when needing to find the shortest paths between all pairs of vertices in a weighted graph, especially if negative edge weights are present but no negative cycles.
//   • Idea: The Floyd-Warshall algorithm is a dynamic programming approach that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path lengths, achieving an O(N^3) time complexity.
//   • Invariants: After k iterations, d[i][j] stores the shortest path from i to j using only vertices {1, ..., k} as intermediate nodes.; d[i][j] always represents a valid path length or infinity, never an invalid negative value unless a negative cycle is detected.
//   • Tips: Initialize direct edge weights and infinity for non-existent edges.; Set distance from a vertex to itself to zero initially.
//   • Pitfalls: Incorrect loop order (k must be outermost) will yield incorrect results.; Improper handling of 'infinity' values can lead to overflow or incorrect comparisons.
// - Floyd-Warshall Algorithm (matrix, graph, recursion, dp-2d)
//   • When to use: Use when you need to find the shortest paths between all pairs of vertices in a weighted graph. It is suitable for graphs with negative edge weights but no negative cycles.
//   • Idea: The Floyd-Warshall algorithm finds all-pairs shortest paths in a weighted graph using dynamic programming. It iteratively considers all possible intermediate vertices, updating path lengths in O(V^3) time.
//   • Invariants: After k iterations, dist[i][j] contains the shortest path from i to j using only vertices 0 to k-1 as intermediate nodes.; dist[i][j] is always non-increasing with each iteration of k.
//   • Tips: Initialize distances with edge weights or infinity, and 0 for self-loops.; The outermost loop iterates through intermediate vertices (k).
//   • Pitfalls: Incorrectly handling infinity values, especially with negative weights (e.g., infinity - 1).; Not checking for negative cycles, which can lead to incorrect shortest path values.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double maxAmount(char* initialCurrency, char*** pairs1, int pairs1Size, int* pairs1ColSize, double* rates1, int rates1Size, char*** pairs2, int pairs2Size, int* pairs2ColSize, double* rates2, int rates2Size) {
    // Step 1: Create a mapping of currencies to indices for both days
    int maxCurrencies = 20; // Maximum number of unique currencies (10 pairs per day)
    char* currencies[maxCurrencies];
    int currencyCount = 0;

    // Helper function to get or add a currency index
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

    // Fill the graphs with the given pairs and rates
    for (int i = 0; i < pairs1Size; i++) {
        int from = getCurrencyIndex(pairs1[i][0]);
        int to = getCurrencyIndex(pairs1[i][1]);
        graph1[from][to] = rates1[i];
        graph1[to][from] = 1.0 / rates1[i]; // Add reverse conversion
    }

    for (int i = 0; i < pairs2Size; i++) {
        int from = getCurrencyIndex(pairs2[i][0]);
        int to = getCurrencyIndex(pairs2[i][1]);
        graph2[from][to] = rates2[i];
        graph2[to][from] = 1.0 / rates2[i]; // Add reverse conversion
    }

    // Step 3: Use Floyd-Warshall algorithm to find maximum conversion rates for both days
    for (int k = 0; k < currencyCount; k++) {
        for (int i = 0; i < currencyCount; i++) {
            for (int j = 0; j < currencyCount; j++) {
                if (graph1[i][k] > 0 && graph1[k][j] > 0) {
                    double newRate = graph1[i][k] * graph1[k][j];
                    if (newRate > graph1[i][j]) {
                        graph1[i][j] = newRate;
                    }
                }
                if (graph2[i][k] > 0 && graph2[k][j] > 0) {
                    double newRate = graph2[i][k] * graph2[k][j];
                    if (newRate > graph2[i][j]) {
                        graph2[i][j] = newRate;
                    }
                }
            }
        }
    }
    
    // Find the maximum amount of initialCurrency that can be obtained after two days
    int initialIndex = getCurrencyIndex(initialCurrency);
    double maxAmount = 0.0;
    
    for (int i = 0; i < currencyCount; i++) {
        if (graph1[initialIndex][i] > 0 && graph2[i][initialIndex] > 0) {
            double totalAmount = graph1[initialIndex][i] * graph2[i][initialIndex];
            if (totalAmount > maxAmount) {
                maxAmount = totalAmount;
            }
        }
    }
    
    return maxAmount;
}
