#include "FibrosisProcessor.h"
#include "qdebug.h"

FibrosisProcessor::FibrosisProcessor()
{
	svm.load("Training/fibrosis_training.xml");
}

FibrosisProcessor::~FibrosisProcessor()
{

}

void FibrosisProcessor::process(Data* data, DataOption* option)
{

}

void FibrosisProcessor::process(DataImage* image, bool option)
{
	cv::Mat mat_model = cv::Mat(image->mat_original.rows, image->mat_original.cols, CV_8UC1);

	cv::Mat mat_enhanced;

	int meanFib = MEAN_FIBROSIS;
	int meanTis = MEAN_TISSUE;

	if (option)
	{
		meanFib = ((FibrosisOption*)image->option)->meanFib;
		meanTis = ((FibrosisOption*)image->option)->meanTis;
	}

	this->enhance(image->mat_original, mat_enhanced, meanFib, meanTis );

	cv::Mat mat_filtered;
	this->lowPassFilter(mat_enhanced, mat_filtered);

	cv::Mat mat_bg;
	this->detectBackground(image->mat_original, mat_bg);

	this->produceModelImage(mat_filtered, mat_bg);
	

	image->data_edited->mat_model = mat_bg.clone();

	
}

void FibrosisProcessor::computePercentage(Data* data)
{
	FibrosisData* fibData = (FibrosisData*)data;

	fibData->px_bg = 0;
	fibData->px_tissue = 0;
	fibData->px_fib = 0;
	fibData->px_nonFib = 0;

	for (int i = 0; i < fibData->mat_model.rows; i++)
	{
		for (int j = 0; j < fibData->mat_model.cols; j++)
		{
			if (fibData->mat_model.at<uchar>(i, j) == BG_COLOR)
				fibData->px_bg++;

			else if (fibData->mat_model.at<uchar>(i, j) == TISSUE_COLOR)
				fibData->px_tissue++;

			else if (fibData->mat_model.at<uchar>(i, j) == FIBROSIS_COLOR)
				fibData->px_fib++;

			else if (fibData->mat_model.at<uchar>(i, j) == NON_FIBROSIS_COLOR)
				fibData->px_nonFib++;

		}
	}

	fibData->percentage = 100.0 * fibData->px_fib / (fibData->px_tissue + fibData->px_nonFib + fibData->px_fib);
}

void FibrosisProcessor::classify(DataImage* image)
{

}

void FibrosisProcessor::setupOption(DataImage* image)
{
	FibrosisOption* fibOption = (FibrosisOption*)image->option;
	
	fibOption->meanFib = MEAN_FIBROSIS;
	fibOption->meanTis = MEAN_TISSUE;
}

void FibrosisProcessor::highlight(Data* data_fib)
{
	cv::Mat& mat_model = data_fib->mat_model;
	cv::Mat& mat_display = data_fib->mat_display;
	cv::Mat& mat_original = data_fib->mat_original;

	for (int i = 0; i < mat_model.rows; i++)
	{
		for (int j = 0; j < mat_model.cols; j++)
		{

			if (mat_model.at<uchar>(i, j) == FIBROSIS_COLOR) {	//highlight fibrosis
				mat_display.at<cv::Vec3b>(i, j)[0] = mat_original.at<cv::Vec3b>(i, j)[0] / 2;			//R  *because orgImg and displayImg is RGB, not BGR
				mat_display.at<cv::Vec3b>(i, j)[1] = (mat_original.at<cv::Vec3b>(i, j)[1] + 255) / 2;	//G
				mat_display.at<cv::Vec3b>(i, j)[2] = mat_original.at<cv::Vec3b>(i, j)[2] / 2;			//B

			}
			else if (mat_model.at<uchar>(i, j) == BG_COLOR) { // set bg color to blue
				mat_display.at<cv::Vec3b>(i, j)[0] = 255;
				mat_display.at<cv::Vec3b>(i, j)[1] = 0;
				mat_display.at<cv::Vec3b>(i, j)[2] = 0;
			}
			else { //non-fat or tissue
				mat_display.at<cv::Vec3b>(i, j)[0] = mat_original.at<cv::Vec3b>(i, j)[0];	//R *because orgImg and displayImg is RGB, not BGR
				mat_display.at<cv::Vec3b>(i, j)[1] = mat_original.at<cv::Vec3b>(i, j)[1];	//G
				mat_display.at<cv::Vec3b>(i, j)[2] = mat_original.at<cv::Vec3b>(i, j)[2];	//B
			}
		}
	}
}

