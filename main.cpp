#include <iostream>
#include <string>
#include <algorithm>

class StringTransformer {
public:
    void transform(std::string& input) {
        input = raw3(input);
        input = replaceCharacter(input, 'B', "tAdA");
        input = replaceCharacter(input, 'A', "sae");
    }

private:
    static std::string replaceCharacter(const std::string& s, char target, const std::string& replacement) {
        std::string result;
        result.reserve(s.size() * replacement.size()); // Reserve space for potential growth
        for (char c : s) {
            if (c == target) {
                result += replacement;
            } else {
                result += c;
            }
        }
        return result;
    }

    static std::string raw3(std::string s) {
        size_t left = s.find('('), right = s.rfind(')');
        if (left != std::string::npos && right != std::string::npos && left < right) {
            char theta = s[left + 1];
            std::string inner = s.substr(left + 2, right - left - 2);
            inner = raw3(inner); // Recursive call
            std::string changed;
            changed += theta;
            for (auto it = inner.rbegin(); it != inner.rend(); ++it) {
                changed += *it;
                changed += theta;
            }
            s.replace(left, right - left + 1, changed);//
        }
        return s;
    }
};

int main() {
    std::string input;
    std::cin >> input;
    StringTransformer transformer;
    transformer.transform(input);
    std::cout << input << std::endl;
    return 0;
}