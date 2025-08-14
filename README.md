# Snake Game (C++ with Raylib)

## 📜 Description
A modern, smooth version of the classic Snake game written in **C++** using the **Raylib** graphics library.  
This version includes **improved input handling** to prevent accidental self-collisions when pressing keys too quickly.

---

## 🎮 Gameplay
- Control the snake with **Arrow Keys**.
- Eat the apple to grow and increase your score.
- Avoid colliding with walls or yourself.
- High score is tracked during your play session.

---

## ✨ Features
- **Smooth Movement** – Snake moves at fixed time intervals.
- **Safe Input Handling** – No more instant reversal into yourself.
- **Random Food Placement** – Apples always spawn in empty spaces.
- **Score & High Score Display** – Real-time tracking.
- **Clean Graphics** – Simple, modern design.

---

## 🛠 Requirements
- **C++17** or later
- **Raylib** installed ([Download Here](https://www.raylib.com/))
- An image for the apple (place in `Graphics/apple.png`)

---

## 📦 Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/snake-game-raylib.git
   cd snake-game-raylib

## Running the Game

`g++ main.cpp -o snake -lraylib -lm -ldl -lpthread`
`./snake`
