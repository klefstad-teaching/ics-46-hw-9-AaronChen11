#include "ladder.h"

void error(string word1, string word2, string msg) {
    throw runtime_error("Error: " + msg + "\nWord 1: " + word1 + "\nWord 2: " + word2);
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();
    
    if (abs(len1 - len2) > d) return false;
    
    
    if (len1 == len2) {
        int differences = 0;
        for (int i = 0; i < len1; i++) {
            if (str1[i] != str2[i]) differences++;
            if (differences > d) return false;
        }
        return true;
    }
    
    const string& shorter = (len1 < len2) ? str1 : str2;
    const string& longer = (len1 < len2) ? str2 : str1;
    
    int i = 0, j = 0;
    int differences = 0;
    
    while (i < shorter.length() && j < longer.length()) {
        if (shorter[i] == longer[j]) {
            i++;
            j++;
        } else {
            differences++;
            if (differences > d) return false;
            j++;
        }
    }
    
    differences += longer.length() - j;
    return differences <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (word_list.find(end_word) == word_list.end() && begin_word != end_word) {
        error(begin_word, end_word, "End word must be in dictionary");
    }
    
    queue<vector<string>> paths;
    set<string> visited;
    
    paths.push({begin_word});
    visited.insert(begin_word);
    
    while (!paths.empty()) {
        vector<string> current_path = paths.front();
        paths.pop();
        
        string current = current_path.back();
        
        if (current == end_word) {
            return current_path;
        }
        
        for (const string& word : word_list) {
            if (visited.find(word) != visited.end()) continue;
            
            if (is_adjacent(current, word)) {
                vector<string> new_path = current_path;
                new_path.push_back(word);
                paths.push(new_path);
                visited.insert(word);
            }
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
            {"work", "play"},    //6
            {"sleep", "awake"},  //8
            {"awake", "sleep"},  //8
            {"car", "cheat"}     //4
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