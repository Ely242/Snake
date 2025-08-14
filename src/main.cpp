// Snake Game
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <deque>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

// Colors
Color GREEN      = {173, 204, 96, 255};
Color DARK_GREEN = {123, 154, 56, 255};

// Game constants
const int CELL_SIZE  = 30;
const int CELL_COUNT = 25;
const int OFFSET     = 75;

// Time tracking
double lastUpdateTime = 0;

bool EventTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

// Pair (x, y) coordinates
class Pair {
public:
    int x, y;
    Pair(int x, int y) : x(x), y(y) {}
    Pair() : x(0), y(0) {}

    bool operator==(const Pair& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Pair& other) const { return x != other.x || y != other.y; }
    Pair operator+(const Pair& other) const  { return Pair(x + other.x, y + other.y); }
    Pair operator-(const Pair& other) const  { return Pair(x - other.x, y - other.y); }
};

// Food object
class Food {
public:
    Pair position;
    Texture2D texture;

    Food(const set<pair<int, int>>& bodySet) {
        Image image = LoadImage("Graphics/apple.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPosition(bodySet);
    }

    ~Food() {
        UnloadTexture(texture);
    }

    void Draw() {
        DrawTexture(texture, OFFSET + position.x * CELL_SIZE, OFFSET + position.y * CELL_SIZE, WHITE);
    }

    Pair GenerateRandomCell() {
        return Pair(GetRandomValue(0, CELL_COUNT - 1), GetRandomValue(0, CELL_COUNT - 1));
    }

    Pair GenerateRandomPosition(const set<pair<int, int>>& bodySet) {
        Pair newPosition;
        do {
            newPosition = GenerateRandomCell();
        } while (bodySet.find(make_pair(newPosition.x, newPosition.y)) != bodySet.end());
        return newPosition;
    }
};

// Direction constants
const Pair UP(0, -1), DOWN(0, 1), LEFT(-1, 0), RIGHT(1, 0);

// Snake object
class Snake {
public:
    deque<Pair> body = {Pair(6, 9), Pair(5, 9), Pair(4, 9)};
    set<pair<int, int>> bodySet = {make_pair(6, 9), make_pair(5, 9), make_pair(4, 9)};
    Pair direction = RIGHT;
    bool addSegment = false;

    void Update() {
        body.push_front(body.front() + direction);
        bodySet.insert(make_pair(body.front().x, body.front().y));

        if (!addSegment) {
            bodySet.erase(make_pair(body.back().x, body.back().y));
            body.pop_back();
        } 
        else {
            addSegment = false;
        }
    }

    void Draw() {
        for (auto& part : body) {
            Rectangle rect = {
                (float)(OFFSET + part.x * CELL_SIZE),
                (float)(OFFSET + part.y * CELL_SIZE),
                (float)CELL_SIZE,
                (float)CELL_SIZE
            };
            DrawRectangleRounded(rect, 0.5, 6, DARK_GREEN);
        }
    }

    void Reset() {
        body = {Pair(6, 9), Pair(5, 9), Pair(4, 9)};
        bodySet = {make_pair(6, 9), make_pair(5, 9), make_pair(4, 9)};
        direction = RIGHT;
        addSegment = false;
    }
};

// Game object
class Game {
public:
    Snake snake;
    Food food;
    bool running = false;
    int score = 0, highScore = 0;

    Game() : snake(), food(snake.bodySet) {}

    void Update() {
        if (running) {
            snake.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithBody();
        }
    }

    void Draw() {
        food.Draw();
        snake.Draw();
    }
private:
    void CheckCollisionWithFood() {
        if (snake.body.front() == food.position) {
            snake.addSegment = true;
            food.position = food.GenerateRandomPosition(snake.bodySet);
            highScore = max(++score, highScore);
        }
    }

    void CheckCollisionWithEdges() {
        Pair head = snake.body.front();
        if (head.x < 0 || head.x >= CELL_COUNT || head.y < 0 || head.y >= CELL_COUNT) {
            GameOver();
        }
    }

    void CheckCollisionWithBody() {
        Pair head = snake.body.front();
        for (size_t i = 1; i < snake.body.size(); i++) {
            if (head == snake.body[i]) {
                GameOver();
            }
        }
    }

    void GameOver() {
        snake.Reset();
        food.position = food.GenerateRandomPosition(snake.bodySet);
        running = false;
        score = 0;
    }
};

// Main entry point
int main() {
    constexpr int sideSize = CELL_SIZE * CELL_COUNT;
    const int frameRate = 60;
    const double interval = 0.2;

    InitWindow(2 * OFFSET + sideSize, 2 * OFFSET + sideSize, "Snake");
    SetTargetFPS(frameRate);

    Game game;

    while (!WindowShouldClose()) {
        BeginDrawing();

        Pair nextDirection = game.snake.direction;

        if (IsKeyPressed(KEY_UP)    && game.snake.direction != DOWN)  { nextDirection = UP;    game.running = true; }
        if (IsKeyPressed(KEY_DOWN)  && game.snake.direction != UP)    { nextDirection = DOWN;  game.running = true; }
        if (IsKeyPressed(KEY_LEFT)  && game.snake.direction != RIGHT) { nextDirection = LEFT;  game.running = true; }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction != LEFT)  { nextDirection = RIGHT; game.running = true; }

        if (EventTriggered(interval)) {
            game.snake.direction = nextDirection;
            game.Update();
        }

        // Draw background
        ClearBackground(GREEN);
        DrawRectangleLinesEx(Rectangle{(float)OFFSET - 5, (float)OFFSET - 5,
            (float)(CELL_SIZE * CELL_COUNT + 10), (float)(CELL_SIZE * CELL_COUNT + 10)}, 5, DARK_GREEN);

        DrawText("Snake", OFFSET - 5, 20, 40, DARK_GREEN);
        DrawText(TextFormat("Score: %d", game.score), OFFSET - 5 + 300, 35, 20, DARK_GREEN);
        DrawText(TextFormat("High Score: %d", game.highScore), OFFSET - 5 + 600, 35, 20, DARK_GREEN);

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
