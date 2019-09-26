#include<string>
#include<iostream>
#include<sstream>
#include<map>
#include<vector>
#include<fstream>
#include<set>
std::string blifname; //blif專案名
std::string Inputnode[999999]; //底層node
std::string Outputnode[999999]; //輸出node
char temp[999999];
std::map<std::string, std::string>outputnode;
std::map<std::string, std::string>::iterator it;
std::set<std::string>node;
int recordInputnode = 0;
int recordOutputnode = 0;
bool isannotation = false; //annotation
bool isnewline = false; //newline /

bool inputs = false;
bool outputs = false;
bool names = false;
bool modles = false;

void Inputdeal(std::string filename) {
	std::fstream inputfile;
	inputfile.open(filename, std::ios::in);
	//openfile
	std::vector<std::string>leaf;
	std::string paragraph;
	while (1) {
		
		inputfile >> paragraph;

		if (paragraph[0] != '#') //本行為註解
		{
			//讀檔結束
			if (paragraph == ".end") break; 
			//換行符號
			else if(paragraph=="\\")
			{ 
			}
			else if (paragraph == ".model")
			{
				inputs = false;
				outputs = false;
				names = false;
				modles = true;
			}
			else if (paragraph == ".inputs") //底層node
			{
				inputs = true;
				outputs = false;
				names = false;
				modles = false;
			}
			else if (paragraph == ".outputs") //output nodes
			{
				inputs = false;
				outputs = true;
				names = false;
				modles = false;
			}
			else if (paragraph == ".names") //boolean
			{
				leaf.clear();
				inputs = false;
				outputs = false;
				names = true;
				modles = false;
				inputfile.getline(temp, std::size(temp));
				std::stringstream ss;
				ss.str(temp);
				std::string temps;
				while (1)
				{
					ss >> temps;
					if (ss.eof())
					{
						if (temps == "\\")
						{
							leaf.push_back(temps);
							inputfile.getline(temp, std::size(temp));
							ss.str(temp);
						}
						else
						{
							leaf.push_back(temps);
							break;
						}
					}
					else {
						leaf.push_back(temps);
					}
					//if (temps == "\\") isnewline = true;
					//else
						//leaf.push_back(temps);
					
					
				}
				
				
			}
			else if(inputs)
			{ 
				Inputnode[recordInputnode] = paragraph;
				recordInputnode++;
			}
			else if (outputs)
			{
				Outputnode[recordOutputnode] = paragraph;
				recordOutputnode++;
			}
			else if(modles)
			{
				blifname = paragraph;
			}
			else if (names)
			{
				std::string func = "";
				for (int i = 0; i < paragraph.length(); i++)
				{
					if (paragraph[i] == '1')
					{
						func += leaf[i];
					}
					else if (paragraph[i] == '0')
					{
						func += leaf[i];
						func += "'";
					}
				}
				inputfile.getline(temp, std::size(temp));
				std::stringstream ss;
				ss.str(temp);
				std::string temps;
				while (1)
				{
					ss >> temps;
					if (ss.eof())
					{
						if (temps == "\\")
						{
							inputfile.getline(temp, std::size(temp));
							ss.str(temp);
							
						}
						else
						{
							if (temps == "1")
							{
								it = outputnode.find(leaf[leaf.size() - 1]);
								if (it != outputnode.end())
								{
									it->second += "+";
									it->second += func;
								}
								else
								{
									outputnode.insert(std::pair<std::string, std::string>(leaf[leaf.size() - 1], func));
								}
							}
							else {
								std::string re = "(";
								re += func;
								re += ")'";
								it = outputnode.find(leaf[leaf.size() - 1]);
								if (it != outputnode.end())
								{
									it->second += "+";
									it->second += re;
								}
								else
								{
									outputnode.insert(std::pair<std::string, std::string>(leaf[leaf.size() - 1], re));
								}
							}
							break;
						}
					}
					else {

					}
					
				
				}

			}

		}

	}
	for (it = outputnode.begin(); it != outputnode.end(); it++)
	{
		std::cout << it->first << "\n" << it->second << "\n";
	}

}

int main()
{
	std::string name = "9symml.blif";
	Inputdeal(name);
	system("pause");
	return 0;
}