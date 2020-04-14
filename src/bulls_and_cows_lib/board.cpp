
#include "board.hpp"
#include "game_options.hpp"
#include "input.hpp"
#include "random.hpp"
#include <map>

namespace bulls_and_cows {

    
Board create_board(const GameOptions& game_options)
{
    Board newCreated{};
    newCreated.secret_code.value.resize(game_options.number_of_characters_per_code, 'O');
    for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
    {
        newCreated.secret_code.value[i] =
            generate_random_character(game_options.minimum_allowed_character, game_options.maximum_allowed_character);
    }

    return newCreated;
}
bool validate_attempt(const GameOptions& game_options, const Code& attempt)
{
    if (game_options.number_of_characters_per_code == attempt.value.size())
    {
        for (const char& i: attempt.value)
        {
            if ((i < game_options.minimum_allowed_character) | (i > game_options.maximum_allowed_character))
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}
bool is_end_of_game(const GameOptions& game_options, const Board& board)
{
    if (game_options.max_number_of_attempts == board.attempts_and_feedbacks.size())
    {
        return true;
    }
    return false;
}


bool is_win(const GameOptions& game_options, const Board& board)
{
    if ((board.attempts_and_feedbacks.empty()))
        return false;

    if (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value)
    {
        return true;
    }
    // TODO: define the body of the functions declared in board.cpp

} // namespace bulls_and_cows