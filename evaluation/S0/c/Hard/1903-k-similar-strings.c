// Source: https://leetcode.com/problems/k-similar-strings/   |   Difficulty: Hard
//
// Problem Description:
// Strings s1 and s2 are k-similar (for some non-negative integer k) if we can swap the positions of two letters in s1 exactly k times so that the resulting string equals s2.
//
// Given two anagrams s1 and s2, return the smallest k for which s1 and s2 are k-similar.
//
// Example:
// Input: s1 = "ab", s2 = "ba"
// Output: 1
// Explanation: The two string are 1-similar because we can use one swap to change s1 to s2: "ab" --> "ba".
//
// Constraints:
// 1 <= s1.length <= 20
// 	s2.length == s1.length
// 	s1 and s2 contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}.
// 	s2 is an anagram of s1.
//

int kSimilarity(char* s1, char* s2) {
    int len = strlen(s1);
    int maxStates = 1;
    for (int i = 0; i < len; i++) {
        maxStates *= 6; /* since only 'a' to 'f' */
    }
    int *dist = (int*)malloc(maxStates * sizeof(int));
    if (!dist) return -1; /* allocation failure */
    for (int i = 0; i < maxStates; i++) dist[i] = -1;

    int startState = 0;
    for (int i = 0; i < len; i++) {
        startState = startState * 6 + (s1[i] - 'a');
    }
    int targetState = 0;
    for (int i = 0; i < len; i++) {
        targetState = targetState * 6 + (s2[i] - 'a');
    }

    int *queue = (int*)malloc(maxStates * sizeof(int));
    if (!queue) {
        free(dist);
        return -1; /* allocation failure */
    }
    int head = 0, tail = 0;
    queue[tail++] = startState;
    dist[startState] = 0;

    while (head < tail) {
        int currState = queue[head++];
        if (currState == targetState) {
            int result = dist[currState];
            free(dist);
            free(queue);
            return result;
        }

        /* Convert state to string */
        char currStr[21];
        int tempState = currState;
        for (int i = len - 1; i >= 0; i--) {
            currStr[i] = (tempState % 6) + 'a';
            tempState /= 6;
        }

        /* Find first mismatch */
        int i = 0;
        while (i < len && currStr[i] == s2[i]) i++;
        for (int j = i + 1; j < len; j++) {
            if (currStr[j] == s2[i] && currStr[j] != s2[j]) {
                /* Swap i and j */
                char temp = currStr[i];
                currStr[i] = currStr[j];
                currStr[j] = temp;

                /* Convert back to state */
                int nextState = 0;
                for (int k = 0; k < len; k++) {
                    nextState = nextState * 6 + (currStr[k] - 'a');
                }

                if (dist[nextState] == -1) {
                    dist[nextState] = dist[currState] + 1;
                    queue[tail++] = nextState;
                }

                /* Swap back */
                temp = currStr[i];
                currStr[i] = currStr[j];
                currStr[j] = temp;
            }
        }
        }
    free(dist);
    free(queue);
    return -1;
}
