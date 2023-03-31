#include "WarHelpers.hpp"
#include "Deck.hpp"

#include <iostream>
#include <optional>

namespace War {

static constexpr std::string_view kSmallBanner{R"""(
  _      __         ______
 | | /| / /__ _____/ / / /
 | |/ |/ / _ `/ __/_/_/_/ 
 |__/|__/\_,_/_/ (_|_|_)  
                          
)"""};

PopResult Pop(std::deque<Card> &player_one, std::deque<Card> &player_two,
              std::vector<Card> &pot, Visibility vis) {
  if (player_one.empty()) {
    throw RoundResult::kPlayerTwo; // Player two wins
  }
  if (player_two.empty()) {
    throw RoundResult::kPlayerOne; // Player one wins
  }

  const auto card_one = player_one.back();
  const auto card_two = player_two.back();

  player_one.pop_back();
  player_two.pop_back();

  if (vis == Visibility::kShow) {
    std::cout << "\tPlayer Two - " << ToString(card_two) << '\n';
    std::cout << "\tPlayer One - " << ToString(card_one) << '\n';
  }

  pot.push_back(card_one);
  pot.push_back(card_two);

  if (card_one > card_two) {
    return PopResult::kPlayerOne;
  } else if (card_two > card_one) {
    return PopResult::kPlayerTwo;
  } else {
    return PopResult::kTie;
  }
}

RoundResult PlayRound(std::deque<Card> &player_one,
                      std::deque<Card> &player_two, std::vector<Card> &pot,
                      Visibility vis) {
  const auto winner = Pop(player_one, player_two, pot, vis);
  const auto player = winner == PopResult::kPlayerOne ? "One" : "Two";
  switch (winner) {
  case PopResult::kPlayerOne: // Fall-through
  case PopResult::kPlayerTwo:
    if (vis == Visibility::kShow) {
      std::cout << "Player " << player << " wins the hand." << '\n';
    }
    return winner == PopResult::kPlayerOne ? RoundResult::kPlayerOne
                                           : RoundResult::kPlayerTwo;
  case PopResult::kTie:
    if (vis == Visibility::kShow) {
      std::cout << kSmallBanner;
      std::cin.ignore();
    }

    Pop(player_one, player_two, pot, Visibility::kHide);
    if (vis == Visibility::kShow) {
      std::cout << "ONE\n";
      std::cin.ignore();
    }

    Pop(player_one, player_two, pot, Visibility::kHide);
    if (vis == Visibility::kShow) {
      std::cout << "TWO\n";
      std::cin.ignore();
    }

    Pop(player_one, player_two, pot, Visibility::kHide);
    if (vis == Visibility::kShow) {
      std::cout << "THREE\n";
      std::cin.ignore();
    }

    return PlayRound(player_one, player_two, pot, vis);
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

void PlayWar(Visibility vis) {
  std::deque<Card> player_one;
  std::deque<Card> player_two;
  Deal(player_one, player_two);
  std::vector<Card> pot;
  pot.reserve(kDeckSize);
  std::optional<RoundResult> game_winner;
  size_t count{0u};
  try {
    while (!player_one.empty() || !player_two.empty()) {
      count++;
      if (vis == Visibility::kShow) {
        std::cout << "Round #" << count << '\n';
        std::cout << "Player One: " << player_one.size() << '\n';
        std::cout << "Player Two: " << player_two.size() << '\n';
      }
      game_winner = PlayRound(player_one, player_two, pot, vis);
      Win(game_winner == RoundResult::kPlayerOne ? player_one : player_two,
          pot);
      if (vis == Visibility::kShow) {
        std::cin.ignore();
      }
    }
  } catch (RoundResult result) {
    game_winner = result;
  }
  const auto player{game_winner == RoundResult::kPlayerOne ? "One" : "Two"};
  std::cout << "Game played for " << count << " rounds.\n";
  std::cout << "Player " << player << " wins the game!\n";
}

} // namespace War