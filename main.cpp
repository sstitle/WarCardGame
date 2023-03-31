#include "Card.hpp"
#include "Deck.hpp"
#include "WarHelpers.hpp"
#include <iostream>
#include <cctype>

using namespace War;

bool UserConfirmation(const std::string &msg) {
  std::cout << msg << " [y/n]: ";
  char input{'?'};
  std::cin >> input;
  return std::tolower(input) == 'y';
}

int main() {
  try {
    std::cout << kBannerText;
    const bool wait_for_user{UserConfirmation("Do you want to wait for user input at each step?")};
    const Visibility visibility{wait_for_user ? Visibility::kShow : Visibility::kHide};
    std::cout << "Press any key to begin\n";
    std::cin.ignore();
    PlayWar(visibility);
  } catch (const std::exception &e) {
    std::cout << "Caught exception: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}