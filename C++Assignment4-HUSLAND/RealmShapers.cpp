#include "RealmShapers.h"
#include <cmath>
#include <algorithm>
#include <queue>

ShaperTree::ShaperTree()
{
}

ShaperTree::~ShaperTree()
{
    for (auto shaper : realmShapers)
    {
        delete shaper;
    }
    realmShapers.clear();
}

void ShaperTree::initializeTree(std::vector<RealmShaper *> shapers)
{
    realmShapers = shapers;
}

int ShaperTree::getSize()
{
    return realmShapers.size();
}

std::vector<RealmShaper *> ShaperTree::getTree()
{
    return realmShapers;
}

bool ShaperTree::isValidIndex(int index)
{
    bool isValid = false;

    if (index >= 0 && index < static_cast<int>(realmShapers.size())) {
        isValid = true;
    }

    return isValid;
}

void ShaperTree::insert(RealmShaper *shaper)
{
    realmShapers.push_back(shaper);
}

int ShaperTree::remove(RealmShaper *shaper)
{
    int index = findIndex(shaper);
    if (index == -1)
        return -1;

    if(isValidIndex(index)) {
        delete realmShapers[index];
        realmShapers.erase(realmShapers.begin() + index);
    }

    return index;
}

int ShaperTree::findIndex(RealmShaper *shaper)
{
    for (size_t i = 0; i < realmShapers.size(); ++i)
    {
        if (*realmShapers[i] == *shaper)
            return i;
    }
    return -1;
}

int ShaperTree::getDepth(RealmShaper *shaper)
{
    int index = findIndex(shaper);
    if (index == -1) {
        return -1;
    }

    return std::floor(std::log2(index + 1));
}

int ShaperTree::getDepth()
{
    if (realmShapers.empty()) {
        return 0;
    }

    return std::floor(std::log2(realmShapers.size()));
}

RealmShaper ShaperTree::duel(RealmShaper *challenger, bool result)
{
    RealmShaper *opponent = getParent(challenger);

    if (!opponent)
    {
        std::cerr << "[Duel] No opponent found for " << challenger->getName() << std::endl;
        return *challenger;
    }

    if (result)
    {
        challenger->gainHonour();
        opponent->loseHonour();

        std::cout << "[Duel] " << challenger->getName() << " won the duel" << std::endl;
        std::cout << "[Honour] " << "New honour points: ";
        std::cout << challenger->getName() << "-" << challenger->getHonour() << " ";
        std::cout << opponent->getName() << "-" << opponent->getHonour() << std::endl;

        replace(challenger, opponent);

        if (opponent->getHonour() <= 0)
        {
            std::cout << "[Duel] " << opponent->getName() << " lost all honour, delete" << std::endl;
            remove(opponent);
        }

        return *challenger;
    }

    challenger->loseHonour();
    opponent->gainHonour();
    std::cout << "[Duel] " << challenger->getName() << " lost the duel" << std::endl;
    std::cout << "[Honour] " << "New honour points: ";
    std::cout << challenger->getName() << "-" << challenger->getHonour() << " ";
    std::cout << opponent->getName() << "-" << opponent->getHonour() << std::endl;

    if (challenger->getHonour() <= 0)
    {
        std::cout << "[Duel] " << challenger->getName() << " lost all honour, delete" << std::endl;
        remove(challenger);
    }
    return *opponent;
}

RealmShaper *ShaperTree::getParent(RealmShaper *shaper)
{
    RealmShaper *parent = nullptr;

    int index = findIndex(shaper);
    if (index <= 0) {
        return nullptr;
    }
    parent = realmShapers[(index - 1) / 2];

    return parent;
}

void ShaperTree::replace(RealmShaper *player_low, RealmShaper *player_high) {
    int lowIndex = findIndex(player_low);
    int highIndex = findIndex(player_high);

    if (lowIndex != -1 && highIndex != -1){
    std::swap(realmShapers[lowIndex], realmShapers[highIndex]);
    }
}

