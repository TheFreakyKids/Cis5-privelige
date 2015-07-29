#include <iostream>						/*              Robert Patterson  ID: 2517666                     */
#include <iomanip>					   /*				  Bro-grammer : Justin Chou			             */
#include <string>					  /* cout << "Its over Milestone, I have the high ground!" << endl; */
#include <fstream>
#include <ctime>
using namespace std;

struct actor
{
	string name;        //if AI, use "AI"
	string classType;  //if AI, use "AI"
	int basicAttack;  //costs no energy. Not stored in file. static number shared with all classes and enemies
	int health;      //Use this to do damage
	int energy;     //energy builds each turn and caps at 5

};

char MenuInputValidation(char userInput);
void StartMenu();
void Continue(char userInput);
void ClassMenu(char userInput, string name);
void SaveData(string name, int Health, int Attack, string playerClass, actor &player); // SAVE FUNCTION BY -- Robert Patterson
void LoadData(string name, int Health, int Attack, string playerClass, actor &player); // LOAD FUNCTION BY -- Justin Chou
//========================================================================================================================//
//NEW PROTOTYPES FOR MILESTONE 3//
void Playerattack(actor &enemy, actor &player, char choice, string playerClass);
void AIattack(actor &enemy, actor &player);
bool block(actor &player, actor &enemy);
void heal(actor &player);
void enemyTurn(actor &enemy, actor &player);
void playerTurn(actor &player);
void battle(actor &enemy, actor &player, actor &source, char choice, string playerClass);
void gameManager(actor &source, string playerClass, string name, int Health, int Attack);

int main()
{
	//char userInput = '0';
	//string name;
	StartMenu();
	//MenuInputValidation(userInput);
	//gameManager(source, choice, playerClass);

	return 0;
}

char MenuInputValidation(char userInput)
{
	if (userInput != '1' && userInput != '2' && userInput != '3')
	{
		cout << "Please use (1), (2) and (3) as your inputs" << endl;
	}
	return userInput;
}

void StartMenu()
{
	char userInput = '0';
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
			ClassMenu;
		}
		else
		{
			StartMenu;
		}
	}

	else if (userInput == '2')
	{
		Continue;
	}

	else (userInput == '3');
	{
		exit(0);
	}

	MenuInputValidation(userInput);
}

void Continue(char userInput)
{
	cout << "Continue game? (1) Yes (2) No" << endl;
	cin >> userInput;
	if (userInput == '1')
	{
		LoadData;
	}
	else (userInput == '2');
	{
		StartMenu;
	}
}

void ClassMenu(char userInput, string name)
{
	int Health = 0;
	int Attack = 0;
	string playerClass = " ";
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
		playerClass = "QuickScoper";
		Health = 300;
		Attack = 150;
		cout << "You have chosen the Quick Scoper. You deal a large amount of damage, but you are not as quick or as tough as the Knife Runner. Use your healing hax wisely" << endl;
		cout << "You have " << Health << " health and deal " << Attack << " damage per attack" << endl;
		cout << "\n\nPlease enter your name" << endl;
		cout << "Your Name:>\n" << name;
		
	}
	else
	{
		playerClass = "KnifeRunner";
		Health = 500;
		Attack = 100;
		cout << "You have chosen the Knife Runner. You don't deal as much damage as the Quick Scoper, but you move faster and can take a lot more of hits using your Juggernaut ability" << endl;
		cout << "You have " << Health << " health and deal " << Attack << " damage per attack" << endl;
		cout << "\n\nPlease enter your name" << endl;
		cout << "Your Name:>\n";
	
	}
	cin.ignore();
	getline(cin, name);
	cout << "Welcome to Super MLG Quest " << name << " the " << playerClass << endl;
	SaveData;
	gameManager;
}

void SaveData(string name, int Health, int Attack, string playerClass, actor &player)
{
	ofstream writeFile;

	writeFile.open("playerinfo.txt");
	writeFile << name << endl;
	writeFile << playerClass << endl;
	writeFile << Attack << endl;
	writeFile << Health << endl;
	
	writeFile.close();
}



//MILESTONE 3 STUFF BELOW

void Playerattack(actor &enemy, actor &player, char choice, string playerClass) 
{
	player.energy++;
	cout << "Choose your attack. \n(1) Basic attack\n(2) Special attack[uses 3 energy]\n(3) Ultimate attack[uses 5 energy to gamble on a massive damage boost]\n(4) Special Ability\n(5) End Turn" << endl;//use attack based from choice and do damage to target's health value.
	cin >> choice;
	if (choice = '1')
	{
		if (player.energy < 1)
		{
			cout << "You don't have enough energy to do this." << endl;
		}
		else
		{
			player.basicAttack;														   //1 = base attack  - base attack value 
			player.energy - 1;
			enemy.health - player.basicAttack;
		}
	}
	else if (choice = '2')
	{
		if (player.energy < 2)
		{
			cout << "You don't have enough energy to do this." << endl;
		}
		else
		{
			int SPattack = player.basicAttack + 42;									  //2 = special attack - costs 3 energy and will modify (without storing) the damage output i.e finalDmg = baseAttack + special
			player.energy - 3;
			enemy.health - SPattack;
		}
	}
	else if (choice = '3')
	{
		if (player.energy < 5)
		{
			cout << "You don't have enough energy to do this." << endl;
		}
		else
		{
			int Ultimate = player.basicAttack + (rand() % (100 - 10) + 10);			 //3 = ultimate - Same method of modifying as above. gamble with 5 energy if this will do damage between 1-8 damage. use rand() for this with a min and max range
			player.energy - 5;
			enemy.health - Ultimate;
		}
	}
	else if (choice = '4')
	{
		if (playerClass == "KnifeRunner")
		{
			//block(player, enemy);
		}
		else (playerClass == "QuickScoper");
		{
			//heal(player);
		}
	}
	else if (choice = '5')
	{
		//4 = end turn - hey, maybe you're out of energy
	}
	if (player.energy = 0)
	{
		cout << "You have run out of energy. Your turn is over." << endl;
	}
	//if successful check, deduct matching energy amount
	//deal damage to target based from player's attack value
}

