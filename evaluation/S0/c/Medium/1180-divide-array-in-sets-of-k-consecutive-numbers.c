// Source: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and a positive integer k, check whether it is possible to divide this array into sets of k consecutive numbers.
//
// Return true if it is possible. Otherwise, return false.
//
// Example:
// Input: nums = [1,2,3,3,4,4,5,6], k = 4
// Output: true
// Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	1 <= nums[i] <= 109
//
//
//  
// Note: This question is the same as 846: https://leetcode.com/problems/hand-of-straights/
//

bool isPossibleDivide(int* nums, int numsSize, int k) {
    if (numsSize % k != 0) {
        return false;
    }

    // Count frequency of each number
    #define HASH_SIZE 100003
    typedef struct Node {
        int key;
        int count;
        struct Node* next;
    } Node;

    Node* hashTable[HASH_SIZE] = {0};

    for (int i = 0; i < numsSize; i++) {
        int key = nums[i] % HASH_SIZE;
        Node* curr = hashTable[key];
        while (curr) {
            if (curr->key == nums[i]) {
                curr->count++;
                break;
            }
            curr = curr->next;
        }
        if (!curr) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->key = nums[i];
            newNode->count = 1;
            newNode->next = hashTable[key];
            hashTable[key] = newNode;
        }
    }

    // Sort the array
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    // Try to form sets
    for (int i = 0; i < numsSize; i++) {
        int key = nums[i] % HASH_SIZE;
        Node* curr = hashTable[key];
        while (curr) {
            if (curr->key == nums[i]) {
                if (curr->count == 0) {
                    break;
                }
                for (int j = 0; j < k; j++) {
                    int nextKey = (nums[i] + j) % HASH_SIZE;
                    Node* nextCurr = hashTable[nextKey];
                    while (nextCurr) {
                        if (nextCurr->key == nums[i] + j) {
                            if (nextCurr->count == 0) {
                                return false;
                            }
                            nextCurr->count--;
                            break;
                        }
                        nextCurr = nextCurr->next;
                    }
                    if (!nextCurr) {
                        return false;
                    }
                }
                break;
            }
            curr = curr->next;
        }
    }

    // Free memory
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* curr = hashTable[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    return true;
}
