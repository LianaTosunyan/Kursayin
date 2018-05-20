#include "stdafx.h"
#include <iostream>

#include "Object.h"
#include "SQLClient.h"

using namespace std;

int main()
{
	char str[200];

	while (true)
	{
		cout << "SQLClient:~ ajemma$ ";
		cin.getline(str, 200, '\n');

		SQLClient sql;
		Object query = str;

		bool result = sql.exec(query);

		if (!result)
		{
			cout << "Query is not falid\n";
		}
	}

	return 0;
}

