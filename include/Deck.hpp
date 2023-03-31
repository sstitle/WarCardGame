#pragma once
#include "Card.hpp"

#include <array>
#include <string>

namespace War {

static constexpr size_t kDeckSize{static_cast<size_t>(Suit::kMax) *
                                  static_cast<size_t>(Rank::kMax)};

using Deck = std::array<Card, kDeckSize>;

Deck MakeDeck();

Deck MakeShuffledDeck();

void PrintDeck(const Deck &deck);
} // namespace War