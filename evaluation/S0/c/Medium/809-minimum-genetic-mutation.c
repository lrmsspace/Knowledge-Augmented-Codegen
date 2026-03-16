// Source: https://leetcode.com/problems/minimum-genetic-mutation/   |   Difficulty: Medium
//
// Problem Description:
// A gene string can be represented by an 8-character long string, with choices from 'A', 'C', 'G', and 'T'.
//
// Suppose we need to investigate a mutation from a gene string startGene to a gene string endGene where one mutation is defined as one single character changed in the gene string.
//
//
// 	For example, "AACCGGTT" --> "AACCGGTA" is one mutation.
//
//
// There is also a gene bank bank that records all the valid gene mutations. A gene must be in bank to make it a valid gene string.
//
// Given the two gene strings startGene and endGene and the gene bank bank, return the minimum number of mutations needed to mutate from startGene to endGene. If there is no such a mutation, return -1.
//
// Note that the starting point is assumed to be valid, so it might not be included in the bank.
//
// Example:
// Input: startGene = "AACCGGTT", endGene = "AACCGGTA", bank = ["AACCGGTA"]
// Output: 1
//
// Constraints:
// 0 <= bank.length <= 10
// 	startGene.length == endGene.length == bank[i].length == 8
// 	startGene, endGene, and bank[i] consist of only the characters ['A', 'C', 'G', 'T'].
//

int minMutation(char* startGene, char* endGene, char** bank, int bankSize) {
    char genes[4] = {'A', 'C', 'G', 'T'};
    int visited[bankSize];
    for (int i = 0; i < bankSize; i++) {
        visited[i] = 0;
    }

    typedef struct Node {
        char gene[9];
        int steps;
        struct Node* next;
    } Node;

    Node* head = (Node*)malloc(sizeof(Node));
    Node* tail = head;
    strcpy(head->gene, startGene);
    head->steps = 0;
    head->next = NULL;

    while (head != NULL) {
        Node* current = head;
        head = head->next;

        if (strcmp(current->gene, endGene) == 0) {
            int result = current->steps;
            free(current);
            while (head != NULL) {
                Node* temp = head;
                head = head->next;
                free(temp);
            }
            return result;
        }

        for (int i = 0; i < bankSize; i++) {
            if (visited[i]) continue;

            int diff = 0;
            for (int j = 0; j < 8; j++) {
                if (current->gene[j] != bank[i][j]) {
                    diff++;
                }
            }

            if (diff == 1) {
                visited[i] = 1;
                Node* newNode = (Node*)malloc(sizeof(Node));
                strcpy(newNode->gene, bank[i]);
                newNode->steps = current->steps + 1;
                newNode->next = NULL;
                tail->next = newNode;
                tail = newNode;
            }
        }

        free(current);
    }

    return -1;      
}
