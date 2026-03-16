// Source: https://leetcode.com/problems/sum-of-distances/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. There exists an array arr of length nums.length, where arr[i] is the sum of |i - j| over all j such that nums[j] == nums[i] and j != i. If there is no such j, set arr[i] to be 0.
//
// Return the array arr.
//
// Example:
// Input: nums = [1,3,1,1,2]
// Output: [5,0,3,4,0]
// Explanation: 
// When i = 0, nums[0] == nums[2] and nums[0] == nums[3]. Therefore, arr[0] = |0 - 2| + |0 - 3| = 5. 
// When i = 1, arr[1] = 0 because there is no other index with value 3.
// When i = 2, nums[2] == nums[0] and nums[2] == nums[3]. Therefore, arr[2] = |2 - 0| + |2 - 3| = 3. 
// When i = 3, nums[3] == nums[0] and nums[3] == nums[2]. Therefore, arr[3] = |3 - 0| + |3 - 2| = 4. 
// When i = 4, arr[4] = 0 because there is no other index with value 2.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
//
//
//  
// Note: This question is the same as  2121: Intervals Between Identical Elements.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* distance(int* nums, int numsSize, int* returnSize) {
    // Hash map to store indices of each number
    #define HASH_SIZE 100003
    typedef struct Node {
        int index;
        struct Node* next;
    } Node;

    Node* hashMap[HASH_SIZE] = {0};

    // Function to compute hash
    unsigned int hash(int key) {
        return ((unsigned int)key) % HASH_SIZE;
    }

    // Insert index into hash map
    void insert(int key, int index) {
        unsigned int h = hash(key);
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->index = index;
        newNode->next = hashMap[h];
        hashMap[h] = newNode;
    }

    // Retrieve indices from hash map
    Node* getIndices(int key) {
        unsigned int h = hash(key);
        return hashMap[h];
    }

    // Build the hash map
    for (int i = 0; i < numsSize; i++) {
        insert(nums[i], i);
    }

    long long* result = (long long*)calloc(numsSize, sizeof(long long));
    
    // Calculate distances
    for (int i = 0; i < numsSize; i++) {
        Node* current = getIndices(nums[i]);
        long long totalDistance = 0;
        int count = 0;

        // First pass to calculate total distance and count
        while (current) {
            if (current->index != i) {
                totalDistance += llabs(i - current->index);
                count++;
            }
            current = current->next;
        }

        result[i] = totalDistance;
    }

    // Free the hash map
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* current = hashMap[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    *returnSize = numsSize;
    return result;      
}
