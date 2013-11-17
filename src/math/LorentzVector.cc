/*
 * =====================================================================================
 *
 *       Filename:  LorentzVector.cc
 *
 *    Description:  Implements a Lorentz vector, complete with changeable coordinate
 *    system
 *
 *        Version:  1.0
 *        Created:  08/08/2013 06:00:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  William Johnson (williamj), bromayn@uw.edu
 *   Organization:  Dept. of Physics
 *
 * =====================================================================================
 */

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

#include <math/LorentzVector.h>

namespace hep {
    namespace math {

        const double LorentzVector::ZERO_VECTOR[DIM] = { 0., 0., 0., 0. };

        LorentzVector::LorentzVector() {
            coords = DEFAULT_COORDS;
            SetComponents( ZERO_VECTOR );
        }
        LorentzVector::LorentzVector( CoordinateSystem c ) {
            coords = c;
            SetComponents( ZERO_VECTOR );
        }

        LorentzVector::LorentzVector( CoordinateSystem c, double x0, double x1, double x2, double x3 ) {
            coords = c;
            SetComponents( x0, x1, x2, x3 );
        }

        LorentzVector::LorentzVector( CoordinateSystem c, double* x ) {
            coords = c;
            SetComponents( x );
        }

        LorentzVector::LorentzVector( double x0, double x1, double x2, double x3 ) {
            coords = DEFAULT_COORDS;
            SetComponents( x0, x1, x2, x3 );
        }

        LorentzVector::LorentzVector( double* x ) {
            coords = DEFAULT_COORDS;
            SetComponents( x );
        }

        double LorentzVector::At( unsigned int i ) {
            if ( ! i < DIM )
                throw std::out_of_range( "Index out of range; coordinates are 0,1,2,3" );

            return components[i];
        }

        double LorentzVector::operator[]( unsigned int i ) {
            return At(i);
        }

        CoordinateSystem LorentzVector::GetCoordinateSystem() {
            return coords;
        }

        double LorentzVector::Mag3() {
            return sqrt( pow( At(1), 2 ) + pow( At(2), 2 ) + pow( At(3), 2 ) );
        }

        double LorentzVector::Mag() {
            return sqrt( pow( At(0), 2 ) - pow( Mag3(), 2 ) );
        }

        void LorentzVector::SetComponents( const double x0, const double x1, const double x2, const double x3 ) {
            double x[DIM] = { x0, x1, x2, x3 };
            SetComponents( x );
        }

        void LorentzVector::SetComponents( const double* x ) {
            for ( int i = 0; i < DIM; i++ )
                components[i] = x[i];
        }

        void LorentzVector::SetComponent( unsigned int i, double x_i ) {
            if ( ! i < DIM )
                throw std::out_of_range( "Index out of range; coordinates are 0,1,2,3" );

            components[i] = x_i;
        }

        LorentzVector LorentzVector::operator+( LorentzVector other ) {
            double xnew[DIM];

            for ( int i = 0; i < DIM; i++ )
                xnew[i] = At(i) + other.At(i);

            return LorentzVector( coords, xnew );
        }

        LorentzVector LorentzVector::operator-( LorentzVector other ) {
            double xnew[DIM];

            for ( int i = 0; i < DIM; i++ )
                xnew[i] = At(i) - other.At(i);

            return LorentzVector( coords, xnew );
        }

        double LorentzVector::operator*( LorentzVector other ) {
            double product = At(0) * other.At(0);
            for ( int i = 1; i < DIM; i++ )
                product -= At(i) * other.At(i);

            return product;
        }

        double LorentzVector::DeltaPhi( LorentzVector other ) {
            LorentzVector this_col  = Convert( *this, Collider );
            LorentzVector other_col = Convert( other, Collider );

            double this_phi  =  this_col.At(2);
            double other_phi = other_col.At(2);

            if ( fabs( this_phi - other_phi ) > M_PI ) {
                if ( this_phi > M_PI )
                    this_phi -= 2*M_PI;
                else
                    other_phi -= 2*M_PI;
            }

            return fabs( this_phi - other_phi );
        }

        double LorentzVector::DeltaR( LorentzVector other ) {
            LorentzVector this_col  = Convert( *this, Collider );
            LorentzVector other_col = Convert( other, Collider );

            double deta = fabs( this_col.At(3) - other_col.At(3) );
            double dphi = DeltaPhi( other );

            return sqrt( pow(deta,2) + pow(dphi,2) );
        }

        LorentzVector::operator double*() {
            return components;
        }

        void LorentzVector::ConvertTo( CoordinateSystem newc ) {
            LorentzVector newv = Convert( *this, newc );

            SetComponents( newv );
            coords = newc;
        }

