#include "compare_mask.h"


compare_mask::compare_mask()
{

	signature s;
	s.type = STATE_TABLE_OG; s.og = GLONASS; s.mask = "<GG><MM><DD><HH>_G.og";
	v_sign.push_back(s);
	s.type = STATE_TABLE_OG; s.og = GPS; s.mask = "<GG><MM><DD><HH>_N.og";
	v_sign.push_back(s);
	s.type = STATE_TABLE_OG; s.og = GALILEO; s.mask = "<GG><MM><DD><HH>_L.og";
	v_sign.push_back(s);
	s.type = STATE_TABLE_OG; s.og = COMPASS; s.mask = "<GG><MM><DD><HH>_C.og";
	v_sign.push_back(s);

	s.type = STATE_TABLE_OG; s.og = GLONASS; s.mask = "ST_<V>_<R><G><E><B>_<GG><MM><DD><HH>.STG";
	v_sign.push_back(s);
	s.type = STATE_TABLE_OG; s.og = GPS; s.mask = "ST_<V>_<R><G><E><B>_<GG><MM><DD><HH>.STN";
	v_sign.push_back(s);
	s.type = STATE_TABLE_OG; s.og = GALILEO; s.mask = "ST_<V>_<R><G><E><B>_<GG><MM><DD><HH>.STL";
	v_sign.push_back(s);
	s.type = STATE_TABLE_OG; s.og = COMPASS; s.mask = "ST_<V>_<R><G><E><B>_<GG><MM><DD><HH>.STC";
	v_sign.push_back(s);

	s.type = ALMANAC; s.og = GLONASS; s.mask = "<NNNN><DDD>0.<YY>ag";
	v_sign.push_back(s);
	s.type = ALMANAC; s.og = GPS; s.mask = "<NNNN><DDD>0.<YY>an";
	v_sign.push_back(s);
	s.type = ALMANAC; s.og = GALILEO; s.mask = "<NNNN><DDD>0.<YY>al";
	v_sign.push_back(s);
	s.type = ALMANAC; s.og = COMPASS; s.mask = "<NNNN><DDD>0.<YY>ac";
	v_sign.push_back(s);

	s.type = RINEX; s.og = GLONASS; s.mask = "<NNNN><DDD>0.<YY>g";
	v_sign.push_back(s);
	s.type = RINEX; s.og = GPS; s.mask = "<NNNN><DDD>0.<YY>n";
	v_sign.push_back(s);
	s.type = RINEX; s.og = GALILEO; s.mask = "<NNNN><DDD>0.<YY>l";
	v_sign.push_back(s);
	s.type = RINEX; s.og = COMPASS; s.mask = "<NNNN><DDD>0.<YY>c";
	v_sign.push_back(s);

	s.type = RINEX; s.og = GLONASS; s.mask = "<NNNN><DDD>0.<YY>g.z";
	v_sign.push_back(s);
	s.type = RINEX; s.og = GPS; s.mask = "<NNNN><DDD>0.<YY>n.z";
	v_sign.push_back(s);
	s.type = RINEX; s.og = GALILEO; s.mask = "<NNNN><DDD>0.<YY>l.z";
	v_sign.push_back(s);
	s.type = RINEX; s.og = COMPASS; s.mask = "<NNNN><DDD>0.<YY>c.z";
	v_sign.push_back(s);
}



bool compare_mask::getType(std::string const &str, type_file *t, type_og *og)// str - это им€ файла
{
	compare comp;
	comp.setFileName(str);
	std::vector<signature>::iterator i = v_sign.begin();
	i = std::find_if(v_sign.begin(), v_sign.end(), comp);
	if (i == v_sign.end()) return false;
	*t = i->type;
	*og = i->og;
	return true;
}


////////////////////////////////////////////////////// функтор /////////////////////////////////////////////////////////////////

compare::compare(){}

bool compare::operator()(signature const &sig)
//bool compare::operator()(compare_mask::pair_file_og const &_pfo, std::string const &mask)	// эти значени€ получаем из метода шаблонного класса multimap,
																							// нам важен второй параметр, еще не оработанна€ маска.
{
	// 1. нужно преоразовать маску
	std::string msk = canonicalMask(sig.mask);
	// 2. тепер сравним пробежимс€ по name (им€ файла) регул€рнвм вырожением которое сравнит его с маской
	return std::regex_search(name, std::regex(msk, std::regex_constants::icase));
}

void compare::setFileName(std::string const & filename)
{
	name = filename;
}

std::string compare::canonicalMask(std::string const &mask)
{
	std::string msk = std::regex_replace(mask, std::regex("\\s*<\\s*DD\\s*>\\s*"), std::basic_string<char>("(\\d\\d)"));
	msk = std::regex_replace(msk, std::regex("\\s*<\\s*DDD\\s*>\\s*"), std::basic_string<char>("(\\d\\d\\d)"));
	msk = std::regex_replace(msk, std::regex("\\s*<\\s*HH\\s*>\\s*"), std::basic_string<char>("(\\d\\d)"));
	msk = std::regex_replace(msk, std::regex("\\s*<\\s*MM\\s*>\\s*"), std::basic_string<char>("(\\d\\d)"));
	msk = std::regex_replace(msk, std::regex("\\s*<\\s*YY\\s*>\\s*"), std::basic_string<char>("(\\d\\d)"));
	msk = std::regex_replace(msk, std::regex("\\s*<\\s*GG\\s*>\\s*"), std::basic_string<char>("(\\d\\d)"));
	msk = std::regex_replace(msk, std::regex("\\s*<\\s*NNNN\\s*>\\s*"), std::basic_string<char>("(....)"));
	msk = std::regex_replace(msk, std::regex("\\s*<\\s*R\\s*>\\s*"), std::basic_string<char>("[GNLC]"));
	msk = std::regex_replace(msk, std::regex("\\s*<\\s*F\\s*>\\s*"), std::basic_string<char>("[GNLC]"));

	return msk;
}

////////////////////////////////////////////////////// функтор закончилс€ //////////////////////////////////////////////////////