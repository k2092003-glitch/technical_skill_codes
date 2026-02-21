#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define TOP_K 5

// Word structure
typedef struct {
    char word[100]; //string size limit is 100
    int frequency;
} Word;

// Trie node
typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int isEndOfWord;

    Word* top[TOP_K];   // top 5 suggestions
} TrieNode;


// Create new node
TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEndOfWord = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;

    for (int i = 0; i < TOP_K; i++)
        node->top[i] = NULL;

    return node;
}


// Update top 5 suggestions (sorted by frequency)
void updateTop(TrieNode* node, Word* w) {

    int i;

    // Check if already present
    for (i = 0; i < TOP_K; i++) {
        if (node->top[i] && strcmp(node->top[i]->word, w->word) == 0) {
            break;
        }
    }

    // If not present, try inserting
    if (i == TOP_K) {
        for (i = 0; i < TOP_K; i++) {
            if (node->top[i] == NULL) {
                node->top[i] = w;
                break;
            }
        }

        // If full, replace smallest
        if (i == TOP_K) {
            int min = 0;
            for (int j = 1; j < TOP_K; j++)
                if (node->top[j]->frequency < node->top[min]->frequency)
                    min = j;

            if (w->frequency > node->top[min]->frequency)
                node->top[min] = w;
        }
    }

    // Sort descending
    for (int i = 0; i < TOP_K - 1; i++) {
        for (int j = i + 1; j < TOP_K; j++) {
            if (node->top[i] && node->top[j] &&
                node->top[j]->frequency > node->top[i]->frequency) {

                Word* temp = node->top[i];
                node->top[i] = node->top[j];
                node->top[j] = temp;
            }
        }
    }
}


// Insert word (frequency increases if already exists)
void insert(TrieNode* root, const char* word) {

    TrieNode* current = root;

    // Traverse and create nodes
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

        if (current->children[index] == NULL)
            current->children[index] = createNode();

        current = current->children[index];
    }

    Word* w;

    if (current->isEndOfWord) {
        // Word already exists
        w = current->top[0];   // first element will contain it
        w->frequency++;
    } else {
        // New word
        w = (Word*)malloc(sizeof(Word));
        strcpy(w->word, word);
        w->frequency = 1;
        current->isEndOfWord = 1;
    }

    // Now update top suggestions along prefix path
    current = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        current = current->children[index];
        updateTop(current, w);
    }
}


// Get top 5 suggestions
void getTopSuggestions(TrieNode* root, const char* prefix) {

    TrieNode* current = root;

    for (int i = 0; prefix[i] != '\0'; i++) {
        int index = prefix[i] - 'a';

        if (current->children[index] == NULL) {
            printf("No suggestions found\n");
            return;
        }

        current = current->children[index];
    }

    printf("Top suggestions for \"%s\":\n", prefix);
    for (int i = 0; i < TOP_K; i++) {
        if (current->top[i])
            printf("%s (%d)\n",
                   current->top[i]->word,
                   current->top[i]->frequency);
    }
}


// Free memory
void freeTrie(TrieNode* root) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            freeTrie(root->children[i]);
    free(root);
}


// Example
int main() {

    TrieNode* root = createNode();
      insert(root, "application");
     insert(root, "application");
      insert(root, "application"); insert(root, "application");
    insert(root, "apple");
    insert(root, "app");
  insert(root, "apple");
insert(root, "apple");
    insert(root, "apply");

    getTopSuggestions(root, "appl");


    freeTrie(root);
    return 0;
}
