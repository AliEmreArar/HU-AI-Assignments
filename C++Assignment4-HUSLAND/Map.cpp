#include "Map.h"

#include <algorithm>
#include <stack>

#include "RealmShaper.h"
#include "RealmShapers.h"
Map::Map()
{
    this->root = nullptr;
}
Map::~Map()
{
    deleteNodes(root);

}
void Map::deleteNodes(MapNode* node) {
    if (!node)
        return;

    deleteNodes(node->left);
    node->left = nullptr;

    deleteNodes(node->right);
    node->right = nullptr;

    delete node;
}

void Map::initializeMap(std::vector<Isle *> isles)
{
    for (Isle *isle : isles) {
        insert(isle);
    }

    populateWithItems();
}

MapNode *Map::rotateRight(MapNode *current)
{
    if (!current || !current->left)
    {
        std::cerr << "[Right Rotation] Called on invalid node!" << std::endl;
        return current;
    }
    MapNode *newRoot = current->left;
    current->left = newRoot->right;
    newRoot->right = current;

    current->height = std::max(height(current->left), height(current->right)) + 1;
    newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

MapNode *Map::rotateLeft(MapNode *current)
{
    if (!current || !current->right)
    {
        std::cerr << "[Left Rotation] Called on invalid node!" << std::endl;
        return current;
    }
    MapNode *newRoot = current->right;
    current->right = newRoot->left;
    newRoot->left = current;

    current->height = std::max(height(current->left), height(current->right)) + 1;
    newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

int Map::calculateMinMapDepthAccess(int playerDepth, int totalShaperTreeHeight, int totalMapDepth)
{
    return (int)totalMapDepth * ((double)playerDepth / totalShaperTreeHeight);
}

int Map::height(MapNode *node)
{
    if ( node == nullptr ) {
        return 0;
    }
    return node->height;
}
int Map::getHeight(Isle *isle)
{
    MapNode *node = findNode(*isle);

    return node->height;
}

MapNode *Map::insert(MapNode *node, Isle *isle)
{
    if (!node)
        return new MapNode(isle);

    if (*isle < *node->isle)
        node->left = insert(node->left, isle);
    else if (*isle > *node->isle)
        node->right = insert(node->right, isle);
    else
        return node;

    node->height = std::max(height(node->left), height(node->right)) + 1;

    int balance = height(node->left) - height(node->right);

    if(balance > 1 || balance < -1) {
        balancedNumber++;
        lastBalance = true;
    }

    if (balance > 1 && *isle < *node->left->isle)
        return rotateRight(node);

    if (balance < -1 && *isle > *node->right->isle)
        return rotateLeft(node);

    if (balance > 1 && *isle > *node->left->isle)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && *isle < *node->right->isle)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void Map::insert(Isle *isle)
{
    root = insert((root), isle);

    // you might need to insert some checks / functions here depending on your implementation
}

MapNode *Map::remove(MapNode *node, Isle *isle)
{
    if (!node)
    {
        std::cout << "[Remove] Tree is Empty" << std::endl;
        return node;
    }

    if (*isle < *node->isle)
        node->left = remove(node->left, isle);
    else if (*isle > *node->isle)
        node->right = remove(node->right, isle);
    else
    {
        if (!node->left || !node->right)
        {
            MapNode *temp = node->left ? node->left : node->right;

            if (!temp)   // node has not children
            {
                temp = node;
                node = nullptr;
            }
            else // node has one child
            {
                node->isle = temp->isle;
                node->left = temp->left;
                node->right = temp->right;
                node->height = temp->height;
            }
            delete temp;
        }
        else  // node has two children
        {
            MapNode *temp = node->right;
            while (temp->left)
                temp = temp->left;

            node->isle = temp->isle;
            node->right = remove(node->right, temp->isle);
        }
    }

    if (!node)
        return node;

    node->height = std::max(height(node->left), height(node->right)) + 1;

    int balance = height(node->left) - height(node->right);

    if(balance > 1 || balance < -1) {
        balancedNumber++;
        lastBalance = true;
    }

    if (balance > 1 && height(node->left->left) >= height(node->left->right))
        return rotateRight(node);

    if (balance > 1 && height(node->left->left) < height(node->left->right))
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && height(node->right->right) >= height(node->right->left))
        return rotateLeft(node);

    if (balance < -1 && height(node->right->right) < height(node->right->left))
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void Map::remove(Isle *isle)
{
    root = remove(root, isle);
    if (root == nullptr)
        std::cout << "[Remove] Tree is now empty." << std::endl;
    // you might need to insert some checks / functions here depending on your implementation

}

void Map::preOrderItemDrop(MapNode *current, int &count)
{
    if (!current)
        return;

    if (++count % 5 == 0)
    {
        current->isle->setItem(EINSTEINIUM);
        std::cout << "[Item Drop] EINSTEINIUM dropped on Isle: " << current->isle->getName() << std::endl;
    }

    preOrderItemDrop(current->left, count);
    preOrderItemDrop(current->right, count);}

// to Display the values by Post Order Method .. left - right - node
void Map::postOrderItemDrop(MapNode *current, int &count)
{
    if (!current)
        return;

    postOrderItemDrop(current->left, count);
    postOrderItemDrop(current->right, count);

    if (++count % 3 == 0)
    {
        current->isle->setItem(GOLDIUM);
        std::cout << "[Item Drop] GOLDIUM dropped on Isle: " << current->isle->getName() << std::endl;
    }
}

MapNode *Map::findFirstEmptyIsle(MapNode *node)
{
    if (!node)
        return nullptr;

    if (node->isle->getItem() == EMPTY)
        return node;

    MapNode *leftResult = findFirstEmptyIsle(node->left);
    if (leftResult)
        return leftResult;

    return findFirstEmptyIsle(node->right);
}

void Map::dropItemBFS()
{
    if (!root) {
      return;
    }

    MapNode *current = findFirstEmptyIsle(root);
    if (current == nullptr) {
        std::cout << "[BFS Drop] No eligible Isle found for AMAZONITE drop." << std::endl;
    }
    else {
        current->isle->setItem(AMAZONITE);
        std::cout << "[BFS Drop] AMAZONITE dropped on Isle: " << current->isle->getName() << std::endl;
    }
}

void Map::displayMap()
{
    std::cout << "[World Map]" << std::endl;
    display(root, 0, 0);
}

int Map::getDepth(MapNode *node)
{
    if (!node || !root)
        return -1;

    int level = 0;
    MapNode *current = root;

    while (current)
    {
        if (current == node)
            return level;

        if (*node->isle < *current->isle)
            current = current->left;
        else
            current = current->right;

        level++;
    }

    return -1;
}

// Function to calculate the depth of a specific node in the AVL tree
int Map::getIsleDepth(Isle *isle)
{
    if (!root || !isle){
        return -1;
    }

    MapNode *current = root;
    int level = 0;

    while (current)
    {
        if (current->isle == isle)
            return level;

        if (*isle < *current->isle)
            current = current->left;
        else
            current = current->right;

        level++;
    }

    return -1;
}

int Map::getDepth()
{
    if (!root)
        return 0;

    return root->height - 1;
}

void Map::populateWithItems()
{
    int postOrderCount = 0;
    postOrderItemDrop(root, postOrderCount);

    int preOrderCount = 0;
    preOrderItemDrop(root, preOrderCount);


}

Isle *Map::findIsle(Isle isle)
{
    MapNode *current = root;

    while (current)
    {
        if (*current->isle == isle) {
            return current->isle;
        }
        if (isle < *current->isle)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return nullptr;
}

Isle *Map::findIsle(std::string name)
{
    MapNode *current = root;

    while (current)
    {
        if (current->isle->getName() == name)
            return current->isle;

        if (name < current->isle->getName())
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return nullptr;
}

MapNode *Map::findNode(Isle isle)
{
    MapNode *current = root;

    while (current)
    {
        if (*current->isle == isle)
            return current;

        if (isle < *current->isle)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return nullptr;
}

MapNode *Map::findNode(std::string name)
{
    MapNode *current = root;

    while (current)
    {
        if (current->isle->getName() == name)
            return current;

        if (name < current->isle->getName())
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return nullptr;
}

void Map::display(MapNode *current, int depth, int state)
{
    // SOURCE:

    if (current->left)
        display(current->left, depth + 1, 1);

    for (int i = 0; i < depth; i++)
        printf("     ");

    if (state == 1) // left
        printf("   ┌───");
    else if (state == 2) // right
        printf("   └───");

    std::cout << "[" << *current->isle << "] - (" << current->height << ")\n"
              << std::endl;

    if (current->right)
        display(current->right, depth + 1, 2);
}

void Map::writeToFile(const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    if (!root)
    {
        outFile << "Tree is empty.\n";
        return;
    }

    std::queue<MapNode *> q;
    q.push(root);
    bool hasNull = false;

    while (!q.empty())
    {
        size_t levelSize = q.size();
        for (size_t i = 0; i < levelSize; ++i)
        {
            MapNode *current = q.front();
            q.pop();

            if (current)
            {
                outFile << current->isle->getName() << " ";
                q.push(current->left);
                q.push(current->right);
            }
            else
            {
                outFile << "NULL ";
                hasNull = true;
            }
        }
        if (hasNull) {
            outFile << "\n";
            break;
        }
        outFile << "\n";
    }

    outFile.close();
    std::cout << "[Output] Tree has been written to " << filename << " in level order." << std::endl;
}


void Map::writeIslesToFile(const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    MapNode *current = root;
    std::stack<MapNode *> stack;

    while (!stack.empty() || current != nullptr)
    {
        while (current != nullptr)
        {
            stack.push(current);
            current = current->left;
        }

        current = stack.top();
        stack.pop();

        outFile << current->isle->getName() << "\n";

        current = current->right;
    }

    outFile.close();
    std::cout << "[Output] Isles have been written to " << filename << " using Inorder Traversal." << std::endl;
}
