#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
using namespace testing;

class Image
{
public:
	Image(int const height, int const width) : height(height), width(width) {}
	int GetHeight() const { return height; }
	int GetWidth() const { return width; }
	int GetNumLayers() const { return static_cast<int>(data.size()); }
	vector<int**> data;
	
private:
	int const height, width;
};

enum PixelColor
{
	Black = 0,
	White = 1,
	Transparent = 2
};

// Function declarations;
int FindLayerWithLeastZeros(Image const& image);
int NumberOfSpecificDigitInLayer(Image const& image, int const layer, int const digit);
Image* CreateImage(istream& stream, int const height, int const width);
void PrintDecodedImage(Image const& decodedImage);
Image* CreateDecodedImage(Image const& encodedImage);

int FindLayerWithLeastZeros(Image const& image)
{
	int layerLeastZeros = 0;
	int leastZeros = NumberOfSpecificDigitInLayer(image, 0, 0);
		
	for (int layer = 1; layer < image.GetNumLayers(); ++layer)
	{
		int const numZeros = NumberOfSpecificDigitInLayer(image, layer, 0);

		if (numZeros < leastZeros)
		{
			layerLeastZeros = layer;
			leastZeros = numZeros;
		}
	}
	return layerLeastZeros;
}

int NumberOfSpecificDigitInLayer(Image const& image, int const layer, int const digit)
{
	int digitCount = 0;
	for (int h = 0; h < image.GetHeight(); ++h)
	{
		for (int w = 0; w < image.GetWidth(); ++w)
		{
			if (image.data[layer][h][w] == digit)
			{
				digitCount++;
			}
		}
	}
	return digitCount;
}

Image* CreateImage(istream& stream, int const height, int const width)
{
	auto image = new Image(height, width);
	int const buffLength = height * width;
	char* buff = new char[buffLength];
	while(stream.peek() != EOF)
	{
		stream.read(buff, buffLength);
		
		// Allocate new array
		int** imageLayer = new int*[height];
		for (int i = 0; i < height; ++i)
			imageLayer[i] = new int[width];
		image->data.push_back(imageLayer);
		
		for (int h = 0; h < height; ++h)
		{
			for (int w = 0; w < width; ++w)
			{
				// Convert character value to actual int value.
				imageLayer[h][w] = buff[h*width+w] - '0';
			}
		}
	}
	
	delete[] buff;
	
	return image;
}

Image* CreateDecodedImage(Image const& encodedImage)
{
	int const height = encodedImage.GetHeight();
	int const width = encodedImage.GetWidth();
	Image* decodedImage = new Image(encodedImage.GetHeight(), encodedImage.GetWidth());

	int** imageLayer = new int* [height];
	for (int i = 0; i < height; ++i)
		imageLayer[i] = new int[width];
	decodedImage->data.push_back(imageLayer);

	// Set all pixels to transparent in decoded image
	for (int h = 0; h < decodedImage->GetHeight(); ++h)
	{
		for(int w = 0; w < decodedImage->GetWidth(); ++w)
		{
			decodedImage->data[0][h][w] = Transparent;
		}
	}

	for (int layer = 0; layer < encodedImage.GetNumLayers(); ++layer)
	{
		for(int h = 0; h < height; ++h)
		{
			for (int w = 0; w < width; ++w)
			{
				if (decodedImage->data[0][h][w] == Transparent && encodedImage.data[layer][h][w] != Transparent)
				{
					decodedImage->data[0][h][w] = encodedImage.data[layer][h][w];
				}
			}
		}
	}	

	return decodedImage;
}

