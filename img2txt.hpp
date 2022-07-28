#ifndef IMG2TXT_H
#define IMG2TXT_H

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include <string>

class Img2Txt {
    public:
        std::string get_text(const std::string &);
};

#endif // IMG2TXT_H
