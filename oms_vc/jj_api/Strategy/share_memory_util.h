#define _LARGEFILE_SOURCE
#ifdef __linux__
#define _LARGEFILE64_SOURCE
#endif
#define _FILE_OFFSET_BITS 64
#ifndef SHARE_MEMORY_UTIL_H
#define SHARE_MEMORY_UTIL_H
#include<string>
#include<vector>

#ifdef __linux__
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <unistd.h>
#else
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#endif
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdio>
#include <sstream>

class share_memory_util
{
public:
	inline static share_memory_util * get_instance()
	{
		static share_memory_util util;
		return &util;
	}

public:

	static void*  LoadPageBuffer(const std::string& path, long long size, bool isWriting, bool quickMode)
	{
#ifdef __linux__
		int fd = open(path.c_str(), (isWriting) ? (O_RDWR | O_CREAT | O_LARGEFILE) : O_RDONLY | O_LARGEFILE, (mode_t)0600);

		if (fd < 0)
		{
			if (!isWriting)
				return nullptr;
			perror("Cannot create/write the file");
			exit(EXIT_FAILURE);
		}

		if (isWriting)
		{
			if (lseek64(fd, size - 1, SEEK_SET) == -1)
			{
				close(fd);
				perror("Error calling lseek() to 'stretch' the file");
				exit(EXIT_FAILURE);
			}
			if (write(fd, "", 1) == -1)
			{
				close(fd);
				perror("Error writing last byte of the file");
				exit(EXIT_FAILURE);
			}
		}

		void* buffer = mmap(0, size, (isWriting) ? (PROT_READ | PROT_WRITE) : PROT_READ, MAP_SHARED, fd, 0);

		if (buffer == MAP_FAILED)
		{
			close(fd);
			perror("Error mapping file to buffer");
			exit(EXIT_FAILURE);
		}

		if (!quickMode && madvise(buffer, size, MADV_RANDOM) != 0 && mlock(buffer, size) != 0)
		{
			munmap(buffer, size);
			close(fd);
			perror("Error in madvise or mlock");
			exit(EXIT_FAILURE);
		}

		close(fd);
		return buffer;
#else
		bool master = isWriting || !quickMode;
		HANDLE dumpFileDescriptor = CreateFileA(path.c_str(),
			(master) ? (GENERIC_READ | GENERIC_WRITE) : GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			(master) ? OPEN_ALWAYS : OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (dumpFileDescriptor == INVALID_HANDLE_VALUE)
		{
			printf("unable to mmap for page %s", path.data());
			return nullptr;
		}

		HANDLE fileMappingObject = CreateFileMapping(dumpFileDescriptor,
			NULL,
			(master) ? PAGE_READWRITE : PAGE_READONLY,
			0,
			size,
			NULL);

		if (fileMappingObject == NULL)
		{
			int nRet = GetLastError();
			printf("CreateFileMapping Error = {%d}, {%s}\n", nRet, path.data());
			return nullptr;
		}


		void* buffer = MapViewOfFile(fileMappingObject,
			(master) ? FILE_MAP_ALL_ACCESS : FILE_MAP_READ,
			0,
			0,
			size);

		if (buffer == nullptr)
		{
			int nRet = GetLastError();
			printf("failed to load page %s, MapViewOfFile Error", std::to_string(nRet).data());
			return nullptr;
		}
		return buffer;
#endif
	}

	static void   ReleasePageBuffer(void* buffer, long long size, bool quickMode);

	static bool FileExists(const std::string& filename);

};

#endif //YIJINJING_PAGEUTIL_H
