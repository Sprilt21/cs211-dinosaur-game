#pragma once

#include <ge211.hxx>
#include "player.hxx"

struct Model
{
public:
    Model();

    void start_game();
    void on_frame(double dt);
    bool is_game_over() const;
    void set_game_over();
    void player_jump();
    Player get_player() const;
    std::vector<Baddie> const& get_baddies() const;

    ge211::Dims<int> scene_dims;
    int floor;

    int score;
    int hiscore;

    ge211::Random_source<int> pause;
    std::vector<int> pauses;
private:


    //config


    ge211::Dims<double> player_dims;
    ge211::Posn<double> player_pos;
    double player_velocity;

    double baddie_velocity;
    std::vector<ge211::Dims<double>> baddies_dims;
    std::vector<ge211::Posn<double>> baddies_pos;

    Player player;
    std::vector<Baddie> baddies;

};
