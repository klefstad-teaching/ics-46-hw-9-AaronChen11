#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << endl;
    cout << "Word 1: " << word1 << endl; 
    cout << "Word 2: " << word2 << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    vector<vector<int>> dp(str1.length() + 1, vector<int>(str2.length() + 1));
    
    for (size_t i = 0; i <= str1.length(); i++)
        dp[i][0] = i;
    for (size_t j = 0; j <= str2.length(); j++)
        dp[0][j] = j;
        
    for (size_t i = 1; i <= str1.length(); i++) {
        for (size_t j = 1; j <= str2.length(); j++) {
            if (tolower(str1[i-1]) == tolower(str2[j-1]))
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }
    return dp[str1.length()][str2.length()] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_neighbors(const string& word) {
    vector<string> neighbors;
    string letters = "abcdefghijklmnopqrstuvwxyz";
    
    for (size_t i = 0; i < word.length(); i++) {
        char original = word[i];
        for (char c : letters) {
            if (c != original) {
                string neighbor = word;
                neighbor[i] = c;
                neighbors.push_back(neighbor);
            }
        }
    }
    
    for (size_t i = 0; i <= word.length(); i++) {
        for (char c : letters) {
            neighbors.push_back(word.substr(0, i) + c + word.substr(i));
        }
    }

    for (size_t i = 0; i < word.length(); i++) {
        neighbors.push_back(word.substr(0, i) + word.substr(i + 1));
    }
    
    return neighbors;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    string start = begin_word;
    string end = end_word;
    transform(start.begin(), start.end(), start.begin(), ::tolower);
    transform(end.begin(), end.end(), end.begin(), ::tolower);
    
    if (start == end) {
        return {};
    }
    
    if (word_list.find(end) == word_list.end()) {
        return {};
    }
    
    queue<vector<string>> ladder_queue;
    set<string> visited;
    
    ladder_queue.push({start});
    visited.insert(start);
    
    const int MAX_DEPTH = 50;  
    
    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        
        if (current_ladder.size() >= MAX_DEPTH) {
            continue;
        }
        
        string last_word = current_ladder.back();
        vector<string> neighbors = generate_neighbors(last_word);
        
        for (const string& neighbor : neighbors) {
            if (visited.count(neighbor)) {
                continue;
            }
            
            if (neighbor != start && word_list.find(neighbor) == word_list.end()) {
                continue;
            }
            
            vector<string> new_ladder = current_ladder;
            new_ladder.push_back(neighbor);
            
            if (neighbor == end) {
                return new_ladder;
            }
            
            visited.insert(neighbor);
            ladder_queue.push(new_ladder);
        }
    }
    
    return {};  
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word ladder found:";
    for (const string& word : ladder) {
        cout << " " << word;
    }
    cout << " " << endl;  
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        throw runtime_error("Could not open dictionary file");
    }
    
    string word;
    while (getline(file, word)) {
        word.erase(word.find_last_not_of(" \n\r\t") + 1);
        if (!word.empty()) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            word_list.insert(word);
        }
    }
}