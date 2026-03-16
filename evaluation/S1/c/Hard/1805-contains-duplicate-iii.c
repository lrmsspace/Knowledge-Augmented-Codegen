// Source: https://leetcode.com/problems/contains-duplicate-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers indexDiff and valueDiff.
//
// Find a pair of indices (i, j) such that:
//
//
// 	i != j,
// 	abs(i - j) <= indexDiff.
// 	abs(nums[i] - nums[j]) <= valueDiff, and
//
//
// Return true if such pair exists or false otherwise.
//
// Example:
// Input: nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
// Output: true
// Explanation: We can choose (i, j) = (0, 3).
// We satisfy the three conditions:
// i != j --> 0 != 3
// abs(i - j) <= indexDiff --> abs(0 - 3) <= 3
// abs(nums[i] - nums[j]) <= valueDiff --> abs(1 - 1) <= 0
//
// Constraints:
// 2 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	1 <= indexDiff <= nums.length
// 	0 <= valueDiff <= 109
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int indexDiff, int valueDiff) {
    if (numsSize <= 1 || indexDiff <= 0 || valueDiff < 0) {
        return false;
    }

    typedef struct Bucket {
        long long min;
        long long max;
        struct Bucket* next;
    } Bucket;

    #define BUCKET_SIZE ((long long)valueDiff + 1)
    #define GET_BUCKET_ID(num) ((num) >= 0 ? (num) / BUCKET_SIZE : ((num) + 1) / BUCKET_SIZE - 1)
    #define HASH_SIZE 100003
    Bucket** hashTable = (Bucket**)calloc(HASH_SIZE, sizeof(Bucket*));
    for (int i = 0; i < numsSize; i++) {
        long long num = (long long)nums[i];
        long long bucketId = GET_BUCKET_ID(num);
        int hashIndex = (bucketId % HASH_SIZE + HASH_SIZE) % HASH_SIZE;

        // Check current bucket
        Bucket* curr = hashTable[hashIndex];
        while (curr) {
            if (curr->min <= num && num <= curr->max) {
                return true;
            }
            curr = curr->next;
        }

        // Check neighboring buckets
        for (long long neighborId = bucketId - 1; neighborId <= bucketId + 1; neighborId += 2) {
            int neighborHashIndex = (neighborId % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
            Bucket* neighbor = hashTable[neighborHashIndex];
            while (neighbor) {
                if (llabs(neighbor->min - num) <= valueDiff || llabs(neighbor->max - num) <= valueDiff) {
                    return true;
                }
                neighbor = neighbor->next;
            }
        }

        // Insert into current bucket
        Bucket* newBucket = (Bucket*)malloc(sizeof(Bucket));
        newBucket->min = num;
        newBucket->max = num;
        newBucket->next = hashTable[hashIndex];
        hashTable[hashIndex] = newBucket;

        // Remove old element if out of indexDiff range
        if (i >= indexDiff) {
            long long oldNum = (long long)nums[i - indexDiff];
            long long oldBucketId = GET_BUCKET_ID(oldNum);
            int oldHashIndex = (oldBucketId % HASH_SIZE + HASH_SIZE) % HASH_SIZE;

            Bucket* prev = NULL;
            Bucket* currOld = hashTable[oldHashIndex];
            while (currOld) {
                if (currOld->min == oldNum && currOld->max == oldNum) {
                    if (prev) {
                        prev->next = currOld->next;
                    } else {
                        hashTable[oldHashIndex] = currOld->next;
                    }
                    free(currOld);
                    break;
                }
                prev = currOld;
                currOld = currOld->next;
            }
        }
    }
    // Cleanup
    for (int i = 0; i < HASH_SIZE; i++) {
        Bucket* curr = hashTable[i];
        while (curr) {
            Bucket* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(hashTable);
    return false;
}
