#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// Final Project: Lake Palestine Fishing Game

struct Fish
{
    string name;
    string correctBait;
};

struct RoundResult
{
    string fishName;
    int fishCaught;
    int failureAttempts;
    bool caughtFish;
};

void displayIntro();
vector<Fish> createFishList();
vector<string> createFishNameList(vector<Fish> fishList);
vector<string> createBaitList();
void displayMenu(vector<string> menuItems, string title);
int getChoice(string message, int lowestChoice, int highestChoice);
bool isFoodBait(string baitName);
bool isCorrectBait(Fish selectedFish, string baitName);
RoundResult playOneRound();
void displayFinalResult(RoundResult result);
char askPlayAgain();

int main()
{
    char playAgain = 'y';
    RoundResult result;

    while (playAgain == 'y' || playAgain == 'Y')
    {
        result = playOneRound();
        displayFinalResult(result);
        playAgain = askPlayAgain();
    }

    cout << endl;
    cout << "Thank you for playing the Lake Palestine Fishing Game!" << endl;

    return 0;
}

void displayIntro()
{
    string intro =
        "==================================================\n"
        "          LAKE PALESTINE FISHING GAME\n"
        "==================================================\n\n"
        "You are currently at Lake Palestine.\n"
        "Your mission is to find the correct bait to catch\n"
        "the fish you want.\n\n"
        "The purpose of this fishing trip is to catch fish\n"
        "for a charity food organization.\n\n"
        "First, choose the type of fish you want to catch.\n"
        "Then, choose the bait that you think is correct.\n"
        "If you choose the correct bait, you catch the fish.\n"
        "If you choose wrong more than 2 times, the round is over.\n";

    cout << intro << endl;
}

vector<Fish> createFishList()
{
    vector<Fish> fishList;
    Fish fish;

    fish = { "Bass", "Plastic worms" };
    fishList.push_back(fish);

    fish = { "Catfish", "Shad bait fish" };
    fishList.push_back(fish);

    fish = { "Bluegill", "Nightcrawlers" };
    fishList.push_back(fish);

    fish = { "Crappie", "Live minnow" };
    fishList.push_back(fish);

    return fishList;
}

vector<string> createFishNameList(vector<Fish> fishList)
{
    vector<string> fishNames;

    for (int i = 0; i < fishList.size(); i++)
    {
        fishNames.push_back(fishList[i].name);
    }

    return fishNames;
}

vector<string> createBaitList()
{
    vector<string> baitList =
    {
        "Nightcrawlers",
        "Shad bait fish",
        "Live minnow",
        "Plastic worms",
        "French fries",
        "Pickles"
    };

    return baitList;
}

void displayMenu(vector<string> menuItems, string title)
{
    cout << title << endl;
    cout << "--------------------------------" << endl;

    for (int i = 0; i < menuItems.size(); i++)
    {
        cout << i + 1 << ") " << menuItems[i] << endl;
    }

    cout << "--------------------------------" << endl;
}

int getChoice(string message, int lowestChoice, int highestChoice)
{
    int choice;

    cout << message;
    cin >> choice;

    while (choice < lowestChoice || choice > highestChoice)
    {
        cout << "Invalid choice. Please enter a number from "
            << lowestChoice << " to " << highestChoice << ": ";
        cin >> choice;
    }

    return choice;
}

bool isFoodBait(string baitName)
{
    return baitName == "French fries" || baitName == "Pickles";
}

bool isCorrectBait(Fish selectedFish, string baitName)
{
    return selectedFish.correctBait == baitName;
}

RoundResult playOneRound()
{
    vector<Fish> fishList = createFishList();
    vector<string> fishNames = createFishNameList(fishList);
    vector<string> baitList = createBaitList();

    int fishChoice;
    int baitChoice;
    int wrongAttempts = 0;

    bool caughtFish = false;

    displayIntro();
    displayMenu(fishNames, "Fish choices:");

    fishChoice = getChoice("Choose the fish you want to catch: ", 1, fishList.size());

    Fish selectedFish = fishList[fishChoice - 1];

    cout << endl;
    cout << "You chose to catch: " << selectedFish.name << endl;

    while (caughtFish == false && wrongAttempts <= 2)
    {
        cout << endl;
        cout << "Wrong attempts: " << wrongAttempts << endl;

        displayMenu(baitList, "Bait choices:");

        baitChoice = getChoice("Then choose the bait you want to use: ", 1, baitList.size());

        string selectedBait = baitList[baitChoice - 1];

        cout << endl;
        cout << "You chose: " << selectedBait << endl;

        if (isFoodBait(selectedBait))
        {
            cout << "This is a fishing challenge, not grocery challenge " << endl;
            wrongAttempts = wrongAttempts + 1;
        }
        else if (isCorrectBait(selectedFish, selectedBait))
        {
            cout << "You caught a very big fish." << endl;
            caughtFish = true;
        }
        else
        {
            cout << "You did not catch anything except get bitten by mosquitoes" << endl;
            wrongAttempts = wrongAttempts + 1;
        }
    }

    if (caughtFish == true)
    {
        cout << endl;
        cout << "You completed the fishing mission for the charity food organization." << endl;
    }
    else
    {
        cout << endl;
        cout << "Unfortunately, you did not catch any fish." << endl;
    }

    RoundResult result;

    result.fishName = selectedFish.name;
    result.failureAttempts = wrongAttempts;
    result.caughtFish = caughtFish;

    if (caughtFish == true)
    {
        result.fishCaught = 1;
    }
    else
    {
        result.fishCaught = 0;
    }

    return result;
}

void displayFinalResult(RoundResult result)
{
    cout << endl;
    cout << "Final Result" << endl;
    cout << "--------------------------------" << endl;
    cout << "Fish selected: " << result.fishName << endl;
    cout << "Fish caught: " << result.fishCaught << endl;
    cout << "Total failure attempts: " << result.failureAttempts << endl;

    if (result.caughtFish == true)
    {
        cout << "You are the champion of the fishing tournament." << endl;
    }
    else
    {
        cout << "You did not catch the selected fish in this round." << endl;
    }

    cout << "--------------------------------" << endl;
}

char askPlayAgain()
{
    char answer;

    cout << endl;
    cout << "Do you want to try again? (y/n): ";
    cin >> answer;

    while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N')
    {
        cout << "Invalid choice. Please enter y or n: ";
        cin >> answer;
    }

    return answer;
}
