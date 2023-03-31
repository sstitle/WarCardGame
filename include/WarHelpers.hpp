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

enum class PopResult { kPlayerOne, kPlayerTwo, kTie };
enum class RoundResult { kPlayerOne, kPlayerTwo };
enum class Visibility { kShow, kHide };

PopResult Pop(std::deque<Card> &player_one, std::deque<Card> &player_two,
           std::vector<Card> &pot, Visibility vis);
RoundResult PlayRound(std::deque<Card> &player_one, std::deque<Card> &player_two,
                 std::vector<Card> &pot, Visibility vis);
void Win(std::deque<Card> &winner, std::vector<Card> &pot);
void Deal(std::deque<Card> &player_one, std::deque<Card> &player_two);

void PlayWar(Visibility vis);

} // namespace War