#include "stdafx.h"
#include "Object.h"

#include <cstring>
#include <cctype>
#include <iostream>
#include <vector>

Object::Object(const char attr[])
{
	m_attr = new char[strlen(attr) + 1];
	strcpy(m_attr, attr);
}

Object::Object(const Object &object)
{
	m_attr = new char[strlen(object.m_attr) + 1];
	strcpy(m_attr, object.m_attr);
}

Object::Object()
{
	m_attr = new char[1];
	m_attr[0] = '\0';
}


Object::~Object()
{
	delete[] m_attr;
}

Object Object::operator=(const char attr[])
{
	char *new_string = new char[strlen(attr) + 1];
	strcpy(new_string, attr);

	delete[] m_attr;
	m_attr = new_string;

	return *this;
}

Object Object::operator=(Object &obj)
{
	*this = obj.m_attr;
	return *this;
}

Object Object::operator+(const char attr[])
{
  char *new_string = new char[strlen(m_attr) + strlen(attr) + 1];
  strcpy(new_string, m_attr);
  strcpy(new_string, attr);

  delete[] m_attr;
  m_attr = new_string;

  return *this;
}

Object Object::operator+(Object &obj)
{
  char *new_string = new char[strlen(m_attr) + strlen(obj.m_attr) + 1];
  strcpy(new_string, m_attr);
  strcpy(new_string, obj.m_attr);

  delete[] m_attr;
  m_attr = new_string;

  return *this;
}

bool Object::operator==(const char attr[])
{
	return strcmp(m_attr, attr) == 0;
}

bool Object::operator==(const int n)
{
	char numStr[12];
	sprintf(numStr, "%d", n);

	return *this == numStr;
}

bool Object::operator==(const Object &obj)
{
	return *this == obj.m_attr;
}

bool Object::operator!=(const char attr[])
{
	return !(*this == attr);
}

bool Object::operator!=(const int n)
{
	return !(*this == n);
}

bool Object::operator!=(const Object &obj)
{
	return !(*this == obj.m_attr);
}

Object::operator int() const
{
  int i;
  sscanf(m_attr, "%d", &i);

  return i;
}

char Object::operator[](int i) const
{
  return m_attr[i];
}

char& Object::operator[](int i)
{
  return m_attr[i];
}

Object Object::trim()
{
	int start = 0, end = 0;

	if (!strlen(m_attr))
	{
		return *this;
	}

	while (isspace(m_attr[start])) 
		start++;

	if (start == strlen(m_attr))
	{
		*this = "";
		return *this;
	}

	while (isspace(m_attr[strlen(m_attr) - 1 - end])) 
		end++;
	
	m_attr += start;
	char *newString = new char[strlen(m_attr) + 1 - end];
	
	strncpy(newString, m_attr, strlen(m_attr) - end);
	newString[strlen(m_attr) - end] = '\0';

	m_attr -= start;
	delete[] m_attr;
	m_attr = newString;

	return *this;
}

int Object::length()
{
	return strlen(m_attr);
}

std::vector<Object> Object::split(const char delimeter)
{
	char str[2] = { delimeter, '\0' };
	return split(str);
}

std::vector<Object> Object::split(const char delimeter[])
{
	std::vector<Object> arr;
	int delimeterLength = strlen(delimeter), start = 0, end;
	char *pointer = m_attr;

	while ((end = indexOf(delimeter, start)) != -1)
	{
		char *localStr = new char[end - start];
		strncpy(localStr, pointer, end - start);
		localStr[end - start] = '\0';
		Object item = localStr;
		arr.push_back(item);
		pointer += end - start + delimeterLength;
		start = end + delimeterLength;
	}

	if (strlen(pointer))
	{
		Object item = pointer;
		arr.push_back(item);
	}

	return arr;
}

int Object::indexOf(const char searchElement, int fromIndex)
{
	int len = strlen(m_attr);

	if (fromIndex < 0)
	{
		fromIndex = 0;
	}

	for (int i = fromIndex; i < len; ++i)
	{
		if (m_attr[i] == searchElement)
		{
			return i;
		}
	}

	return -1;
}

int Object::indexOf(const char *searchString, int fromIndex)
{
	int len = strlen(m_attr);
	int searchLen = strlen(searchString);
	char *p = m_attr;

	if (fromIndex < 0)
	{
		fromIndex = 0;
	}

	for (int i = fromIndex; i < len - searchLen + 1; ++i)
	{
		if (strncmp(p + i, searchString, searchLen) == 0)
		{
			return i;
		}
	}

	return -1;
}

int Object::indexOf(const Object &obj, int fromIndex)
{
	return indexOf(obj.m_attr, fromIndex);
}

int Object::lastIndexOf(const char searchElement, int fromIndex)
{
	int len = strlen(m_attr);

	if (fromIndex < 0 || fromIndex > len)
	{
		fromIndex = len;
	}

	for (int i = fromIndex - 1; i >= 0; --i)
	{
		if (m_attr[i] == searchElement)
		{
			return i;
		}
	}

	return -1;
}

Object Object::substring(const int start, const int end)
{
	int len = strlen(m_attr);
	Object result = "";

	if (start >= end || start >= len - 1 || end > len) 
	{
		return result;
	}

	char *newStr = new char[strlen(m_attr) + 1];

	strcpy(newStr, m_attr);

	newStr += start;

	newStr[end - start] = '\0';

	result = newStr;

	return result;
}

Object Object::substr(const int start, const int count)
{
  return substring(start, strlen(m_attr) - count - 1);
}

Object Object::remove(const int start, const int count)
{
  char *newStr = new char[strlen(m_attr) + 1 - count];

  strcpy(newStr, substring(0, start).m_attr);
  strcpy(newStr, substring(start + count).m_attr);

  delete[] m_attr;
  m_attr = newStr;

  return *this;
}

Object Object::substring(const int start)
{
	return substring(start, strlen(m_attr));
}

ostream &operator<<(ostream &output, const Object &obj)
{
	output << obj.m_attr;

	return output;
}

istream &operator>>(istream &input, const Object &obj)
{
  return input >> obj.m_attr;
}

void Object::toLowerCase()
{
	for (int i = 0; i < strlen(m_attr); i++)
	{
		m_attr[i] = tolower(m_attr[i]);
	}
}

void Object::toUpperCase()
{
	for (int i = 0; i < strlen(m_attr); i++)
	{
		m_attr[i] = toupper(m_attr[i]);
	}
}

char* Object::toString()
{
	char newStr[255];
	strcpy(newStr, m_attr);

	return newStr;
}