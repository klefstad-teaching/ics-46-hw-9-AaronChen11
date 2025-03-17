#include "ladder.h"

void error(string word1, string word2, string msg) {
    throw runtime_error("Error: " + msg + "\nWord 1: " + word1 + "\nWord 2: " + word2);
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (str1 == str2) return d > 0; 
    
    int len1 = str1.length();
    int len2 = str2.length();
    
    if (abs(len1 - len2) > d){
        return false;
    }
    if (len1 == len2) {
        int differences = 0;
        for (size_t i = 0; i < len1; i++) {
            if (str1[i] != str2[i]) differences++;
            if (differences > d) return false;
        }
        return true;
    }
    
    if (len1 > len2){
        return edit_distance_within(str2, str1, d);
    }

    for (size_t i = 0; i <= str2.length(); i++) {
        string temp = str2;
        temp.erase(i, 1);
        if (temp == str1){
            return true;
        }
    }
    
    return false;
}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1.length() == word2.length()) {
        int differences = 0;
        for (size_t i = 0; i < word1.length(); i++) {
            if (word1[i] != word2[i]) differences++;
            if (differences > 1) return false;
        }
        return differences == 1;
    }
    
    if (abs(int(word1.length()) - int(word2.length())) != 1) return false;
    
    const string& shorter = (word1.length() < word2.length()) ? word1 : word2;
    const string& longer = (word1.length() < word2.length()) ? word2 : word1;
    
    size_t i = 0, j = 0;
    bool found_diff = false;
    
    while (i < shorter.length() && j < longer.length()) {
        if (shorter[i] != longer[j]) {
            if (found_diff) return false;
            found_diff = true;
            j++;
        } else {
            i++;
            j++;
        }
    }
    
    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return {begin_word};
    }
    
    queue<vector<string>> paths;
    set<string> visited;
    
    paths.push({begin_word});
    visited.insert(begin_word);
    
    while (!paths.empty()) {
        vector<string> current_path = paths.front();
        paths.pop();
        
        string current = current_path.back();
        
        for (const string& word : word_list) {
            if (visited.count(word)) continue;
            
            if (is_adjacent(current, word)) {
                vector<string> new_path = current_path;
                new_path.push_back(word);
                
                if (word == end_word) {
                    return new_path;
                }
                
                visited.insert(word);
                paths.push(new_path);
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
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    vector<pair<string, string>> test_cases = {
        {"work", "play"},
        {"sleep", "awake"},
        {"awake", "sleep"},
        {"car", "cheat"}
    };
    
    for (const auto& test : test_cases) {
        vector<string> ladder = generate_word_ladder(test.first, test.second, word_list);
        print_word_ladder(ladder);
    }
}