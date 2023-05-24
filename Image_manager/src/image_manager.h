#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <string>

class ImageManager {
public:
    void renameFiles(const std::string& folderPath, const std::string& prefix);
    void convertFormat(const std::string& folderPath, const std::string& newFormat);
    void resizeImages(const std::string& folderPath, int width, int height);
    void scaleImages(const std::string& folderPath, double scaleFactor);
};

#endif // IMAGE_MANAGER_H
