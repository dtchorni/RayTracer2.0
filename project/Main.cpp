// Fall 2018

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "scene_lua.hpp"
#include "Options.hpp"

Opts options= Opts();


void printDialogue(){
	std::cout<<"Ray Tracer: by Daniel Tchorni\n"<<
			"Usage: ./Raytracer [file] [flags]\n"<<
			"\t [*.lua file]\n"<<
			"\t\t -d (exclude diffuse portion of lighting calculation)\n"<<
			"\t\t -s (exclude specular portion of lighting calculation)\n"<<
			"\t\t -a (exclude ambient light calculation) \n"<<
			"\t\t -b (produce the bounding volumes rather than the meshes)\n"<<
			"\t\t -sh (remove shadows)\n"<<
			"\t\t -ph (Completely disable Phong lighting)\n"<<
			"\t\t -th (disable multi-threading optimizations)\n"<<
			"\t\t -nth [n] (run with n multiple threads) \n"<<
			"\t\t -go (disable Gourard shading) \n"<<
			"\t\t -ua (default all boolean nodes to union operations) \n"<<
			"\t\t -db (debug mode -> disables multi-threading and anti-aliasing)\n"<<
			"\t\t -ss [n] (enter number of points per pixel to sample with) \n"<<
			"\t\t -h (Print dialogue)\n"<<std::endl;

}

bool handleFlags(int argc, char ** argv){
	if(argc>=3){
		for(int i =2; i < argc; ++i){
			if(strcmp(argv[i],"-d")==0) options.diffuse=false;
			else if(strcmp(argv[i],"-s")==0) options.spec=false;
			else if(strcmp(argv[i],"-a")==0) options.ambient=false;
			else if(strcmp(argv[i],"-b")==0) options.bound=true;
			else if(strcmp(argv[i],"-sh")==0) options.shadows=false;
			else if(strcmp(argv[i],"-ph")==0) options.phong=false;
			else if(strcmp(argv[i],"-th")==0) options.thread=false;
			else if(strcmp(argv[i],"-go")==0) options.gourard=false;
			else if(strcmp(argv[i],"-ua")==0) options.unionAll=true;
			else if(strcmp(argv[i],"-db")==0) {
			    options.thread=false;
			    options.samples=1;
			}
			else if(strcmp(argv[i],"-ss")==0) {
				++i;
				if (i < argc) {
					options.cores/=options.samples;
					options.samples = atoi(argv[i]);
					options.cores*=options.samples;
				} else {
					printDialogue();
					return false;
				}

			}else if(strcmp(argv[i],"-nth")==0){
				++i;
				if(i<argc){
					options.cores=atoi(argv[i]);
				}else{
					printDialogue();
					return false;
				}
			}else{
				printDialogue();
				return false;
			}
		}
	}
	return true;
}


int main(int argc, char** argv)
{
	srand(0);
	std::string filename = "Assets/simple.lua";
	if (argc >= 2) {
        if(strcmp(argv[1],"-h")==0) {
            printDialogue();
            return 0;
        }
        filename = argv[1];
		if(!handleFlags(argc,argv)){
			return 1;
		}

	}

	if (!run_lua(filename)) {
		std::cerr << "Could not open " << filename << std::endl;
		return 1;
	}
}
