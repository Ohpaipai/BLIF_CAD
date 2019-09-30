#include<string>
#include<iostream>
#include<sstream>
#include<map>
#include<vector>
#include<fstream>
#include<set>
const int LEN_LENGTH=99999;
std::string blifname; //blif專案名
std::string Inputnode[999999]; //底層node
std::string Outputnode[999999]; //輸出node
char temp[999999];
int t = 0;
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

bool specialcase = false;
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
				/*std::cout << "test\n"<<t++;
				if(t==33){
				std::cout<<"dsad\n";
				}*/

				if (specialcase == true)
				{
					it = outputnode.find(leaf[0]);
					if (it != outputnode.end())
					{
						it->second = "0";
					}
					else
					{
						outputnode.insert(std::pair<std::string, std::string>(leaf[0], "0"));
					}
					specialcase = false;
				}
				leaf.clear();
				inputs = false;
				outputs = false;
				names = true;
				modles = false;
				inputfile.getline(temp,LEN_LENGTH);
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
							//leaf.push_back(temps);
							inputfile.getline(temp,LEN_LENGTH);
							ss.clear();
							ss.str("");
							temps.clear();
							ss.str(temp);
						}
						else
						{
							bool isexit = false;
							for (int i = 0; i < leaf.size(); i++)
							{
								//std::cout << leaf[i] << "--->" << temp;
								if (leaf[i] == temp)
								{
									isexit = true;
									break;
								}
							}
							if (isexit == false)
								leaf.push_back(temps);
						}
						break;
					}
					else {
						bool isexit = false;
						for (int i = 0; i < leaf.size(); i++)
						{
							if (leaf[i] == temp)
							{
								isexit = true;
								break;
							}
						}
						if(isexit==false)
							leaf.push_back(temps);
					}
					//if (temps == "\\") isnewline = true;
					//else
						//leaf.push_back(temps);
					
					
				}
				if (leaf.size() == 1)
				{
					specialcase = true;
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
				if (specialcase == true)
				{
					specialcase = false;
					it = outputnode.find(leaf[0]);
					if (it != outputnode.end())
					{
						it->second = "1";
					}
					else
					{
						outputnode.insert(std::pair<std::string, std::string>(leaf[0], "1"));
					}
				}
				else {
					std::string func = "";
					for (int i = 0; i < paragraph.length(); i++)
					{
						if (paragraph[i] == '1')
						{
							func += leaf[i];
							func += " ";
						}
						else if (paragraph[i] == '0')
						{
							func += leaf[i];
							func += "' ";
						}
					}
					inputfile.getline(temp,LEN_LENGTH);
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
								inputfile.getline(temp,LEN_LENGTH);
								ss.clear();
								ss.str("");
								temps.clear();
								ss.str(temp);

							}
							else
							{
								if (temps == "1")
								{
									it = outputnode.find(leaf[leaf.size() - 1]);
									if (it != outputnode.end())
									{
										it->second += " + ";
										it->second += func;
									}
									else
									{
										outputnode.insert(std::pair<std::string, std::string>(leaf[leaf.size() - 1], func));
									}
								}
								else {
									std::string re = " ( ";
									re += func;
									re += " )' ";
									it = outputnode.find(leaf[leaf.size() - 1]);
									if (it != outputnode.end())
									{
										it->second += " + ";
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
		else {
			 inputfile.getline(temp,LEN_LENGTH);
		}

	}
	
	

}
void outAncient() {
	std::string str;
	bool isfindp = false;
	bool isfinds = false;
	std::set<std::string>predecessor;
	std::set<std::string>successor;
	std::set<std::string>::iterator iter;
	while (1)
	{
		predecessor.clear();
		successor.clear();
		isfindp = false;
		isfinds = false;
		std::cout << "Please input a node:";
		std::cin >> str;
		
		if (str == "0") break;
		
		it = outputnode.find(str);
		if (it == outputnode.end()) {}
		else {
			isfindp = true;
			//std::cout << "predecessor : ";
			if ((it->second == "1" || it->second == "0")&&it->second.length()==1) predecessor.insert("-");
			else {
				std::stringstream ss;
				ss.str(it->second);
				std::string tempswww;
				while (1) {
					ss >> tempswww;
					if (tempswww == "(" || tempswww == ")'"||tempswww=="+") {}
					if (tempswww[tempswww.length() - 1] == '\'')
					{
						std::string hj;
						for (int i = 0; i < tempswww.length() - 1; i++)
						{
							hj += tempswww[i];
						}
						predecessor.insert(hj);
					}
					else {
						if (tempswww == "0" || tempswww == "1"||tempswww=="+"|| tempswww == "(" || tempswww == ")'")
						{
						}
						else {
							predecessor.insert(tempswww);
						}
					}
					if (ss.eof()) break;

				}
			}

		}
			
			//std::cout << "\nsuccessor: ";
			for (it = outputnode.begin(); it != outputnode.end(); it++)
			{
				std::stringstream ss;
				ss.str(it->second);
				std::string tempswww;
				while (1) {
					ss >> tempswww;
					std::string strsec = str + "'";
					if (tempswww == str || tempswww == strsec)
					{
						isfinds = true;
						successor.insert(it->first);
					}

					if (ss.eof()) break;

				}
			}

			

		
		
	//out
		if (isfindp == false && isfinds == false)
		{
			bool reall = false;
			for (int i = 0; i < recordInputnode; i++)
			{
				if (str == Inputnode[i]) {
					reall = true;
					break;
				}
			}
			for (int i = 0; i < recordOutputnode; i++)
			{
				if (str == Outputnode[recordOutputnode])
				{
					reall = true;
					break;
				}
			}
			if(!reall)
				std::cout << "node " << str << " does not exist\n";
			else
				std::cout << "node " << str << " exist. But not use\n";

		}
		else
		{
			if (isfindp == false) predecessor.insert("-");
			if (isfinds == false)successor.insert("-");
			std::cout << "predecessor : ";
			for (iter = predecessor.begin(); iter != predecessor.end(); iter++)
			{
				if (iter == predecessor.begin()) std::cout << *iter;
				else std::cout << " , " << *iter;
			}
			std::cout << "\nsuccessor: ";
			for (iter = successor.begin(); iter != successor.end(); iter++)
			{
				if (iter == successor.begin()) std::cout << *iter;
				else std::cout << " , " << *iter;
			}
			std::cout << "\n";
		}
		
	}
}
void outfunction()
{
	std::cout << "Node function:\n";
	for (it = outputnode.begin(); it != outputnode.end(); it++)
	{
		std::cout << it->first << " = " << it->second << "\n";
	}
	std::cout << "END\n";
}

int main(int argc,char* argv[])
{
	//std::string name = "test.blif";
	std::string name=argv[1];
	Inputdeal(name);
	outAncient();
	outfunction();
	//system("pause");
	return 0;
}
