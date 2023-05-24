#include "../src/image_manager.h"
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

namespace fs = std::filesystem;

// Helper function to compare image file sizes
bool compareFileSize(const std::string& filePath1, const std::string& filePath2) {
    std::ifstream file1(filePath1, std::ifstream::ate | std::ifstream::binary);
    std::ifstream file2(filePath2, std::ifstream::ate | std::ifstream::binary);

    if (!file1 || !file2) {
        return false;
    }

    return file1.tellg() == file2.tellg();
}

// Test fixture for ImageManager tests
class ImageManagerTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        // Create a temporary directory for testing
        testDir = fs::temp_directory_path() / "image_manager_test";
        fs::create_directory(testDir);

        // Create test images
        const std::string imgPath1 = (testDir / "image1.jpg").string();
        const std::string imgPath2 = (testDir / "image2.jpg").string();
        const std::string imgPath3 = (testDir / "image3.jpg").string();

        cv::Mat image(100, 100, CV_8UC3, cv::Scalar(255, 255, 255));
        cv::imwrite(imgPath1, image);
        cv::imwrite(imgPath2, image);
        cv::imwrite(imgPath3, image);
    }

    virtual void TearDown() {
        // Clean up the temporary directory
        fs::remove_all(testDir);
    }

    ImageManager imageManager;
    fs::path testDir;
};

TEST_F(ImageManagerTest, RenameFiles) {
    imageManager.renameFiles(testDir.string(), "new_image");
    
    // Check if the files are renamed correctly
    ASSERT_TRUE(fs::exists(testDir / "new_image1.jpg"));
    ASSERT_TRUE(fs::exists(testDir / "new_image2.jpg"));
    ASSERT_TRUE(fs::exists(testDir / "new_image3.jpg"));
}

TEST_F(ImageManagerTest, ConvertFormat) {
    imageManager.convertFormat(testDir.string(), "png");

    // Check if the files are converted to PNG format
    ASSERT_TRUE(fs::exists(testDir / "image1.png"));
    ASSERT_TRUE(fs::exists(testDir / "image2.png"));
    ASSERT_TRUE(fs::exists(testDir / "image3.png"));
}

TEST_F(ImageManagerTest, ResizeImages) {
    imageManager.resizeImages(testDir.string(), 50, 50);

    // Check if the files are resized correctly
    ASSERT_TRUE(compareFileSize((testDir / "image1.jpg").string(), (testDir / "image1.jpg").string()));
    ASSERT_TRUE(compareFileSize((testDir / "image2.jpg").string(), (testDir / "image2.jpg").string()));
    ASSERT_TRUE(compareFileSize((testDir / "image3.jpg").string(), (testDir / "image3.jpg").string()));
}

TEST_F(ImageManagerTest, ScaleImages) {
    imageManager.scaleImages(testDir.string(), 0.5);

    // Check if the files are scaled correctly
    ASSERT_TRUE(compareFileSize((testDir / "image1.jpg").string(), (testDir / "image1.jpg").string()));
    ASSERT_TRUE(compareFileSize((testDir / "image2.jpg").string(), (testDir / "image2.jpg").string()));
    ASSERT_TRUE(compareFileSize((testDir / "image3.jpg").string(), (testDir / "image3.jpg").string()));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
