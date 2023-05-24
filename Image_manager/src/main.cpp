#include <iostream>
#include <string>
#include <cxxopts.hpp>
#include "image_manager.h"
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    cxxopts::Options options("ImageManager", "Command-line Image Manager");
    options.add_options()
        ("r,rename", "Rename files in a folder", cxxopts::value<std::string>())
        ("c,convert", "Convert image formats in a folder", cxxopts::value<std::string>())
        ("resize", "Resize images in a folder", cxxopts::value<std::string>())
        ("scale", "Scale images in a folder", cxxopts::value<std::string>())
        ("h,help", "Print help")
        ("man", "Display manual");

    options.parse_positional({ "rename", "convert", "resize", "scale" });

    try {
        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return 0;
        }
        
        if (result.count("man")) {
        std::cout << "Manual or detailed information about your program." << std::endl;
        // Print the detailed information or manual here
        std::cout << "-r remame : $> image_manager.exe -r <Image Directory>" << std::endl;
        std::cout << "-c convert (default coversion to -> bmp): $>image_manager.exe -c <Image Directory>" << std::endl;
        std::cout << "/resize resize image (default 800X600) : $>image_manager.exe /resize <Image Directory>" << std::endl;
        std::cout << "/scale scale image : $>image_manager.exe /scale <Image Directory>" << std::endl;
       
        return 0;
        }


        ImageManager imageManager;

       if (result.count("rename")) {
            std::string folderPath = result["rename"].as<std::string>();
            std::string prefix = "new_image";
       
            if (!std::filesystem::exists(folderPath)) {
                throw std::runtime_error("Folder path does not exist.");
            }

            imageManager.renameFiles(folderPath, prefix);
            std::cout << "Files renamed successfully." << std::endl;
        }

        if (result.count("convert")) {
            std::string folderPath = result["convert"].as<std::string>();
            std::cout << "Folder path: " << folderPath << std::endl; // Print the folder path
            std::string newFormat = "bmp";
            imageManager.convertFormat(folderPath, newFormat);
            std::cout << "Files converted successfully." << std::endl;
        }

        if (result.count("resize")) {
            std::string folderPath = result["resize"].as<std::string>();
            int width = 800;
            int height = 600;
            imageManager.resizeImages(folderPath, width, height);
            std::cout << "Images resized successfully." << std::endl;
        }

        if (result.count("scale")) {
            std::string folderPath = result["scale"].as<std::string>();
            double scaleFactor = 0.5;
            imageManager.scaleImages(folderPath, scaleFactor);
            std::cout << "Images scaled successfully." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Error parsing command-line options: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
