// Source: https://leetcode.com/problems/count-the-number-of-infection-sequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an array sick sorted in increasing order, representing positions of infected people in a line of n people.
//
// At each step, one uninfected person adjacent to an infected person gets infected. This process continues until everyone is infected.
//
// An infection sequence is the order in which uninfected people become infected, excluding those initially infected.
//
// Return the number of different infection sequences possible, modulo 109+7.
//
// Example:
// Input: n = 5, sick = [0,4]
//
// Output: 4
//
// Explanation:
//
// There is a total of 6 different sequences overall.
//
//
// 	Valid infection sequences are [1,2,3], [1,3,2], [3,2,1] and [3,1,2].
// 	[2,3,1] and [2,1,3] are not valid infection sequences because the person at index 2 cannot be infected at the first step.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= sick.length <= n - 1
// 	0 <= sick[i] <= n - 1
// 	sick is sorted in increasing order.
//

int numberOfSequence(int n, int* sick, int sickSize) {
    const int MOD = 1000000007;

    /* Precompute factorials and inverse factorials for combinations */
    int *fact = (int*)malloc((n + 1) * sizeof(int));
    int *invFact = (int*)malloc((n + 1) * sizeof(int));
    if (!fact || !invFact) {
        free(fact); free(invFact); return 0;
    }
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = (long long)fact[i - 1] * i % MOD;
    }
    invFact[n] = 1; // Fermat's little theorem for modular inverse
    for (int i = n - 1; i >= 0; --i) {
        invFact[i] = (long long)invFact[i + 1] * (i + 1) % MOD;
    }

    /* Function to compute nCr % MOD */
    auto nCr = [&](int N, int R) {
        if (R > N || R < 0) return 0;
        return (long long)fact[N] * invFact[R] % MOD * invFact[N - R] % MOD;
    };

    int result = 1;
    int prev = -1;
    for (int i = 0; i <= sickSize; ++i) {
        int left = (i == 0) ? sick[i] : sick[i] - sick[i - 1] - 1;
        int right = (i == sickSize) ? n - sick[i - 1] - 1 : sick[i + 1] - sick[i] - 1;

        int len = left + right;
        if (len > 0) {
            result = (long long)result * nCr(len, left) % MOD;
            if (left > 0 && right > 0) {
                result = (long long)result * fact[len - 1] % MOD;
            } else {
                result = (long long)result * fact[len] % MOD;
            }
        }
    }

    free(fact);
    free(invFact);
    return result;      
}
