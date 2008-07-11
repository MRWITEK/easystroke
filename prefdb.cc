#include "prefdb.h"
#include "main.h"

#include <fstream>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/export.hpp>

#include <X11/Xlib.h>

const double pref_p_default = 0.5;
const ButtonInfo pref_button_default = { Button2, 0 };
const int pref_radius_default = 16;

PrefDB::PrefDB() :
	filename(config_dir+"preferences"),
	p(pref_p_default),
	button(pref_button_default),
	trace(TraceShape),
	advanced_ignore(false),
	radius(pref_radius_default),
	ignore_grab(false),
	timing_workaround(false)
{}

bool PrefDB::write() const {
	try {
		std::ofstream ofs(filename.c_str());
		boost::archive::text_oarchive oa(ofs);
		const PrefDB *me = this;
		oa << *me;
		if (verbosity >= 2)
			std::cout << "Saved preferences." << std::endl;
		return true;
	} catch (...) {
		std::cout << "Error: Couldn't save preferences." << std::endl;
		return false;
	}
}

void PrefDB::read() {
	try {
		std::ifstream ifs(filename.c_str(), std::ios::binary);
		boost::archive::text_iarchive ia(ifs);
		ia >> *this;
		if (verbosity >= 2)
			std::cout << "Loaded preferences." << std::endl;
	} catch (...) {
		std::cout << "Error: Couldn't read preferences." << std::endl;
	}
}

PrefDB& prefs() {
	static PrefDB prefs_;
	return prefs_;
}

