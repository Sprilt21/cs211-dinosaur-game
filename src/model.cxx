#include"model.hxx"

//Constructor
Model::Model()
    :
    scene_dims(1000, 600),
    floor(scene_dims.height * 0.9),
    score(0),
    hiscore(0),

    pause(0,300),
    player_dims(64,64),
    player_pos(20, floor - player_dims.height),
    player_velocity(-7),
    baddie_velocity(110),
    player(player_pos,
           player_dims,
           player_velocity,
           floor)
{
    //baddie type 1: mushroom
    ge211::Dims<double> dims_1 = {48, 48};
    baddies_dims.push_back(dims_1);
    ge211::Posn<double> pos_1 = {scene_dims.into<double>().width + 1000,
                                 floor - baddies_dims[0]
                                 .height};
    baddies_pos.push_back(pos_1);

    Baddie const& mushroom = Baddie("mushroom.png",
                                    baddies_pos[0],
                                    baddies_dims[0], baddie_velocity);
    baddies.push_back(mushroom);

    //baddie type 2: asteroid
    ge211::Dims<double> dims_2 = {48, 48};
    baddies_dims.push_back(dims_2);
    ge211::Posn<double> pos_2 = {scene_dims.into<double>().width + 500,
                                 floor - 2 * baddies_dims[1].height  - 40};
    baddies_pos.push_back(pos_2);

    Baddie const& asteroid = Baddie("asteroid.png",
                                    baddies_pos[1],
                                    baddies_dims[0], baddie_velocity);
    baddies.push_back(asteroid);

    ge211::Dims<double> dims_3 = {48, 96};
    baddies_dims.push_back(dims_3);
    ge211::Posn<double> pos_3 = {scene_dims.into<double>().width - 100,
                                 floor - baddies_dims[2].height};
    baddies_pos.push_back(pos_3);

    //baddie type 3: tree
    Baddie const& tree = Baddie("tree.png",
                                    baddies_pos[2],
                                    baddies_dims[2], baddie_velocity);
    baddies.push_back(tree);

    ge211::Dims<double> dims_4 = {48, 48};
    baddies_dims.push_back(dims_4);
    ge211::Posn<double> pos_4 = {scene_dims.into<double>().width,
                                 floor - baddies_dims[3].height};
    baddies_pos.push_back(pos_4);

    //baddie type 4: slime
    Baddie const& slime = Baddie("slime.png",
                                baddies_pos[3],
                                baddies_dims[3], baddie_velocity);
    baddies.push_back(slime);

}

//Public member functions

void
Model::start_game()
{
    //set player grounded, live = true
    player.reset_position();
    player.living = true;

    //set baddies offscreen
    for (auto& baddie : baddies) {
        baddie.reset_pos();
        baddie.reset_velocity(80);
        for (auto& timer : pauses) {
            timer = pause.next();
        }
    }

    pauses.push_back(pause.next());
    pauses.push_back(pause.next());
    pauses.push_back(pause.next());
    pauses.push_back(pause.next());
    pause(0,300);

    //reset counter to 0 but keep high score
    score = 0;

}

void
Model::on_frame(double dt)
{
    //only update frame if player is living
    if (!player.living) {
        return;
    } else {
        //check if game is over (checks for collisions)
        if (is_game_over()) {
            set_game_over();
        }
        else {
            int i = 0;
            //update player state
            player.update(dt);
            //iterate through baddies in vector
            for (auto& baddie : baddies) {
                if (pauses[i] > 0) {
                    pauses[i]--;
                } else {
                    baddie.update(dt);
                    baddie_velocity += dt * 0.5;
                    if (baddie.hits_wall()) {
                        baddie.reset_pos();
                        pauses[i] = pause.next();
                    }
                }
                i++;
            }
            score++;
        }
    }
}

bool
Model::is_game_over() const
{
    //check for collisions
    for (auto baddie : baddies) {
        if (player.is_touching(baddie)) {
            return true;
        }
    }
    return false;
}

void
Model::set_game_over()
{
    //set player live = false
    player.living = false;
    //set high score
    if (score > hiscore) {
        hiscore = score;
    }
}

void
Model::player_jump()
{
    player.jump();
}

Player Model::get_player() const
{
    return player;
}

std::vector<Baddie> const& Model::get_baddies() const {
    return baddies;
}

