#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>

using namespace std;

class trie_node
{
public:
    unordered_map<char, shared_ptr<trie_node>> children;
    string word;
};

class trie
{
    void insert(const string &word);

public:
    shared_ptr<trie_node> root{nullptr};
    trie(vector<string> words);
};

trie::trie(vector<string> words)
{
    root = make_shared<trie_node>();
    for (const auto &word : words)
        insert(word);
}

void trie::insert(const string &word)
{
    auto current = root;
    for (const auto c : word)
    {
        if (current->children.count(c) > 0)
        {
            current = current->children[c];
        }
        else
        {
            auto temp = make_shared<trie_node>();
            current->children.insert({c, temp});
            current = temp;
        }
    }

    current->word = word;
}

vector<pair<int, int>> getNeighbours(const int row, const int col, const int height, const int width)
{
    vector<pair<int, int>> neighbours;

    for (int rIdx = row - 1; rIdx < row + 2 and rIdx < height; rIdx++)
    {
        if (rIdx < 0)
            continue;

        for (int cIdx = col - 1; cIdx < col + 2 and cIdx < width; cIdx++)
        {
            if (cIdx < 0 or (rIdx == row and cIdx == col))
                continue;

            neighbours.push_back({rIdx, cIdx});
        }
    }

    return neighbours;
}

vector<string> explore(const int row, const int col, const vector<vector<char>> &board, vector<vector<bool>> &visited, const shared_ptr<trie_node> &trie);

vector<string> boggleBoard(vector<vector<char>> board, vector<string> words)
{
    const int width = board[0].size();
    const int height = board.size();
    trie multiWordSearch(words);
    vector<vector<bool>> visited(height, vector<bool>(width, false));
    unordered_set<string> wordsFoundOnBoard;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            const auto wordsFound = explore(row, col, board, visited, multiWordSearch.root);
            wordsFoundOnBoard.insert(cbegin(wordsFound), cend(wordsFound));
        }
    }
    return vector<string>(cbegin(wordsFoundOnBoard), cend(wordsFoundOnBoard));
}

vector<string> explore(const int row, const int col, const vector<vector<char>> &board, vector<vector<bool>> &visited, const shared_ptr<trie_node> &trie)
{
    if (visited[row][col])
        return {};

    const auto c = board[row][col];
    if (trie->children.count(c) == 0)
        return {};

    const int width = board[0].size();
    const int height = board.size();
    unordered_set<string> wordsFound;
    visited[row][col] = true;

    const auto currentTrie = trie->children.at(c);
    if (currentTrie->word != "")
        wordsFound.insert(currentTrie->word);

    const auto neighbours = getNeighbours(row, col, height, width);
    for (const auto &[r, c] : neighbours)
    {
        const auto matchFound = explore(r, c, board, visited, currentTrie);
        for (const auto &w : matchFound)
            wordsFound.insert(w);
    }

    visited[row][col] = false;
    return vector<string>(cbegin(wordsFound), cend(wordsFound));
}

int main()
{
    const auto result = boggleBoard(
        {{'t', 'h', 'i', 's', 'i', 's', 'a'},
         {'s', 'i', 'm', 'p', 'l', 'e', 'x'},
         {'b', 'x', 'x', 'x', 'x', 'e', 'b'},
         {'x', 'o', 'g', 'g', 'l', 'x', 'o'},
         {'x', 'x', 'x', 'D', 'T', 'r', 'a'},
         {'R', 'E', 'P', 'E', 'A', 'd', 'x'},
         {'x', 'x', 'x', 'x', 'x', 'x', 'x'},
         {'N', 'O', 'T', 'R', 'E', '-', 'P'},
         {'x', 'x', 'D', 'E', 'T', 'A', 'E'}},
        {"this", "is", "not", "a", "simple", "boggle", "board", "test", "REPEATED", "NOTRE-PEATED"});
    return 0;
}