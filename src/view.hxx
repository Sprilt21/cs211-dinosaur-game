#pragma once

#include "model.hxx"

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

private:
    Model const& model_;
    std::vector<ge211::Image_sprite> playerImages;
    int currIndex = 0;
    ge211::Rectangle_sprite background;
    ge211::Rectangle_sprite const floor;
    ge211::Font font{"ARCADECLASSIC.ttf", 30};
    ge211::Text_sprite score;
    ge211::Text_sprite gameover;
    std::vector<ge211::Image_sprite> bgs;
    ge211::Transform const transform{ge211::Transform().scale(2)};

    ge211::Transform const transform_baddie{ge211::Transform().scale(1.5)};
};
