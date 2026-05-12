//
// Created by Lev on 07.05.2026.
//

#ifndef DATALINE_SETLIMIT_H
#define DATALINE_SETLIMIT_H


#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>


#if defined(_WIN32) || defined(_WIN64)

    #include <windows.h>
    constexpr bool isWindows = true;
    constexpr bool isLinux = false;
    constexpr bool isUnix = false;
    constexpr bool isMac = false;

#elif defined(__APPLE__)

    #include <unistd.h>
    #include <TargetConditionals.h>
    constexpr bool isWindows = false;
    constexpr bool isLinux = false;
    constexpr bool isUnix = true;
    constexpr bool isMac = true;

#elif defined(__linux__)

    #include <sys/resource.h>
    constexpr bool isWindows = false;
    constexpr bool isLinux = true;
    constexpr bool isUnix = true;
    constexpr bool isMac = false;

#elif defined(__unix__)

    #include <unistd.h>
    constexpr bool isWindows = false;
    constexpr bool isLinux = false;
    constexpr bool isUnix = true;
    constexpr bool isMac = false;

#else

    #error "Unsupported platform"
    constexpr bool isWindows = false;
    constexpr bool isLinux = false;
    constexpr bool isUnix = false;
    constexpr bool isMac = false;

#endif


constexpr char ramTooLow[] = "ram to low\n";
constexpr char memorySet[] = "memory limit set to: ";
constexpr char failedMemorySet[] = "memory was not set ";

inline void setLimit(uint64_t maxRamValue)
{

    if (maxRamValue == 0)
    {
        std::cerr << ramTooLow << std::endl;
        exit(1);
    }

    #if defined(_WIN32) || defined(_WIN64)
    {
        SIZE_T maxRam = maxRamValue;
        HANDLE hJob = CreateJobObject(nullptr, nullptr);

        if (!hJob)
        {
            std::cerr << "CreateJobObject failed: " << GetLastError() << std::endl;
            exit(1);
        }

        JOBOBJECT_EXTENDED_LIMIT_INFORMATION jobInfo = {};
        jobInfo.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_PROCESS_MEMORY;
        jobInfo.ProcessMemoryLimit = maxRam;

        if (!SetInformationJobObject(hJob, JobObjectExtendedLimitInformation, &jobInfo, sizeof(jobInfo)))
        {
            std::cerr << "SetInformationJobObject failed " << GetLastError() << std::endl;
            CloseHandle(hJob);
            exit(1);
        }

        if (!AssignProcessToJobObject(hJob, GetCurrentProcess()))
        {
            std::cerr << "AssignProcessToJobObject failed: " << GetLastError() << std::endl;
            CloseHandle(hJob);
            exit(1);
        }

        std::cout << memorySet << maxRamValue << " bytes" << std::endl;
        CloseHandle(hJob);
    }

    #elif defined(__APPLE__) || defined(__linux__) || defined(__unix__)
    {
        rlim_t maxRam = static_cast<rlim_t>(maxRamValue);
        struct rlimit memLimit;

        if (getrlimit(RLIMIT_AS, &memLimit) != 0)
        {
            std::cerr << "failed to get memory limit: " << strerror(errno) << std::endl;
            exit(1);
        }

        if (maxRam > memLimit.rlim_max && maxRam != RLIM_INFINITY)
        {
            std::cerr << "memory limit " << maxRamValue
                      << " exceeds system hard limit: " << memLimit.rlim_max
                      << std::endl;
            exit(1);
        }

        memLimit.rlim_cur = maxRam;

        if (setrlimit(RLIMIT_AS, &memLimit) != 0)
        {
            std::cerr << failedMemorySet << strerror(errno) << std::endl;
            exit(1);
        }

        std::cout << memorySet << maxRamValue << " bytes" << std::endl;
    }
    #else
    {
        std::cerr << "sorry, your operating system is not supported" << std::endl;
        exit(1);
    }
    #endif
}

#endif //DATALINE_SETLIMIT_H