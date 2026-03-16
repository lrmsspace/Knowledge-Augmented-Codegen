// Source: https://leetcode.com/problems/count-number-of-bad-pairs/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. A pair of indices (i, j) is a bad pair if i < j and j - i != nums[j] - nums[i].
//
// Return the total number of bad pairs in nums.
//
// Example:
// Input: nums = [4,1,3,3]
// Output: 5
// Explanation: The pair (0, 1) is a bad pair since 1 - 0 != 1 - 4.
// The pair (0, 2) is a bad pair since 2 - 0 != 3 - 4, 2 != -1.
// The pair (0, 3) is a bad pair since 3 - 0 != 3 - 4, 3 != -1.
// The pair (1, 2) is a bad pair since 2 - 1 != 3 - 1, 1 != 2.
// The pair (2, 3) is a bad pair since 3 - 2 != 3 - 3, 1 != 0.
// There are a total of 5 bad pairs, so we return 5.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

long long countBadPairs(int* nums, int numsSize) {
    long long total_pairs = ((long long)numsSize * (numsSize - 1)) / 2;
    long long good_pairs = 0;

    // Using a hash map to count occurrences of (nums[i] - i)
    #define HASH_SIZE 200003
    typedef struct Node {
        long long key;
        long long count;
        struct Node* next;
    } Node;

    Node* hash_map[HASH_SIZE] = {0};

    for (int i = 0; i < numsSize; i++) {
        long long key = (long long)nums[i] - i;
        int hash_index = (key % HASH_SIZE + HASH_SIZE) % HASH_SIZE;

        Node* curr = hash_map[hash_index];
        Node* prev = NULL;
        while (curr != NULL && curr->key != key) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL) {
            curr = (Node*)malloc(sizeof(Node));
            curr->key = key;
            curr->count = 0;
            curr->next = NULL;
            if (prev == NULL) {
                hash_map[hash_index] = curr;
            } else {
                prev->next = curr;
            }
        }

        good_pairs += curr->count;
        curr->count++;
    }

    // Free the hash map
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* curr = hash_map[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    return total_pairs - good_pairs;        
}
