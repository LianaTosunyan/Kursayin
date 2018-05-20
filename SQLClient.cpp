#include "stdafx.h"
#include <vector>

#include "SQLClient.h"
#include "Object.h"
#include "Group.h"
#include "FilePath.h"

using namespace std;

SQLClient::SQLClient()
{
	strcpy(m_keys[0], "name");
	strcpy(m_keys[1], "dep");
	strcpy(m_keys[2], "studentCount");

	// Creating file if not exists
	FILE *f = fopen(FILE_PATH, "a");
	fclose(f);
}

SQLClient::~SQLClient()
{
}

bool SQLClient::exec(Object& query)
{
	query.trim();

	if (query.indexOf("SELECT") == 0)
	{
		return selectData(query);
	}
	else if (query.indexOf("ADD") == 0)
	{
		return insertData(query);
	}

	return false;
}

bool SQLClient::selectData(Object& query)
{
	int conditionIndex = query.indexOf("WHERE");

	vector<Object> fields = query.substring(query.indexOf("SELECT") + 6, conditionIndex != -1
							? conditionIndex 
							: query.length()).split(',');

	for (int i = 0; i < fields.size(); i++)
	{
		fields[i].trim();

		bool isFiledValid = false;

		for (int j = 0; j < _countof(m_keys); j++)
		{
			if (fields[i] == m_keys[j])
			{
				isFiledValid = true;
				break;
			}
		}

		if (!isFiledValid)
		{
			cout << "Field is invalid: " << fields[i] << '\n';
			return false;
		}
	}

	vector<Object> conditions;

	if (conditionIndex != -1)
	{
		conditions = getConditions(query);
	}

	int n;
	Group *data = readFile(n);

	cout << endl;

	for (int i = 0; i < fields.size(); ++i)
	{
		cout << fields[i] << '\t';
	}

	cout << endl << endl;

	for (int i = 0; i < n; ++i)
	{
		if (!checkConditions(conditions, data[i]))
		{
			continue;
		}

		for (int j = 0; j < fields.size(); ++j)
		{
			if (fields[j] == "name")
			{
				cout << data[i].name;
			}
			else if (fields[j] == "dep")
			{
				cout << data[i].dep;
			}
			else if (fields[j] == "studentCount")
			{
				cout << data[i].studentCount;
			}

			cout << '\t';
		}

		cout << '\n';
	}

	return true;
}


bool SQLClient::insertData(Object &query)
{
	vector<Object> data = query.substring(query.indexOf("ADD") + 3).split(',');
	Group newItem;

	if (data.size() != _countof(m_keys))
	{
		cout << "You need input " << _countof(m_keys) << " fields, " << data.size() << " given\n";
		return false;
	}

	for (int i = 0; i < data.size(); ++i)
	{
		data[i].trim();

		bool isDataValid = false;

		for (int j = 0; j < _countof(m_keys); ++j)
		{
			if (data[i].indexOf(m_keys[j]) == 0 && data[i].indexOf('=') != -1)
			{
				isDataValid = true;
				break;
			}
		}

		if (!isDataValid)
		{
			cout << "Problem in data: " << data[i] << '\n';
			return false;
		}

		if (data[i].indexOf("name") == 0)
		{
			strcpy(newItem.name, data[i].substring(data[i].indexOf('=') + 1).trim().toString());
		}
		else if (data[i].indexOf("dep") == 0)
		{
			strcpy(newItem.dep, data[i].substring(data[i].indexOf('=') + 1).trim().toString());
		}
		else if (data[i].indexOf("studentCount") == 0)
		{
			char num[100];
			strcpy(num, data[i].substring(data[i].indexOf('=') + 1).trim().toString());

			int dec = 0, len;

			len = strlen(num);

			for (int i = 0; i < len; ++i) {
				dec = dec * 10 + (num[i] - '0');
			}

			newItem.studentCount = dec;
		}
	}

	FILE *f = fopen(FILE_PATH, "ab");

	fwrite(&newItem, sizeof(Group), 1, f);

	fclose(f);

	cout << "Done\n";

	return true;
}

vector<Object> SQLClient::getConditions(Object& query)
{
	vector<Object> conditions = query.substring(query.indexOf("WHERE") + 5).split(',');

	for (int i = 0; i < conditions.size(); ++i)
	{
		conditions[i].trim();

		bool isConditionValid = false;

		for (int j = 0; j < _countof(m_keys); ++j)
		{
			if (conditions[i].indexOf(m_keys[j]) == 0 && conditions[i].indexOf("=") != -1)
			{
				isConditionValid = true;
				break;
			}
		}

		if (!isConditionValid)
		{
			cout << "Problem in condition: " << conditions[i] << '\n';
			exit;
		}
	}

	return conditions;
}

bool SQLClient::checkConditions(vector<Object>& conditions, const Group& data)
{
	bool matching = true;

	for (int j = 0; j < conditions.size(); ++j)
	{
		bool mustEqual = conditions[j].indexOf("!=") == -1;
		bool isEqual;

		Object str = conditions[j].substring(conditions[j].indexOf("=") + 1);
		str.trim();

		if (conditions[j].indexOf("name") == 0)
		{
			isEqual = str == data.name;
		}
		else if (conditions[j].indexOf("dep") == 0)
		{
			isEqual = str == data.dep;
		}
		else if (conditions[j].indexOf("studentCount") == 0)
		{
			isEqual = str == data.studentCount;
		}


		if (mustEqual ^ isEqual != 0)
		{
			matching = false;
			break;
		}
	}

	return matching;
}

Group* SQLClient::readFile(int& n)
{
	FILE *f = fopen(FILE_PATH, "rb");

	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	n = size / sizeof(Group);

	Group *data = new Group[n];

	fread(data, sizeof(Group), n, f);

	fclose(f);

	return data;
}