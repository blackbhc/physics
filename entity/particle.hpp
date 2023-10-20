// This header define a particle class: a point mass in classical mechanics

#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_
#include "../coordinate/flat.hpp"
#include "../math_concept/basic.hpp"
namespace entity {
template < typename T > class particle
{
private:
    T                          mass;
    coordinate::cartesian< T > coordinate{ 3 };  // 3D cartesian coordinate
    // the position, velocity and acceleration of the particle, w.r.t. the visual absolute
    // coordinate frame
    math_concept::vector< T > position{ 3 };
    math_concept::vector< T > velocity{ 3 };
    math_concept::vector< T > acceleration{ 3 };

public:
    // vebose constructor
    particle( T m = 1, T x = 0, T y = 0, T z = 0, T vx = 0, T vy = 0, T vz = 0, T ax = 0, T ay = 0,
              T az = 0 )
    {
        mass              = m;
        position[ 0 ]     = x;
        position[ 1 ]     = y;
        position[ 2 ]     = z;
        velocity[ 0 ]     = vx;
        velocity[ 1 ]     = vy;
        velocity[ 2 ]     = vz;
        acceleration[ 0 ] = ax;
        acceleration[ 1 ] = ay;
        acceleration[ 2 ] = az;
    }
    // copy constructor
    particle( const particle& p ) = default;

    inline T& get_mass( void ) const
    {
        return mass;
    }
    inline math_concept::vector< T > get_coordinates( void ) const
    {
        return position;
    }
    inline math_concept::vector< T > get_velocity( void ) const
    {
        return velocity;
    }
    inline math_concept::vector< T > get_acceleration( void ) const
    {
        return acceleration;
    }
    inline T get_position_comp( unsigned int i ) const
    {
        assert( i < 3 );
        return position[ i ] * coordinate[ i ];
    }
    inline T get_velocity_comp( unsigned int i ) const
    {
        assert( i < 3 );
        return velocity[ i ] * coordinate[ i ];
    }
    inline T get_acceleration_comp( unsigned int i ) const
    {
        assert( i < 3 );
        return acceleration[ i ] * coordinate[ i ];
    }
    inline math_concept::vector< T > net_force( void ) const
    {
        return mass * acceleration;
        /* return acceleration * mass; */
    }
};
}  // namespace entity
#endif
