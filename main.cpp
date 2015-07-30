#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

struct Actor
{
	string name;
	string classType;
	int basicAttack;
	int health;
	int energy;
};

void startMenu();
void classMenu(char user);
void saveData(Actor &player);
void gameManager(Actor &player, char user);
void loadData(char user);
void battle(Actor &player, Actor &enemy);
void playerTurn(Actor &player, Actor &enemy);
void enemyTurn(Actor &enemy, Actor &player);
void playerAttack(Actor &player, Actor &enemy);
void contnu();
void aIAttack(Actor &enemy, Actor &player);
void heal(Actor &player);
bool block(Actor &player, Actor &enemy);

int main()
{
    startMenu();

    return 0;
}

void startMenu()
{
	char userInput;
	cout << "---------------------\n" << endl;
	cout << "Super Dank MLG Bros:\n\nThe Quest For The Dew\n" << endl;
	cout << "---------------------\n" << endl;
	cout << "(1) Start new game" << endl;
	cout << "(2) Continue saved game" << endl;
	cout << "(3) Quit the game" << endl;
	cout << "Choice:>";
	cin >> userInput;
	if (userInput == '1')
	{
		cout << "WARNING! Starting a new game will overwrite any previous save, would you like to start a new game? (1) Yes (2) No" << endl;
		cin >> userInput;
		if (userInput == '1')
		{
			classMenu(userInput);
		}
		else
		{
			startMenu();
		}
	}
	else if (userInput == '2')
	{
		contnu();
	}
	else (userInput == '3');
	{
		exit(EXIT_SUCCESS);
	}
}

void classMenu(char user)
{
    Actor player;
    char userInput;

	cout << "\n\nPlease select your class" << endl;
	cout << "\n(1) Knife Runner  :>  Weaker attacks, but moves faster and has more health with the Juggernaut ability" << endl;
	cout << "\n(2) Quick Scoper  :>  Stronger attacks and healing hax, but less health" << endl;
	cout << "Choice:>";
	cin >> userInput;
	while (userInput != '1' && userInput != '2')
	{
		cout << "Please use (1) and (2) as your inputs" << endl;
		cin >> userInput;
	}

    if (userInput == '2')
	{
		player.classType = "QuickScoper";
		player.health = 300;
		player.basicAttack = 150;
		player.energy = 0;
		cout << "You have chosen the Quick Scoper. You deal a large amount of damage, but you are not as quick or as tough as the Knife Runner. Use your healing hax wisely" << endl;
		cout << "You have " << player.health << " health and deal " << player.basicAttack << " damage per attack" << endl;
		cout << "\n\nPlease enter your name" << endl;
		cout << "Your Name:>\n" << player.name;
	}
    else
	{
		player.classType = "KnifeRunner";
		player.health = 500;
		player.basicAttack = 100;
		player.energy = 0;
		cout << "You have chosen the Knife Runner. You don't deal as much damage as the Quick Scoper, but you move faster and can take a lot more of hits using your Juggernaut ability" << endl;
		cout << "You have " << player.health << " health and deal " << player.basicAttack << " damage per attack" << endl;
		cout << "\n\nPlease enter your name" << endl;
		cout << "Your Name:>\n";
	}


    cin.ignore();
    getline(cin, player.name);
    cout << "Welcome to Super MLG Quest " << player.name << " the " << player.classType << endl;
    saveData(player);
    gameManager(player, user);
}

void saveData(Actor &player)
{
	ofstream writeFile;

	writeFile.open("playerinfo.txt");
	writeFile << player.name << endl;
	writeFile << player.classType << endl;
	writeFile << player.basicAttack << endl;
	writeFile << player.health << endl;

	writeFile.close();
}

void gameManager(Actor &player, char user)
{
	Actor enemy;
	enemy.basicAttack = 100;
	enemy.classType = "Try-Hard";
	enemy.energy = 0;
	enemy.health = 250;
	enemy.name = "Try-Hard";

    if (user == '2')
    {
        loadData(user);

    }
    else
    {
        battle(player, enemy);
    }
}

void contnu()
{
    char userInput;
	cout << "Continue game? (1) Yes (2) No" << endl;
	cin >> userInput;
	if (userInput == '1')
	{
		loadData(userInput);
	}
	else (userInput == '2');
	{
		startMenu();
	}
}

void loadData(char user)
{
    Actor player;
	ifstream inFile;
	inFile.open("playerinfo.txt");
	cout << "Loading Player Info..." << endl;

	if (inFile.fail())
	{
		cout << "The file does not exist, please start a new game." << endl;
		startMenu();
	}

	else
	{
		inFile >> player.name;
		inFile >> player.classType;
		inFile >> player.basicAttack;
		inFile >> player.health;

        cout << "Welcome back " << player.name << endl;

		cout << "\nYou have chosen the " << player.classType << " \nYou have " << player.basicAttack << " Attack and " << player.health << " Health" << endl;
		inFile.close();
		user = '1';
		gameManager(player, user);
	}
}

