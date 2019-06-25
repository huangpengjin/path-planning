#include <vector>
#include <tinyxml2.h>
#include <opencv2/core.hpp>
#include <PathSegment.h>

/**
 * @brief a class of path
 */
class Path
{
    public:
        Path(int id = -1):id_(id),is_forward_(true){};
        ~Path() = default;

        bool isForward(){return is_forward_;}

        /**
         * @brief parse a path from a string
         * @param str 
         * @return success or not
         */
        bool parseFromString(std::string str);

        void draw(cv::Mat& img,
                cv::Point2d shift,
                double scale = 1,
                double thickness = 1,
                cv::Scalar color = cv::Scalar(0,0,255));

        std::vector<cv::Point2d> getNodes(){return nodes_;}

    private:
        int id_;
        bool is_forward_;
        
        std::vector<PathSegmentPtr> path_segments_;
        std::vector<cv::Point2d> nodes_;

};