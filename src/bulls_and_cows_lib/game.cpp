
#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include <bulls_and_cows_lib/random.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <iomanip>
#include <string>
#include<istream>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <bulls_and_cows_lib\main_menu.cpp>
#include <thread>
#include <bulls_and_cows_lib\game_solver.cpp>



#define VERTICALE   205
#define HORIZONTALE 186
 
#define COIN_HAUT_DROIT     187
#define COIN_HAUT_GAUCHE    201
#define COIN_BAS_DROIT      188
#define COIN_BAS_GAUCHE     200
namespace bulls_and_cows {
    std::string secret_code = "";
    size_t taille_code = 5;
    bool contains_duplicates(std::string s)
    {
        std::sort(s.begin(), s.end());
        return std::adjacent_find(s.begin(), s.end()) != s.end();
    }
    /*
    void afficherTableau( unsigned int p_largeur,  unsigned int p_hauteur)
    {
        char tableau[p_largeur][p_hauteur];

        // Créations des bordures et du vide à l'intérieur
        for (unsigned int y = 0; y < p_hauteur; y++)
        {
            for (unsigned int x = 0; x < p_largeur; x++)
            {
                if (x == 0 || x == p_largeur - 1)
                {
                    tableau[x][y] = HORIZONTALE;
                }
                else if (y == 0 || y == p_hauteur - 1)
                {
                    tableau[x][y] = VERTICALE;
                }
                else
                {
                    tableau[x][y] = '0';
                }
            }
        }

        // Créations des coins
        tableau[0][0] = COIN_HAUT_GAUCHE;
        tableau[p_largeur - 1][0] =COIN_HAUT_DROIT;
        tableau[0][p_hauteur - 1] = COIN_BAS_GAUCHE;
        tableau[p_largeur - 1][p_hauteur - 1] = COIN_BAS_DROIT;

        // Finalement, on affiche tout le contenu du tableau
        for (unsigned int y = 0; y < p_hauteur; y++)
        {
            for (unsigned int x = 0; x < p_largeur; x++)
            {
                std::cout << tableau[x][y];
            }
            std::cout << "\n";
        }
    }*/

    void user_plays_against_computer(const GameOptions& game_options)
    {
        std::string acceptes = "abcdefghijklmnopqrstuvwyz";

        for (int i = 0; i < taille_code; i++)
        {

            secret_code += generate_random_character('a', 'k');
        } /*
        std::cout<<secret_code ;*/
        std::cout << "\n Oh no! The computer has generated a secret code. Can you guess it?\n";
        typedef std::string::size_type index;

        std::string guess;

        while (std::cout << "Your guess? ", std::getline(std::cin, guess))
        {

            if (guess.length() != taille_code || guess.find_first_not_of(acceptes) != std::string::npos ||
                contains_duplicates(guess))
            {
                std::cout << guess << " is not a valid guess!";
                continue;
            }

            unsigned int bulls = 0;
            unsigned int cows = 0;
            for (index i = 0; i != taille_code; ++i)
            {
                index pos = secret_code.find(guess[i]);
                if (pos == i)
                    ++bulls;
                else if (pos != std::string::npos)
                    ++cows;
            }
            std::cout << bulls << " bulls, " << cows << " cows.\n";
            if (bulls == taille_code || guess == secret_code)
            {
                std::cout << "Congratulations! You have won!\n";
                return;
            }
        }
    }

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        
            std::cout
                << "TODO:\n"
                   "    Create a board with a randomly generated secret code\n"
                   "    Generate the list of all the possible codes\n"
                   "    DO\n"
                   "       Display the board and the list of attempts so far\n"
                   "       Display the number of remaining possible codes so far\n"
                   "       Wait for 2 seconds\n"
                   "       Pick a random attempt among in the list of remaining possible codes\n"
                   "       Compare the computer's attempt with the secret code and deduce the number of bulls and "
                   "cows\n"
                   "       Add the computer's attempt to the list of attempts of the board\n"
                   "       Remove all the codes that are incompatible with the attempt's feedback from the list of "
                   "possible codes\n"
                   "    WHILE not end of game\n"
                   "    Display the board and the list of attempts so far\n"
                   "    Display a message telling if the computer won or lost\n";

            Board computergameboard = bulls_and_cows::create_board(game_options);
            std::vector<Code> all_possible{};

            all_possible = generate_possibilities(game_options);

            bulls_and_cows::display_board(std::cout, game_options, computergameboard);

            while (all_possible.size() > 0)
            {
                Code s = pick_random_attempt(all_possible);
                AttemptAndFeedback newcomputerattemp;
                newcomputerattemp.attempt = s;
                newcomputerattemp.feedback = bulls_and_cows::compare_attempt_with_secret_code(s, computergameboard.secret_code);

                computergameboard.attempts_and_feedbacks.push_back(newcomputerattemp);

                bulls_and_cows::display_board(std::cout, game_options, computergameboard);

                if (bulls_and_cows::is_win(game_options, computergameboard))
                {
                    std::cout << "Well done Computer\n";
                    return;
                }
                if (bulls_and_cows::is_end_of_game(game_options, computergameboard))
                {
                    std::cout << " Computer loose\n";
                    return;
                }

                remove_all_bad_codes(all_possible, game_options, newcomputerattemp);
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        
    }



void display_main_menu1(std::ostream& output_stream)
{
    output_stream << "Configuration of the main Options\n"
                     "0 - Back to the menu\n"
                     "1 - Modify number of character in the code\n"
                     "2 - Modify minimum allowed character\n"
                     "3 - Modify maximum allowed character\n"
                     "What is your choice ? ";
}
void modify_the_number_of_character()
{
    int N=0;
    std::cout << " How much character do you want\n";
    std::cin, N;
    for (int i = 0; i < N; i++)
    {
        
        secret_code += generate_random_character('a', 'k');
        
    }
    
} 

void configure_game_options(GameOptions& game_options)
{
    while (true)
    {
        std::cout << "\n#################################\n";
        display_main_menu1(std::cout);
        const auto user_choice = ask_main_menu_choice1(std::cin);
        switch (user_choice)
        {
        case MainMenuChoice1::BackToTheMainMenu:
            display_main_menu1(std::cout);
            
            return;
        case MainMenuChoice1::ModifyTheNumberOfCharacter:
            modify_the_number_of_character();
           
            break;
        case MainMenuChoice1::ModifyTheMinimumCharacter:
            computer_plays_against_computer(game_options);
            break;
        case MainMenuChoice1::ModifyTheMaximumCharacter:
            configure_game_options(game_options);
            break;
        case MainMenuChoice1::Error:
            std::cout << "\nYou did not enter a valid choice, please try again\n";
            break;
        }
        "       Treat the user's choice\n"
        "    UNTIL user's choice is to go back to main menu\n";
    }
}

void play_game()
{
    GameOptions game_options{};

    while (true)
    {
        std::cout << "\n#################################\n";
        display_main_menu(std::cout);

        const auto user_choice = ask_main_menu_choice(std::cin);
        switch (user_choice)
        {
        case MainMenuChoice::Quit:
            std::cout << "\nBye bye!\n";
            return;
        case MainMenuChoice::UserPlaysAgainstComputer:
            user_plays_against_computer(game_options);
            break;
        case MainMenuChoice::ComputerPlaysAgainstComputer:
            computer_plays_against_computer(game_options);
            break;
        case MainMenuChoice::ConfigureOptions:
            configure_game_options(game_options);
            break;
        case MainMenuChoice::Error:
            std::cout << "\nYou did not enter a valid choice, please try again\n";
            break;
        }
    }
}

} // namespace bulls_and_cows
