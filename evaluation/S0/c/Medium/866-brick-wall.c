// Source: https://leetcode.com/problems/brick-wall/   |   Difficulty: Medium
//
// Problem Description:
// There is a rectangular brick wall in front of you with n rows of bricks. The ith row has some number of bricks each of the same height (i.e., one unit) but they can be of different widths. The total width of each row is the same.
//
// Draw a vertical line from the top to the bottom and cross the least bricks. If your line goes through the edge of a brick, then the brick is not considered as crossed. You cannot draw a line just along one of the two vertical edges of the wall, in which case the line will obviously cross no bricks.
//
// Given the 2D array wall that contains the information about the wall, return the minimum number of crossed bricks after drawing such a vertical line.
//
// Example:
// Input: wall = [[1,2,2,1],[3,1,2],[1,3,2],[2,4],[3,1,2],[1,3,1,1]]
// Output: 2
//
// Constraints:
// n == wall.length
// 	1 <= n <= 104
// 	1 <= wall[i].length <= 104
// 	1 <= sum(wall[i].length) <= 2 * 104
// 	sum(wall[i]) is the same for each row i.
// 	1 <= wall[i][j] <= 231 - 1
//

int leastBricks(int** wall, int wallSize, int* wallColSize) {
    // Hash map to count edge frequencies
    #define HASH_SIZE 20011
    typedef struct HashNode {
        int key;
        int value;
        struct HashNode* next;
    } HashNode;

    HashNode* hashTable[HASH_SIZE] = {0};

    int maxEdges = 0;

    for (int i = 0; i < wallSize; i++) {
        int sum = 0;
        for (int j = 0; j < wallColSize[i] - 1; j++) {
            sum += wall[i][j];
            int hashIndex = (sum % HASH_SIZE + HASH_SIZE) % HASH_SIZE;

            HashNode* node = hashTable[hashIndex];
            while (node) {
                if (node->key == sum) {
                    node->value++;
                    if (node->value > maxEdges) {
                        maxEdges = node->value;
                    }
                    break;
                }
                node = node->next;
            }
            if (!node) {
                HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
                newNode->key = sum;
                newNode->value = 1;
                newNode->next = hashTable[hashIndex];
                hashTable[hashIndex] = newNode;
                if (newNode->value > maxEdges) {
                    maxEdges = newNode->value;
                }
            }
        }
    }

    // Free hash table memory
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* node = hashTable[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }

    return wallSize - maxEdges;     
}
