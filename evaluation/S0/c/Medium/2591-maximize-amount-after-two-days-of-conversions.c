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

double maxAmount(char* initialCurrency, char*** pairs1, int pairs1Size, int* pairs1ColSize, double* rates1, int rates1Size, char*** pairs2, int pairs2Size, int* pairs2ColSize, double* rates2, int rates2Size) {
    // Build adjacency list for day 1
    typedef struct Edge {
        char* to;
        double rate;
        struct Edge* next;
    } Edge;

    typedef struct Node {
        char* currency;
        Edge* edges;
        struct Node* next;
    } Node;

    Node* graph1 = NULL;
    Node* graph2 = NULL;

    void addEdge(Node** graph, char* from, char* to, double rate) {
        Node* curr = *graph;
        while (curr) {
            if (strcmp(curr->currency, from) == 0) break;
            curr = curr->next;
        }
        if (!curr) {
            curr = (Node*)malloc(sizeof(Node));
            curr->currency = from;
            curr->edges = NULL;
            curr->next = *graph;
            *graph = curr;
        }
        Edge* edge = (Edge*)malloc(sizeof(Edge));
        edge->to = to;
        edge->rate = rate;
        edge->next = curr->edges;
        curr->edges = edge;
    }

    for (int i = 0; i < pairs1Size; i++) {
        addEdge(&graph1, pairs1[i][0], pairs1[i][1], rates1[i]);
        addEdge(&graph1, pairs1[i][1], pairs1[i][0], 1.0 / rates1[i]);
    }

    for (int i = 0; i < pairs2Size; i++) {
        addEdge(&graph2, pairs2[i][0], pairs2[i][1], rates2[i]);
        addEdge(&graph2, pairs2[i][1], pairs2[i][0], 1.0 / rates2[i]);
    }

    // DFS to find maximum amount for a given graph
    double dfs(Node* graph, char* current, char* target, double amount, int* visited, int* visitCount) {
        if (strcmp(current, target) == 0) {
            return amount;
        }
        visited[*visitCount] = 1;
        (*visitCount)++;
        Node* currNode = graph;
        while (currNode) {
            if (strcmp(currNode->currency, current) == 0) {
                break;
            }
            currNode = currNode->next;
        }
        double maxAmount = amount;
        if (currNode) {
            Edge* edge = currNode->edges;
            while (edge) {
                int alreadyVisited = 0;
                for (int i = 0; i < *visitCount; i++) {
                    if (strcmp(edge->to, graph[i].currency) == 0 && visited[i]) {
                        alreadyVisited = 1;
                        break;
                    }
                }
                if (!alreadyVisited) {
                    double newAmount = dfs(graph, edge->to, target, amount * edge->rate, visited, visitCount);
                    if (newAmount > maxAmount) {
                        maxAmount = newAmount;
                    }
                }
                edge = edge->next;
            }
        }
        (*visitCount)--;
        visited[*visitCount] = 0;
        return maxAmount;
    }
    int visited1[20] = {0};
    int visitCount1 = 0;
    double maxDay1 = dfs(graph1, initialCurrency, initialCurrency, 1.0, visited1, &visitCount1);
    int visited2[20] = {0};
    int visitCount2 = 0;
    double maxDay2 = dfs(graph2, initialCurrency, initialCurrency, maxDay1, visited2, &visitCount2);
    return maxDay2;
}
