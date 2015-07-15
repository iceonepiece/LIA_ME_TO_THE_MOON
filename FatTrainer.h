#ifndef FATTRAINER_H
#define FATTRAINER_H

#include <string>
#include <vector>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include "FatProcessor.h"
#include "FeatureExtractor.h"

class FatTrainer 
{

public:

	static const int FAT_COLOR = 0;
	static const int NON_FAT_COLOR = 128;
	static const int FAT_LABEL = 1;
	static const int NON_FAT_LABEL = 0;

	FatTrainer();
	~FatTrainer();

	static void train(std::string path);
	static void convertBlobToVector(const std::vector<Blob>& list_blob, cv::Mat& vect_feature, cv::Mat& vect_label);
	static std::vector<std::string> getListFromFile(std::string path);
	static void findContoursFromGt(const cv::Mat& mat_blob, std::vector<Blob>& list_blob);
	static void produceBlobs(const cv::Mat& mat_blob, int color, int label, std::vector<Blob>& list_blob);
	static void detectColor(const cv::Mat& img, const int color, cv::Mat& out);
	static void extractFeatures( cv::Mat& mat_original, std::vector<Contour>& list_contour, std::vector<Blob>& list_blob);
	static float normalize(float x, float min, float max);
	static void trainSVM(const cv::Mat& vect_feature, const cv::Mat& vect_label);

	
};

#endif // FATTRAINER_H
