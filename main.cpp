#include "Card.hpp"
#include "Deck.hpp"
#include "WarHelpers.hpp"
#include <deque>
#include <iostream>
#include <vector>

using namespace War;

int main() {
  try {
    std::cout << kBannerText;
    std::cout << "Press any key to begin\n";
    std::cin.ignore();
    PlayWar();
  } catch (const std::exception &e) {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}