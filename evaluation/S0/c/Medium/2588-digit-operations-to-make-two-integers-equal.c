// Source: https://leetcode.com/problems/digit-operations-to-make-two-integers-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers n and m that consist of the same number of digits.
//
// You can perform the following operations any number of times:
//
//
// 	Choose any digit from n that is not 9 and increase it by 1.
// 	Choose any digit from n that is not 0 and decrease it by 1.
//
//
// The integer n must not be a prime number at any point, including its original value and after each operation.
//
// The cost of a transformation is the sum of all values that n takes throughout the operations performed.
//
// Return the minimum cost to transform n into m. If it is impossible, return -1.
//
// Example:
// Input: n = 10, m = 12
//
// Output: 85
//
// Explanation:
//
// We perform the following operations:
//
//
// 	Increase the first digit, now n = 20.
// 	Increase the second digit, now n = 21.
// 	Increase the second digit, now n = 22.
// 	Decrease the first digit, now n = 12.
//
// Constraints:
// 1 <= n, m < 104
// 	n and m consist of the same number of digits.
//

int minOperations(int n, int m) {
    // Function to check if a number is prime
    int isPrime(int num) {
        if (num < 2) return 0;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return 0;
        }
        return 1;
    }

    // Convert number to digit array
    void toDigits(int num, int* digits, int size) {
        for (int i = size - 1; i >= 0; i--) {
            digits[i] = num % 10;
            num /= 10;
        }
    }

    int size = 0, temp = n;
    while (temp > 0) {
        size++;
        temp /= 10;
    }

    int nDigits[size], mDigits[size];
    toDigits(n, nDigits, size);
    toDigits(m, mDigits, size);

    long long totalCost = n;
    for (int i = 0; i < size; i++) {
        while (nDigits[i] != mDigits[i]) {
            if (nDigits[i] < mDigits[i]) {
                nDigits[i]++;
            } else {
                nDigits[i]--;
            }

            // Reconstruct the number from digits
            int currentNum = 0;
            for (int j = 0; j < size; j++) {
                currentNum = currentNum * 10 + nDigits[j];
            }

            if (isPrime(currentNum)) {
                return -1;
            }
            totalCost += currentNum;
        }
    }
    return (int)totalCost;
}