void FibrosisProcessor::copy(Data* from, Data* to)
{
	FibrosisData* fromFat = (FibrosisData*)from;
	FibrosisData* toFat = (FibrosisData*)to;

	toFat->mat_model = fromFat->mat_model.clone();
	toFat->mat_display = fromFat->mat_display.clone();
	toFat->px_bg = fromFat->px_bg;
	toFat->px_tissue = fromFat->px_tissue;
	toFat->px_fib = fromFat->px_fib;
	toFat->px_nonFib = fromFat->px_nonFib;

	toFat->percentage = fromFat->percentage;
}

void FibrosisProcessor::lowPassFilter( cv::Mat& input, cv::Mat& result)
{
	cv::boxFilter(input, result, -1, cv::Size(7, 7));
}

void FibrosisProcessor::enhance(const cv::Mat& mat_original, cv::Mat& mat_output, int meanFib, int meanTis )
{
	const int rows = mat_original.rows;
	const int cols = mat_original.cols;

	mat_output = mat_original.clone();

	double mF = meanFib;
	double mT = meanTis;
	
	//for each pixel
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//find the distance
			double disT = abs(mT - mat_original.at<cv::Vec3b>(i, j)[2]);
			double disF = abs(mF - mat_original.at<cv::Vec3b>(i, j)[2]);

			//fibrosis
			if ((disT > disF) && (mat_original.at<cv::Vec3b>(i, j)[1] > mat_original.at<cv::Vec3b>(i, j)[2]))
			{
				
				double c = 6 * disF;
				double newVal = mat_original.at<cv::Vec3b>(i, j)[2] - c - 50;
				if (newVal < 0)
					newVal = 0;
				mat_output.at<cv::Vec3b>(i, j)[2] = (uchar)newVal;
			}

			//tissue
			else if ((disT < disF) && (mat_original.at<cv::Vec3b>(i, j)[1] < mat_original.at<cv::Vec3b>(i, j)[2]))
			{
				
				double c = 6 * disT;
				double newVal = mat_original.at<cv::Vec3b>(i, j)[2] + c + 25;
				if (newVal > 255)
					newVal = 255;
				mat_output.at<cv::Vec3b>(i, j)[2] = (uchar)newVal;
			}
		}
	}
}


