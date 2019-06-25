#include <map>
#include <memory>

class Path;
/**
 * @brief a simple drawer of the paths
 */
class PathDrawer
{
    public:
        PathDrawer(int width = 640,int height = 480);
        
        /**
         * @brief main function of the drawer
         * 
         * @param paths paths to be drawn
         * @param ms waitkey time
         */
        void draw(std::map<int, std::shared_ptr<Path>> paths, int ms);

    private:
        int image_width_;
        int image_height_;
};