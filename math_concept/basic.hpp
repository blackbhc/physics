// This header define the basic concept in mathematics.
#ifndef _CALCULUS_HPP_
#define _CALCULUS_HPP_
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>

// dangerous macro, only for internal use
#define CHECK_LENGTH( v, this )                                                 \
    {                                                                           \
        if ( v.get_length() != this->length )                                   \
            throw( "The length of the vectors are not equal for operations." ); \
    }

namespace math_concept {
template < typename T > class vector
{
private:
    T*           data   = nullptr;
    unsigned int length = 0;

public:
    vector( unsigned int n = 3 )
    {
        length = n;
        data   = new T[ n ];
        memset( data, 0, n * sizeof( T ) );
    }  // the constructor

    ~vector()
    {
        if ( data != nullptr )
            delete[] data;
    };  // the destructor

    vector( const vector& v ) = default;  // the copy constructor

    vector( T array[], unsigned int n )  // the constructor with a array
    {
        length = n;
        data   = new T[ n ];
        memset( data, 0, n * sizeof( T ) );
        for ( unsigned int i = 0; i < n; ++i )
        {
            data[ i ] = array[ i ];
        }
    }

    unsigned int get_length() const
    {
        return length;
    }

    inline T* get_data() const
    {
        return data;
    }

    inline T& set( T value, unsigned int i )  // set the value of the i-th element
    {
        this->data[ i ] = value;
    }

    inline T& set( double array[], unsigned int n )  // set the value by a array
    {
        if ( n != this->length )
            throw( "The length of the array is not equal to the length of the vector." );
        for ( int i = 0; i < n; ++i )
        {
            this->data[ i ] = array[ i ];
        }
    }

    inline T get_norm( unsigned int ord ) const  // get the norm of the vector for ord-th norm
    {
        if ( ord == 0 )
            return ( T )this->length;

        T norm = 0;
        for ( unsigned int i = 0; i < this->length; ++i )
        {
            norm += pow( data[ i ], ord );
        }
        return ( T )pow( norm, 1.0 / ord );
    }

    inline vector< T >& normalize() const  // normalize the vector
    {
        T norm = this->get_norm( 2 );
        for ( unsigned int i = 0; i < this->length; ++i )
        {
            this->data[ i ] /= norm;
        }
    }

    inline vector< T > cross( vector< T > v ) const
    {
        if ( this->length != 3 || v.get_length() != 3 )
            throw( "The cross product is only defined for 3-dimensional vectors." );
        vector< T > result( 3 );
        for ( unsigned int i = 0; i < 3; ++i )
        {
            result[ i ] = this->data[ ( i + 1 ) % 3 ] * v[ ( i + 2 ) % 3 ]
                          - this->data[ ( i + 2 ) % 3 ] * v[ ( i + 1 ) % 3 ];
        }
        return result;
    }

    // operator overloading part
    inline T& operator[]( unsigned int i ) const
    {
        return data[ i ];
    }

    inline vector< T > operator=( vector& v ) const  // copy assignment operator
    {
        CHECK_LENGTH( v, this );
        for ( unsigned int i = 0; i < this->length; ++i )
        {
            this->data[ i ] = v[ i ];
        }
        return *this;
    }

    inline T operator*( vector& v ) const  // inner product
    {
        CHECK_LENGTH( v, this );
        T product = 0;
        for ( unsigned int i = 0; i < this->length; ++i )
        {
            product += this->data[ i ] * v[ i ];
        }
        return product;
    }

    inline vector< T > operator*( T v ) const  // scalar product
    {
        math_concept::vector< T > product = *this;
        for ( unsigned int i = 0; i < this->length; ++i )
        {
            product[ i ] *= v;
        }
        return product;
    }

    inline vector< T > operator+( vector& v ) const  // vector addition
    {
        CHECK_LENGTH( v, this );
        vector result( this->length );
        for ( unsigned int i = 0; i < this->length; ++i )
        {
            result[ i ] = this->data[ i ] + v[ i ];
        }
        return result;
    }

    inline vector< T > operator-( vector& v ) const  // vector subtraction
    {
        CHECK_LENGTH( v, this );
        vector< T > result( this->length );
        for ( unsigned int i = 0; i < this->length; ++i )
        {
            result[ i ] = this->data[ i ] - v[ i ];
        }
        return result;
    }


    inline vector< T >& operator*=( T& v )  // scalar product
    {
        for ( unsigned int i = 0; i < this->length; ++i )
        {
            this->data[ i ] *= v;
        }
        return this;
    }

    inline vector< T >& operator+=( vector& v )  // vector addition
    {
        CHECK_LENGTH( v, this );
        for ( unsigned int i = 0; i < this->length; ++i )
        {
            this->data[ i ] += v[ i ];
        }
        return this;
    }

    inline vector< T >& operator-=( vector& v )  // vector subtraction
    {
        CHECK_LENGTH( v, this );
        for ( unsigned int i = 0; i < this->length; ++i )
        {
            this->data[ i ] -= v[ i ];
        }
        return this;
    }

    // TODO: define a class for matrix, and define the matrix-vector, vector outer product, etc.
};

template < typename T > void print( math_concept::vector< T > v )
{
    printf( "The vector is: [" );
    for ( unsigned int i = 0; i < v.get_length(); ++i )
    {
        printf( "%lf\t", ( double )v[ i ] );
    }
    printf( "]\n" );
};

template < typename T >
vector< T > operator*( T v, vector< T > v1 )  // scalar product: for scalar first multiplication
{
    return v1 * v;
}

}  // namespace math_concept

#endif
