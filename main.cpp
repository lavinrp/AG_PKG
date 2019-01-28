#include <iostream>
#include <Poco/URI.h>
#include <Poco/Net/HTTPStreamFactory.h>
#include <Poco/Net/FTPStreamFactory.h>
#include <Poco/URIStreamOpener.h>
#include <Poco/StreamCopier.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

#include <Poco/Zip/Decompress.h>
#include <Poco/Delegate.h>

#include <memory>
#include <fstream>
#include <iostream>

class ZipThing
{
public:
    void onZipError(const void* pSender, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string>& info)
    {
        std::cout << "hey man. Errors here" << std::endl;
    }
    void DownloadDependencies(const std::string& uriString, const std::string& destination)
    {
        Poco::URI uri(uriString);
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, uriString, Poco::Net::HTTPMessage::HTTP_1_1);
        session.sendRequest(req);
        Poco::Net::HTTPResponse res;
        std::istream& rs = session.receiveResponse(res);
        Poco::Zip::Decompress dec(rs, Poco::Path(destination, Poco::Path::Style::PATH_GUESS));
        // if an error happens invoke the ZipTest::onDecompressError method
        dec.EError += Poco::Delegate<ZipThing, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string> >(this, &ZipThing::onZipError);
        dec.decompressAllFiles();
        dec.EError -= Poco::Delegate<ZipThing, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string> >(this, &ZipThing::onZipError);
    } 
};


int main(int, char**) {
    Poco::Net::HTTPStreamFactory::registerFactory();
    Poco::Net::FTPStreamFactory::registerFactory();

    try
    {
        ZipThing z;
        z.DownloadDependencies("https://github.com/lavinrp/GameBackbone/archive/master.zip", "/home/lavinrp/hdd/programming/cpp/AG_PKG/AG_PKG");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}



// download.cpp

// This sample demonstrates the URIStreamOpener class.

// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

// SPDX-License-Identifier:	BSL-1.0



// #include "Poco/URIStreamOpener.h"
// #include "Poco/StreamCopier.h"
// #include "Poco/Path.h"
// #include "Poco/URI.h"
// #include "Poco/Exception.h"
// #include "Poco/Net/HTTPStreamFactory.h"
// #include "Poco/Net/FTPStreamFactory.h"
// #include <memory>
// #include <iostream>


// using Poco::URIStreamOpener;
// using Poco::StreamCopier;
// using Poco::Path;
// using Poco::URI;
// using Poco::Exception;
// using Poco::Net::HTTPStreamFactory;
// using Poco::Net::FTPStreamFactory;


// int main(int argc, char** argv)
// {
// 	HTTPStreamFactory::registerFactory();
// 	FTPStreamFactory::registerFactory();
	
// 	if (argc != 2)
// 	{
// 		Path p(argv[0]);
// 		std::cerr << "usage: " << p.getBaseName() << " <uri>" << std::endl;
// 		std::cerr << "       Download <uri> to standard output." << std::endl;
// 		std::cerr << "       Works with http, ftp and file URIs." << std::endl;
// 		return 1;
// 	}

// 	try
// 	{
// 		URI uri(argv[1]);
// 		std::unique_ptr<std::istream> pStr(URIStreamOpener::defaultOpener().open(uri));
// 		StreamCopier::copyStream(*pStr.get(), std::cout);
// 	}
// 	catch (Exception& exc)
// 	{
// 		std::cerr << exc.displayText() << std::endl;
// 		return 1;
// 	}
		
// 	return 0;
// }
