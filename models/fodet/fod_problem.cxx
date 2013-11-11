#include <fod_problem.hxx>
#include <iostream>

namespace aptk {

	FOD_Problem::~FOD_Problem() {
	}

	FOD_Problem::Atom&
	FOD_Problem::new_atom( const std::string& name ) {
		Atom*	a = new Atom( name, atoms.size() );
		atoms.push_back( a );

		Clause::set_num_lits( 2*(atoms.size()) );
		init.resize_bitmap();
		goal.resize_bitmap();
		return *a;
	}
		
	FOD_Problem::Action&
	FOD_Problem::new_action( const std::string& name ) {
		Action* a = new Action( name, actions.size() );
		actions.push_back( a );

		return *a;
	}

	void
	FOD_Problem::add_invariant( const Clause& inv ) {
		invariants.push_back( inv );
	}

	void
	FOD_Problem::Action::print( std::ostream& os, const FOD_Problem& model ) const {
		os << name << std::endl;
		os << "Precondition: ";
		precondition.write( os, model );
		os << std::endl;
		os << "Effects: " << std::endl;
		for ( const Effect& eff : effect ) {
			eff.condition.write( os, model );
			os << " -> " << std::endl;
			os << "\t";
			eff.effect.write( os, model );
			os << std::endl;
		}
		os << std::endl;
		
	}
}
