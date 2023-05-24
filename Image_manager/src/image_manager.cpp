#include "image_manager.h"
#include "image_manager.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <filesystem>
#include <fstream>


namespace fs = std::filesystem;
using namespace cv;
using namespace std;

void ImageManager::renameFiles(const std::string& folderPath, const std::string& prefix) {
    int counter = 1;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        const auto& oldPath = entry.path();
        const auto& extension = oldPath.extension().string();
        const auto& newPath = fs::path(oldPath).replace_filename(prefix + std::to_string(counter++) + extension).string();
        fs::rename(oldPath, newPath);
    }
}

void ImageManager::convertFormat(const std::string& folderPath, const std::string& newFormat) {
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        const auto& oldPath = entry.path();
        const auto& newExtension = newFormat == "jpg" ? ".jpg" : ".bmp";
        const auto& newPath = fs::path(oldPath).replace_extension(newExtension).string();
        cv::Mat image = cv::imread(oldPath.string(),1);
        cv::imwrite(newPath, image);
    }
}

void ImageManager::resizeImages(const std::string& folderPath, int width, int height) {
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        const auto& oldPath = entry.path();
        const auto& newPath = fs::path(oldPath).replace_extension(".jpg");
        cv::Mat image = cv::imread(oldPath.string());
        cv::resize(image, image, cv::Size(width, height));
        cv::imwrite(newPath.string(), image);
    }
}

void ImageManager::scaleImages(const std::string& folderPath, double scaleFactor) {
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        const auto& oldPath = entry.path();
        const auto& newPath = fs::path(oldPath).replace_extension(".jpg");
        cv::Mat image = cv::imread(oldPath.string());
        cv::resize(image, image, cv::Size(), scaleFactor, scaleFactor);
        cv::imwrite(newPath.string(), image);
    }
}
