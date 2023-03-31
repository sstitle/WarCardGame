#pragma once
#include "Card.hpp"

#include <deque>
#include <string_view>
#include <vector>

namespace War {

static constexpr std::string_view kBannerText{R"""(
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

bool UserConfirmation(std::string_view msg);

enum class Visibility { kShow, kHide };

enum class PopResult { kPlayerOne, kPlayerTwo, kTie };
PopResult Pop(std::deque<Card> &player_one, std::deque<Card> &player_two,
              std::vector<Card> &pot, Visibility vis);

enum class RoundResult { kPlayerOne, kPlayerTwo };
RoundResult PlayRound(std::deque<Card> &player_one,
                      std::deque<Card> &player_two, std::vector<Card> &pot,
                      Visibility vis);

void Deal(std::deque<Card> &player_one, std::deque<Card> &player_two);
void Win(std::deque<Card> &winner, std::vector<Card> &pot);

void PlayWar(Visibility vis);

} // namespace War