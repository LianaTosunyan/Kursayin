#ifndef SQLClient_h__
#define SQLClient_h__

#include "Object.h"
#include "Group.h"

using namespace std;

class SQLClient
{
public:
	SQLClient();
	~SQLClient();
	bool exec(Object&);

private:
	char m_keys[3][20];

	vector<Object> getConditions(Object&);
	bool checkConditions(vector<Object>&, const Group&);
	Group* readFile(int &);

	bool selectData(Object&);
	bool insertData(Object&);
};

#endif // SQLClient_h__
