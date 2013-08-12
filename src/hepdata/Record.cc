/*
 * =====================================================================================
 *
 *       Filename:  Record.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/10/2013 07:04:33 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  William Johnson (williamj), bromayn@uw.edu
 *   Organization:  Dept. of Physics
 *
 * =====================================================================================
 */

namespace Data {
    Record::Record( string n ) {
        name = n;
        data = 0;
    }

    Record::Record( string n, T d ) {
        name = n;
        data = &d;
    }

    T Record::GetData() { if ( data ) return *data; else return 0; }
    void Record::SetData( T d ) { data = &d };

    string Record::GetName() { return name; }
    void SetName( string n ) { name = n; }

    Record::operator T() { return GetData() };
}
