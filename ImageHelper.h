#ifndef IMAGEHELPER_H
#define IMAGEHELPER_H

#include <queue>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>

class Blob;

class ImageHelper
{
public:
	ImageHelper();
	~ImageHelper();

	static void convertToGreyScale( const cv::Mat& in, cv::Mat& out );
	static QImage matToQImage( const cv::Mat& in );
	static void floodFill(cv::Mat& img, cv::Point point, int newColor, std::vector<cv::Point>& list_point);
	static void removeBackground(std::vector<Blob>& list_blob, cv::Mat& mat_blob);
	static double findZoomSize(int originalSize, int zoomValue);
};

#endif // IMAGEHELPER_H
