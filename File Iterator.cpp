#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#define replace 1

/** This code iterates a file and print lines with desired contents.
 * You should define those contents in the function correto().
 */

using namespace std;

bool correto(string text)
{
	if (replace) //text.find('.') != -1 && text.find("_readme.txt") == -1 && text.find(".masok") == -1
		return true;
	else
		return false;
}

int main(int argc, char *argv[])
{
	if (argc <= 1)
		return -1;
	string text = string();
	text.append(argv[1]);
	int i = text.rfind('\\');
	text.erase(text.begin(),text.begin()+i);
	ifstream file;
	file.open(text.c_str(), ios::out);
	for(getline(file,text); !file.fail(); getline(file,text))
		if (correto(text))
			cout << text << '\n';
	file.close();
	system("pause");
	return 0;
}
