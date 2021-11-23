#include <iostream>
#include "reader.h"
#include "general_datataype.h"
#include "compare_mask.h"

int main()
{
	std::cout<<"Start reader!"<<std::endl;

    ///
	std::string str;
	str = "E:\\1\\tmp\\21080101_g.og";
	// ��� Windows
	// ����� ���:
	//str = "E:/1/text.txt";
	// ��� ���:
	//str = "E:\\1\\����� �����\\text.txt";// ������� � ������� �����������!
	// � ������� ���� ���� �����
	//str = "\\\\NAS_SPN\\_Exp_Data\\spn_data_general\\CPI_M\\Poi\\OG\\2021\\08\\21080101_G.og";
	//str = "//nas_spn/_Exp_Data/spn_data_general/CPI_M/Poi/OG/2021/08/21080101_G.og";
	//
	// ��� Linux
	//
	//str = "/home/mouse/testfiles/21080101_G.og";
	

	reader r(str);
	std::string filename = r.getName();

	// ����� ���� ����� �������� ��� ����� �� ������� ����, ����� ���������� ������ ������ ���� ���� ����

	compare_mask comp;
	type_file myFile;  // ���������� ��� ���� �����, ���� �������� � "general_datataype.h"
	type_og   myOg;    // ���������� ��� ���� ��,    ���� �������� � "general_datataype.h"

	if(comp.getType(filename, &myFile, &myOg))
	{
		std::cout << filename << std::endl << std::endl;
		switch (myFile)
		{
		case 0 : std::cout << "STATE_TABLE_OG" << std::endl;
			break;
		case 1 : std::cout << "ALMANAC" << std::endl;
			break;
		case 2 : std::cout << "RINEX" << std::endl;
			break;
		case 3 : std::cout << "ZIP" << std::endl;
			break;
		case 4 : std::cout << "UNKNOWN" << std::endl;
			break;
		default : std::cout << "ERROR" << std::endl;
			break;
		}
		switch (myOg)
		{
		case 0 : std::cout << "GLONASS" << std::endl;
			break;
		case 1 : std::cout << "GPS" << std::endl;
			break;
		case 2 : std::cout << "GALILEO" << std::endl;
			break;
		case 3 : std::cout << "COMPASS" << std::endl;
			break;
		default : std::cout << "ERROR" << std::endl;
			break;
		}
		std::cout << std::endl;
	} else {
		std::cout << "File format unrecognized!" << std::endl;
	}

	r.print();

	system("pause"); // �������� ��������� ���������
}