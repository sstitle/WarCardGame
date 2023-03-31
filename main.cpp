#include <algorithm>
#include <array>
#include <chrono>
#include <deque>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include "Card.hpp"

using namespace War;

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

enum class Result { kPlayerOne, kPlayerTwo, kTie };

Result Pop(std::deque<Card> &player_one, std::deque<Card> &player_two,
           std::vector<Card> &pot, bool print = true) {
  const auto card_one = player_one.back();
  if (player_one.empty()) {
    throw Result::kPlayerTwo; // Player two wins
  }

  const auto card_two = player_two.back();
  if (player_two.empty()) {
    throw Result::kPlayerOne; // Player one wins
  }

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

Result PlayRound(std::deque<Card> &player_one, std::deque<Card> &player_two,
                 std::vector<Card> &pot) {
  const auto winner = Pop(player_one, player_two, pot, true);
  switch (winner) {
  case Result::kPlayerOne:
    std::cout << "Player One wins the hand." << '\n';
    return Result::kPlayerOne;
  case Result::kPlayerTwo:
    std::cout << "Player Two wins the hand." << '\n';
    return Result::kPlayerTwo;
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

    return PlayRound(player_one, player_two, pot);
  }
}

void Win(std::deque<Card> &winner, std::vector<Card> &pot) {
  for (const auto &card : pot) {
    winner.push_front(card);
  }
  pot.clear();
}

void Deal(std::deque<Card> &player_one, std::deque<Card> &player_two) {
  const Deck deck{MakeShuffledDeck()};
  for (size_t i = 0; i < deck.size(); i++) {
    if (i % 2 == 0) {
      player_one.push_back(deck.at(i));
    } else {
      player_two.push_back(deck.at(i));
    }
  }
}

void PlayWar() {
  std::cout << kBannerText;
  std::cout << "Press any key to begin\n";
  std::cin.ignore();

  std::deque<Card> player_one;
  std::deque<Card> player_two;
  Deal(player_one, player_two);

  std::vector<Card> pot;
  pot.reserve(kDeckSize);


  Result winner{Result::kTie};
  size_t count{0u};
  try {
    while (!player_one.empty() || !player_two.empty()) {
      std::cout << "Round #" << ++count << '\n';
      std::cout << "Player One: " << player_one.size() << '\n';
      std::cout << "Player Two: " << player_two.size() << '\n';
      winner = PlayRound(player_one, player_two, pot);
      switch (winner) {
      case Result::kPlayerOne:
        Win(player_one, pot);
        break;
      case Result::kPlayerTwo:
        Win(player_two, pot);
        break;
      default:
        throw std::runtime_error("Developer error");
      }
      std::cin.ignore();
    }
  } catch (Result result) {
    winner = result;
  }

  switch (winner) {
    case Result::kPlayerOne:
      std::cout << "Player One wins the game!\n";
      break;
    case Result::kPlayerTwo:
      std::cout << "Player Two wins the game!\n";
      break;
    default:
      throw std::runtime_error("Developer error");
  }
}

int main() {
  try {
    PlayWar();
  } catch (const std::exception &e) {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}