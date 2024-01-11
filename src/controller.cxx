#include "controller.hxx"
Controller::Controller()
        : model_(),
          view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void Controller::on_frame(double dt) {
    model_.on_frame(dt);
}

void
Controller::on_key_down(ge211::Key key)
{
    if (key == ge211::Key::up() || key == ge211::Key::code(' ')) {

        if (!model_.is_game_over() && model_.get_player().living) {
            model_.player_jump();
        }
        else {
            model_.start_game();
        }
    }
}