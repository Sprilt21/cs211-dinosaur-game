#include "model.hxx"
#include <catch.hxx>
#include <iostream>

TEST_CASE("example test movement")
{
    Model g;

    g.start_game();
    for (int& pause : g.pauses) {
        pause = 99999;
    }
    //check that game starts correctly
    CHECK(g.get_player().living);
    CHECK(g.get_player().is_grounded());

    //check that player comes down after jumping
    g.player_jump();
    g.on_frame(0.5);
    CHECK_FALSE(g.get_player().is_grounded());
    int i = 0;
    while (i < 200 or !g.get_player().is_grounded()) {
        g.on_frame(.5);
        i++;
    }
    std::cout << g.get_player().get_pos();
    CHECK_FALSE(g.is_game_over());
    CHECK(g.get_player().is_grounded());

}

TEST_CASE("baddies generated properly") {
    Model m;

    m.start_game();
    for (int& pause : m.pauses) {
        pause = 0;
    }
    CHECK(m.get_player().living);
    //check that baddies spawn at x > screen_dims
    for (auto baddie : m.get_baddies()) {
        CHECK(baddie.get_pos().x >= m.scene_dims.width - 100);
    }
    std::vector<ge211::Posn<double>> posses;
    std::vector<double> vels;
    for (auto baddie : m.get_baddies()) {
        posses.push_back(baddie.get_pos());
        vels.push_back(baddie.get_velocity());
    }
    for (int i = 0; i < 10; i++) {
        m.on_frame(0.5);
    }
    int i = 0;
    for (auto baddie : m.get_baddies()) {
        CHECK(baddie.get_pos() != posses[i]);
        CHECK(baddie.get_velocity() > vels[i]);
        i++;
    }


}

TEST_CASE("collision")
{
    //set baddie position not colliding, check
    Model m;
    m.start_game();
    for (int& pause : m.pauses) {
        pause = 0;
    }

    for (int i = 0; i < 9; i++) {
        m.on_frame(0.5);
        CHECK_FALSE(m.is_game_over());
    }

    //player collides with the baddies;
    m.on_frame(0.5);

    CHECK(m.is_game_over());

}

TEST_CASE("game over")
{
    Model m;

    m.start_game();
    for (int& pause : m.pauses) {
        pause = 0;
    }

    m.on_frame(0.5);
    m.set_game_over();

    ge211::Posn<double> player_pos = m.get_player().get_pos();
    std::vector<ge211::Posn<double>> baddie_posses;
    for (auto baddie : m.get_baddies()) {
        baddie_posses.push_back(baddie.get_pos());
    }

    m.on_frame(0.5);
    CHECK(player_pos == m.get_player().get_pos());
    int i = 0;
    for (auto baddie : m.get_baddies()) {
        CHECK(baddie.get_pos() == baddie_posses[i]);
        i++;
    }
}

TEST_CASE("counter")
{
    Model m;

    m.start_game();
    for (int& pause : m.pauses) {
        pause = 99999;
    }

    m.on_frame(0.5);
    CHECK(m.score == 1);
    //check if score updates correctly
    m.on_frame(0.5);
    CHECK(m.score == 2);

    int score = m.score;
    CHECK(score > 0);
    m.set_game_over();
    CHECK(m.hiscore == score);
    m.start_game();
    m.on_frame(0.5);
    CHECK(m.score == 1);
    m.set_game_over();
    CHECK_FALSE(m.hiscore != score);
}
