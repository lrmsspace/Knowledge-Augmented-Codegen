// Source: https://leetcode.com/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string num, representing a large integer, and an integer k.
//
// We call some integer wonderful if it is a permutation of the digits in num and is greater in value than num. There can be many wonderful integers. However, we only care about the smallest-valued ones.
//
//
// 	For example, when num = "5489355142":
//
// 	
// 		The 1st smallest wonderful integer is "5489355214".
// 		The 2nd smallest wonderful integer is "5489355241".
// 		The 3rd smallest wonderful integer is "5489355412".
// 		The 4th smallest wonderful integer is "5489355421".
// 	
// 	
//
//
// Return the minimum number of adjacent digit swaps that needs to be applied to num to reach the kth smallest wonderful integer.
//
// The tests are generated in such a way that kth smallest wonderful integer exists.
//
// Example:
// Input: num = "5489355142", k = 4
// Output: 2
// Explanation: The 4th smallest wonderful number is "5489355421". To get this number:
// - Swap index 7 with index 8: "5489355142" -> "5489355412"
// - Swap index 8 with index 9: "5489355412" -> "5489355421"
//
// Constraints:
// 2 <= num.length <= 1000
// 	1 <= k <= 1000
// 	num only consists of digits.
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

int getMinSwaps(char* num, int k) {
    // Step 1: Find the kth smallest wonderful integer
    char target[1001]; // Assuming num length is at most 1000
    strcpy(target, num);
    
    for (int i = 0; i < k; i++) {
        // Generate the next permutation of target
        int n = strlen(target);
        int j = n - 2;
        
        // Find the rightmost pair of indices (j, j+1) where target[j] < target[j+1]
        while (j >= 0 && target[j] >= target[j + 1]) {
            j--;
        }
        
        if (j >= 0) {
            // Find the rightmost index l where target[j] < target[l]
            int l = n - 1;
            while (target[j] >= target[l]) {
                l--;
            }
            
            // Swap target[j] and target[l]
            char temp = target[j];
            target[j] = target[l];
            target[l] = temp;
        }
        
        // Reverse the subarray from j + 1 to the end
        int left = j + 1, right = n - 1;
        while (left < right) {
            char temp = target[left];
            target[left] = target[right];
            target[right] = temp;
            left++;
            right--;
        }
    }
    
    // Step 2: Count the minimum adjacent swaps to transform num to target
    int swaps = 0;
    int len = strlen(num);
    
    for (int i = 0; i < len; i++) {
        if (num[i] != target[i]) {
            // Find the position of the character in num that matches target[i]
            int j = i + 1;
            while (num[j] != target[i]) {
                j++;
            }
            
            // Swap characters in num until we bring the character at position j to position i
            while (j > i) {
                char temp = num[j];
                num[j] = num[j - 1];
                num[j - 1] = temp;
                swaps++;
                j--;
            }
        }
    }
    
    return swaps;       
}
