#include <iostream>
#include "detect.h"

using namespace std;

void format(const std::string& program_name)
{
    std::cout << "Usage: " << program_name << " [--debug] picture_file_path"
              << std::endl;
}

int main(int argc, char ** argv)
{
    // No arguments or more than 2 arguments are refused
    if (argc < 2 || argc > 3)
    {
        format(argv[0]);
        return -1;
    }

    if (argc == 3 && string(argv[1]).compare("--debug") == 0)
        return DetectBarCode(argv[2], true);
    else if (argc == 3 && string(argv[1]).compare("--video") == 0)
        VideoBarCode(argv[2]);
    else if (argc == 2 &&string(argv[1]).compare("--video") == 0)
        return VideoBarCode();
    else
        return DetectBarCode(argv[1]);
}
