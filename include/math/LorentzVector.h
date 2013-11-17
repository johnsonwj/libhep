/*
 * =====================================================================================
 *
 *       Filename:  LorentzVector.h
 *
 *    Description:  Defines the LorentzVector class (which is to say, it implements
 *                  a four-vector which transforms "properly" under Lorentz
 *                  transformations) and the CoordinateSystem enum which describes four
 *                  common coordinate systems used in high energy physics: standard
 *                  Cartesian coordinates (t-x-y-z), spherical coordinates 
 *                  (t-r-phi-theta), cylindrical coordinates (t-s-phi-z), and "collider"
 *                  coordinates common to high energy collider experiments (t-s-phi-eta)
 *                  (where eta = pseudorapidity = -log tan (theta/2))
 *
 *        Version:  1.0
 *        Created:  08/08/2013 03:01:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  William Johnson (williamj), bromayn@uw.edu
 *   Organization:  Dept. of Physics
 *
 * =====================================================================================
 */

namespace hep {
    namespace math {
        enum CoordinateSystem {
            // t, x, y, z, eta: (-inf, inf)
            // r, s: [0, inf)
            // phi: [0, 2pi)
            // theta: [0, pi]
            Cartesian,       // t x y z
            Spherical,       // t r phi theta
            Cylindrical,     // t s phi z
            Collider         // t s phi eta (or for momenta, E pT phi eta)
        };

        class LorentzVector {
            public:
                // initialize all coordinates to zero in default (Cartesian) coordinate system
                LorentzVector();
                // initialize coordinates in default (Cartesian) coordinate system
                LorentzVector( double, double, double, double );
                LorentzVector( double* );
                // set coordinate system but initialize all coords to zero
                LorentzVector( CoordinateSystem );
                // set coordinate system and initialize coordinates
                LorentzVector( CoordinateSystem, double, double, double, double );
                LorentzVector( CoordinateSystem, double* );

                // get a component
                double At( unsigned int );
                double operator[]( unsigned int );

                CoordinateSystem GetCoordinateSystem();

                // get the magnitude of the three spatial components
                double Mag3();

                // get the magnitude of the four-vector, under the Minkowski metric
                double Mag();

                // set the components
                void SetComponents( const double, const double, const double, const double );
                void SetComponents( const double* );
                void SetComponents( LorentzVector );
                void SetComponents(); // zero vector

                void SetComponent( unsigned int, const double );

                // standard operations
                LorentzVector operator+( LorentzVector );
                LorentzVector operator-( LorentzVector );

                // inner product between two Lorentz vectors, under the Minkowski metric
                double operator*( LorentzVector );

                double DeltaPhi( LorentzVector );
                double DeltaR( LorentzVector );

                // get the coordinates as an array
                operator double*();

                // convert to a new coordinate system
                void ConvertTo( CoordinateSystem );

                static LorentzVector Convert( LorentzVector, CoordinateSystem );

                static LorentzVector CarToSph( LorentzVector );
                static LorentzVector CarToCyl( LorentzVector );
                static LorentzVector CarToCol( LorentzVector );

                static LorentzVector SphToCar( LorentzVector );
                static LorentzVector SphToCyl( LorentzVector );
                static LorentzVector SphToCol( LorentzVector );

                static LorentzVector CylToCar( LorentzVector );
                static LorentzVector CylToSph( LorentzVector );
                static LorentzVector CylToCol( LorentzVector );

                static LorentzVector ColToCar( LorentzVector );
                static LorentzVector ColToSph( LorentzVector );
                static LorentzVector ColToCyl( LorentzVector );

            private:
                static const int DIM = 4;
                static const CoordinateSystem DEFAULT_COORDS = Cartesian;
                static const double ZERO_VECTOR[DIM];

                double components[DIM];
                CoordinateSystem coords;
        };
    }
}
