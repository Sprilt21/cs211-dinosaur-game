#include "view.hxx"

View::View(Model const& model)
        : model_(model),
        background({2000,800},ge211::Color(255,255,255)),
        floor({2000,800}, ge211::Color(10,200,0))

{
    //initialize player image sprites
    playerImages.push_back(ge211::Image_sprite("player_1.png"));
    playerImages.push_back(ge211::Image_sprite("player_2.png"));

    // Set up animation file names
    std::vector<std::string> bg_files;
    for (int i=0; i<20; i++) {
        std::string filename = std::to_string(i) += ".png";
        bg_files.push_back(filename);
    }

    // create and save image sprites
    for (std::string filename : bg_files) {
        bgs.push_back(ge211::sprites::Image_sprite(filename));
    }

}

void
View::draw(ge211::Sprite_set& set)
{

    //add player sprite in initial player sprite position
    //for baddie in baddies vector:
    //draw baddie sprite
    set.add_sprite(background, {0,0}, 0);
    set.add_sprite(bgs[currIndex/6 % 20], {0,0}, 1, transform);
    set.add_sprite(floor,
                   {0,model_.floor}, 2);
    set.add_sprite(playerImages[currIndex/6 % 2],model_.get_player()
                                                        .get_pos().into<int>
                                                                (),300,
                                                                transform);
    for (auto& baddie : model_.get_baddies()) {
        set.add_sprite(baddie.get_sprite(),
                       baddie.get_pos().into<int>(),
                       150, transform_baddie);
    }

    if (!model_.is_game_over()) {

        if (model_.get_player().living) {
            currIndex++;
        }
    } else {
        //create game over message
        ge211::Color textColor(0,0,0);
        ge211::Text_sprite::Builder gameover_builder(font);
        gameover_builder.color(textColor);
        std::string text = "Game Over";
        gameover_builder.message(text);

        gameover.reconfigure(gameover_builder);
        set.add_sprite(gameover, {model_.scene_dims.width*3/5, 30}, 600);

    }
    //create text sprite for displaying score and high score
    ge211::Color textColor(0,0,0);
    ge211::Text_sprite::Builder score_builder(font);
    score_builder.color(textColor);
    std::string text = "Score " + std::to_string(model_.score)
            + "  High Score " + std::to_string(model_.hiscore);
    score_builder.message(text);

    score.reconfigure(score_builder);

    set.add_sprite(score, {30,30}, 600);


}