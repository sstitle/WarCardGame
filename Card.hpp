#include <string>

namespace War {
    
enum class Suit { kClub, kSpade, kHeart, kDiamond, kMax };
std::string ToString(Suit suit);

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
std::string ToString(Rank rank);

class Card {
public:
  Card() noexcept = default;
  Card(Suit suit, Rank rank);
  Suit GetSuit() const;
  Rank GetRank() const;
  bool operator==(const Card &other) const;
  bool operator<(const Card &other) const;
  bool operator>(const Card &other) const;
  Card &operator++();

private:
  Suit suit_{Suit::kMax};
  Rank rank_{Rank::kMax};
};

}