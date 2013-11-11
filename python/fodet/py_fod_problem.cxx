#include <py_fod_problem.hxx>
#include <gp_atoms.hxx>
#include <cstring>
#include <fstream>

using namespace boost::python;

	FOD_Problem::FOD_Problem( std::string domain, std::string instance ) {
		m_parsing_time = 0.0f;
		m_model = new aptk::FOD_Problem( domain, instance );

	}

	FOD_Problem::~FOD_Problem() {
	}

	void
	FOD_Problem::add_atom( std::string name ) {
		m_model->new_atom( name );
	}

	void
	FOD_Problem::add_action( std::string name ) {
		m_model->new_action( name );
	}	

	void
	FOD_Problem::add_precondition( int index, boost::python::list& lits ) {
		aptk::FOD_Problem::Action& action = *(m_model->actions[index]);
		for ( int i = 0; i < len(lits); i++ ) {
			boost::python::tuple li = extract< tuple >( lits[i] );
			action.precondition.add( aptk::mkLit( extract<int>(li[0]), extract<bool>(li[1]) ) );
		}	
		instance()->max_precondition_size = std::max( instance()->max_precondition_size, action.precondition.size() );
	}

	void
	FOD_Problem::add_cond_effect( int index, boost::python::list& cond_lits, boost::python::list& eff_lits ) {
		aptk::FOD_Problem::Action& action = *(m_model->actions[index]);
		aptk::FOD_Problem::Effect eff;
		for ( int i = 0; i < len(cond_lits); i++ ) {
			boost::python::tuple li = extract< tuple >( cond_lits[i] );
			eff.condition.add( aptk::mkLit( extract<int>(li[0]), extract<bool>(li[1]) ) );
		}	
		for ( int i = 0; i < len(eff_lits); i++ ) {
			boost::python::tuple li = extract< tuple >( eff_lits[i] );
			eff.effect.add( aptk::mkLit( extract<int>(li[0]), extract<bool>(li[1]) ) );
		}	
		action.effects.push_back( eff );
	}

	void
	FOD_Problem::add_effect( int index, boost::python::list& lits ) {
		aptk::FOD_Problem::Action& action = *(m_model->actions[index]);
		aptk::FOD_Problem::Effect eff;
		for ( int i = 0; i < len(lits); i++ ) {
			boost::python::tuple li = extract< tuple >( lits[i] );
			eff.effect.add( aptk::mkLit( extract<int>(li[0]), extract<bool>(li[1]) ) );
		}	
		action.effects.push_back( eff );

	}

	void
	FOD_Problem::add_invariant( boost::python::list& lits ) {
		aptk::DNF_Clause invariant;
		for ( int i = 0; i < len(lits); i++ ) {
			boost::python::tuple li = extract< tuple >( lits[i] );
			invariant.add( aptk::mkLit( extract<int>(li[0]), extract<bool>(li[1]) ) );
			instance()->add_invariant( invariant );
		}
	}

	void
	FOD_Problem::set_init( boost::python::list& lits ) {
		for ( int i = 0; i < len(lits); i++ ) {
			boost::python::tuple li = extract< tuple >( lits[i] );
			instance()->init.add( aptk::mkLit( extract<int>(li[0]), extract<bool>(li[1]) ) );
		}
		// Complete negation
		for ( aptk::Atom p = 0; p < (int)instance()->n_atoms(); p++ ) {
			aptk::Lit l = aptk::mkLit( p, false );
			if ( !instance()->init.entails( l ) )
				instance()->init.add( ~l );
			l = aptk::mkLit( p, true );
			if ( !instance()->init.entails(~l) )
				instance()->init.add( l );
		}
	}

	void
	FOD_Problem::set_goal( boost::python::list& lits ) {
		for ( int i = 0; i < len(lits); i++ ) {
			boost::python::tuple li = extract< tuple >( lits[i] );
			instance()->goal.add( aptk::mkLit( extract<int>(li[0]), extract<bool>(li[1]) ) );
		}
	}

	void
	FOD_Problem::print_action( int index ) {
		instance()->actions[index]->print( std::cout, *instance() );
	}
	
	void
	FOD_Problem::write_ground_pddl( std::string domain, std::string problem ) {
		/*
		std::ofstream domain_stream( domain.c_str() );
		m_inst->write_domain( domain_stream );
		std::ofstream problem_stream( problem.c_str() );
		m_inst->write_problem( problem_stream );
		*/
	}

/*
BOOST_PYTHON_MODULE(  )
{
	class_<FOD_Problem>("FOD_Problem", init< std::string, std::string >())
		.def( "add_atom", &FOD_Problem::add_atom )
		.def( "add_action", &FOD_Problem::add_action )
		.def( "add_invariant", &FOD_Problem::add_invariant )
		.def( "num_atoms", &FOD_Problem::n_atoms )
		.def( "num_actions", &FOD_Problem::n_actions )
		.def( "get_atom_name", &FOD_Problem::get_atom_name )
		.def( "add_precondition", &FOD_Problem::add_precondition )
		.def( "add_effect", &FOD_Problem::add_effect )
		.def( "set_init", &FOD_Problem::set_init )
		.def( "set_goal", &FOD_Problem::set_goal )
		.def( "write_ground_pddl", &FOD_Problem::write_ground_pddl )
		.def( "print_action", &FOD_Problem::print_action )
		.def_readwrite( "parsing_time", &FOD_Problem::m_parsing_time )
	;
}
*/
