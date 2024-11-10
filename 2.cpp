#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <map>
#include <cmath>
#include <algorithm> // Include for std::find

using namespace std;

class Node {
public:
    int freq;
    char symbol;
    Node* left;
    Node* right;

    Node(int freq, char symbol, Node* left = nullptr, Node* right = nullptr)
        : freq(freq), symbol(symbol), left(left), right(right) {}

    // Overloading the comparison operator for priority queue
    bool operator<(const Node& other) const {
        return freq > other.freq; // Higher frequency has lower priority
    }
};

// Function to calculate Huffman codes
void calculateHuffmanCodes(const Node* node, const string& code, map<char, string>& huffmanCodes) {
    if (node) {
        // If it's a leaf node, store the code for the symbol
        if (!node->left && !node->right) {
            huffmanCodes[node->symbol] = code;
        }
        calculateHuffmanCodes(node->left, code + "0", huffmanCodes);
        calculateHuffmanCodes(node->right, code + "1", huffmanCodes);
    }
}

// Function to delete the Huffman tree to avoid memory leaks
void deleteHuffmanTree(Node* node) {
    if (node) {
        deleteHuffmanTree(node->left);
        deleteHuffmanTree(node->right);
        delete node;
    }
}

int main() {
    int n; // Number of unique characters
    cout << "Enter the number of unique characters: ";
    cin >> n;

    vector<char> chars(n);
    vector<int> freq(n);

    // Input characters and their frequencies
    cout << "Enter the characters and their frequencies:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Character " << i + 1 << ": ";
        cin >> chars[i];
        cout << "Frequency of " << chars[i] << ": ";
        cin >> freq[i];
    }

    priority_queue<Node> nodes;

    // Push all characters and their frequencies into the priority queue
    for (size_t i = 0; i < chars.size(); ++i) {
        nodes.push(Node(freq[i], chars[i]));
    }

    auto start_time = chrono::high_resolution_clock::now();

    // Build the Huffman Tree
    Node* root = nullptr; // Pointer to hold the root of the tree
    while (nodes.size() > 1) {
        Node* left = new Node(nodes.top());
        nodes.pop();
        Node* right = new Node(nodes.top());
        nodes.pop();

        // Create new internal node, does not have a symbol
        Node* newNode = new Node(left->freq + right->freq, '\0', left, right);
        nodes.push(*newNode);
    }

    // The last node is the root of the Huffman tree
    root = new Node(nodes.top());
    nodes.pop();

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    cout << "Huffman Tree Construction Elapsed Time: " << duration.count() << " microseconds" << endl;

    map<char, string> huffmanCodes;
    calculateHuffmanCodes(root, "", huffmanCodes);

    // Print the Huffman codes
    cout << "Huffman Codes for characters:\n";
    for (const auto& kv : huffmanCodes) {
        cout << kv.first << ": " << kv.second << endl;
    }

    // Calculate space used for the Huffman codes
    double spaceUsed = 0;
    for (const auto& kv : huffmanCodes) {
        spaceUsed += kv.second.length() * freq[find(chars.begin(), chars.end(), kv.first) - chars.begin()];
    }
    spaceUsed = ceil(spaceUsed / 8); // Convert bits to bytes

    cout << "Estimated Space Used for Huffman Codes: " << spaceUsed << " bytes" << endl;

    // Clean up the dynamically allocated nodes
    deleteHuffmanTree(root); // Pass the root to delete the entire tree

    return 0;
}
