libhep
======

The current standard in particle physics for data analysis is ROOT, a feature-rich C++ library which attempts to
also provide a runtime environment powered by the CINT command-line interpreter (which attempts to approximate,
but does not (and is not intended to) fully conform to, the ANSI C++ standard). Unfortunately this makes using ROOT as a simple
library incredibly awkward and error-prone, usually in ways that are difficult to diagnose.

This library attempts to provide as many features in one place as ROOT does, but as a pure library. Also recognizing physicists'
inherent lack of...software development finesse, I try to rely on already-existing open-source libraries whenever possible.

At the moment, I plan on including:

* gsl: the GNU Scientific Library for various mathematical operations on data (fitting, statistics...)
* mathgl: for data visualization
* boost: for development tools like serialization

Some more particle physics-specific features are being written mostly from scratch:

* Data: high energy physics data describes "events" which are the collection of particles and their subsequent decays
produced by collisions; we attempt to provide an intuitive way to handle this sort of data.
* Mathematical constructs: presently only an implementation of a LorentzVector complete with coordinate transformations.
More if any show up, but other cases likely will already exist in external libraries.

Whenever possible, attempts will be made to provide an interface to external libraries tailored for HEP applications,
rather than simply telling the user to go find a feature somewhere else.

(readme last updated: Nov 16 2013)
