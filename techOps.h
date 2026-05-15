


#ifndef DATALINE_STRINGVIEW_CLASS_H
#define DATALINE_STRINGVIEW_CLASS_H


#pragma once
#include <string_view>
#include "ConfigClass.h"
#include <iostream>


namespace techOps
{
    //success
    inline constexpr std::string_view kSeparated = "files separated successfully";
    inline constexpr std::string_view kMerged = "files merged successfully";
    inline constexpr std::string_view kSuccess = "mission complete";

    //errors
    inline constexpr std::string_view kFileOpenError = "Cannot open file: ";
    inline constexpr std::string_view kRamTooLow = "for this file ram to small";
    inline constexpr std::string_view kDataUnitTooBig = "Data unit too big";
    inline constexpr std::string_view kCreateOutputFailed = "error make outputFile";

    inline constexpr std::string kEndNameForSeparated = "SortedPartN";

    // Info
    inline constexpr std::string_view kInputIsEmpty = "Input directory is empty";
    inline constexpr std::string_view kTechIsEmpty = "Tech directory is empty";
    inline constexpr std::string_view kFailed = "task not completed";

    //constants
    constexpr int kMin = 30 * 1024 * 1024;
    constexpr int kMid = 40 * 1024 * 1024;
    constexpr int kHigh = 50 * 1024 * 1024;

    constexpr int kExtrm = 70 * 1024 * 1024;
    constexpr size_t kSizeULL = sizeof(uint64_t);

    size_t calcBufSz(const ConfigClass& config);

    uint64_t maxFileParts(const ConfigClass& config);

}

#endif //DATALINE_STRINGVIEW_CLASS_H