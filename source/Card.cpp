#include "Card.hpp"

namespace War {

std::string ToString(Suit suit) {
  switch (suit) {
  case Suit::kClub:
    return "Club";
  case Suit::kDiamond:
    return "Diamond";
  case Suit::kHeart:
    return "Heart";
  case Suit::kSpade:
    return "Spade";
  default:
    throw std::invalid_argument("Invalid suit value");
  }
}

std::string ToString(Rank rank) {
  switch (rank) {
  case Rank::kAce:
    return "Ace";
  case Rank::kTwo:
    return "Two";
  case Rank::kThree:
    return "Three";
  case Rank::kFour:
    return "Four";
  case Rank::kFive:
    return "Five";
  case Rank::kSix:
    return "Six";
  case Rank::kSeven:
    return "Seven";
  case Rank::kEight:
    return "Eight";
  case Rank::kNine:
    return "Nine";
  case Rank::kTen:
    return "Ten";
  case Rank::kJack:
    return "Jack";
  case Rank::kQueen:
    return "Queen";
  case Rank::kKing:
    return "King";
  case Rank::kMax:
  // Fall-through
  default:
    throw std::invalid_argument("Invalid rank value");
  }
}

Card::Card(Suit suit, Rank rank) : suit_(suit), rank_(rank) {}

Suit Card::GetSuit() const { return suit_; }

Rank Card::GetRank() const { return rank_; }

bool Card::operator==(const Card &other) const {
  return this->rank_ == other.rank_;
}

bool Card::operator<(const Card &other) const {
  return this->rank_ < other.rank_;
}

bool Card::operator>(const Card &other) const {
  return this->rank_ > other.rank_;
}

Card &Card::operator++() {
  static constexpr Rank one_less_than_max =
      static_cast<Rank>(static_cast<size_t>(Rank::kMax) - 1);
  if (rank_ == one_less_than_max) {
    suit_ = static_cast<Suit>(static_cast<size_t>(suit_) + 1);
    rank_ = Rank::kTwo;
  } else {
    rank_ = static_cast<Rank>(static_cast<size_t>(rank_) + 1);
  }
  return *this;
}

std::string ToString(const Card &card) {
  return ToString(card.GetRank()) + " of " + ToString(card.GetSuit()) + "s";
}

} // namespace War