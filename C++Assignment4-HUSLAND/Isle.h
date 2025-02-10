#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

// Items their collectable energy points
enum Item
{
  EMPTY = 0,
  GOLDIUM = 250,
  EINSTEINIUM = 2000,
  AMAZONITE = 500000
};

class Isle
{
private:
  const std::string name;  // Name of the Isle
  const int capacity = 10; // If more realm shapers than this capacity gathers at this isle, it self-destructs and must be deleted from the map
  int shaperCount = 0;     // Number of realm shapers that exist in the Isle at the same time
  Item item = EMPTY;       // Possible item Isle holds

public:
  // Constructor decleration
  Isle(std::string name);

  // Getters-Setters
  const std::string &getName() const;
  Item getItem();
  void setItem(Item item);
  int getShaperCount();
  bool increaseShaperCount();
  bool decreaseShaperCount();

  // Overloaded operators
  bool operator==(const Isle &other) const;
  bool operator<(const Isle &other) const;
  bool operator>(const Isle &other) const;
  friend std::ostream &operator<<(std::ostream &os, const Isle &p);

  // Isle parser
  static std::vector<Isle *> readFromFile(const std::string &filename);
};

#endif