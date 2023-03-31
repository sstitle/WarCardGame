#include "Deck.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <random>

namespace War {

std::string ToString(const Card &card) {
  return ToString(card.GetRank()) + " of " + ToString(card.GetSuit()) + "s";
}

Deck MakeDeck() {
  Deck deck;
  std::iota(deck.begin(), deck.end(), Card{Suit::kClub, Rank::kAce});
  return deck;
}

Deck MakeShuffledDeck() {
  Deck deck{MakeDeck()};
  const unsigned seed =
      std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
  return deck;
}

void PrintDeck(const Deck &deck) {
  for (const auto &card : deck) {
    std::cout << "\t" << ToString(card) << std::endl;
  }
}

} // namespace War