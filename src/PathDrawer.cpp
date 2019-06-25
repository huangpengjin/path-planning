#include <set>
#include <Path.h>
#include <PathDrawer.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

PathDrawer::PathDrawer(int width,int height)
: image_width_(width),image_height_(height)
{

}

void PathDrawer::draw(std::map<int, std::shared_ptr<Path>> paths, int ms)
{
    
    // TODO 
    // auto adjust shift, scale
    Mat img(image_height_,image_width_,CV_8UC3,Scalar(255,255,255));

    for (auto path:paths)
    {
        path.second->draw(img,Point2d(0,0),12);
    }

    imshow("Path",img); 
    waitKey(ms);

}