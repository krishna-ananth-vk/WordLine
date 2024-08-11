#include <iostream>
#include <vector>
#include <string>

using namespace std;

void printGameIntro()
{
    std::cout << R"(
 _    _               _ _     _            
| |  | |             | | |   (_)           
| |  | | ___  _ __ __| | |    _ _ __   ___ 
| |/\| |/ _ \| '__/ _` | |   | | '_ \ / _ \
\  /\  / (_) | | | (_| | |___| | | | |  __/
 \/  \/ \___/|_|  \__,_\_____/_|_| |_|\___|
)" << std::endl;

    std::cout << "Welcome to WordLine!\n\n";
    std::cout << "Game Instructions:\n";
    std::cout << "1. Guess the 5-letter word.\n";
    std::cout << "2. For each guess, you will receive feedback:\n";
    std::cout << "   - 'X' indicates a correct letter in the correct position.\n";
    std::cout << "   - 'O' indicates a correct letter in the wrong position.\n";
    std::cout << "   - '-' indicates an incorrect letter.\n";
    std::cout << "3. You have 6 attempts to guess the word.\n";
    std::cout << "4. Type 'q' to quit the game at any time.\n";
    std::cout << "\nGood luck!\n";
}
string checkUserInoutAndGetResult(const string &user_input, const string &secretWord)
{
    string result = "-----";

    for (int i = 0; i < 5; ++i)
    {
        if (user_input[i] == secretWord[i])
        {
            result[i] = 'X';
        }
    }

    for (int i = 0; i < 5; ++i)
    {
        if (result[i] != 'X' && count(secretWord.begin(), secretWord.end(), user_input[i]) > 0)
        {
            result[i] = 'O';
        }
    }
    return result;
}

int runGame()
{
    vector<string>
        wordList = {"learn", "state"};

    srand(time(0));

    string wordle = wordList[rand() % wordList.size()];

    int attempts = 6;
    string user_input;
    while (attempts > 0)
    {
        cout << "Enter word:";
        cin >> user_input;

        if (user_input == "q")
        {
            cout << "Exiting the game. The word was '" << wordle << endl;
            return 0;
        }

        transform(user_input.begin(), user_input.end(), user_input.begin(), [](unsigned char c)
                  { return tolower(c); });
        if (user_input.length() != 5 || find(wordList.begin(), wordList.end(), user_input) == wordList.end())
        {
            cout << "Invalid guess. Please enter a valid 5-letter word." << endl;
            continue;
        }

        string result = checkUserInoutAndGetResult(user_input, wordle);
        cout << "Result: " << result << "\n";

        if (user_input == wordle)
        {
            cout << "Congratulations! You guessed the word '" << wordle << endl;
            break;
        }

        --attempts;

        if (attempts == 0)
        {
            cout << "Game over! The word was '" << wordle << endl;
        }
    }
    return 0;
}

int main()
{
    char playAgain;
    printGameIntro();
    do
    {
        runGame();

        cout << endl
             << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        playAgain = std::tolower(playAgain);
    } while (playAgain == 'y');
    return 0;
}