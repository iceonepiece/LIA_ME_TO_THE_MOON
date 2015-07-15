#include "FatProcessor.h"
#include "qdebug.h"

FatProcessor::FatProcessor()
{
	svm.load("Training/fat_training.xml");
}

FatProcessor::~FatProcessor()
{

}

void FatProcessor::processWithOption(DataImage* image)
{
	FatImage* img_fat = (FatImage*)image;

	removeNonFatBlob(img_fat->mat_blob, img_fat->list_blob, img_fat->data_edited->mat_model, (FatOption*)img_fat->option);
}

void FatProcessor::process( DataImage* image, bool option )
{
	FatImage* img_fat = (FatImage*)image;

	if (!img_fat->hasProcessed)
	{
		cv::Mat mat_grey;
		ImageHelper::convertToGreyScale(img_fat->mat_original, mat_grey);

		cv::Mat mat_blob(mat_grey.rows, mat_grey.cols, CV_8UC1);

		tranformImage(mat_grey, mat_blob);

		cv::Mat mat_cloneBlob = mat_blob.clone();

		findContours(mat_cloneBlob, img_fat->list_blob);

		FeatureExtractor::findAreaAndCircularity(img_fat->list_blob);
		FeatureExtractor::findAverageGreyLevel(mat_grey, mat_blob, img_fat->list_blob);

		ImageHelper::removeBackground( img_fat->list_blob, mat_blob );
		
		img_fat->mat_blob = mat_blob.clone();

		findMinMaxBlobSize(img_fat);
		img_fat->hasProcessed = true;
	}

	if (option)
	{
		removeNonFatBlob(img_fat->mat_blob, img_fat->list_blob, img_fat->data_edited->mat_model, (FatOption*)img_fat->option );
	}
	else
	{
		removeNonFatBlob(img_fat->mat_blob, img_fat->list_blob, img_fat->data_edited->mat_model);
	}

}

void FatProcessor::classify(DataImage* image)
{
	FatImage* img_fat = (FatImage*)image;

	removeNonFatBlob(img_fat->mat_blob, img_fat->list_blob, img_fat->data_processed->mat_model);

}

void FatProcessor::copy(DataImage* image)
{
	this->copy(image->data_processed, image->data_edited);
}

void FatProcessor::setupOption(DataImage* image)
{
	FatOption* fatOption = (FatOption*)image->option;
	FatImage* fatImage = (FatImage*)image;

	fatOption->min_size = fatOption->min_blobSize = fatImage->minBlobSize;
	fatOption->max_size = fatOption->max_blobSize = fatImage->maxBlobSize;
	fatOption->min_circularity = 0;
	fatOption->max_circularity = 100;
}

void FatProcessor::process(Data* data, DataOption* option )
{
	data->mat_model = cv::Mat(data->mat_original.rows, data->mat_original.cols, CV_8UC1);

	cv::Mat mat_grey;
	ImageHelper::convertToGreyScale(data->mat_original, mat_grey);

	cv::Mat mat_blob(mat_grey.rows, mat_grey.cols, CV_8UC1);

	tranformImage(mat_grey, mat_blob);

	cv::Mat mat_cloneBlob = mat_blob.clone();

	std::vector<Blob> list_blob;
	findContours(mat_cloneBlob, list_blob);

	FeatureExtractor::findAreaAndCircularity(list_blob);
	FeatureExtractor::findAverageGreyLevel(mat_grey, mat_blob, list_blob);

	//detectBackground( mat_blob, list_blob );
	
	if (option == nullptr)
	{
		removeNonFatBlob(mat_blob, list_blob, data->mat_model);

	}
	else
		removeNonFatBlob(mat_blob, list_blob, data->mat_model, (FatOption*)option );

	//computePercentage( (FatData*)data );

}

void FatProcessor::findMinMaxBlobSize( FatImage* fatImage )
{
	std::vector<Blob>& list_blob = fatImage->list_blob;

	float min, max;

	if (list_blob.size() == 0)
	{
		min = max = -1;
		return;
	}

	int i = 0;
	for (; i < list_blob.size(); i++)
	{
		if (list_blob[i].type == Blob::BACKGROUND)
			continue;

		min = max = list_blob[i].area;
		break;
	}

	float area;

	for (; i < list_blob.size(); i++)
	{
		if (list_blob[i].type == Blob::BACKGROUND)
			continue;

		area = list_blob[i].area;
		if (area < min)
			min = area;

		if (area > max)
			max = area;
	}

	fatImage->minBlobSize = min;
	fatImage->maxBlobSize = max;
}

