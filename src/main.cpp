#include "../include/Game.h"
#include <unordered_map>
#include "../include/init.h"
#include "../include/constants.h"
#include "../include/weapons/Airstrike.h"
#include "../include/weapons/Bazooka.h"
#include "../include/weapons/Blowtorch.h"
#include "../include/weapons/Melee.h"
#include "../include/weapons/Pistol.h"
#include "../include/weapons/Teleporter.h"
#include "../include/commands/ActionCommand.h"
#include "../include/commands/ChooseCommand.h"
#include "../include/commands/HelpCommand.h"
#include "../include/commands/MapCommand.h"
#include "../include/commands/MoveCommand.h"
#include "../include/commands/QuitCommand.h"
#include "../include/commands/StateCommand.h"
#include "Random.h"

int turn = 0;

void turnPlayer(Game &game)
{
    // turn player
    const size_t p = (turn + 1) % game.allPlayers.size(); // result is always 0 or 1
    game.currentPlayer = game.allPlayers[p];
    game.selectedWorm = &game.currentPlayer->worms[0];   // select always the first worm by default
    game.selectedWeapon = game.selectedWorm->weapons[0]; // select always the first weapon by default
    turn++;

    // drop case
    se::Random *r = new se::Random();
    const int col = r->getRandomInt(0, game.map.numColumns - 1);
    game.map.field[0][col].value = CASE;
    applyGravityAtColumn(game, col);
}

void handleCommand(Game &game, const vector<string> args)
{
    if (args.empty() || args.size() > 3)
    {
        printf("[ERROR] Wrong number of paramters!\n");
        return;
    }
    unordered_map<string, ICommand *> validCommands = {
        {"help", new HelpCommand()},
        {"map", new MapCommand(game)},
        {"quit", new QuitCommand()},
        {"state", new StateCommand(game)},
        {"action", NULL},
        {"choose", NULL},
        {"move", NULL},
    };

    const string rootCommand = args[0];
    if (validCommands.find(rootCommand) == validCommands.end())
    {
        printf("[ERROR] Command '%s' not found\n", rootCommand.c_str());
        return;
    }

    unique_ptr<ActionCommand> actionCmd = NULL;
    bool success = false;

    if (args.size() == 1)
    {
        if (rootCommand.compare("action") == 0)
        {
            actionCmd = make_unique<ActionCommand>(game);
            success = actionCmd->execute();
            if (success)
            {
                turnPlayer(game);
            }
            return;
        }

        if (validCommands[rootCommand] == NULL) {
            printf("[ERROR] Invalid command!\n");
            return;
        }
        validCommands[rootCommand]->execute();
    }

    if (args.size() == 2)
    {
        const string cmdParam = args[1];

        if (rootCommand.compare("action") == 0)
        {
            if (cmdParam.compare("idle") == 0)
            {
                turnPlayer(game);
                return;
            }

            try
            {
                // try to parse the given parameter string to integer
                // if it fails, then it is considered as a direction, which is handled in the catch block below
                int column = stoi(cmdParam);

                // use airstike
                actionCmd = make_unique<ActionCommand>(game, column);
                success = actionCmd->execute();
                if (success)
                {
                    turnPlayer(game);
                }
                return;
            }
            catch (const std::exception &e)
            {
                // use other weapon
                actionCmd = make_unique<ActionCommand>(game, cmdParam);
                success = actionCmd->execute();
                if (success)
                {
                    turnPlayer(game);
                }
            }

            return;
        }

        if (rootCommand.compare("choose") == 0)
        {
            ChooseCommand c(game, cmdParam);
            c.execute();
        }
    }

    if (args.size() == 3)
    {
        // ex: action 3 5 => args : "action", "3", "5"

        if (rootCommand.compare("action") == 0)
        {
            try
            {
                const int col = stoi(args[1]);
                const int row = stoi(args[2]);

                // use teleporter
                actionCmd = make_unique<ActionCommand>(game, col, row);
                success = actionCmd->execute();
                if (success)
                {
                    turnPlayer(game);
                }
                return;
            }
            catch (const std::exception &e)
            {
                printf(" [ERROR] Column and row should be a number!\n");
                printf("\tex: action 11 4\n");
                return;
            }
        }

        if (rootCommand.compare("choose") == 0 && args[1].compare("worm") == 0)
        {
            string wormName = args[2];
            game.currentPlayer->selectWorm(wormName);
            return;
        }

        if (rootCommand.compare("move") == 0)
        {
            const string direction = args[1];

            if (direction.compare("l") != 0 && direction.compare("r") != 0)
            {
                printf("[ERROR] Worm can only move left/right!\n");
                printf("\tex: move l/r [0...3]\n");
                return;
            }

            try
            {
                const int steps = stoi(args[2]);
                // move worm
                MoveCommand m(game, *game.selectedWorm, DIRECTIONS[direction], steps);
                success = m.execute();
                if (success)
                {
                    turnPlayer(game);
                }
            }
            catch (const std::exception &e)
            {
                printf("Column and row should be a number!\n");
                printf("\tex: action 11 4\n");
            }
        }
    }
}

int main()
{
    Game game;
    initGame(game);
    string command;
    getline(cin, command); // prevent empty command at beginning

    while (game.gameRunning)
    {
        printf("___________________________________________\n");
        printf("Player %s %s ", game.currentPlayer->name.c_str(), game.cmdPrompt.c_str()); // Player 1 >
        getline(cin, command);                                                             // type in command

        handleCommand(game, splitString(command, " "));
    }

    return 0;
}