#include <iostream>
#include <opencv2/highgui.hpp>
#include <Path.h>
#include <PathParser.h>

using namespace std;
using namespace cv;

std::map<int,std::shared_ptr<Path>> PathParser::parseFromXmlFile(std::string filename)
{
    tinyxml2::XMLDocument doc;
    auto res = doc.LoadFile(filename.c_str());

    if (res != tinyxml2::XMLError::XML_SUCCESS)
    {
        cerr<<"error reading xml file, the error code is "<<res<<endl;
        return map<int,std::shared_ptr<Path>>();
    }

    return parseFromXmlElement(doc.FirstChildElement("Paths"));
}


std::map<int,std::shared_ptr<Path>> PathParser::parseFromXmlElement(tinyxml2::XMLElement* element)
{
    if (!element) 
    {
        cerr<<"invalid input parameter"<<endl;
        return map<int,std::shared_ptr<Path>>();
    }
    map<int,std::shared_ptr<Path>> paths;

    auto path_element = element->FirstChildElement("Path");

    while (path_element)
    {
        int id;
        auto res = path_element->QueryIntAttribute("No",&id);
        //cerr<<"parsing path no."<<id<<endl;

        if (res == tinyxml2::XMLError::XML_SUCCESS)
        {
            auto ch = path_element->Attribute("Detail");
            auto path = make_shared<Path>(id);
            if (path->parseFromString(string(ch)))
            {
                if (paths.find(id) == paths.end())
                {
                    paths.insert(std::make_pair(id,path));
                }
                else
                {
                    cerr<<"duplicated path id:"<<id<<endl;
                }
            }
            else
            {
                cerr<<"error parsing path string,path id:"<<id<<endl;
            }
        }
        else
        {
            cerr<<"error parsing path id"<<endl;
        }

        path_element = path_element->NextSiblingElement("Path");
    }

    return paths;
}
