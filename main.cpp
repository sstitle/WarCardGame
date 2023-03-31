#include "Card.hpp"
#include "Deck.hpp"
#include "WarHelpers.hpp"

#include <iostream>

using namespace War;

int main() {
  try {
    std::cout << kBannerText;
    const bool wait{UserConfirmation("Do you want to show information and wait "
                                     "for user input at each step?")};
    const Visibility visibility{wait ? Visibility::kShow : Visibility::kHide};
    std::cout << "Press any key to begin\n";
    std::cin.ignore();
    PlayWar(visibility);
  } catch (const std::exception &e) {
    std::cout << "Caught exception: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}