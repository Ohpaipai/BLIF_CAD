#pragma once
#include<string>
#include<iostream>
#include<sstream>
#include<map>
#include<vector>
#include<fstream>
std::string blifname; //name of project
std::string Inputnode[999999];
std::string Outputnode[999999];
std::map<std::string, std::string>output;
int recordInputnode = 0;
int recordOutputnode = 0;
void Inputdeal(std::string filename) {
	std::fstream inputfile; 
	inputfile.open(filename, std::ios::in);
	//openfile
	std::string paragraph;
	while (1) {
		inputfile >> paragraph;
		if (paragraph == ".end") break;
		else if (paragraph == ".model") //getfile name
		{
			inputfile >> blifname;	//get project name
		}
		else if (paragraph == ".inputs") //input nodes
		{
			while (1)
			{
				inputfile >> paragraph;
				if (paragraph == "/n") break;
				Inputnode[recordInputnode] = paragraph;
				recordInputnode++;
			}
		}
		else if (paragraph == ".inputs") //output nodes
		{
			while (1)
			{
				inputfile >> paragraph;
				if (paragraph == "/n") break;
				Outputnode[recordOutputnode] = paragraph;
				recordOutputnode++;
				
			}
		}
			
	}


} 