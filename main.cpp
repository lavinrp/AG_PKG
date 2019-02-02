
#include "Poco/Exception.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/StreamCopier.h"
#include "Poco/URI.h"
#include "Poco/URIStreamOpener.h"
#include <Poco/Delegate.h>
#include <Poco/Zip/Decompress.h>
#include <Poco/Net/HTTPSStreamFactory.h>


// #include <nana/gui.hpp>
// #include <nana/gui/widgets/label.hpp>


#include <fstream>
#include <iostream>
#include <memory>
#include <string>

void UnzipFileToDest(Poco::Path compressedPath, const std::string& destination)
{
    std::ifstream inp(compressedPath.toString().c_str(), std::ios::binary);
    Poco::Zip::Decompress dec(inp, Poco::Path(destination, Poco::Path::Style::PATH_GUESS));
    dec.decompressAllFiles();
}


void DownloadFile(const std::string& uriToDownload, const std::string& filePathToSave)
{
    std::string content {};
    std::ofstream outFile(filePathToSave, std::ofstream::binary);

    try {
        auto& opener = Poco::URIStreamOpener::defaultOpener();
        auto uri = Poco::URI { uriToDownload };
        auto is = std::shared_ptr<std::istream> { opener.open(uri) };
        Poco::StreamCopier::copyStream(*(is.get()), outFile);
        // Poco::StreamCopier::copyToString(*(is.get()), content);
    } catch (Poco::Exception& e) {
        std::cerr << e.displayText() << std::endl;
    }

    //std::cout << content << std::endl;
    //outFile << content;
}

int TextMode()
{
    // download file
    Poco::Net::HTTPSStreamFactory::registerFactory();
    Poco::Net::HTTPStreamFactory::registerFactory();


    std::string pathToDownload;
    std::cout << "URL to download" << std::endl;
    std::cin >> pathToDownload;
    std::string pathToInstallTo;
    std::cout << "install path" << std::endl;
    std::cin >> pathToInstallTo;
    DownloadFile(pathToDownload, pathToInstallTo);

    // query user for unzip information
    std::string pathToZip;
    std::cout << "Input the absolute path to the zipped AG_Dependencies: " << std::endl;
    std::cin >> pathToZip;

    std::string destinationPath;
    std::cout << "Input the path to deposit the unzipped dependencies: " << std::endl;
    std::cin >> destinationPath;
    UnzipFileToDest(pathToZip, destinationPath);

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

int GuiMode()
{
    // nana::form mainForm;
    // mainForm.caption();
    // //nana::label
    // return 0;
}

int main(int argc, char**)
{
    if (argc == 0)
    {
        return TextMode();
    }
    else
    {
        return GuiMode();
    }
}
