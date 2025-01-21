#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class GameState {
public:
    static GameState& getInstance() {
        static GameState instance;
        return instance;
    }

    int getScore() const {
        return score;
    }

    void setScore(int newScore) {
        score = newScore;
    }

    void incrementScore(int amount) {
        score += amount;
    }

    void increase_score_bonus_per_click(int amount) {
        score_bonus_per_click += amount;
    }

    int get_score_bonus_per_click() const {
        return score_bonus_per_click;
    }

    void increase_score_bonus_per_10_clicks(int amount) {
        score_bonus_per_10_clicks += amount;
    }

    int get_score_bonus_per_10_clicks() const {
        return score_bonus_per_10_clicks;
    }

    void increase_score_bonus_per_second(int amount) {
        score_bonus_per_second += amount;
    }

    int get_score_bonus_per_second() const {
        return score_bonus_per_second;
    }

private:
    GameState() : score(0) {}
    GameState(const GameState&) = delete;
    GameState& operator=(const GameState&) = delete;

    int score;
    int score_bonus_per_click;
    int score_bonus_per_10_clicks;
    int score_bonus_per_second;
};
