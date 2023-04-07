# mem-game

## Description

A simple memory game written in C.

Then navigate to the game folder and run the `mem-game.exe` file.

## Project Structure

The project consists of the following files.

```
PROJECT_ROOT
├── mem-game.cpp               
└── mem-game.exe               
```

## Scope

The project utilized the following C components: 

-	Input, Output
-	Arithmetic Operations
-	Conditional Statements
-	Loops
-	Functions
-	Strings, Arrays

All of which are learned from CS 1101 Laboratory B — Computer Programming I.

## Importance to end-user/s

Mem-game could provide entartainment for its users. The memorization involved in-game could also train the brain to memorize five words at once, instead of the usual three.

## Screenshots

![image](https://user-images.githubusercontent.com/107972883/206701746-4a037c41-4217-471d-8532-d930735b3d55.png)

![image](https://user-images.githubusercontent.com/107972883/206702118-c7fa32ed-9498-40ce-aeee-918ba9660626.png)

![image](https://user-images.githubusercontent.com/107972883/206702161-32df85a8-e60f-4aa7-939d-7b1bad0d9961.png)

![image](https://user-images.githubusercontent.com/107972883/206702189-e86cdde2-2846-4896-b69d-08fd4608abcc.png)

## How to Play

The game menu is navigated using `number keys`.

The game proper is subdivided into two phases:

### 1. Memorize Phase

Upon starting the game from the menu, the player must memorize the words enclosed within boxes for 5 seconds before it disappears.

### 2. Input Phase

The player will then input the missing words in correct order, spelling, and case.

### Points and Life System

If the player inputs a word in correct order, spelling, and case, this is called a correct word. This will reward the player 5 points and a single life (+:white_heart:), not exceeding the maximum life.

Otherwise, it is considered a wrong word and will deduct a single life (-:white_heart:).

The player starts with 3 maximum lives (:white_heart: :white_heart: :white_heart:).

If the player inputs five 5 consecutive correct words, this is considered a perfect round.

If the player scores consecutive perfect rounds this is called a streak and will double the current score and increase the maximum lives that could be earned (max :white_heart:+).
