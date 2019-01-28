#include <iostream>
#include <Poco/URI.h>

#include <Poco/Zip/Decompress.h>
#include <Poco/Delegate.h>

#include <fstream>
#include <string>

void unzipFileToDest(Poco::Path compressedPath, const std::string& destination)
{
    std::ifstream inp(compressedPath.toString().c_str(), std::ios::binary);
    Poco::Zip::Decompress dec(inp, Poco::Path(destination, Poco::Path::Style::PATH_GUESS));
    dec.decompressAllFiles();
}


int main(int, char**)
{
    std::string pathToZip;
    std::cout << "Input the absolute path to the zipped AG_Dependencies: " << std::endl;
    std::cin >> pathToZip;

    std::string destinationPath;
    std::cout << "Input the path to deposit the unzipped dependencies: " << std::endl;
    std::cin >> destinationPath;
    unzipFileToDest(pathToZip, destinationPath);

    std::cout << "How will you be invoking CMake?\n[1] Visual Studio\n[2] Visual Studio Code\n[3] CMake Command Line" << std::endl;
    int cMakeInterface;
    std::cin >> cMakeInterface;

    switch (cMakeInterface)
    {
        case 1:
        {
            std::cout << "VS" << std::endl;
            break;
        }
        case 2:
        {
            std::cout << "VSC" << std::endl;

            break;
        }
    
        default:
        {
            std::cout << "CMD" << std::endl;
            break;
        }
    }

    return 0;
}
