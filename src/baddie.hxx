#include <ge211.hxx>

class Baddie {
public:
    Baddie(std::string const& fname,
           ge211::Posn<double> const& position,
           ge211::Dims<double> const& dims,
           double velocity);


    ge211::Dims<double> get_dims() const {
        return dims;
    }

    ge211::Posn<double> get_pos() const {
        return position;
    }
    ge211::Image_sprite const& get_sprite() const {
        return sprite;
    }
    double const& get_velocity() const {
        return velocity;
    }
    virtual void update(double dt);
    virtual bool hits_wall();
    virtual void reset_pos();
    virtual void reset_velocity(double init);

private:
    ge211::Image_sprite sprite;
    ge211::Posn<double> position;
    ge211::Dims<double> dims;
    double velocity;
    double starting_pos;

};