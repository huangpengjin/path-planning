#include <string>
#include <map>
#include <tinyxml2.h>
#include <memory>

class Path;
/**
 * @brief a parser of paths
 */
class PathParser
{
    public:
        PathParser() = default;
        ~PathParser() = default;

        /**
         * @brief parse from a xml file
         * @param filename the file name of the xml file
         * @return a map from id to path
         */
        std::map<int,std::shared_ptr<Path>> parseFromXmlFile(std::string filename);

        /**
         * @brief parse from a xml element
         * @param element the xml element
         * @return a map from id to path
         */
        std::map<int,std::shared_ptr<Path>> parseFromXmlElement(tinyxml2::XMLElement* element);

};