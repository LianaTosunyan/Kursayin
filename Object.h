#pragma warning(disable: 4996)

#ifndef Object_h__
#define Object_h__

#include <iostream>
#include <vector>

using namespace std;
class Object
{
private:
	char* m_attr;
	friend ostream& operator<<(ostream&, const Object&);
	friend istream& operator>>(istream&, const Object&);

public:
	Object();
	Object(const char attr[]);
	Object(const Object&);
	~Object();

	Object operator=(const char[]);
	Object operator=(Object& obj);
	Object operator+(const char[]);
	Object operator+(Object& obj);
	bool operator==(const char[]);
	bool operator==(const int);
	bool operator==(const Object&);
	bool operator!=(const char[]);
	bool operator!=(const int);
	bool operator!=(const Object&);
	operator int() const;
	char operator [](int i) const;
	char &operator [](int i);

	int length();
	Object trim();
	vector<Object> split(const char);
	vector<Object> split(const char[]);

	int indexOf(const char, int = 0);
	int indexOf(const char*, int = 0);
	int indexOf(const Object&, int = 0);
	int lastIndexOf(const char, int = -1);

	Object substring(const int);
	Object substring(const int, const int);
	Object substr(const int, const int);
	Object remove(const int, const int);

	void toLowerCase();
	void toUpperCase();

	char* toString();
};

#endif //Object_h__
