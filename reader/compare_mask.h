#ifndef COMPARE_MASK_H
#define COMPARE_MASK_H
#include <iostream>
//#include <boost/regex.hpp>
#include <vector>
#include <regex>
//#include <utility>
#include "general_datataype.h"


// DD	���� (01-31)				<DD>	-> (\d\d)
// DDD	����� ��� � ���� (001-366)	<DDD>	-> (\d\d\d)
// HH	��� (00-23)					<HH>	-> (\d\d)
// MM	����� (00-12)				<MM>	-> (\d\d)
// YY	��� (00-99)					<YY>	-> (\d\d)
// NNNN	������������� ������ (****) <NNNN>	-> (....)
// R	��� ��					<R> ��� <F>	-> [GNLC]
// (G-�������, N-GPS, L-GALILEO, C-COMPASS) � "general_datataype.h" type_og

struct signature
{
	type_file	type;
	type_og		og;
	std::string	mask;
};

class compare_mask
{
private:
	std::vector<signature> v_sign;
	
public:
	compare_mask();
	// ��������� ���� ���� ���� �� �� ����� �����
	bool getType(std::string const &str, type_file*, type_og*);

};

// �������
// ��������� � ������������ ������
class compare
{
private:
	std::string name;
	std::string canonicalMask(std::string const &);
public:
	compare ();
	void setFileName(std::string const &);
	bool operator()(signature const &);
};

#endif //COMPARE_MASK_H