RealmShaper *ShaperTree::findPlayer(RealmShaper shaper)
{
    RealmShaper *foundShaper = nullptr;

    for (auto player : realmShapers)
    {
        if (*player == shaper) {
            foundShaper = player;
        }
    }

    return foundShaper;
}

// Find shaper by name
RealmShaper *ShaperTree::findPlayer(std::string name)
{
    RealmShaper *foundShaper = nullptr;

    for (auto player : realmShapers)
    {
        if (player->getName() == name)
            foundShaper = player;
    }

    return foundShaper;
}

std::vector<std::string> ShaperTree::inOrderTraversal(int index)
{
    std::vector<std::string> result = {};

    if (!isValidIndex(index))
        return result;

    int left = 2 * index + 1;
    int right = 2 * index + 2;

    auto leftResult = inOrderTraversal(left);
    result.insert(result.end(), leftResult.begin(), leftResult.end());

    result.push_back(realmShapers[index]->getName());

    auto rightResult = inOrderTraversal(right);
    result.insert(result.end(), rightResult.begin(), rightResult.end());

    return result;
}

std::vector<std::string> ShaperTree::preOrderTraversal(int index)
{
    std::vector<std::string> result = {};

     if (!isValidIndex(index))
        return result;

    result.push_back(realmShapers[index]->getName());

    int left = 2 * index + 1;
    int right = 2 * index + 2;

    auto leftResult = preOrderTraversal(left);
    result.insert(result.end(), leftResult.begin(), leftResult.end());

    auto rightResult = preOrderTraversal(right);
    result.insert(result.end(), rightResult.begin(), rightResult.end());

    return result;
}


std::vector<std::string> ShaperTree::postOrderTraversal(int index)
{
    std::vector<std::string> result = {};

     if (!isValidIndex(index))
        return result;

    int left = 2 * index + 1;
    int right = 2 * index + 2;

    auto leftResult = postOrderTraversal(left);
    result.insert(result.end(), leftResult.begin(), leftResult.end());

    auto rightResult = postOrderTraversal(right);
    result.insert(result.end(), rightResult.begin(), rightResult.end());

    result.push_back(realmShapers[index]->getName());

    return result;
}

void ShaperTree::preOrderTraversal(int index, std::ofstream &outFile)
{
    if (!isValidIndex(index))
        return;

    outFile << realmShapers[index]->getName() << std::endl;

    int left = 2 * index + 1;
    int right = 2 * index + 2;

    preOrderTraversal(left, outFile);
    preOrderTraversal(right, outFile);
}

void ShaperTree::breadthFirstTraversal(std::ofstream &outFile)
{
    if (realmShapers.empty())
        return;

    std::queue<int> q;
    q.push(0);

    while (!q.empty())
    {
        int index = q.front();
        q.pop();

        outFile << realmShapers[index]->getName() << '\n';

        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (isValidIndex(left))
            q.push(left);
        if (isValidIndex(right))
            q.push(right);
    }
    outFile << std::endl;
    outFile.close();
}

void ShaperTree::displayTree()
{
    std::cout << "[Shaper Tree]" << std::endl;
    printTree(0, 0, "");
}

// Helper function to print tree with indentation
void ShaperTree::printTree(int index, int level, const std::string &prefix)
{
    if (!isValidIndex(index))
        return;

    std::cout << prefix << (level > 0 ? "   └---- " : "") << *realmShapers[index] << std::endl;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (isValidIndex(left) || isValidIndex(right))
    {
        printTree(left, level + 1, prefix + (level > 0 ? "   │   " : "")); // ╎
        printTree(right, level + 1, prefix + (level > 0 ? "   │   " : ""));
    }
}

void ShaperTree::writeShapersToFile(const std::string &filename)
{

    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
    }

    breadthFirstTraversal(outFile);

    std::cout << "[Output] Shapers have been written to " << filename << " according to rankings." << std::endl;
}

void ShaperTree::writeToFile(const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    preOrderTraversal(0, outFile);

    outFile.close();
    std::cout << "[Output] Tree has been written to " << filename << " in pre-order." << std::endl;
}
