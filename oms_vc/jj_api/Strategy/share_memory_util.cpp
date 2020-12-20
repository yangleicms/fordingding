#include "share_memory_util.h"
#include <fstream>

void share_memory_util::ReleasePageBuffer(void *buffer, long long size, bool quickMode)
{
#ifdef __linux__
	if (!quickMode && munlock(buffer, size) != 0)
	{
		perror("ERROR in munlock");
		exit(EXIT_FAILURE);
	}

	if (munmap(buffer, size) != 0)
	{
		perror("ERROR in munmap");
		exit(EXIT_FAILURE);
	}
#else
	UnmapViewOfFile(buffer);
#endif
}

bool share_memory_util::FileExists(const std::string& filename)
{
#ifdef __linux__
	int fd = open(filename.c_str(), O_RDONLY, (mode_t)0600);
	if (fd >= 0)
	{
		close(fd);
		return true;
	}
	return false;
#else
	std::ifstream f(filename.c_str());
	return f.good();
#endif

}
