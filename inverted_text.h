#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

class InvertedIndex {

private:

    std::map<std::string, std::vector<int> > index;

    std::vector<std::string> stopwords;

    bool isstopword(const std::string& word) {
        return find(stopwords.begin(), stopwords.end(), word) != stopwords.end();
    }

    std::string cleanword(const std::string& word) {

        std::string cleaned;
        for (char c : word) {
            if (!ispunct(c)) {
                cleaned += tolower(c);
            }
        }
        return cleaned;
    }

public:

    void addstopwordsdefault() {

        std::string Stopwords[] = {"a", "and", "the", "to", "for", "they", "in", "on", "of", "is", "it", "at", "with"};

        stopwords.insert(stopwords.begin(),Stopwords,Stopwords + 13);
    }

    void buildfromfile(const std::string& filename) {

        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        std::string word;
        int position = 0;

        while (file >> word) {

            std::string cleaned = cleanword(word);
            if (cleaned.empty() || isstopword(cleaned)) continue;
            index[cleaned].push_back(position);
            ++position;
        }

        file.close();
    }

    void savetofile(const std::string& outputFilename) const {
        std::ofstream out(outputFilename);
        if (!out) {
            std::cerr << "Failed to open output file: " << outputFilename << std::endl;
            return;
        }

        out << "{\n";
        bool first = true;

        for (auto it = index.begin(); it != index.end(); ++it) {
            if (!first) out << ",\n";
            out << "  \"" << it->first << "\": [";

            const auto& pos = it->second;

            for (size_t i = 0; i < pos.size(); ++i) {
                out << pos[i];
                if (i < pos.size() - 1) out << ", ";
            }

            out << "]";
            first = false;
        }

        out << "\n}\n";

        out.close();
        std::cout << "Inverted index saved to " << outputFilename << std::endl;
    }
};