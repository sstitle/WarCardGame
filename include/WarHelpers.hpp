#pragma once
#include "Card.hpp"
#include <deque>
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

enum class Result { kPlayerOne, kPlayerTwo, kTie };

Result Pop(std::deque<Card> &player_one, std::deque<Card> &player_two,
           std::vector<Card> &pot, bool print = true);
Result PlayRound(std::deque<Card> &player_one, std::deque<Card> &player_two,
                 std::vector<Card> &pot);
void Win(std::deque<Card> &winner, std::vector<Card> &pot);
void Deal(std::deque<Card> &player_one, std::deque<Card> &player_two);

void PlayWar();

} // namespace War