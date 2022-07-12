#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include "bit_sequence.h"
#include "handler.h"
#include "translator.h"


int init();

int main(int argc, char* argv[]){
#ifdef __CMAKE_DEBUG__
    char input_path[256] =       "../input/input.txt";
    char output_path[256] =      "../output/output.txt";
    char commentless_path[256] = "../temp/commentless.txt";
    char setless_path[256] =     "../temp/setless.txt";
    char segmentless_path[256] = "../temp/segmentless.txt";
    char aliasless_path[256] =   "../temp/aliasless.txt";
    char segidless_path[256] =   "../temp/segidless.txt";
    char sepaless_path[256] =    "../temp/sepaless.txt";
#elif defined __CMAKE_RELEASE__
    char input_path[256] =       "./input.txt";
    char output_path[256] =      "./output.txt";
    char commentless_path[256] = "./commentless.txt";
    char setless_path[256] =     "./setless.txt";
    char segmentless_path[256] = "./segmentless.txt";
    char aliasless_path[256] =   "./aliasless.txt";
    char segidless_path[256] =   "./segidless.txt";
    char sepaless_path[256] =    "./sepaless.txt";
#endif

    if(argc > 1){
        for(int i=1; i<=argc-1; i++){
            if( (!std::strcmp(argv[i], "-i")) || (!std::strcmp(argv[i], "-I")) ){
                if(argc < i+2){
                    std::cout << "[ERROR] There is no input path entered after parameter \"-i\"." << std::endl;
                    return -1;
                }
                std::ifstream in(argv[i + 1]);
                if(!in){
                    std::cout << "[ERROR] Invalid input file path: " << argv[i + 1] << " ." << std::endl;
                    return -1;
                }
                else {
                    strcpy(input_path, argv[i + 1]);
                    in.close();
                }
            }

            if( (!std::strcmp(argv[i], "-r")) || (!std::strcmp(argv[i], "-R")) ){
                if(argc < i+2){
                    std::cout << "[ERROR] There is no directory for storing temporary files entered after parameter \"-r\"." << std::endl;
                    return -1;
                }
                char temp_directory[256];
                std::strcpy(temp_directory, argv[i + 1]);
                if( std::strlen(temp_directory) - 1 >=0 && temp_directory[std::strlen(temp_directory) - 1] == '/' ){
                    std::strcpy(commentless_path, temp_directory);
                    std::strcat(commentless_path, "commentless.txt");
                    std::strcpy(setless_path, temp_directory);
                    std::strcat(setless_path, "setless.txt");
                    std::strcpy(segmentless_path, temp_directory);
                    std::strcat(segmentless_path, "segmentless.txt");
                    std::strcpy(aliasless_path, temp_directory);
                    std::strcat(aliasless_path, "aliasless.txt");
                    std::strcpy(segidless_path, temp_directory);
                    std::strcat(segidless_path, "segidless.txt");
                    std::strcpy(sepaless_path, temp_directory);
                    std::strcat(sepaless_path, "sepaless.txt");
                }
                else{
                    std::strcpy(commentless_path, temp_directory);
                    std::strcat(commentless_path, "commentless.txt");
                    std::strcpy(setless_path, temp_directory);
                    std::strcat(setless_path, "setless.txt");
                    std::strcpy(segmentless_path, temp_directory);
                    std::strcat(segmentless_path, "segmentless.txt");
                    std::strcpy(aliasless_path, temp_directory);
                    std::strcat(aliasless_path, "aliasless.txt");
                    std::strcpy(segidless_path, temp_directory);
                    std::strcat(segidless_path, "segidless.txt");
                    std::strcpy(sepaless_path, temp_directory);
                    std::strcat(sepaless_path, "sepaless.txt");
                }

                std::ofstream temp(commentless_path);
                if(!temp){
                    std::cout << "[ERROR] Invalid directory for storing temporary files: " << argv[i + 1] << " ." << std::endl;
                    return -1;
                }
                else
                    temp.close();
            }

            if( (!std::strcmp(argv[i], "-o")) || (!std::strcmp(argv[i], "-O")) ){
                if(argc < i+2){
                    std::cout << "[ERROR] There is no output path entered after parameter \"-o\"." << std::endl;
                    return -1;
                }
                std::ofstream out(argv[i + 1]);
                if(!out){
                    std::cout << "[ERROR] Invalid output file path: " << argv[i + 1] << " ." << std::endl;
                    return -1;
                }
                else {
                    strcpy(output_path, argv[i + 1]);
                    out.close();
                }
            }

            if( (!std::strcmp(argv[i], "-help")) || (!std::strcmp(argv[i], "--help")) ){
                std::printf("cg -i (input file path)\n");
                std::printf("cg -r (path for storing temporary files)\n");
                std::printf("cg -o (output file path)\n");
                std::printf("example:\n");
                std::printf("cg -i ./cluster_0.txt -o ./cluster_0_machine_code.txt\n");
                std::printf("cg -i ./cluster_0.txt -t ./temp/ -o./cluster_0_machine_code.txt\n");
                return 0;
            }
        }
    }
    std::printf("input file path:  %s;\n", input_path);
    std::printf("temporary file:   %s\n", commentless_path);
    std::printf("                  %s\n", setless_path);
    std::printf("                  %s\n", segmentless_path);
    std::printf("                  %s\n", aliasless_path);
    std::printf("                  %s\n", segidless_path);
    std::printf("                  %s\n", sepaless_path);
    std::printf("output file path: %s;\n", output_path);

    /** DO NOT CHANGE EASILY **/
//    operation_code_init();
//    assembly_format_init();
//    instruction_format_init();
    init();
    int error = 0;
    error += comments_hide(input_path, commentless_path);
    error += reg_alias_extract(commentless_path, setless_path);
    error += segment_id_extract(setless_path, segmentless_path);
    error += alias_substitute(segmentless_path, aliasless_path);
    error += segment_id_substitute(aliasless_path, segidless_path);
    error += imm_separation_remove(segidless_path, sepaless_path);
    error += translate(sepaless_path, segmentless_path, output_path, "instrs");
    if(error == 0)
        std::cout << "Machine code generation has been done. No error occurred.";
    else
        std::cout << "There are errors. Please look the console output for detail.";
    return 0;
}


