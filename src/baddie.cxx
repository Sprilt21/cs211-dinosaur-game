#include "baddie.hxx"
#include <string>

Baddie::Baddie(std::string const& fname,
               ge211::Posn<double> const& position,
               ge211::Dims<double> const& dims,
               double velocity)
    :
    sprite(ge211::Image_sprite(fname)),
    position(position),
    dims(dims),
    velocity(velocity),

    starting_pos(position.x)

    {
}

void Baddie::update(double dt) {
    //change position x
    position.x -= velocity * 2 * dt;
    //increase velocity
    velocity += dt * 2;
}

bool Baddie::hits_wall()
{
    //check if x position is less than the 0 x coordinate - dimension width
    return position.x <= -dims.width;
}

void Baddie::reset_pos() {
    //reset starting position
    position.x = starting_pos;
}

void Baddie::reset_velocity(double init) {
    //reset velocity to initial velocity
    velocity = init;
}