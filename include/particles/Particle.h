/*
 * =====================================================================================
 *
 *       Filename:  Particle.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/16/2013 04:57:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  William Johnson (williamj), bromayn@uw.edu
 *   Organization:  Dept. of Physics
 *
 * =====================================================================================
 */

#include <utility>
#include <math/LorentzVector.h>

#include <boost/serialization/utility.hpp>

namespace hep {
    namespace particles {
        class Particle {
            private:
                hep::math::LorentzVector four_momentum;

                std::pair<Particle*,Particle*> children;
                Particle* parent;

                int pdg_id;

                friend class boost::serialization::access;
                template<class Archive>
                    void serialize(Archive& ar, const unsigned int version) {
                        ar & four_momentum;
                        ar & children;
                        ar & parent;
                        ar & pdg_id;
                    }

                Particle(hep::math::LorentzVector _fourp, std::pair<Particle*,Particle*> _kids, Particle* _parent, int _pdg) :
                    four_momentum(_fourp), children(_kids), parent(_parent), pdg_id(_pdg) {}

            protected:
                void set_parent(Particle*);

            public:
                hep::math::LorentzVector fourp() { return four_momentum; }
                double mass() { return four_momentum.Mag(); }
        }
    }
}
