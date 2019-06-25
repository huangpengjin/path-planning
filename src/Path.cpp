#include <Path.h>
#include <string>
#include <iostream>

using namespace std;
using namespace cv;

bool Path::parseFromString(std::string str)
{
    string temp;
    stringstream ss(str);

    // parse forward or backward
    getline(ss,temp,';');
    if (temp.compare("B")!=0 && temp.compare("F")!=0)
    {
        cerr<<"invalid input string: no \"F\" or \"B\""<<endl;
        return false;
    }
    is_forward_ = temp.compare("F") == 0;

    std::vector<double> radius;
    // parse segments
    while(getline(ss,temp,';'))
    {
        stringstream segment_stream(temp);
        Point2d segment;
        double r;
        segment_stream >> segment.x;
        getline(segment_stream,temp,',');
        segment_stream >> segment.y;
        getline(segment_stream,temp,',');
        segment_stream >> r;
        nodes_.push_back(segment);
        radius.push_back(r);
    }

    if (nodes_.size()<2)
    {
        cerr<<"invalid input string: not enough points"<<endl;
        return false;
    }

    // create path segments
    for (auto i = 0; i < nodes_.size() - 1; i++)
    {
        PathSegmentPtr path_segment;
        if (radius[i+1]==0)
        {
            path_segment = make_shared<LineSegment>(
                nodes_[i],nodes_[i+1]);
        }
        else
        {
            path_segment = make_shared<ArcSegment>(
                nodes_[i],nodes_[i+1],radius[i+1]);
        }
        path_segments_.push_back(path_segment);

    }

    return true;
}

void Path::draw(cv::Mat& img,
                cv::Point2d shift,
                double scale,
                double thickness,
                cv::Scalar color)
{
    for (auto path_segment : path_segments_)
    {
        path_segment->draw(img,shift,scale,thickness);
    }
}