#include "ladder.h"

void error(string word1, string word2, string msg) {
    throw runtime_error("Error: " + msg + "\nWord 1: " + word1 + "\nWord 2: " + word2);
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (str1.length() != str2.length()) return false;
    
    int differences = 0;
    for (size_t i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) differences++;
        if (differences > d) return false;
    }
    return differences == d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word.length() != end_word.length()) {
        error(begin_word, end_word, "Words must be the same length");
    }
    
    if (word_list.find(begin_word) == word_list.end() || 
        word_list.find(end_word) == word_list.end()) {
        error(begin_word, end_word, "Both words must be in dictionary");
    }
    
    map<string, string> previous;
    queue<string> q;
    set<string> visited;
    
    q.push(begin_word);
    visited.insert(begin_word);
    
    bool found = false;
    while (!q.empty() && !found) {
        string current = q.front();
        q.pop();
        
        for (const string& word : word_list) {
            if (visited.find(word) != visited.end()) continue;
            
            if (is_adjacent(current, word)) {
                previous[word] = current;
                visited.insert(word);
                
                if (word == end_word) {
                    found = true;
                    break;
                }
                
                q.push(word);
            }
        }
    }
    
    vector<string> path;
    if (found) {
        string current = end_word;
        while (current != begin_word) {
            path.push_back(current);
            current = previous[current];
        }
        path.push_back(begin_word);
        reverse(path.begin(), path.end());
    }
    
    return path;
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
        cout << "No word ladder exists between these words." << endl;
        return;
    }
    
    cout << "Found ladder of length " << ladder.size() << ":" << endl;
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i < ladder.size() - 1) cout << " -> ";
    }
    cout << endl;
}