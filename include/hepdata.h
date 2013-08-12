/*
 * =====================================================================================
 *
 *       Filename:  hepdata.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/09/2013 02:03:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  William Johnson (williamj), bromayn@uw.edu
 *   Organization:  Dept. of Physics
 *
 * =====================================================================================
 */
#include <string>

namespace Data {
    template <class T> class Record {
        public:
            Record( string );
            Record( string, T );

            T GetData();
            void SetData( T );
            
            string GetName();
            void SetName( string );

            operator T();

        private:
            string name;
            T* data;
    };

    class Dataset;

    class Event {
        public:
            Event();
            Event( vector<Record> );
            Event( unsigned int, Record* );
            Event( Record );

            T GetData( string );
            void SetData( string, T );

            template <class T> void AddRecord( Record<T> );
            bool RemoveRecord( string );

            friend class Dataset;

        private:
            vector<Record> my_records;
            unsigned int evtnum = -1;
    };

    class Dataset {
        public:
            Dataset();
            Dataset( vector<Event> events );
            Dataset( unsigned int nevents, Event* events );

            unsigned int Size();

            void AddEvent( Event );
            Event GetEvent( unsigned int );
            Event* NewEvent();

            Event Next();
    };
}
