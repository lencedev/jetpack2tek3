# Jetpack2Tek3

Jetpack2Tek3 is a multiplayer game developed in C++ as part of the Epitech curriculum. The goal of this project is to create a real-time 2D multiplayer platformer where players navigate through levels, avoiding obstacles, collecting fuel, and competing to reach the goal.

The project requires implementing both server-side and client-side components to handle game logic, real-time communication, and player interaction.
Project Components

    Server: Manages the game state, player connections, and synchronizes game events in real-time.
    Client: Displays the game to the player, handles input, and communicates with the server for game updates.

## Features

    Real-time Multiplayer: Allows multiple clients to connect and play simultaneously.
    Physics Engine: Implements gravity and collision detection for a platforming experience.
    Jetpack Mechanics: Players can use a jetpack to navigate levels.
    Resource Collection: Collect fuel to keep your jetpack powered.
    Competitive Gameplay: Race against other players to reach the goal first.

## Requirements

    C++17 or higher - Required for language features
    CMake - For configuring the project build
    Make - For compiling the code
    SFML - For graphical rendering and handling player input
    Network Libraries - For handling client-server communication (e.g., boost::asio)
