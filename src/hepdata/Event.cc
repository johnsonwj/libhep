/*
 * =====================================================================================
 *
 *       Filename:  Event.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/10/2013 07:10:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  William Johnson (williamj), bromayn@uw.edu
 *   Organization:  Dept. of Physics
 *
 * =====================================================================================
 */

namespace Data {
    Event::Event() {}
    
    Event::Event( vector<Record> recs ) {
        for ( size_t i = 0; i < recs.size(); i++ ) {
            my_records.push_back( recs.at(i) );
        }
    }

    Event::Event( unsigned int nrecords, Record* records ) {
        for ( size_t i = 0; i < nrecords; i++ ) {
            my_records.push_back( records[i] );
        }
    }

    Event::Event( Record r ) {
        my_records.push_back( r );
    }

    T Event::GetData( string n ) {
        for ( size_t i = 0; i < recs.size(); i++ ) {
            T temp = my_records.at(i);
            if ( temp.GetName() == n )
                return temp
        }

        return 0;
    }
}