void FatProcessor::copy(Data* from, Data* to)
{
	FatData* fromFat = (FatData*)from;
	FatData* toFat = (FatData*)to;

	toFat->mat_model = fromFat->mat_model.clone();
	toFat->mat_display = fromFat->mat_display.clone();
	toFat->px_bg = fromFat->px_bg;
	toFat->px_tissue = fromFat->px_tissue;
	toFat->px_fat = fromFat->px_fat;
	toFat->px_nonFat = fromFat->px_nonFat;
	toFat->percentage = fromFat->percentage;
}


void FatProcessor::computePercentage( Data* data )
{
	FatData* data_fat = (FatData*)data;

	data_fat->px_bg = 0;
	data_fat->px_tissue = 0;
	data_fat->px_fat = 0;
	data_fat->px_nonFat = 0;

	for (int i = 0; i < data_fat->mat_model.rows; i++)
	{

		for (int j = 0; j < data_fat->mat_model.cols; j++)
		{
			if (data_fat->mat_model.at<uchar>(i, j) == BG_COLOR)
				data_fat->px_bg++;

			else if (data_fat->mat_model.at<uchar>(i, j) == TISSUE_COLOR)
				data_fat->px_tissue++;

			else if (data_fat->mat_model.at<uchar>(i, j) == FAT_COLOR)
				data_fat->px_fat++;

			else if (data_fat->mat_model.at<uchar>(i, j) == NON_FAT_COLOR)
				data_fat->px_nonFat++;

		}
	}

	
	data_fat->percentage = 100.0 * data_fat->px_fat / (float)(data_fat->px_tissue + data_fat->px_nonFat + data_fat->px_fat );
	
}

void FatProcessor::tranformImage( cv::Mat& input, cv::Mat& output )
{
	cv::Mat mat_temp1, mat_temp2;

	//lowpass filter
	cv::GaussianBlur(input, mat_temp1, cv::Size(7, 7), 1.5);

	//binarization process threshold 220
	cv::threshold(mat_temp1, mat_temp2, 220, 255, cv::THRESH_BINARY);

	//Morphological openning
	cv::Mat element = cv::getStructuringElement(cv::MORPH_OPEN, cv::Size(9, 9));
	cv::morphologyEx(mat_temp2, output, cv::MORPH_OPEN, element);
}

