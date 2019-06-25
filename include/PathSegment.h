#include <opencv2/core.hpp>
#include <memory>

/**
 * @brief virtual base class of path segments
 */
class PathSegment
{
    public:
        PathSegment(cv::Point2d start, cv::Point2d end, double radius);

        /**
         * @brief draw this segment on an image
         * @param img the image 
         * @param shift the drawing offset
         * @param scale the drawing scale
         * @param thickness line thickness
         */
        virtual void draw(  cv::Mat& img,
                            cv::Point2d shift,
                            double scale = 1,
                            double thickness = 1,
                            cv::Scalar color = cv::Scalar(0,0,255) ) = 0;
        
        double getLength(){return length_;}
        cv::Point2d getStartPoint(){return start_;}
        cv::Point2d getEndPoint(){return end_;}
        double getRadius(){return radius_;}
    protected:
        cv::Point2d start_;
        cv::Point2d end_;
        double radius_;
        double length_;
};

typedef std::shared_ptr<PathSegment> PathSegmentPtr;

/**
 * @brief class of line segment
 */
class LineSegment : public PathSegment
{
    public:

        LineSegment(cv::Point2d start, cv::Point2d end)
        : PathSegment(start,end,0)
        {
            length_ = cv::norm(start_-end_);
        }

       virtual void draw(  cv::Mat& img,
                            cv::Point2d shift,
                            double scale = 1,
                            double thickness = 1,
                            cv::Scalar color = cv::Scalar(0,0,0));

};

/**
 * @brief class of arc segment
 */
class ArcSegment : public PathSegment
{
    public:
        ArcSegment(cv::Point2d start, cv::Point2d end,double radius);

        virtual void draw(  cv::Mat& img,
                            cv::Point2d shift,
                            double scale = 1,
                            double thickness = 1,
                            cv::Scalar color = cv::Scalar(0,0,0) );
    protected:
        cv::Point2d center_; 
        double angle_;
        double start_angle_;
        double end_angle_;
        bool ccw_;
};

