// Source: https://leetcode.com/problems/reconstruct-itinerary/   |   Difficulty: Hard
//
// Problem Description:
// You are given a list of airline tickets where tickets[i] = [fromi, toi] represent the departure and the arrival airports of one flight. Reconstruct the itinerary in order and return it.
//
// All of the tickets belong to a man who departs from "JFK", thus, the itinerary must begin with "JFK". If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string.
//
//
// 	For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
//
//
// You may assume all tickets form at least one valid itinerary. You must use all the tickets once and only once.
//
// Example:
// Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
// Output: ["JFK","MUC","LHR","SFO","SJC"]
//
// Constraints:
// 1 <= tickets.length <= 300
// 	tickets[i].length == 2
// 	fromi.length == 3
// 	toi.length == 3
// 	fromi and toi consist of uppercase English letters.
// 	fromi != toi
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findItinerary(char*** tickets, int ticketsSize, int* ticketsColSize, int* returnSize) {
    // Build graph
    #define MAX_AIRPORTS 1000
    #define MAX_TICKETS 300

    typedef struct Node {
        char* dest;
        struct Node* next;
    } Node;

    Node* graph[MAX_AIRPORTS] = {0};
    int airportCount = 0;
    char* airports[MAX_AIRPORTS];

    int getAirportIndex(char* code) {
        for (int i = 0; i < airportCount; i++) {
            if (strcmp(airports[i], code) == 0) return i;
        }
        airports[airportCount] = code;
        return airportCount++;
    }

    for (int i = 0; i < ticketsSize; i++) {
        int fromIdx = getAirportIndex(tickets[i][0]);
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->dest = tickets[i][1];
        newNode->next = graph[fromIdx];
        graph[fromIdx] = newNode;
    }

    // Sort adjacency lists
    for (int i = 0; i < airportCount; i++) {
        // Simple insertion sort for linked list
        Node* sorted = NULL;
        Node* current = graph[i];
        while (current) {
            Node* next = current->next;
            if (!sorted || strcmp(current->dest, sorted->dest) < 0) {
                current->next = sorted;
                sorted = current;
            } else {
                Node* temp = sorted;
                while (temp->next && strcmp(current->dest, temp->next->dest) >= 0) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }
        graph[i] = sorted;
    }

    // Hierholzer's algorithm for Eulerian path
    char** result = (char**)malloc(sizeof(char*) * (ticketsSize + 1));
    *returnSize = 0;

    void dfs(char* airport) {
        int idx = getAirportIndex(airport);
        Node* node = graph[idx];
        while (node) {
            char* nextDest = node->dest;
            graph[idx] = node->next; // Remove edge
            free(node);
            node = graph[idx];
            dfs(nextDest);
        }
        result[(*returnSize)++] = airport;

}
    dfs("JFK");

    // Reverse result
    for (int i = 0; i < *returnSize / 2; i++) {
        char* temp = result[i];
        result[i] = result[*returnSize - 1 - i];
        result[*returnSize - 1 - i] = temp;
    }

    return result;
}