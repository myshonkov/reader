#ifndef TRACKING_H
#define TRACKING_H
#include <string>
#include <vector>
#include <thread>
//#include <boost\thread\thread.hpp>
//#include <boost\chrono.hpp>
// �� ���� ������ �������� ������������� ������, ���� ��� ������
// � ������� ������ �� ��������� ������

class tracking
{
public:
	tracking();
	void newTracking(std::string, int);
	~tracking();
private:
	//int sec;
	void wait(int);
//	std::vector<boost::thread*> threads;

	void myThred();
};


#endif //TRACKING_H