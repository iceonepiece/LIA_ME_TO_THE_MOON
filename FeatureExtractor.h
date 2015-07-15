#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Blob.h"

class FeatureExtractor
{
public:
	FeatureExtractor();
	~FeatureExtractor();

	static void extractFat(const cv::Mat& mat_original, std::vector<Blob>& list_blob);
	static void findAreaAndCircularity(std::vector<Blob>& list_blob);
	static void findAverageGreyLevel(const cv::Mat& mat_grey, const cv::Mat& mat_blob, std::vector<Blob>& list_blob);
	
};

#endif // FEATUREEXTRACTOR_H
