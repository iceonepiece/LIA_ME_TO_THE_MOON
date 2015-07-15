#ifndef FATPROCESSOR_H
#define FATPROCESSOR_H

#include "FeatureExtractor.h"
#include "Processor.h"
#include "FatData.h"
#include "Blob.h"
#include "FatOption.h"
#include "FatImage.h"

class FatProcessor : public Processor
{
public:

	static const uchar TISSUE_COLOR = 0;
	static const uchar BG_COLOR = 128;
	static const uchar NON_FAT_COLOR = 200;
	static const uchar FAT_COLOR = 255;

	static const int NON_FAT_LABEL = 0;
	static const int FAT_LABEL = 1;

	FatProcessor();
	~FatProcessor();

	void processWithOption(DataImage* image);
	void process(DataImage* image, bool option = false );
	void classify(DataImage* image);
	void copy(DataImage* image);
	void setupOption(DataImage* image);

	void process(Data* data, DataOption* option );
	void highlight(Data* data_fat);
	void copy(Data* from, Data* to);
	void computePercentage(Data* data);

	bool click(Data* data, int x, int y);
	void miniComputePercentage(Data* data);
	void miniHighlight( Data* data, std::vector<cv::Point>& list_point);
	
private:
	cv::SVM svm;

	void tranformImage(cv::Mat& input, cv::Mat& output);
	void findContours(const cv::Mat& mat_blob, std::vector<Blob>& list_blob );
	void removeNonFatBlob(const cv::Mat& mat_blob, const cv::vector<Blob>& list_blob, cv::Mat& output);
	void removeNonFatBlob(const cv::Mat& mat_blob, const cv::vector<Blob>& list_blob, cv::Mat& output, FatOption* opt_fat);
	void findMinMaxBlobSize(std::vector<Blob> list_blob, FatData* data_fat);
	void findMinMaxBlobSize(FatImage* fatImage);

};

#endif // FATPROCESSOR_H
