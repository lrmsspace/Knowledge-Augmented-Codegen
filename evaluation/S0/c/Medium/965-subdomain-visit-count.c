// Source: https://leetcode.com/problems/subdomain-visit-count/   |   Difficulty: Medium
//
// Problem Description:
// A website domain "discuss.leetcode.com" consists of various subdomains. At the top level, we have "com", at the next level, we have "leetcode.com" and at the lowest level, "discuss.leetcode.com". When we visit a domain like "discuss.leetcode.com", we will also visit the parent domains "leetcode.com" and "com" implicitly.
//
// A count-paired domain is a domain that has one of the two formats "rep d1.d2.d3" or "rep d1.d2" where rep is the number of visits to the domain and d1.d2.d3 is the domain itself.
//
//
// 	For example, "9001 discuss.leetcode.com" is a count-paired domain that indicates that discuss.leetcode.com was visited 9001 times.
//
//
// Given an array of count-paired domains cpdomains, return an array of the count-paired domains of each subdomain in the input. You may return the answer in any order.
//
// Example:
// Input: cpdomains = ["9001 discuss.leetcode.com"]
// Output: ["9001 leetcode.com","9001 discuss.leetcode.com","9001 com"]
// Explanation: We only have one website domain: "discuss.leetcode.com".
// As discussed above, the subdomain "leetcode.com" and "com" will also be visited. So they will all be visited 9001 times.
//
// Constraints:
// 1 <= cpdomain.length <= 100
// 	1 <= cpdomain[i].length <= 100
// 	cpdomain[i] follows either the "repi d1i.d2i.d3i" format or the "repi d1i.d2i" format.
// 	repi is an integer in the range [1, 104].
// 	d1i, d2i, and d3i consist of lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** subdomainVisits(char** cpdomains, int cpdomainsSize, int* returnSize) {
    #define MAX_DOMAIN_LENGTH 100
    #define MAX_SUBDOMAINS 3000

    typedef struct {
        char domain[MAX_DOMAIN_LENGTH + 1];
        int count;
    } DomainCount;

    DomainCount domainCounts[MAX_SUBDOMAINS];
    int domainCountSize = 0;

    for (int i = 0; i < cpdomainsSize; i++) {
        char* entry = cpdomains[i];
        int count = atoi(entry);
        char* domain = entry + strchr(entry, ' ') - entry + 1;

        char* subdomain = domain;
        while (subdomain) {
            // Check if subdomain already exists
            int found = 0;
            for (int j = 0; j < domainCountSize; j++) {
                if (strcmp(domainCounts[j].domain, subdomain) == 0) {
                    domainCounts[j].count += count;
                    found = 1;
                    break;
                }
            }
            // If not found, add new entry
            if (!found) {
                strcpy(domainCounts[domainCountSize].domain, subdomain);
                domainCounts[domainCountSize].count = count;
                domainCountSize++;
            }
            // Move to the next subdomain
            subdomain = strchr(subdomain, '.');
            if (subdomain) {
                subdomain++; // Skip the dot
            }
        }
    }

    // Prepare the result
    char** result = (char**)malloc(domainCountSize * sizeof(char*));
    for (int i = 0; i < domainCountSize; i++) {
        result[i] = (char*)malloc((MAX_DOMAIN_LENGTH + 20) * sizeof(char));
        sprintf(result[i], "%d %s", domainCounts[i].count, domainCounts[i].domain);
    }

    *returnSize = domainCountSize;
    return result;      
}
