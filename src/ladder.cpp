#include "ladder.h"

void error(string word1, string word2, string msg) {
    throw runtime_error("Error: " + msg + "\nWord 1: " + word1 + "\nWord 2: " + word2);
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();
    
    if (abs(len1 - len2) > d) return false;
    
    int differences = 0;
    
    if (len1 == len2) {
        for (int i = 0; i < len1; i++) {
            if (str1[i] != str2[i]) differences++;
        }
        return differences <= d;
    }
    
    const string& shorter = (len1 < len2) ? str1 : str2;
    const string& longer = (len1 < len2) ? str2 : str1;
    int short_len = shorter.length();
    int long_len = longer.length();
    
    int i = 0, j = 0;
    while (i < short_len && j < long_len) {
        if (shorter[i] != longer[j]) {
            differences++;
            j++;
        } else {
            i++;
            j++;
        }
    }
    
    differences += (long_len - j) + (short_len - i);
    return differences <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> paths;
    set<string> visited;
    
    paths.push({begin_word});
    visited.insert(begin_word);
    
    while (!paths.empty()) {
        vector<string> current_path = paths.front();
        paths.pop();
        
        string current = current_path.back();
        
        string word = current;
        for (size_t i = 0; i < current.length(); i++) {
            char original = word[i];
            for (char c = 'a'; c <= 'z'; c++) {
                word[i] = c;
                if (word_list.count(word) && !visited.count(word)) {
                    vector<string> new_path = current_path;
                    new_path.push_back(word);
                    
                    if (word == end_word) {
                        return new_path;
                    }
                    
                    paths.push(new_path);
                    visited.insert(word);
                }
            }
            word[i] = original;
        }
    }
    
    return vector<string>();
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        throw runtime_error("Cannot open dictionary file: " + file_name);
    }
    
    string word;
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i < ladder.size() - 1) cout << " ";
    }
    cout << " " << endl;
}

void verify_word_ladder() {
    try {
        set<string> word_list;
        load_words(word_list, "words.txt");
        
        vector<pair<string, string>> test_cases = {
            {"work", "play"},
            {"sleep", "awake"},
            {"awake", "sleep"}
        };
        
        for (const auto& test : test_cases) {
            vector<string> ladder = generate_word_ladder(test.first, test.second, word_list);
            print_word_ladder(ladder);
        }
    }
    catch (const exception& e) {
        cout << "Error during verification: " << e.what() << endl;
    }
}