//============================================================================
// Name        : rvs.cpp
// Author      : HDL-DH
// Version     :
// Copyright   : (c) 2018
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <iostream>
#include <dlfcn.h>
#include <string.h>

#include <fstream>
#include "yaml-cpp/yaml.h"

#include "rvsif0.h"
#include "rvsif1.h"
#include "rvsaction.h"
#include "rvsmodule.h"



using namespace std;

// TOTO: move into rvs::module
// int listmodules(void)
// {
//     YAML::Node config = YAML::LoadFile("./rvsmodules.config");
//     
//     YAML::const_iterator it=config.begin();
//     std::string key=it->first.as<std::string>();
//     std::string value=it->second.as<std::string>();
//     if(value!="1")
//     {
//         printf("ERROR: version is not 1");
//         return -1;
//     }
//     
//     for(it++; it!=config.end(); ++it) 
//     {
//         std::string key=it->first.as<std::string>();
//         std::string value=it->second.as<std::string>();
//         std::cout << "Key: " << key <<"\n"; 
//         std::cout << "Value: " << value << "\n";
//         
//         rvs::module* module = rvs::module::create(value.c_str());
//         rvs::if0* pif0 = (rvs::if0*)rvs::module->get_interface(0);
// 
//         
//         fprintf(stdout, "Module: %s\n", pif0->get_name() );
// 
//         fprintf(stdout, "Description: %s\n", pif0->get_description() );
//         int Major,Minor,Patch;
//         pif0->get_version(&Major,&Minor,&Patch);
//         std::cout << "Version: " << Major << "." << Minor << "." << Patch << "\n";
//         rvs::module::destroy(module);
//     }
//     return 0;
// }

int main(int Argc, char**Argv)
{
    for (int i=1;i<Argc;i++)
    {
        if (!strcmp(Argv[i],"--modules"))
        {
        //int status=listmodules();
        }
    }
    
    rvs::module::initialize("./rvsmodules.config");

	rvs::action* pa = rvs::module::action_create("gpup");
	if(!pa)
	{
		cout << "Could not create 'gpup' action." << endl;
		return -1;
	}
	
	rvs::if0* pif0 = dynamic_cast<rvs::if0*>(pa->get_interface(0));
	if(!pif0)
	{
		cout << "Could not get interface 'IF0'." << endl;
		return -1;
	}
	
	std::cout << "Module: " << pif0->get_name() << endl;
	std::cout << "Description: " << pif0->get_description() << endl;

	rvs::if1* pif1 = dynamic_cast<rvs::if1*>(pa->get_interface(1));
	if(!pif0)
	{
		cout << "Could not get interface 'IF1'." << endl;
		return -1;
	}
	
	int sts = pif1->run();
	
	rvs::module::action_destroy(pa);

	rvs::module::terminate();
    
	return 0;
}




