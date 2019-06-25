#include <math.h>
#include <PathSegment.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

PathSegment::PathSegment(cv::Point2d start, cv::Point2d end,double radius)
: radius_(radius)
{
    start_ = Point2d(start.x,start.y);
    end_ = Point2d(end.x,end.y);
}     

void LineSegment::draw(cv::Mat& img,
                cv::Point2d shift,
                double scale,
                double thickness,
                cv::Scalar color)
{
    Point start = start_ * scale + shift;
    Point end = end_ * scale + shift;
    cv::line(img,start,end,color,thickness);
}

void ArcSegment::draw(cv::Mat& img,
                cv::Point2d shift,
                double scale,
                double thickness,
                cv::Scalar color)
{
    double start_angle = start_angle_;
    double end_angle = start_angle + angle_;

    if (angle_ < 0)
    {
        swap(start_angle,end_angle);
    }
    cv::ellipse(img,center_ * scale + shift,
    Size(abs(radius_) * scale,abs(radius_) *scale) , 0 , 
    start_angle / M_PI * 180,
    end_angle /M_PI * 180,
    color, thickness);
}

ArcSegment::ArcSegment(cv::Point2d start, cv::Point2d end,double radius)
: PathSegment(start,end,radius),ccw_(radius>0)
{
    // find center
    auto vec = end_ - start_;
    double direction = atan2(vec.y,vec.x);
    double direction_n = direction + (radius_>0?1:-1) * M_PI/2;
    auto n = cv::Point2d(cos(direction_n),sin(direction_n));
    double norm = sqrt(radius_ * radius_ - vec.x * vec.x/4 - vec.y * vec.y/4);
    center_ = norm * n + (start_ + end_)/2;

    // calculate angle and length
    auto center_to_start = start_ - center_;
    auto center_to_end = end_ - center_;
    start_angle_ =  atan2(center_to_start.y,center_to_start.x);
    end_angle_ = atan2(center_to_end.y,center_to_end.x);

    angle_ = end_angle_ - start_angle_;

    if (angle_ > M_PI) angle_-= (M_PI * 2);
    else if (angle_ < -M_PI) angle_ += (M_PI * 2);

    length_ = abs(angle_ * radius_);

}