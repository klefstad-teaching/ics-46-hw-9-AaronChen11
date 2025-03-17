#include "ladder.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <dictionary_file> <start_word> <end_word>" << endl;
        return 1;
    }

    try {
        set<string> word_list;
        load_words(word_list, argv[1]);
        string start_word = argv[2];
        string end_word = argv[3];
        
        transform(start_word.begin(), start_word.end(), start_word.begin(), ::tolower);
        transform(end_word.begin(), end_word.end(), end_word.begin(), ::tolower);
        
        if (start_word == end_word) {
            cout << "Word ladder found: " << start_word << " " << endl;
            return 0;
        }
        
        if (word_list.find(end_word) == word_list.end()) {
            error(start_word, end_word, "End word must be in dictionary");
        }
        
        vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
        print_word_ladder(ladder);
        
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    
    return 0;
}