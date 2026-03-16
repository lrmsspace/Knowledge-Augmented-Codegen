// Source: https://leetcode.com/problems/contains-duplicate-ii/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums and an integer k, return true if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.
//
// Example:
// Input: nums = [1,2,3,1], k = 3
// Output: true
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	0 <= k <= 105
//

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    typedef struct HashNode {
        int key;
        int value;
        struct HashNode* next;
    } HashNode;

    #define TABLE_SIZE 100003
    HashNode* table[TABLE_SIZE] = {0};

    unsigned int hash(int key) {
        return ((unsigned int)(key + 1000000000)) % TABLE_SIZE;
    }

    for (int i = 0; i < numsSize; i++) {
        unsigned int idx = hash(nums[i]);
        HashNode* node = table[idx];
        while (node) {
            if (node->key == nums[i]) {
                if (i - node->value <= k) {
                    // Free allocated memory before returning
                    for (int j = 0; j < TABLE_SIZE; j++) {
                        HashNode* curr = table[j];
                        while (curr) {
                            HashNode* temp = curr;
                            curr = curr->next;
                            free(temp);
                        }
                    }
                    return true;
                } else {
                    node->value = i; // Update the index
                    break;
                }
            }
            node = node->next;
        }
        if (!node) {
            HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
            newNode->key = nums[i];
            newNode->value = i;
            newNode->next = table[idx];
            table[idx] = newNode;
        }
    }

    // Free allocated memory
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* curr = table[i];
        while (curr) {
            HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    return false;       
}
