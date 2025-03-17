#include "ladder.h"

void verify_word_ladder() {
    cout << "Running verification tests...\n" << endl;
    
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    
    struct TestCase {
        string start;
        string end;
        int expected_length;
    };
    
    vector<TestCase> tests = {
        {"cat", "dog", 4},
        {"marty", "curls", 6},
        {"code", "data", 6},
        {"work", "play", 6},
        {"sleep", "awake", 8},
        {"car", "cheat", 4}
    };
    
    int passed = 0;
    for (const auto& test : tests) {
        cout << "\nTesting: " << test.start << " -> " << test.end << endl;
        vector<string> ladder = generate_word_ladder(test.start, test.end, word_list);
        print_word_ladder(ladder);
        
        bool passed_test = (ladder.size() == test.expected_length);
        cout << "Expected length: " << test.expected_length 
             << ", Got length: " << ladder.size() 
             << " - " << (passed_test ? "PASSED" : "FAILED") << endl;
        
        if (passed_test) passed++;
    }
    
    cout << "\nPassed " << passed << " out of " << tests.size() << " tests." << endl;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        verify_word_ladder();
        return 0;
    }
    
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <dictionary_file> <start_word> <end_word>" << endl;
        cerr << "Or run without arguments to execute verification tests" << endl;
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
            return 1;
        }
        
        vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
        print_word_ladder(ladder);
        
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    
    return 0;
}