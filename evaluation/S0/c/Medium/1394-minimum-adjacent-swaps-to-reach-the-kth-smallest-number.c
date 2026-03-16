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

int getMinSwaps(char* num, int k) {
    int len = strlen(num);
    char target[1001];
    strcpy(target, num);

    // Generate the k-th smallest wonderful number
    for (int step = 0; step < k; step++) {
        // Find the rightmost ascent
        int i = len - 2;
        while (i >= 0 && target[i] >= target[i + 1]) {
            i--;
        }

        // Find the smallest digit on right side of i which is larger than target[i]
        int j = len - 1;
        while (j > i && target[j] <= target[i]) {
            j--;
        }

        // Swap the found digits
        char temp = target[i];
        target[i] = target[j];
        target[j] = temp;

        // Reverse the digits after index i
        int left = i + 1, right = len - 1;
        while (left < right) {
            temp = target[left];
            target[left] = target[right];
            target[right] = temp;
            left++;
            right--;
        }
    }

    // Calculate minimum adjacent swaps to transform num to target
    int swaps = 0;
    for (int i = 0; i < len; i++) {
        if (num[i] != target[i]) {
            int j = i + 1;
            while (j < len && num[j] != target[i]) {
                j++;
            }
            // Bring the found digit to position i by swapping adjacent digits
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
