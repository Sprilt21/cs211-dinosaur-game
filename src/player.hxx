#pragma once

#include <ge211.hxx>
#include "baddie.hxx"
class Player {
public:
    Player(ge211::Posn<double> const& starting_position,
           ge211::Dims<double> const& dims,
           double const& velocity,
           int floor);

    ge211::Posn<double> const& get_pos() {
        return position;
    }
    double const& get_vel() {
        return velocity;
    }

    bool const& is_living() {
        return living;
    }

    void reset_position();
    virtual void update(double dt);
    virtual bool is_touching(Baddie const& baddie) const;
    virtual bool is_grounded()  const;
    virtual void jump();
    bool living;
private:

    double velocity;
    double start_vel;
    ge211::Dims<double> dims;
    ge211::Posn<double> position;

    bool isJumping;

    unsigned int floor;

};