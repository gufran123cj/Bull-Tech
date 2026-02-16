#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

namespace {
    const char* const DEFAULT_FILE = "sample.txt";
}

int main(int argc, char* argv[]) {
    std::cout << "--- Longest Word ---\n" << std::flush;

    const char* path = (argc >= 2) ? argv[1] : DEFAULT_FILE;
    if (argc < 2) {
        std::cout << "Arguman yok, varsayilan: " << DEFAULT_FILE << "\n" << std::flush;
    }

    std::cout << "Input file : " << path << "\n" << std::flush;

    std::ifstream in(path);
    if (!in) {
        std::cout << "Error: dosya acilamadi: " << path << "\n" << std::flush;
        return 1;
    }

    std::vector<std::string> longest_words;
    std::string current;
    current.reserve(128);
    std::size_t max_len = 0;

    char c;
    while (in.get(c)) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            current += c;
        } else {
            if (!current.empty()) {
                if (current.size() > max_len) {
                    max_len = current.size();
                    longest_words.clear();
                    longest_words.push_back(current);
                } else if (current.size() == max_len) {
                    longest_words.push_back(current);
                }
                current.clear();
            }
        }
    }

    if (!current.empty()) {
        if (current.size() > max_len) {
            max_len = current.size();
            longest_words.clear();
            longest_words.push_back(current);
        } else if (current.size() == max_len) {
            longest_words.push_back(current);
        }
    }

    if (!longest_words.empty()) {
        std::cout << "\n--- Result ---\n";
        std::cout << "Longest word(s) (" << longest_words.size() << " adet, uzunluk " << max_len << "):\n";
        for (std::size_t i = 0; i < longest_words.size(); ++i) {
            std::string& w = longest_words[i];
            for (char& ch : w) {
                ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            }
            std::cout << "  " << (i + 1) << ") " << w << "  addr=" << static_cast<const void*>(w.data()) << "\n";
        }
    } else {
        std::cout << "\n--- Result ---\n(no words)\n";
    }
    std::cout << std::flush;
    return 0;
}