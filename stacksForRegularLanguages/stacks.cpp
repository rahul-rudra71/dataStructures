#include "stacks_for_regular_languages.h"
#include<vector>
#include<string>

void testLang (std::vector<std::string> test, int testAns[], int testType) {
    std::cout << "****************** L" << testType << " Test ******************\n";
    stacks_for_regular_languages input;

    for(int i = 0; i < test.size(); i++) {
        char c[test[i].size() + 1];
        test[i].copy(c, test[i].size() + 1);
        c[test[i].size()] = '\0';

        std::string answer = "fail";

        if(testType == 1) {
            bool testIn = input.L1(c);
            if(testIn == testAns[i])
                answer = "pass";
        } else if(testType == 2) {
            bool testIn = input.L2(c);
            if(testIn == testAns[i])
                answer = "pass";
        }   else if(testType == 3) {
            bool testIn = input.L3(c);
            if(testIn == testAns[i])
                answer = "pass";
        } else {
            bool testIn = input.L4(c);
            if(testIn == testAns[i])
                answer = "pass";
        }        
        

        std::cout << test[i] << ": " << answer << "\n";
    }
}


int main() {
    std::vector<std::string> l1Test = { "ABAB", "AABB", "AAAABBB", "AAABBBB", "ABABBABABABAB", "AABBAAABBBBA", "AAA" };
    int l1Ans[] = {1, 1, 0, 0, 0, 1, 0};

    std::vector<std::string> l2Test = { "ABAB", "AABB", "AAAABBB", "AAABBBB", "ABABBABABABAB", "AABBAAABBBBA", "AAAABBBB", "AABBAABB", "AACB", "AACC", "BBAA", "AB", "AAA" };
    int l2Ans[] = {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};

    std::vector<std::string> l3Test = { "ABAB", "AABB", "AAAABBB", "AAABBBB", "ABABBABABABAB", "AABBAAABBB", "AAAABBBB", "AABBAABB", "AACB", "AACC", "BBAA", "AB", "AAA", "AABBAABBAABB", "BA", "AABBAABBB", "ABABABABAB", "AAABBBAAABBBAAA", "AABABB", "AABBAB"};
    int l3Ans[] = {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0};

    std::vector<std::string> l4Test = { "ABAB", "AABB", "AAAABBB", "AAABBBB", "ABABBABABABAB", "AABBAAABBB", "AAAABBBB", "AABBAABB", "AACB", "AACC", "BBAA", "AB", "AAA", "AABBAABBAABB", "BA", "AABBAABBB", "ABABABABAB", "AAABBBAAABBBAAA", "AABABB", "AABBBAABBB", "AAABBAAABB", "AAABBAAABBAAABB", "AAABBAAABBAAABBAAABBAAABB", "AAABBAAABBAABBBAABBB"};
    int l4Ans[] = {1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0};

    testLang(l1Test, l1Ans, 1);
    testLang(l2Test, l2Ans, 2);
    testLang(l3Test, l3Ans, 3);
    testLang(l4Test, l4Ans, 4);
    

    return 0;
}