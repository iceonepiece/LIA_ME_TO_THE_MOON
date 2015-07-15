#include "FeatureExtractor.h"
#include "qdebug.h"

FeatureExtractor::FeatureExtractor()
{

}

FeatureExtractor::~FeatureExtractor()
{

}

void FeatureExtractor::extractFat(const cv::Mat& mat_original, std::vector<Blob>& list_blob)
{
	findAreaAndCircularity(list_blob);

	cv::Mat mat_grey;
	cv::cvtColor(mat_original, mat_grey, CV_BGR2GRAY);
	//findAverageGreyLevel(mat_grey, list_blob);
}

void FeatureExtractor::findAreaAndCircularity(std::vector<Blob>& list_blob)
{
	double area, perimeter, circularity;

	for (int i = 0; i < list_blob.size(); i++ )
	{
		area = cv::contourArea(list_blob[i].contour, 0);
		perimeter = cv::arcLength(list_blob[i].contour, 1);
		circularity = (4 * 3.14159 * area) / (perimeter*perimeter);

		list_blob[i].area = area;
		list_blob[i].circularity = circularity;

	}

}

void FeatureExtractor::findAverageGreyLevel( const cv::Mat& mat_grey, const cv::Mat& mat_blob, std::vector<Blob>& list_blob )
{
	double sum;
	cv::Mat mat_tempBlob;
	mat_tempBlob = mat_blob.clone();

	for (int i = 0; i < list_blob.size(); i++ )
	{
		std::vector<cv::Point> list_point;
		
		ImageHelper::floodFill(mat_tempBlob, list_blob[i].contour[0], 77, list_point);

		sum = 0;
		for (cv::Point point : list_point)
			sum += mat_grey.at<uchar>(point);

		list_blob[i].avgGrayLevel = sum / list_point.size();
	}
}