void AIattack(actor &enemy, actor &player)
{	
	if (enemy.energy >= 2)
	{
		cout << "Enemy attacks you" << endl;
		enemy.basicAttack;
		enemy.energy-2;
		player.health-100;
	}
	
	
	//establish an energy amount cost for the attack   [1 engergy]
	//energy check if energy == cost
	//Make the game interesting. Allow the enemy to randomly modify his damage output each attack by allowing  baseAttack + random range from 1-5.
	//deduct energy amount i.e 1 or 2 per turn
	//deal damage to target based from player's attack value
	//else End turn
}

/*bool block(actor &player, actor &enemy)
{
	int min = 1;
	int max = 10;
	int	coinToss = rand() % ((max - min) + 1) + min;
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
} */

/*void heal(actor &player)
{
	int min = 1;
	int max = 10;
	int	coinToss = rand() % ((max - min) + 1) + min;
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
}*/

void enemyTurn(actor &enemy, actor &player)  
{
	enemy.energy++;
	AIattack;
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

void playerTurn(actor &player)
{
	
	player.energy++;
	Playerattack;   // Grab input from player on attack choice from a menu of choices
														//energy check. if invalid choice loop for another choice

	// Call attack function based on player choice.
	//  - attack(actor &, actor, char )
	//  - block()
	//  - heal()

	// For example: attack() and pass as reference enemy as target and player as player as a read only argument
}

void battle(actor &enemy, actor &player, actor &source, char choice, string playerClass)
{
	cout << "\n=================================\n" << endl;
	cout << "A wild try-hard appears!" << endl;     //battle starting text
	
	//coin toss to see who goes first. heads (0) you, tails (1) enemy. 
	//Use srand ((unsigned) time(0)); Requires <ctime>
	//coinToss = (rand() % 2) + 1;
	srand((unsigned)time(0));
	int	coinToss = (rand() % 2) + 1;
	
	if (coinToss = 0)
	{
		cout << "You will make the first move" << endl;
		playerTurn;
		while (player.health > 0 && enemy.health > 0)
		{
			enemyTurn;
			playerTurn;
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
	else (coinToss = 1);
	{
		cout << "\nThe scrub rushes you without hesitation" << endl;
		enemyTurn;
		cout << "\nWe are back inside the battle function" << endl;
		while (player.health > 0 && enemy.health > 0)
		{
			playerTurn;
			enemyTurn;
			cout << "Results of turn: " << player.health << enemy.health << endl;
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
	
	//while loop that checks the enemy and player's health. While it is greater than 0, keep playing.
	//{
	// turn attack system. Could be loop with iterating variable that counts from 0-1 and then resets after one. Just make sure each player gets a sequential turn.
	// give current attacking actor 1 energy ++
	// Call turn function (Player or Enemy) based on turn order.

	// End the loop when the player or enemy reaches 0 health.
	//}
	// Keep a running tally of the player and enemy's stats (i.e health and energy)
	// Print an ending message indicating winner
	
}

/*void loadData(actor &player, actor &enemy)//modify to pass player by reference, pass enemy by value 
{

	// Use fstream to read in player and enemy data
	// Initialize ifstream
	//Utilize loadData(). Modify if needed.
	//set variables equal to s
}*/

void LoadData(string name, int Health, int Attack, string playerClass, actor &player)
{

	ifstream inFile;
	inFile.open("playerinfo.txt");
	cout << "Loading Player Info" << endl;

	if (inFile.fail())
	{
		cout << "The file does not exist, please start a new game." << endl;
		StartMenu;
	}

	else
	{

		inFile >> player.name;
		//player.name = name;
		cout << "Welcome back " << player.name << endl;
		inFile >> player.classType;
		//player.classType = playerClass;
		inFile >> player.basicAttack;
		//player.basicAttack = Attack;
		inFile >> player.health;
		//player.health = Health;

		cout << "\nYou have chosen the " << player.classType << " \nYou have " << player.basicAttack << " Attack and " << player.health << " Health" << endl;
		inFile.close();
	}
}

void gameManager(actor &source, string playerClass, string name, int Health, int Attack)
{
	
	// create player
	actor player;
	player.basicAttack;
	player.classType;
	player.energy;
	player.health;
	player.name;

	// create enemy 
	actor enemy;
	enemy.basicAttack = 100;
	enemy.classType = "Try-Hard";
	enemy.energy = 0;
	enemy.health = 250;
	enemy.name = "Try-Hard";


	// Initialize the players
	LoadData;// send player and enemy structs as arguments

	// Start the fight
	battle;
}
