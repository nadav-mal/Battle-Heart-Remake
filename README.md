BATTLE-HEART GAME PROJECT, 2022

Description:
At this game your goal is to kill all the minions spawned in every level.
At each level the player begins with different characters such as:
Cleric, Knight, Archer, and Wizard.
Each ally has a unique set of skills which can help the player kill the spawned minions and complete the level.
By completing a level, the player will unlock the next level.
Ally characters
A mighty knight- the knight is known as the game tank,
He has a high amount of health and shielding stats but low attack damage.
The wise old mage – the mage has studied the elements and now can use those to cast impressive skills which could impact single and multiple targets.
The divine cleric – the cleric can heal and cast shield buffs on ally characters.
The archer – along with a wooden crossbow the archer has mastered a single target skill, the archer is agile and strong, but he dies fast.
Enemy characters:
Dark cleric: heals all enemy minions, moves towards the closest enemy minion.
Demon:  melee attacks players causing damage
Wolf: melee attacks players, low health minion
MiniDragon: ranged attacks on players
Game Design
Object:
Object is the base class for all drawable in-game objects such as projectiles and characters.
The object contains a virtual set of functions and an implemented set of functions which is the same for both projectiles and characters.
Projectile: (inherits from "Object")
Projectile is the visual effect of a skill; each skill has its own projectile that is built once a skill Is pressed and destroyed once the projectile reaches its target.
Character: (inherits from "Object")
Character represents all the in-game allies and enemies, all allies and enemies inherit from this class


Skill:
Skill is a class for every active/passive skill in-game.
The skill is created by a strategy design pattern, each skill has its own specifiers such as: multi/single target, player/enemy targeted. Along with those specifiers, each skill has its own effect and projectile. The projectile is the visual effect for a skill and the effect contains the functionality of the skill. for example: an arrow is a projectile, and the arrow's affect is to cause damage. 
Effect:
Effect is an abstract class which only contains a virtual "affect" function which is overridden by the different effects. (See more below)
Heal, Defend, Damage, LifeDrain:  
All those classes inherit from class "Effect" and overrides the "affect" function in a different way. Adding a new effect is easily done by adding a new class which inherit from "Effect" and to write a new "affect" implementation. 
Controller:
Contains all the in-game screens, used to swap between screens and play music
Screen
Class screen is an abstract class which contains virtual functions such as: run, update, draw etc. each in-game screen inherit from this class.
Menu, LevelSelect, Help, Gameplay:
All those classes inherit from class "screen". Each class is a different screen mode, the controller replaces between the different screens and draws the current used screen on the window.
Animation:
Any drawable animated object contains a class animation variable which updates the animation.
SteeringInterface:
The movement of every Enemy/Player is handled by this class. The class contains functions which prevents enemies from overlapping and deepens the movement. 
LevelLoader: 
This class is used to load all levels from a given txt file and returns all the data. The process of adding a level will be explained below.
Stat:
Each character contains a vector of stats. Stats such as hp/defense/damage/attack speed
Are changeable.
Timer:  this class represents a timer; timer is used by skills to know if a skill is usable or in cooldown.
HealthBar: 
Displays an hp bar with current health of a player/enemy. Also helps with giving visual feedback of damage taken.
Resources:
This class loads all the textures and buffers for all sprites and sounds which are used in game. All of those are loaded once by using a singleton.
Hash Table:
a template class which contains an unordered map of two changeable types of elements. Used in a various way (mainly in board)

Data structures used in the program:
Class Board: 
Contains an unordered_map<int, shared_ptr<player>> which returns a shared_ptr to a character (the character is determined by the given key), the class also contains a different map of enemies which is implemented similar
This is used to load enemies and players for a level selected.
Also contains a vector<shared_ptr<enemy>>, vector<shared_ptr<player>> which contains all the current characters.
class Controller:
contains a vector<unique_ptr<screens>> which are all the different screens in the game.
Class Level Select:
Contains an unordered_map<string, int>, a map of all enemies in a level.
Macros:
Contains initialization parameters for animation parameters, sprite sheet row length, skill's cooldowns, strings of resources names (used to load textures) and more.


Input file format:
To add new levels to the game, add the new level’s name to the file named “Levels.txt”.
To edit levels, open the file and insert chars by this format:
1.	Write "Level x" (instead of x put current level number)
2.	Write the ally characters for this level (write each ally on a different line).
3.	Write an enemy and how many enemies you want. 
4.	You have the ability to define "Waves" of enemies in each level. To begin a wave type "!", to end a wave type "!" again.

For example:
Level 1
Cleric
Knight
! Wolf 2!
! Demon 3! 

This input will load a level with a Cleric and a knight, the level will have 2 waves, the first enemy wave contains 2 wolf's and the next contains 3 demons.

	
Maximum number of levels can be 15. Note that each third level is a Fire-themed level, therefor the background sprite and background music will change to a fire-theme. 
