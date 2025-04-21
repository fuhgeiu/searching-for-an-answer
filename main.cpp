#include "inverted_text.h"

int main() {

    InvertedIndex index;
    index.addstopwordsdefault();
    index.buildfromfile("input.txt");
    index.savetofile("inverted_index.txt");
    return 0;
}