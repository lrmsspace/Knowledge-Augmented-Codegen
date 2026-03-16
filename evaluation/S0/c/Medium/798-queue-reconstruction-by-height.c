// Source: https://leetcode.com/problems/queue-reconstruction-by-height/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of people, people, which are the attributes of some people in a queue (not necessarily in order). Each people[i] = [hi, ki] represents the ith person of height hi with exactly ki other people in front who have a height greater than or equal to hi.
//
// Reconstruct and return the queue that is represented by the input array people. The returned queue should be formatted as an array queue, where queue[j] = [hj, kj] is the attributes of the jth person in the queue (queue[0] is the person at the front of the queue).
//
// Example:
// Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
// Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
// Explanation:
// Person 0 has height 5 with no other people taller or the same height in front.
// Person 1 has height 7 with no other people taller or the same height in front.
// Person 2 has height 5 with two persons taller or the same height in front, which is person 0 and 1.
// Person 3 has height 6 with one person taller or the same height in front, which is person 1.
// Person 4 has height 4 with four people taller or the same height in front, which are people 0, 1, 2, and 3.
// Person 5 has height 7 with one person taller or the same height in front, which is person 1.
// Hence [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] is the reconstructed queue.
//
// Constraints:
// 1 <= people.length <= 2000
// 	0 <= hi <= 106
// 	0 <= ki < people.length
// 	It is guaranteed that the queue can be reconstructed.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes) {
    // Sort people by height in descending order. If heights are equal, sort by k in ascending order.
    int cmp(const void* a, const void* b) {
        int* personA = *(int**)a;
        int* personB = *(int**)b;
        if (personA[0] != personB[0]) {
            return personB[0] - personA[0];
        }
        return personA[1] - personB[1];
    }
    
    qsort(people, peopleSize, sizeof(int*), cmp);
    
    // Allocate memory for the result
    int** result = (int**)malloc(peopleSize * sizeof(int*));
    for (int i = 0; i < peopleSize; i++) {
        result[i] = (int*)malloc(2 * sizeof(int));
    }
    
    // Reconstruct the queue
    for (int i = 0; i < peopleSize; i++) {
        int k = people[i][1];
        // Shift elements to the right to make space for the current person
        for (int j = peopleSize - 1; j > k; j--) {
            if (result[j - 1][0] != 0 || result[j - 1][1] != 0) {
                result[j][0] = result[j - 1][0];
                result[j][1] = result[j - 1][1];
            }
        }
        // Place the current person at index k
        result[k][0] = people[i][0];
        result[k][1] = people[i][1];
    }
    
    *returnSize = peopleSize;
    *returnColumnSizes = (int*)malloc(peopleSize * sizeof(int));
    for (int i = 0; i < peopleSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    
    return result;      
}