void FatProcessor::findContours(const cv::Mat& mat_blob, std::vector<Blob>& list_blob)
{
	std::vector<Contour> list_contour;
	cv::findContours(mat_blob, list_contour, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (Contour contour : list_contour)
	{
		Blob blob;
		blob.contour = contour;
		list_blob.push_back(blob);
	}
}


void FatProcessor::removeNonFatBlob(const cv::Mat& mat_blob, const cv::vector<Blob>& list_blob, cv::Mat& output, FatOption* opt_fat )
{
	output = mat_blob.clone();

	for (int i = 0; i < list_blob.size(); i++)
	{
		if (list_blob[i].type == Blob::BACKGROUND)
			continue;


		if ((
			(opt_fat->min_size <= (int)list_blob[i].area) && (opt_fat->max_size >= (int)list_blob[i].area)
			)
			&&
			(
				(opt_fat->min_circularity / 100.0 <= list_blob[i].circularity) && (list_blob[i].circularity <= opt_fat->max_circularity / 100.0 )
			))
			continue;

		cv::floodFill(output, list_blob[i].contour[1], 200);

	}

}

void FatProcessor::removeNonFatBlob(const cv::Mat& mat_blob, const cv::vector<Blob>& list_blob, cv::Mat& output)
{
	output = mat_blob.clone();
	//create a vector to store features
	cv::Mat vect_feature(1, 3, CV_32FC1);

	//Normalization data with max min
	for (int i = 0; i < list_blob.size(); i++)
	{
		if ( list_blob[i].type == Blob::BACKGROUND )
			continue;

		float area = list_blob[i].area;
		if ( area > 3000 )
			area = 3000;

		vect_feature.at<float>(0, 0) = MathHelper::normalize(area, 1, 3000);
		vect_feature.at<float>(0, 1) = MathHelper::normalize(list_blob[i].circularity, 0, 1);
		vect_feature.at<float>(0, 2) = MathHelper::normalize(list_blob[i].avgGrayLevel, 0, 255);

		float response = svm.predict(vect_feature, 3);

		//qDebug() << "res: " << response;
		/*	cout <<"++++++ RES +++++++ : "<< respones << endl;*/
		if ( response > 0 )
		{
			cv::floodFill(output, list_blob[i].contour[1], 200);
		}
	}

}


void FatProcessor::highlight( Data* data_fat )
{

	cv::Mat& mat_model = data_fat->mat_model;
	cv::Mat& mat_display = data_fat->mat_display;
	cv::Mat& mat_original = data_fat->mat_original;

	for (int i = 0; i < mat_model.rows; i++)
	{
		for (int j = 0; j < mat_model.cols; j++)
		{
		
			if (mat_model.at<uchar>(i, j) == FAT_COLOR) 
			{	
				mat_display.at<cv::Vec3b>(i, j)[0] = mat_original.at<cv::Vec3b>(i, j)[0] / 2;			//R  *because orgImg and displayImg is RGB, not BGR
				mat_display.at<cv::Vec3b>(i, j)[1] = (mat_original.at<cv::Vec3b>(i, j)[1] + 255) / 2;	//G
				mat_display.at<cv::Vec3b>(i, j)[2] = mat_original.at<cv::Vec3b>(i, j)[2] / 2;			//B
			}

			else if (mat_model.at<uchar>(i, j) == BG_COLOR) 
			{ 
				mat_display.at<cv::Vec3b>(i, j)[0] = 128;
				mat_display.at<cv::Vec3b>(i, j)[1] = 128;
				mat_display.at<cv::Vec3b>(i, j)[2] = 128;
			}

			else 
			{ 
				mat_display.at<cv::Vec3b>(i, j)[0] = mat_original.at<cv::Vec3b>(i, j)[0];	//R *because orgImg and displayImg is RGB, not BGR
				mat_display.at<cv::Vec3b>(i, j)[1] = mat_original.at<cv::Vec3b>(i, j)[1];	//G
				mat_display.at<cv::Vec3b>(i, j)[2] = mat_original.at<cv::Vec3b>(i, j)[2];	//B
			}
		}
	}
}

bool FatProcessor::click(Data* data, int x, int y)
{
	FatData* fatData = (FatData*)data;
	cv::Mat& mat_model = fatData->mat_model;

	if (mat_model.at<uchar>(y, x) == FAT_COLOR )
	{
		std::vector<cv::Point> points;
		ImageHelper::floodFill(mat_model, cv::Point(x, y), NON_FAT_COLOR, points);

		int numPixels = points.size();

		fatData->px_fat -= numPixels;
		fatData->px_nonFat += numPixels;

		this->miniComputePercentage(data);
		this->miniHighlight(data, points);

		return true;
	}

	if (mat_model.at<uchar>(y, x) == NON_FAT_COLOR)
	{
		std::vector<cv::Point> points;
		ImageHelper::floodFill(mat_model, cv::Point(x, y), FAT_COLOR, points);
		int numPixels = points.size();
		
		fatData->px_fat += numPixels;
		fatData->px_nonFat -= numPixels;

		this->miniComputePercentage(data);
		this->miniHighlight(data, points);

		return true;
	}

	return false;
}

void FatProcessor::miniComputePercentage(Data* data)
{
	FatData* data_fat = (FatData*)data;
	data_fat->percentage = 100.0 * data_fat->px_fat / (float)(data_fat->px_tissue + data_fat->px_nonFat + data_fat->px_fat);
}

void FatProcessor::miniHighlight( Data* data, std::vector<cv::Point>& list_point)
{
	cv::Mat& mat_model = data->mat_model;
	cv::Mat& mat_display = data->mat_display;
	cv::Mat& mat_original = data->mat_original;

	int i, j;

	for (cv::Point point : list_point)
	{
		i = point.y;
		j = point.x;

		if (mat_model.at<uchar>(i, j) == FAT_COLOR)
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