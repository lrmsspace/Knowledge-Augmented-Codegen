// Source: https://leetcode.com/problems/unique-email-addresses/   |   Difficulty: Easy
//
// Problem Description:
// Every valid email consists of a local name and a domain name, separated by the '@' sign. Besides lowercase letters, the email may contain one or more '.' or '+'.
//
//
// 	For example, in "alice@leetcode.com", "alice" is the local name, and "leetcode.com" is the domain name.
//
//
// If you add periods '.' between some characters in the local name part of an email address, mail sent there will be forwarded to the same address without dots in the local name. Note that this rule does not apply to domain names.
//
//
// 	For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward to the same email address.
//
//
// If you add a plus '+' in the local name, everything after the first plus sign will be ignored. This allows certain emails to be filtered. Note that this rule does not apply to domain names.
//
//
// 	For example, "m.y+name@email.com" will be forwarded to "my@email.com".
//
//
// It is possible to use both of these rules at the same time.
//
// Given an array of strings emails where we send one email to each emails[i], return the number of different addresses that actually receive mails.
//
// Example:
// Input: emails = ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
// Output: 2
// Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive mails.
//
// Constraints:
// 1 <= emails.length <= 100
// 	1 <= emails[i].length <= 100
// 	emails[i] consist of lowercase English letters, '+', '.' and '@'.
// 	Each emails[i] contains exactly one '@' character.
// 	All local and domain names are non-empty.
// 	Local names do not start with a '+' character.
// 	Domain names end with the ".com" suffix.
// 	Domain names must contain at least one character before ".com" suffix.
//

int numUniqueEmails(char** emails, int emailsSize) {
    char uniqueEmails[emailsSize][101];
    int uniqueCount = 0;

    for (int i = 0; i < emailsSize; i++) {
        char local[101] = {0};
        char domain[101] = {0};
        int j = 0, k = 0;

        // Split email into local and domain parts
        while (emails[i][j] != '@') {
            if (emails[i][j] == '+') {
                // Ignore everything after '+'
                while (emails[i][j] != '@') j++;
                break;
            }
            if (emails[i][j] != '.') {
                local[k++] = emails[i][j];
            }
            j++;
        }
        local[k] = '\0';
        j++; // Skip '@'

        // Copy domain part
        k = 0;
        while (emails[i][j] != '\0') {
            domain[k++] = emails[i][j++];
        }
        domain[k] = '\0';

        // Combine local and domain to form the normalized email
        char normalizedEmail[202];
        snprintf(normalizedEmail, sizeof(normalizedEmail), "%s@%s", local, domain);

        // Check if this normalized email is unique
        int isUnique = 1;
        for (int m = 0; m < uniqueCount; m++) {
            if (strcmp(uniqueEmails[m], normalizedEmail) == 0) {
                isUnique = 0;
                break;
            }
        }

        // If unique, add to the list
        if (isUnique) {
            strcpy(uniqueEmails[uniqueCount++], normalizedEmail);
        }
    }

    return uniqueCount;     
}