void FibrosisProcessor::detectBackground(const cv::Mat& mat_original, cv::Mat& mat_output )
{
	cv::Mat mat_gray = mat_original.clone();
	cv::cvtColor(mat_original, mat_gray, CV_BGR2GRAY);

	cv::Mat mat_blurred;
	cv::GaussianBlur(mat_gray, mat_blurred, cv::Size(11, 11), 2.5);

	cv::threshold(mat_blurred, mat_output, 180, 255, cv::THRESH_BINARY);

	std::vector<Contour> list_contour;
	cv::Mat mat_tempBinary = mat_output.clone();
	cv::findContours(mat_tempBinary, list_contour, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	std::vector<Blob> list_blob;
	extractBlobArea( list_blob, list_contour );

	ImageHelper::removeBackground(list_blob, mat_output);
}

void FibrosisProcessor::extractBlobArea( std::vector<Blob>& list_blob, std::vector<Contour>& list_contour)
{
	for (int i = 0; i < list_contour.size(); i++)
	{
		Blob blob;
		blob.area = cv::contourArea(list_contour[i], 0);
		blob.contour = list_contour[i];
		list_blob.push_back(blob);
	}
}

void FibrosisProcessor::produceModelImage(cv::Mat& mat_input, cv::Mat& mat_output)
{

	cv::Mat a_ftVector(1, 4, CV_32FC1);

	//fibrosis

	float min1 = 1 / 256.0;
	float max1 = 256;

	float min2 = 1 / 513.0;
	float max2 = 256 / 258.0;

	float min3 = -255 / 256.0;
	float max3 = 255;

	float min4 = -256 / 513.0;
	float max4 = 255 / 258.0;

	for (int i = 0; i < mat_input.rows; i++)
	{
		for (int j = 0; j < mat_input.cols; j++)
		{
			if (mat_output.at<uchar>(i, j) == BG_COLOR)
				continue;

			float blue = mat_input.at<cv::Vec3b>(i, j)[0] + 1;
			float green = mat_input.at<cv::Vec3b>(i, j)[1] + 1;
			float red = mat_input.at<cv::Vec3b>(i, j)[2] + 1;

			a_ftVector.at<float>(0, 0) = MathHelper::normalize(red, 1, 256);
			a_ftVector.at<float>(0, 1) = MathHelper::normalize((green - red) / blue, min3, max3);
			a_ftVector.at<float>(0, 2) = MathHelper::normalize(red / blue, min1, max1);
			a_ftVector.at<float>(0, 3) = MathHelper::normalize((green - red) / (red + green + blue), min4, max4);


			float response = svm.predict(a_ftVector, 4);

			if (response > 1.5)
			{
				mat_output.at<uchar>(i, j) = FIBROSIS_COLOR;
			}
			else
			{
				mat_output.at<uchar>(i, j) = TISSUE_COLOR;
			}
		}
	}

}

bool FibrosisProcessor::click(Data* data, int x, int y)
{
	FibrosisData* fibData = (FibrosisData*)data;
	cv::Mat& mat_model = fibData->mat_model;

	if (mat_model.at<uchar>(y, x) == FIBROSIS_COLOR )
	{
		std::vector<cv::Point> points;
		ImageHelper::floodFill(mat_model, cv::Point(x, y), NON_FIBROSIS_COLOR, points);

		int numPixels = points.size();

		fibData->px_fib -= numPixels;
		fibData->px_nonFib += numPixels;

		this->miniComputePercentage(data);
		this->miniHighlight(data, points);

		return true;
	}

	if (mat_model.at<uchar>(y, x) == NON_FIBROSIS_COLOR)
	{
		std::vector<cv::Point> points;
		ImageHelper::floodFill(mat_model, cv::Point(x, y), FIBROSIS_COLOR, points);
		int numPixels = points.size();

		fibData->px_fib += numPixels;
		fibData->px_nonFib -= numPixels;

		this->miniComputePercentage(data);
		this->miniHighlight(data, points);

		return true;
	}

	return false;
}


void FibrosisProcessor::miniComputePercentage(Data* data)
{
	FibrosisData* fibData = (FibrosisData*)data;
	fibData->percentage = 100.0 * fibData->px_fib / (fibData->px_tissue + fibData->px_nonFib + fibData->px_fib);
}

void FibrosisProcessor::miniHighlight( Data* data, std::vector<cv::Point>& list_point)
{
	cv::Mat& mat_model = data->mat_model;
	cv::Mat& mat_display = data->mat_display;
	cv::Mat& mat_original = data->mat_original;

	int i, j;

	for (cv::Point point : list_point)
	{
		i = point.y;
		j = point.x;
		
		if (mat_model.at<uchar>(i, j) == FIBROSIS_COLOR) 
		{	
			mat_display.at<cv::Vec3b>(i, j)[0] = mat_original.at<cv::Vec3b>(i, j)[0] / 2;			//R  *because orgImg and displayImg is RGB, not BGR
			mat_display.at<cv::Vec3b>(i, j)[1] = (mat_original.at<cv::Vec3b>(i, j)[1] + 255) / 2;	//G
			mat_display.at<cv::Vec3b>(i, j)[2] = mat_original.at<cv::Vec3b>(i, j)[2] / 2;			//B

		}
		else if (mat_model.at<uchar>(i, j) == BG_COLOR) 
		{ 
			mat_display.at<cv::Vec3b>(i, j)[0] = 255;
			mat_display.at<cv::Vec3b>(i, j)[1] = 0;
			mat_display.at<cv::Vec3b>(i, j)[2] = 0;
		}
		else 
		{ 
			mat_display.at<cv::Vec3b>(i, j)[0] = mat_original.at<cv::Vec3b>(i, j)[0];	//R *because orgImg and displayImg is RGB, not BGR
			mat_display.at<cv::Vec3b>(i, j)[1] = mat_original.at<cv::Vec3b>(i, j)[1];	//G
			mat_display.at<cv::Vec3b>(i, j)[2] = mat_original.at<cv::Vec3b>(i, j)[2];	//B
		}
	}

}