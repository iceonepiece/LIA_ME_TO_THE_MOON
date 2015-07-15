#ifndef FIBROSISPROCESSOR_H
#define FIBROSISPROCESSOR_H

#include "Processor.h"
#include "Blob.h"

class FibrosisProcessor : public Processor
{
public:

	static const uchar TISSUE_COLOR = 255;
	static const uchar BG_COLOR = 128;
	static const uchar NON_FIBROSIS_COLOR = 200;
	static const uchar FIBROSIS_COLOR = 0;

	FibrosisProcessor();
	~FibrosisProcessor();

	void process(DataImage* image, bool option = false );
	void classify(DataImage* image);
	void copy(Data* from, Data* to);
	void setupOption(DataImage* image);
	void highlight(Data* data_fat);
	void process(Data* data, DataOption* option);
	void computePercentage(Data* data);
	
	bool click(Data* data, int x, int y);
	void miniComputePercentage(Data* data);
	void miniHighlight(Data* data, std::vector<cv::Point>& list_point);

private:

	const int MEAN_TISSUE = 126;
	const int MEAN_FIBROSIS = 110;

	cv::SVM svm;
	
	void enhance(const cv::Mat& mat_original, cv::Mat& mat_output, int meanFib, int meanTis );
	void lowPassFilter(cv::Mat& input, cv::Mat& result);
	void detectBackground(const cv::Mat& mat_original, cv::Mat& mat_output);
	void extractBlobArea( std::vector<Blob>& list_blob, std::vector<Contour>& list_contour);
	void produceModelImage(cv::Mat& mat_input, cv::Mat& mat_output);
};

#endif // FIBROSISPROCESSOR_H
