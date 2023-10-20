// This header define the classical coordinate system in the flat space: cartesian, cylindrical and
// spherical.

#ifndef _FLAT_HPP_
#define _FLAT_HPP_
#include "../math_concept/basic.hpp"
#include <vector>
namespace coordinate {
// a enum type to indicate the type of coordinate system
enum Type { Cartesian, Cylindrical, Spherical };
/* enum Orthonormal { Not, Yes }; */

template < typename T > class cartesian
{
public:
    cartesian( unsigned int dim = 3 )
    {
        assert( dim > 0 );
        this->dim = dim;
        // bases.resize( dim );
        for ( unsigned int i = 0; i < dim; ++i )
        {
            math_concept::vector< T > vec{ dim };
            bases.push_back( vec );
            bases[ i ][ i ] = 1;  // set the i-th element to 1, which coincides with the visual
                                  // absolute coordinate system
        }
    };
    cartesian( const cartesian& ) = default;  // the copy constructor
    ~cartesian()                  = default;  // the destructor

    cartesian& operator=( const cartesian& ) = default;  // the copy assignment operator
    math_concept::vector< T >& operator[]( unsigned int i ) const
    {
        assert( i <= dim );
        return bases[ i ];
    }
    // TODO: add a function to update the basis, which also check the orthogonality of the basis


private:
    unsigned int dim = 0;  // the dimension of the space
    std::vector< math_concept::vector< T > >
        bases;  // the basis of the space w.r.t. a visual absolute coordinate system
    // TODO: after implemant the matrix class, ues the matrix to represent the basis

    inline bool check_orthogonal() const
    {
        for ( unsigned int i = 0; i < dim; ++i )
        {
            for ( unsigned int j = i; j < dim; ++j )
            {
                if ( i == j && bases[ i ] * bases[ j ] != 1 )
                    return false;
                else if ( bases[ i ] * bases[ j ] != 0 )
                    return false;
            }
        }
        return true;
    }
};

}  // namespace coordinate
#endif
