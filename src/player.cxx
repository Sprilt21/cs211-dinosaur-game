#include "player.hxx"

Player::Player(ge211::Posn<double> const& starting_position,
               ge211::Dims<double> const& dims,
               double const& velocity,
               int floor)
    :
    living(false),
    velocity(velocity),

    start_vel(velocity),
    dims(dims),
    position(starting_position),
    isJumping(false),
    floor(floor)
    {

}

void
Player::update(double dt)
{
    if (isJumping) {
        //max jump height
        if (position.y <= 200) {
            velocity *= -1;
        }
        position.y += velocity;
    }

    start_vel -= dt/100;

    if (is_grounded()) {
        reset_position();
    }
}

void Player::reset_position()
{
    isJumping = false;
    velocity = start_vel;
    position.y = floor - dims.height;
}

bool Player::is_touching(Baddie const& baddie) const
{
    ge211::Posn<double> baddiePos = baddie.get_pos();
    ge211::Dims<double> baddieDims = baddie.get_dims();

    //case 1: RHS of player is to the left of LHS of obstacle
    if (position.x + dims.width < baddiePos.x + 5) {
        return false;
    }
    //case 2: LHS of player is to the right of RHS of obstacle
    else if (position.x > baddiePos.x + baddieDims.width - 5) {
        return false;
    }
    //case 3: bottom of player is above top of obstacle
    else if (position.y + dims.height < baddiePos.y + 5) {
        return false;
    }
    //case 4: top of player is below the bottom of obstacle
    else if (position.y > baddiePos.y + baddieDims.height - 5) {
        return false;
    }
    return true;
}
bool Player::is_grounded() const {
    bool grounded = position.y + dims.height >= floor;
    return grounded;
}

void Player::jump() {
    if (is_grounded()) {
        isJumping = true;
    }
}