        LorentzVector LorentzVector::Convert( LorentzVector lv, CoordinateSystem newc ) {
            switch ( lv.coords ) {
                case Cartesian:
                    switch( newc ) {
                        case Spherical:
                            return CarToSph( lv );
                        case Cylindrical:
                            return CarToCyl( lv );
                        case Collider:
                            return CarToCol( lv );
                    }
                case Spherical:
                    switch( newc ) {
                        case Cartesian:
                            return SphToCar( lv );
                        case Cylindrical:
                            return SphToCyl( lv );
                        case Collider:
                            return SphToCol( lv );
                    }
                case Cylindrical:
                    switch( newc ) {
                        case Cartesian:
                            return CylToCar( lv );
                        case Spherical:
                            return CylToSph( lv );
                        case Collider:
                            return CylToCol( lv );
                    }
                case Collider:
                    switch( newc ) {
                        case Cartesian:
                            return ColToCar( lv );
                        case Spherical:
                            return ColToSph( lv );
                        case Cylindrical:
                            return ColToCyl( lv );
                    }
            }

            return lv;
        }

        LorentzVector LorentzVector::CarToSph( LorentzVector lv ) {
            double newx[DIM];
            newx[0] = lv.At(0);

            newx[1] = lv.Mag3();

            if ( lv.Mag3() > 0. ) {
                newx[2] = acos( lv.At(3) / lv.Mag3() );
            } else {
                newx[2] = 0.;
            }

            if ( lv.At(1) > 0. ) {
                newx[3] = atan2( lv.At(2), lv.At(1) );
            } else {
                newx[3] = 0.;
            }

            return LorentzVector( Spherical, newx );
        }

        LorentzVector LorentzVector::CarToCyl( LorentzVector lv ) {
            double newx[DIM];
            newx[0] = lv.At(0);

            newx[1] = sqrt( pow( lv.At(1), 2 ) + pow( lv.At(2), 2 ) );

            if ( newx[1] > 0. ) {
                newx[2] = atan2( lv.At(2), lv.At(1) );
            } else {
                newx[2] = 0.;
            }

            newx[3] = lv.At(3);

            return LorentzVector( Cylindrical, newx );
        }

        LorentzVector LorentzVector::CarToCol( LorentzVector lv ) {
            double newx[DIM];
            newx[0] = lv.At(0);

            newx[1] = sqrt( pow( lv.At(1), 2 ) + pow( lv.At(2), 2 ) );

            if ( newx[1] > 0. ) {
                newx[2] = atan2( lv.At(2), lv.At(1) );
            } else {
                newx[2] = 0.;
            }

            double theta = ( lv.Mag3() > 0. )
                ? acos( lv.At(3) / lv.Mag3() )
                : 0.;

            newx[3] = -log( tan( theta/2 ) );

            return LorentzVector( Collider, newx );
        }

        LorentzVector LorentzVector::SphToCar( LorentzVector lv ) {
            double newx[DIM];
            newx[0] = lv.At(0);

            newx[1] = lv.At(1) * cos(lv.At(2)) * cos(lv.At(3));
            newx[2] = lv.At(1) * cos(lv.At(2)) * sin(lv.At(3));
            newx[3] = lv.At(1) * sin(lv.At(2));

            return LorentzVector( Cartesian, newx );
        }

        LorentzVector LorentzVector::SphToCyl( LorentzVector lv ) {
            double* newx = (double*) CarToCyl( SphToCar( lv ) );
            return LorentzVector( Cylindrical, newx );
        }

        LorentzVector LorentzVector::SphToCol( LorentzVector lv) {
            double* newx = (double*) CarToCol( SphToCar( lv ) );
            return LorentzVector( Collider, newx );
        }

        LorentzVector LorentzVector::CylToCar( LorentzVector lv ) {
            double newx[DIM];
            newx[0] = lv.At(0);

            newx[1] = lv.At(1) * cos(lv.At(2));
            newx[2] = lv.At(1) * sin(lv.At(2));
            newx[3] = lv.At(3);

            return LorentzVector( Cartesian, newx );
        }

        LorentzVector LorentzVector::CylToSph( LorentzVector lv ) {
            double* newx = (double*) CarToSph( CylToCar( lv ) );
            return LorentzVector( Spherical, newx );
        }

        LorentzVector LorentzVector::CylToCol( LorentzVector lv ) {
            double* newx = (double*) CarToCol( CylToCar( lv ) );
            return LorentzVector( Collider, newx );
        }

        LorentzVector LorentzVector::ColToCar( LorentzVector lv ) {
            double* newx = (double*) SphToCar( ColToSph( lv ) );
            return LorentzVector( Cartesian, newx );
        }

        LorentzVector LorentzVector::ColToSph( LorentzVector lv ) {
            double newx[DIM];
            newx[0] = lv.At(0);

            double theta = 2 * atan( exp( -lv.At(2) ) );

            newx[1] = lv.At(1) / sin(theta);
            newx[2] = lv.At(2);
            newx[3] = theta;

            return LorentzVector( Spherical, newx );
        }

        LorentzVector LorentzVector::ColToCyl( LorentzVector lv ) {
            double* newx = (double*) SphToCyl( ColToSph( lv ) );
            return LorentzVector( Cartesian, newx );
        }
    }
}
