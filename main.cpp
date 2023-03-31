#include <algorithm>
#include <array>
#include <chrono>
#include <deque>
#include <iostream>
#include <numeric>
#include <random>
#include <string>

const std::string kBannerText{R"""(
  _____                  ____        _____   
 |\    \   _____    ____|\   \   ___|\    \  
 | |    | /    /|  /    /\    \ |    |\    \ 
 \/     / |    || |    |  |    ||    | |    |
 /     /_  \   \/ |    |__|    ||    |/____/ 
|     // \  \   \ |    .--.    ||    |\    \ 
|    |/   \ |    ||    |  |    ||    | |    |
|\ ___/\   \|   /||____|  |____||____| |____|
| |   | \______/ ||    |  |    ||    | |    |
 \|___|/\ |    | ||____|  |____||____| |____|
    \(   \|____|/   \(      )/    \(     )/  
     '      )/       '      '      '     '   
            '                                

)"""};

enum class Suit { kClub, kSpade, kHeart, kDiamond, kMax };
enum class Rank {
  kAce,
  kTwo,
  kThree,
  kFour,
  kFive,
  kSix,
  kSeven,
  kEight,
  kNine,
  kTen,
  kJack,
  kQueen,
  kKing,
  kMax
};

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

class Card {
public:
  Card() noexcept = default;
  Card(Suit suit, Rank rank) : suit_(suit), rank_(rank) {}
  Suit GetSuit() const { return suit_; }
  Rank GetRank() const { return rank_; }
  bool operator==(const Card &other) const {
    return this->rank_ == other.rank_;
  }
  bool operator<(const Card &other) const { return this->rank_ < other.rank_; }
  bool operator>(const Card &other) const { return this->rank_ > other.rank_; }

  Card &operator++() {
    if (rank_ == Rank::kKing) {
      suit_ = static_cast<Suit>(static_cast<size_t>(suit_) + 1);
      rank_ = Rank::kAce;
    } else {
      rank_ = static_cast<Rank>(static_cast<size_t>(rank_) + 1);
    }
    return *this;
  }

private:
  Suit suit_{Suit::kMax};
  Rank rank_{Rank::kMax};
};

static constexpr size_t kDeckSize{static_cast<size_t>(Suit::kMax) *
                                  static_cast<size_t>(Rank::kMax)};

using Deck = std::array<Card, kDeckSize>;

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

enum class Result { kPlayerOne, kPlayerTwo, kTie};

Result Pop(std::deque<Card>& player_one, std::deque<Card>& player_two, std::vector<Card>& pot, bool print = true) {
  const auto card_one = player_one.back();
  const auto card_two = player_two.back();

  player_one.pop_back();
  player_two.pop_back();

  if (print) {
    std::cout << "\tPlayer Two - " << ToString(card_two) << '\n';
    std::cout << "\tPlayer One - " << ToString(card_one) << '\n';
  }

  pot.push_back(card_one);
  pot.push_back(card_two);

  if (card_one > card_two) {
    return Result::kPlayerOne;
  } else if (card_two > card_one) {
    return Result::kPlayerTwo;
  } else {
    return Result::kTie;
  }
}

void PlayRound(std::deque<Card>& player_one, std::deque<Card>& player_two, std::vector<Card>& pot) {
  const auto winner = Pop(player_one, player_two, pot, true);
  switch (winner) {
  case Result::kPlayerOne:
    std::cout << "Player One wins the hand." << '\n';
    break;
  case Result::kPlayerTwo:
    std::cout << "Player Two wins the hand." << '\n';
  case Result::kTie:
    std::cout << kBannerText;
    std::cin.ignore();
    
    Pop(player_one, player_two, pot, false);
    std::cout << "ONE\n";
    std::cin.ignore();

    Pop(player_one, player_two, pot, false);
    std::cout << "TWO\n";
    std::cin.ignore();

    Pop(player_one, player_two, pot, false);
    std::cout << "THREE\n";
    std::cin.ignore();

    PlayRound(player_one, player_two, pot);
  }
}

int main() {
  std::cout << kBannerText;
  std::cout << "Press any key to begin\n";
  std::cin.ignore();

  const Deck deck{MakeShuffledDeck()};

  std::deque<Card> player_one;
  std::deque<Card> player_two;

  // Deal the cards
  for (size_t i = 0; i < deck.size(); i++) {
    if (i % 2 == 0) {
      player_one.push_back(deck.at(i));
    } else {
      player_two.push_back(deck.at(i));
    }
  }

  std::vector<Card> pot;
  pot.reserve(kDeckSize);

  size_t count{0u};
  while (!player_one.empty() || !player_two.empty()) {
    std::cout << "Round #" << ++count << '\n';
    std::cout << "Player One: " << player_one.size() << '\n';
    std::cout << "Player Two: " << player_two.size() << '\n';
    PlayRound(player_one, player_two, pot);
    std::cin.ignore();
  }
  return EXIT_SUCCESS;
}