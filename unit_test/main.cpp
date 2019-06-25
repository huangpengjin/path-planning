#include <iostream>
#include <PathParser.h>
#include <PathDrawer.h>

using namespace std;
int main(int arg, char** argc)
{
    cerr<<"Hello world"<<endl;

    if (arg < 2) 
    {
        cerr<<"please input the full path of the xml file"<<endl;
        return -1;
    }

    PathParser parser;
    auto paths = parser.parseFromXmlFile(argc[1]);

    PathDrawer drawer(1000,900);
    drawer.draw(paths,0);

    return 0;
}