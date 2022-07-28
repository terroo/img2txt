#include "img2txt.hpp"

std::string Img2Txt::get_text(const std::string& path){
    std::string str {};

    cv::Mat im = cv::imread(path, cv::IMREAD_COLOR);

    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();

    ocr->Init(NULL, "por", tesseract::OEM_LSTM_ONLY);

    ocr->SetPageSegMode(tesseract::PSM_AUTO);

    ocr->SetImage(im.data, im.cols, im.rows, 3, im.step);

    str = std::string(ocr->GetUTF8Text());
    ocr->End();

    return str;
}