void battle(Actor &player, Actor &enemy)
{
	cout << "\n=================================\n" << endl;
	cout << "A wild try-hard appears!" << endl;

	int	coinToss = (rand() % 2);

	if (coinToss == 0)
	{
		cout << "You will make the first move" << endl;
		while (player.health > 0 && enemy.health > 0)
		{
            playerTurn(player, enemy);
			enemyTurn(enemy, player);
		}
        if (player.health <= 0)
        {
            cout << "You got rekt m8. Git gud scrub." << endl;
        }
        else (enemy.health <= 0);
        {
            cout << "You shrekt the Try-Hard. Go forth and consume your Mtn. Dew and Doritos m80." << endl;
        }
	}
	else (coinToss == 1);
	{
        cout << "\nThe scrub rushes you without hesitation" << endl;
        while (player.health > 0 && enemy.health > 0)
        {
            enemyTurn(enemy, player);
            playerTurn(player, enemy);

            cout << "Results of turn: " << "\nPlayer Health: " << player.health << "\nEnemy Health: " << enemy.health << endl;
        }
        if (player.health <= 0)
        {
            cout << "You got rekt m8. Git gud scrub." << endl;
        }
        else (enemy.health <= 0);
        {
            cout << "You shrekt the Try-Hard. Go forth and consume your Mtn. Dew and Doritos m80." << endl;
        }
	}
}

void playerTurn(Actor &player, Actor &enemy)
{
	player.energy++;
	playerAttack(player, enemy);
}

void enemyTurn(Actor &enemy, Actor &player)
{
	enemy.energy++;
	aIAttack(enemy, player);
	cout << "Enemy turn ends." << endl;
	cout << "enemy's energy = " << enemy.energy << endl;
	cout << "enemy's health = " << enemy.health << endl;
	cout << "your health = " << player.health << endl;

	// Randomly select an enemy action based on simple AI logic. Randomize choice and use basic logic to make the game interesting.
	// Call attack function based on AI choice.
	//  - attack(actor &, actor, char )
	//  - block() or heal() if you want to give the enemy this functionality (not required).

	// For example: attack() and pass as reference enemy as target and player as player as a read only argument (nothing returned or stored for that argument)
}

void playerAttack(Actor &player, Actor &enemy)
{
	player.energy++;
	char choice;

	cout << "Choose your attack. \n(1) Basic attack\n(2) Special attack[uses 3 energy]\n(3) Ultimate attack[uses 5 energy to gamble on a massive damage boost]\n(4) Special Ability\n(5) End Turn" << endl;//use attack based from choice and do damage to target's health value.
	cin >> choice;
	
	if (choice == '1')
	{
		if (player.energy < 1)
		{
			cout << "You don't have enough energy to do this." << endl;
		}
		else
		{
			player.basicAttack;														   //1 = base attack  - base attack value
			player.energy -= 1;
			enemy.health -= player.basicAttack;
		}
	}
	else if (choice == '2')
	{
		if (player.energy < 2)
		{
			cout << "You don't have enough energy to do this." << endl;
		}
		else
		{
            int SPattack = player.basicAttack + 42;									  //2 = special attack - costs 3 energy and will modify (without storing) the damage output i.e finalDmg = baseAttack + special
			player.energy -= 3;
			enemy.health -= SPattack;
		}
	}
	else if (choice == '3')
	{
		if (player.energy < 5)
		{
		    cout << "You don't have enough energy to do this." << endl;
		}
		else
		{
		    int Ultimate = player.basicAttack + (rand() % (100 - 10) + 10);			 //3 = ultimate - Same method of modifying as above. gamble with 5 energy if this will do damage between 1-8 damage. use rand() for this with a min and max range
		    player.energy -= 5;
	    	    enemy.health -= Ultimate;
		}
	}
	else if (choice == '4')
	{
		if (player.classType == "KnifeRunner")
		{
			block(player, enemy);
		}
		else (player.classType == "QuickScoper");
		{
			heal(player);
		}
	}
	else if (choice == '5')
	{
		cout << "Your turn has ended." << endl;
	}
	if (player.energy == 0)
	{
		cout << "You have run out of energy. Your turn is over." << endl;
	}
	//if successful check, deduct matching energy amount
	//deal damage to target based from player's attack value
}

void aIAttack(Actor &enemy, Actor &player)
{
	if (enemy.energy >= 2)
	{
		cout << "Enemy attacks you" << endl;
		enemy.basicAttack;
		enemy.energy -= 2;
		player.health -= 100;
	}
}

void heal(Actor &player)
{
	int min_ = 1;
	int max_ = 10;
	int	coinToss = rand() % ((max_ - min_) + 1) + min_;
	if (coinToss = 5)
	{
		player.health + 50;
		cout << "You used your hax to restore 50 health" << endl;
	}
	else;
	{
		cout << "Your heal hax don't work scrub" << endl;
	}
	//if the player is a mage, he can have a chance to self heal at the start of the turn.
	// The chance will be a random chance between 1 - 10 odds you will need to choose one number as a constant in that range. Compare the random number to that number.
	//choose an amount to heal your player and add that to their health.
}

bool block(Actor &player, Actor &enemy)
{
	int min_ = 1;
	int max_ = 10;
	int	coinToss = rand() % ((max_ - min_) + 1) + min_;
	if (coinToss = 5)
	{
		enemy.basicAttack = 0;
		cout << "Your Juggernaut has blocked the incoming damage." << endl;
		return true;
	}
	else;
	{
		cout << "Your juggs didn't work scrub" << endl;
		return false;
	}
	//this is if the player is a warrior there is a chance to block all damage from an incoming attack.
	//return true or false based from a random chance between 1 - 10 odds you will need to choose one number as a constant in that range. compare the random number to that number.
}
