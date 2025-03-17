#include "ladder.h"

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (str1 == str2) return true; 
    
    int len1 = str1.length();
    int len2 = str2.length();
    
    if (abs(len1 - len2) > d) return false;
    
    if (len1 == len2) {
        int differences = 0;
        for (size_t i = 0; i < len1; i++) {
            if (str1[i] != str2[i]) differences++;
            if (differences > d) return false;
        }
        return true;
    }
    
    const string& shorter = (len1 < len2) ? str1 : str2;
    const string& longer = (len1 < len2) ? str2 : str1;
    
    for (size_t i = 0; i <= longer.length(); i++) {
        string temp = longer;
        temp.erase(i, 1);
        if (temp == shorter) return true;
    }
    
    return false;
}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1 == word2) return true; 
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return vector<string>();  
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