void PrintDecodedImage(Image const& decodedImage)
{
	int const height = decodedImage.GetHeight();
	int const width = decodedImage.GetWidth();
	cout << "P1" << endl;
	cout << width << " " << height << endl;
	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			cout << decodedImage.data[0][h][w] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

TEST(Day8TestSuite, Test_NumberOfSpecificDigitInLayer)
{
	string const imageData = "123000225411";
	stringstream ss(imageData);
	int const imageWidth = 3;
	int const imageHeight = 2;
	auto const actualImage = CreateImage(ss, imageHeight, imageWidth);
	
	{
		int const digit = 0;
		int const layer = 0;
		int const expectedNumDigits = 3;
		int const actualNumDigits = NumberOfSpecificDigitInLayer(*actualImage, layer, digit);
		EXPECT_EQ(expectedNumDigits, actualNumDigits);
	}
	{
		int const digit = 2;
		int const layer = 0;
		int const expectedNumDigits = 1;
		int const actualNumDigits = NumberOfSpecificDigitInLayer(*actualImage, layer, digit);
		EXPECT_EQ(expectedNumDigits, actualNumDigits);
	}
	{
		int const digit = 2;
		int const layer = 1;
		int const expectedNumDigits = 2;
		int const actualNumDigits = NumberOfSpecificDigitInLayer(*actualImage, layer, digit);
		EXPECT_EQ(expectedNumDigits, actualNumDigits);
	}
	{
		int const digit = 4;
		int const layer = 1;
		int const expectedNumDigits = 1;
		int const actualNumDigits = NumberOfSpecificDigitInLayer(*actualImage, layer, digit);
		EXPECT_EQ(expectedNumDigits, actualNumDigits);
	}
}

TEST(Day8TestSuite, Test_FindLayerWithLeastZeros)
{
	{
		string const imageData = "111000111110";
		stringstream ss(imageData);
		int const imageWidth = 3;
		int const imageHeight = 2;
		auto const actualImage = CreateImage(ss, imageHeight, imageWidth);
		int const layerWithLeastZeros = FindLayerWithLeastZeros(*actualImage);
		EXPECT_EQ(1, layerWithLeastZeros);
	}
	{
		string const imageData = "123111225411";
		stringstream ss(imageData);
		int const imageWidth = 3;
		int const imageHeight = 2;
		auto const actualImage = CreateImage(ss, imageHeight, imageWidth);
		int const layerWithLeastZeros = FindLayerWithLeastZeros(*actualImage);
		EXPECT_EQ(0, layerWithLeastZeros);
	}

}

TEST(Day8TestSuite, ExampleImage)
{
	string const imageData = "123456789012";
	stringstream ss(imageData);
	int const imageWidth = 3;
	int const imageHeight = 2;
	int const imageNumLayers = 2;
	int expectedImage[imageNumLayers][imageHeight][imageWidth] = {
		{
			{1,2,3},
			{4,5,6}
		},
		{
			{7,8,9},
			{0,1,2}
		}
	};

	auto const actualImage = CreateImage(ss, imageHeight, imageWidth);

	for (int layer = 0; layer < imageNumLayers; ++layer)
	{
		for (int height = 0; height < imageHeight; ++height)
		{
			for (int width = 0; width < imageWidth; ++width)
			{
				EXPECT_EQ(expectedImage[layer][height][width], actualImage->data[layer][height][width]);
			}
		}
	}

	EXPECT_EQ(imageWidth, actualImage->GetWidth());
	EXPECT_EQ(imageHeight, actualImage->GetHeight());
	EXPECT_EQ(imageNumLayers, actualImage->GetNumLayers());
}

TEST(Day8TestSuite, ExampleDecodedImage)
{
	string const imageData = "0222112222120000";
	stringstream ss(imageData);
	int const imageWidth = 2;
	int const imageHeight = 2;
	int const imageNumLayers = 1;
	int expectedDecodedImage[imageHeight][imageWidth] = {
		{0,1},
		{1,0}
	};

	auto const actualImage = CreateImage(ss, imageHeight, imageWidth);
	auto const actualDecodedImage = CreateDecodedImage(*actualImage);

	EXPECT_EQ(imageWidth, actualDecodedImage->GetWidth());
	EXPECT_EQ(imageHeight, actualDecodedImage->GetHeight());
	EXPECT_EQ(imageNumLayers, actualDecodedImage->GetNumLayers());
	
	for (int height = 0; height < imageHeight; ++height)
	{
		for (int width = 0; width < imageWidth; ++width)
		{
			EXPECT_EQ(expectedDecodedImage[height][width], actualDecodedImage->data[0][height][width]);
		}
	}
}


TEST(Day8TestSuite, Part1)
{
	int const width = 25;
	int const height = 6;
	string const filePath = "src/input.txt";
	ifstream fin(filePath);
	if (!fin.is_open())
		throw exception("File not found");

	Image* const image = CreateImage(fin, height, width);
	int const layerWithLeastZeros = FindLayerWithLeastZeros(*image);
	int const num1Digits = NumberOfSpecificDigitInLayer(*image, layerWithLeastZeros, 1);
	int const num2Digits = NumberOfSpecificDigitInLayer(*image, layerWithLeastZeros, 2);

	int const answer = num1Digits * num2Digits;
	cout << answer << endl;
	EXPECT_EQ(answer, 2048);
}

TEST(Day8TestSuite, Part2)
{
	int const width = 25;
	int const height = 6;
	string const filePath = "src/input.txt";
	ifstream fin(filePath);
	if (!fin.is_open())
		throw exception("File not found");

	Image* const image = CreateImage(fin, height, width);
	Image* const decodedImage = CreateDecodedImage(*image);

	// Outputs string in PBM format.
	PrintDecodedImage(*decodedImage);

	//EXPECT_EQ(answer, HFYAK);
}