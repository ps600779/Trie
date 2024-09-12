#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TrieNode {
public:
  char data;
  TrieNode *children[26];
  bool isEndOfWord;

  TrieNode(char c) {
    this->data = c;
    for (int i = 0; i < 26; i++) {
      children[i] = NULL;
    }
    isEndOfWord = false;
  }
};

class Trie {
public:
  TrieNode *root;

  Trie() { root = new TrieNode('\0'); }

  void insertRecur(TrieNode *root, string word) {
    if (word.length() == 0) {
      root->isEndOfWord = true;
      return;
    }

    // assumption word will be in lower case english letters only
    int index = word[0] - 'a';
    TrieNode *child;

    // present
    if (root->children[index] != NULL) {
      child = root->children[index];
    } else { // absent
      child = new TrieNode(word[0]);
      root->children[index] = child;
    }

    // recurssion
    insertRecur(child, word.substr(1));
  }

  void insertNode(string word) { insertRecur(root, word); }

  bool searchRecur(TrieNode *root, string word) {
    if (word.length() == 0) {
      return root->isEndOfWord;
    }

    int index = word[0] - 'a';

    TrieNode *child;
    if (root->children[index] != NULL) {
      child = root->children[index];
    } else {
      return false;
    }
    return searchRecur(child, word.substr(1));
  }

  bool searchNode(string word) { return searchRecur(root, word); }

  TrieNode *getPrefixNode(TrieNode *root, string word) {
    TrieNode *current = root;

    for (int i = 0; i < word.size(); i++) {
      int index = word[i] - 'a';

      if (current->children[index] != NULL) {
        current = current->children[index];
      } else {
        return NULL;
      }
    }
    return current;
  }

  void findWords(TrieNode *node, string word, vector<string> &result) {
    if (node == nullptr) {
      return;
    }

    if (node->isEndOfWord) {
      result.push_back(word);
    }
    for (int i = 0; i < 26; i++) {
      char ch = 'a' + i;
      if (node->children[i] != nullptr) {
        findWords(node->children[i], word + ch, result);
      }
    }
  }

  vector<string> autoComplete(string word) {
    vector<string> result;

    TrieNode *prefixNode = getPrefixNode(root, word);

    if (!prefixNode) {
      return result;
    }

    findWords(prefixNode, word, result);

    return result;
  }

  int minDistance(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();

    vector<vector<int> > t(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++) {
      t[i][0] = i;
    }

    for (int i = 0; i <= n; i++) {
      t[0][i] = i;
    }

    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        if (word1[i - 1] == word2[j - 1]) {
          t[i][j] = t[i - 1][j - 1];
        } else {
          t[i][j] = 1 + min(t[i - 1][j], min(t[i][j - 1], t[i - 1][j - 1]));
        }
      }
    }
    return t[m][n];
  }

  void findwordsRecur(TrieNode *node, string currentWord, string targetWord,
                      vector<string> &result) {
    if (node == NULL) {
      return;
    }

    if (node->isEndOfWord) {
      int distance = minDistance(currentWord, targetWord);
      if (distance <= 3) {
        result.push_back(currentWord);
      }
    }

    for (int i = 0; i < 26; i++) {
      if (node->children[i] != NULL) {
        char ch = 'a' + i;
        findwordsRecur(node->children[i], currentWord + ch, targetWord, result);
      }
    }
  }

  vector<string> findWordsAutoCorrect(string word) {
    vector<string> result;
    findwordsRecur(root, "", word, result);

    return result;
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  Trie *t = new Trie();

  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    t->insertNode(s);
  }

  for (int i = 0; i < q; i++) {
    int chioce;
    string str;
    cin >> chioce >> str;

    if (chioce == 1) {
      bool found = t->searchNode(str);
      
      cout << (found ? "1" : "0") << endl;
    } else if (chioce == 2) {
      vector<string> completions = t->autoComplete(str);
      sort(completions.begin(), completions.end());

      cout << completions.size() << endl;

      for (string word : completions) {
        cout << word << endl;
      }
    } else if (chioce == 3) {
      vector<string> corrections = t->findWordsAutoCorrect(str);
      sort(corrections.begin(), corrections.end());

      cout << corrections.size() << endl;

      for (string word : corrections) {
        cout << word << endl;
      }

    }

  }

  return 0;
}