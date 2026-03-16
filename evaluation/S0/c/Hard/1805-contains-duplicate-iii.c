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

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int indexDiff, int valueDiff) {
    if (numsSize <= 1 || indexDiff <= 0 || valueDiff < 0) return false;

    typedef long long ll;
    typedef struct Bucket {
        ll key;
        ll val;
        struct Bucket* next;
    } Bucket;

    ll width = (ll)valueDiff + 1;
    Bucket** table = (Bucket**)calloc(numsSize, sizeof(Bucket*));
    if (!table) return false;

    for (int i = 0; i < numsSize; ++i) {
        ll num = (ll)nums[i];
        ll key = num / width;
        if (num < 0) key--;

        // Check current bucket
        Bucket* b = table[key % numsSize];
        while (b) {
            if (b->key == key) {
                free(table);
                return true;
            }
            b = b->next;
        }

        // Check neighboring buckets
        for (ll neighborKey = key - 1; neighborKey <= key + 1; neighborKey += 2) {
            b = table[neighborKey % numsSize];
            while (b) {
                if (b->key == neighborKey && llabs(b->val - num) <= valueDiff) {
                    free(table);
                    return true;
                }
                b = b->next;
            }
        }

        // Insert into bucket
        Bucket* newBucket = (Bucket*)malloc(sizeof(Bucket));
        if (!newBucket) {
            free(table);
            return false;
        }
        newBucket->key = key;
        newBucket->val = num;
        newBucket->next = table[key % numsSize];
        table[key % numsSize] = newBucket;

        // Remove old entry
        if (i >= indexDiff) {
            ll oldNum = (ll)nums[i - indexDiff];
            ll oldKey = oldNum / width;
            if (oldNum < 0) oldKey--;

            Bucket** pprev = &table[oldKey % numsSize];
            Bucket* curr = *pprev;
            while (curr) {
                if (curr->key == oldKey) {
                    *pprev = curr->next;
                    free(curr);
                    break;
                }
                pprev = &curr->next;
                curr = curr->next;
            }
        }
    }

    // Free remaining buckets
    for (int i = 0; i < numsSize; ++i) {
        Bucket* b = table[i];
        while (b) {
            Bucket* temp = b;
            b = b->next;
            free(temp);
        }
    }
    free(table);
    return false;
}
