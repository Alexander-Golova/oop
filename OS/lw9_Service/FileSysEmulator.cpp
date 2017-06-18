#include "stdafx.h"
#include "FileSysEmulator.h"

using namespace std;
using namespace std::placeholders;

typedef map<string, function<void(string &args)>> ActionMap;

const string DISK_FILE_EXT = ".disk";
const size_t START_DATA_OFFSET = 16;

#define DISK_HEADER_SIZE 16
#define CLUSTER_MINIMAL_SIZE 64

#define INVALID_OFFSET_VALUE 0xFFFFFFFF
#define FILE_NOT_EXIST   0x0001
#define FILE_ATTR_NORMAL 0x0002

struct BlockHeader
{
	BlockHeader()
	{
		memcpy(name, "\0\0\0\0\0\0\0\0\0", 9);
		memcpy(ext, "\0\0\0\0", 4);

		size = 0;
		attrib = 0;
		next = INVALID_OFFSET_VALUE;
	}

	uint32_t size;
	char name[9];
	char ext[4];
	uint16_t attrib;
	size_t next;
};

#define FIND_BY_SIZE     1
#define FIND_BY_NAME     2
#define FIND_BY_EXT      4
#define FIND_BY_ATTRIB   8
#define FIND_SIZE_LESS  16
#define FIND_SIZE_EQUAL 32
#define FIND_SIZE_MORE  64

ActionMap g_actionMap;

HANDLE g_hFile = INVALID_HANDLE_VALUE;
HANDLE g_hMapping = INVALID_HANDLE_VALUE;
uint8_t *g_diskData = nullptr;
stringstream g_strm;

// ----------------------------------------------------------------------------
// Interactions with users
// ----------------------------------------------------------------------------
void CreateActionMap();


void CreateDiskCommand(string &args);
void MountCommand(string &args);
void UnMountCommand(string &args);
void FormatCommand(string &args);
void WriteCommand(string &args);
void ReadCommand(string &args);
void DirCommand(string &args);
void DeleteCommand(string &args);
void SqueezeCommand(string &args);
void MapCommand(string &args);

string GetDiskFileNameFromArgs(string &args);
void GetDiskFileNameAndSizeFromArgs(string &args, string &name, size_t &size);

string GetStringArg(string &args);
string GetStringArgEx(string &args, const string &pattern);
int GetNumberArg(string &args);

// ----------------------------------------------------------------------------
// Implementation of file system logic
// ----------------------------------------------------------------------------
void CreateDisk(const string &diskFileName, size_t diskSize);
void MountDisk(const string &diskFileName, HANDLE &hDiskFile, HANDLE &hDiskMapping, uint8_t **diskData);
void UnMountDisk(HANDLE &hDiskFile, HANDLE &hDiskMapping, uint8_t **diskData);
void FormatDisk(void *diskData);

void WriteFileToDisk(const string &fileName, void *diskData);
size_t GetExternalFileSize(const string &fileName);
void ReadExternalFile(const string &fileName, char *diskData, size_t count);
void ParseFileNameAndSaveInHeader(const string &fileName, BlockHeader &fileHeader);

void ReadFileFromDisk(const string &sourceFile, const string &destFile, void *diskData);
void WriteExternalFile(void *diskData, size_t offset, const string &fileName);

size_t FindEnoughSpaceToWriteFile(void *diskData, size_t size);
size_t FindFileByHeader(void *diskData, BlockHeader &header, uint32_t options);
size_t FindFileByName(void *diskData, const string &fileName);

void CheckMatchBlockHeadersBySize(bool &match, const BlockHeader &found, const BlockHeader &source, uint32_t options);
void CheckMatchBlockHeadersByAttrib(bool &match, const BlockHeader &found, const BlockHeader &source, uint32_t options);
void CheckMatchBlockHeadersByName(bool &match, const BlockHeader &found, const BlockHeader &source, uint32_t options);
void CheckMatchBlockHeadersByExt(bool &match, const BlockHeader &found, const BlockHeader &source, uint32_t options);

void Dir(void *diskData);
void DeleteFileFromDisk(const string &fileName, void *diskData);

void SqueezeDiskData(void *diskData);
void ReduceBlockAndMoveNextBlockUp(void *diskData, size_t offset, BlockHeader &header, BlockHeader &nextHeader);
void BlockMoveUp(void* diskData, BlockHeader &header, size_t newOffset, size_t oldOffset);

BlockHeader ReadBlockHeader(void* diskData, size_t offset);
void WriteBlockHeader(void *diskData, const BlockHeader &header, size_t offset);

size_t GetBlockSize(void *diskData, size_t offset);
size_t GetDiskSize(void *diskData);

bool BlockIsEmpty(const BlockHeader &header);
bool BlockIsNotEmpty(const BlockHeader &header);
bool IsFileLessThanBlock(void* diskData, size_t offset);

string GetFileNameFromHeader(const BlockHeader &header);
size_t GetFileSizeByHeader(const BlockHeader &header);

void AssertDiskMounted(void *diskData);
void AssertDiskFormat(void *diskData);

void ShowDiskMap(void *diskData);
void PrintSymbol(char symbol, size_t count);

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Interactions with users
// ----------------------------------------------------------------------------

void StartFileSystemEmulator()
{
	CreateActionMap();
}

void GetFileSystemEmulatorInfo()
{
	g_strm << "File system emulator service, v. 1.0" << endl;
	g_strm << "(c) Mikhail Glizerin, 2017" << endl;
}


bool HandleCommand(const string &cmd)
{
	string command = cmd;

	g_strm.clear();
	g_strm.str("");

	string action = GetStringArg(command);
	auto it = g_actionMap.find(action);

	if (it != g_actionMap.end())
	{
		try
		{
			it->second(command);
		}
		catch (exception &e)
		{
			g_strm << "Exec error: " << e.what() << endl;
		}

		return true;
	}

	g_strm << "Unknown command!" << endl;

	return false;
}

string GetActionResultMessage()
{
	return g_strm.str();
}

void CreateActionMap()
{
	g_actionMap.clear();

	g_actionMap.insert(make_pair("crdisk", bind(&CreateDiskCommand, _1)));
	g_actionMap.insert(make_pair("mount", bind(&MountCommand, _1)));
	g_actionMap.insert(make_pair("unmount", bind(&UnMountCommand, _1)));
	g_actionMap.insert(make_pair("format", bind(&FormatCommand, _1)));
	g_actionMap.insert(make_pair("write", bind(&WriteCommand, _1)));
	g_actionMap.insert(make_pair("read", bind(&ReadCommand, _1)));
	g_actionMap.insert(make_pair("dir", bind(&DirCommand, _1)));
	g_actionMap.insert(make_pair("delete", bind(&DeleteCommand, _1)));
	g_actionMap.insert(make_pair("squeeze", bind(&SqueezeCommand, _1)));
	g_actionMap.insert(make_pair("map", bind(&MapCommand, _1)));
}

void CreateDiskCommand(string &args)
{
	string diskFileName;
	size_t diskSize;

	GetDiskFileNameAndSizeFromArgs(args, diskFileName, diskSize);
	CreateDisk(diskFileName += DISK_FILE_EXT, diskSize);

	g_strm << "Disk <" << diskFileName << "> was successfully created" << endl;
}

void MountCommand(string &args)
{
	string diskFileName = GetDiskFileNameFromArgs(args);

	if (diskFileName == "")
	{
		throw logic_error("Cannot mount disk file (invalid name value)");
	}

	if (g_diskData != nullptr)
	{
		UnMountDisk(g_hFile, g_hMapping, &g_diskData);
	}

	MountDisk(diskFileName += DISK_FILE_EXT, g_hFile, g_hMapping, &g_diskData);

	g_strm << "Disk <" << diskFileName << "> was successfully mounted" << endl;
}

void UnMountCommand(string &args)
{
	UnMountDisk(g_hFile, g_hMapping, &g_diskData);

	g_strm << "Current disk was successfully unmounted" << endl;
}

void FormatCommand(string &args)
{
	FormatDisk(g_diskData);

	g_strm << "Current disk was format successfully" << endl;
}

void WriteCommand(string &args)
{
	string fileName = GetStringArgEx(args, "[A-Za-z0-9.]+");
	WriteFileToDisk(fileName, g_diskData);

	g_strm << "File " << fileName << " was write successfully" << endl;
}

void ReadCommand(string &args)
{
	string sourceFile = GetStringArgEx(args, "[A-Za-z0-9.]+");
	string destFile = GetStringArgEx(args, "[A-Za-z0-9.]+");

	ReadFileFromDisk(sourceFile, destFile, g_diskData);

	g_strm << "File " << sourceFile << " was read successfully as file " << destFile << endl;
}

void DirCommand(string &args)
{
	Dir(g_diskData);
}

void DeleteCommand(string &args)
{
	string fileName = GetStringArgEx(args, "[A-Za-z0-9.]+");
	DeleteFileFromDisk(fileName, g_diskData);

	g_strm << "File " << fileName << " was delete successfully" << endl;
}

void SqueezeCommand(string &args)
{
	SqueezeDiskData(g_diskData);

	g_strm << "Disk data was squeezed successfully" << endl;
}

void MapCommand(string& args)
{
	ShowDiskMap(g_diskData);
}

string GetDiskFileNameFromArgs(string &args)
{
	return GetStringArgEx(args, "[A-Za-z0-9]+");
}

void GetDiskFileNameAndSizeFromArgs(string &args, string &name, size_t &size)
{
	name = GetDiskFileNameFromArgs(args);

	if (name == "")
	{
		throw logic_error("Cannot create disk file (invalid name value)");
	}

	try
	{
		size = GetNumberArg(args);
	}
	catch (invalid_argument &e)
	{
		throw logic_error(e.what());
	}
}

string GetStringArg(string &args)
{
	return GetStringArgEx(args, "[A-Za-z]+");
}

string GetStringArgEx(string &args, const string &pattern)
{
	smatch searchResult;
	regex rgx(pattern);

	if (regex_search(args, searchResult, rgx))
	{
		string value = searchResult.str();
		args = searchResult.suffix().str();

		return value;
	}

	return "";
}

int GetNumberArg(string &args)
{
	smatch searchResult;
	regex rgx("[0-9]+");

	if (!regex_search(args, searchResult, rgx))
	{
		throw invalid_argument("GetNumberArg error: invalid argument value!");
	}

	string value = searchResult.str();
	args = searchResult.suffix().str();

	return atoi(value.c_str());
}

// ----------------------------------------------------------------------------
// Implementation of file system logic
// ----------------------------------------------------------------------------

void CreateDisk(const string &diskFileName, size_t diskSize)
{
	if (ifstream(diskFileName))
	{
		throw logic_error("Cannot create disk file (already exists)");
	}

	ofstream output(diskFileName, ofstream::binary);

	if (!output.is_open())
	{
		throw logic_error("Failed to create disk <" + diskFileName + ">");
	}

	// Записать размер диска
	output.write((char*)&diskSize, sizeof(diskSize));

	// Остальное пространство диска заполнить нулями
	for (size_t i = 0; i < diskSize - sizeof(diskSize); ++i)
	{
		output.write("\0", 1);
	}
}

void MountDisk(const string &diskFileName, HANDLE &hDiskFile, HANDLE &hDiskMapping, uint8_t **diskData)
{
	hDiskFile = CreateFile(wstring(diskFileName.begin(), diskFileName.end()).c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hDiskFile == INVALID_HANDLE_VALUE)
	{
		throw logic_error("Failed to open disk file <" + diskFileName + ">");
	}

	auto diskFileSize = GetFileSize(hDiskFile, nullptr);

	if (diskFileSize == INVALID_FILE_SIZE)
	{
		throw logic_error("Failed to get size of disk file <" + diskFileName + ">");
	}

	hDiskMapping = CreateFileMapping(hDiskFile, nullptr, PAGE_READWRITE, 0, 0, nullptr);

	if (hDiskMapping == nullptr)
	{
		throw logic_error("Failed to mapped disk file <" + diskFileName + ">");
	}

	*diskData = (uint8_t*)MapViewOfFile(hDiskMapping, FILE_MAP_ALL_ACCESS, 0, 0, diskFileSize);

	if (*diskData == nullptr)
	{
		throw logic_error("Failed to view map of disk file <" + diskFileName + ">");
	}
}

void UnMountDisk(HANDLE &hDiskFile, HANDLE &hDiskMapping, uint8_t **diskData)
{
	AssertDiskMounted(*diskData);

	if (!FlushViewOfFile(*diskData, 0))
	{
		throw logic_error("Failed to flush disk file");
	}

	if (!UnmapViewOfFile(*diskData))
	{
		throw logic_error("Failed to unmap disk file");
	}

	CloseHandle(hDiskMapping);
	CloseHandle(hDiskFile);

	hDiskMapping = INVALID_HANDLE_VALUE;
	hDiskFile = INVALID_HANDLE_VALUE;
	*diskData = nullptr;
}

void FormatDisk(void *diskData)
{
	AssertDiskMounted(diskData);

	uint32_t *data = static_cast<uint32_t*>(diskData);
	data[1] = 0xFFFFFFFF; // Записываем флаг, показывающий, что диск отформатирован

	uint32_t diskSize = data[0]; // Первые четыре байта - размер диска

								 // Записываем пустой заголовок первого (еще не существующего) файла.
								 // Запись файла будет выполнена в блок с этим заголовком, затем
								 // будет создан следующий пустой заголовок (если будет свободное место)
	BlockHeader header;

	// Доступное пространство для будущего файла:
	// Размер диска - заголовок диска (16 байт) - заголовок файла (24 байт)
	header.size = diskSize - DISK_HEADER_SIZE - sizeof(BlockHeader);
	header.attrib |= FILE_NOT_EXIST;
	header.next = INVALID_OFFSET_VALUE;

	// Заголовок первого файла записывается сразу после заголовка диска
	WriteBlockHeader(diskData, header, DISK_HEADER_SIZE);
}

void WriteFileToDisk(const string &fileName, void *diskData)
{
	AssertDiskFormat(diskData);

	char *data = static_cast<char*>(diskData);

	size_t fileSize = GetExternalFileSize(fileName);
	size_t enoughSpaceOffset = FindEnoughSpaceToWriteFile(diskData, fileSize);
	BlockHeader enoughSpaceHeader = ReadBlockHeader(diskData, enoughSpaceOffset);

	ReadExternalFile(fileName, &data[enoughSpaceOffset + sizeof(BlockHeader)], fileSize);

	BlockHeader header;
	header.size = fileSize;
	header.attrib |= FILE_ATTR_NORMAL;
	header.next = enoughSpaceHeader.next;

	ParseFileNameAndSaveInHeader(fileName, header);
	bool canCreateEmptyFile = enoughSpaceHeader.size - header.size >= CLUSTER_MINIMAL_SIZE;

	if (canCreateEmptyFile)
	{
		header.next = enoughSpaceOffset + fileSize + sizeof(BlockHeader);
		enoughSpaceHeader.size -= (header.size + sizeof(BlockHeader));

		WriteBlockHeader(diskData, enoughSpaceHeader, header.next);
	}

	WriteBlockHeader(diskData, header, enoughSpaceOffset);
}

void ParseFileNameAndSaveInHeader(const string &fileName, BlockHeader &fileHeader)
{
	string args = fileName;

	string name = GetStringArgEx(args, "[A-Za-z0-9]+");
	string ext = GetStringArgEx(args, "[A-Za-z0-9]+");

	if (name.length() > 8)
	{
		name = name.substr(0, 8);
	}

	if (ext.length() > 3)
	{
		ext = ext.substr(0, 3);
	}

	memcpy(fileHeader.name, name.c_str(), name.length());
	memcpy(fileHeader.ext, ext.c_str(), ext.length());
}

void ReadFileFromDisk(const string &sourceFile, const string &destFile, void *diskData)
{
	AssertDiskFormat(diskData);

	if (!sourceFile.length() || !destFile.length())
	{
		throw logic_error("Invalid filename value");
	}

	size_t offset = FindFileByName(diskData, sourceFile);
	WriteExternalFile(diskData, offset, destFile);
}

size_t GetExternalFileSize(const string &fileName)
{
	ifstream externalFile(fileName, ios::binary | ios::beg);

	if (!externalFile.is_open())
	{
		throw logic_error("Failed to open external file" + fileName);
	}

	externalFile.seekg(0, ios::end);

	return static_cast<size_t>(externalFile.tellg());
}

void ReadExternalFile(const string &fileName, char *diskData, size_t count)
{
	ifstream externalFile(fileName, ios::binary | ios::beg);

	if (!externalFile.is_open())
	{
		throw logic_error("Failed to open external file" + fileName);
	}

	externalFile.read(diskData, count);
}

void WriteExternalFile(void *diskData, size_t offset, const string &fileName)
{
	ofstream externalFile(fileName, ios::binary | ios::beg);

	if (!externalFile.is_open())
	{
		throw logic_error("Failed to open external file" + fileName);
	}

	char *data = static_cast<char*>(diskData);
	BlockHeader header = ReadBlockHeader(diskData, offset);

	externalFile.write(&data[offset + sizeof(BlockHeader)], header.size);
}

size_t FindEnoughSpaceToWriteFile(void *diskData, size_t size)
{
	BlockHeader fileHeader;

	fileHeader.size = size;
	fileHeader.attrib = FILE_NOT_EXIST;
	uint32_t options = FIND_BY_SIZE | FIND_BY_ATTRIB | FIND_SIZE_EQUAL | FIND_SIZE_MORE;

	size_t enoughSpaceOffset = FindFileByHeader(diskData, fileHeader, options);

	if (enoughSpaceOffset == INVALID_OFFSET_VALUE)
	{
		throw logic_error("No enough space to write file");
	}

	return enoughSpaceOffset;
}

size_t FindFileByHeader(void *diskData, BlockHeader &header, uint32_t options)
{
	size_t offset = INVALID_OFFSET_VALUE;
	size_t currOffset = START_DATA_OFFSET;
	size_t diskSize = GetDiskSize(diskData);

	while (currOffset < diskSize)
	{
		bool match = true;
		BlockHeader foundHeader = ReadBlockHeader(diskData, currOffset);

		CheckMatchBlockHeadersBySize(match, foundHeader, header, options);
		CheckMatchBlockHeadersByAttrib(match, foundHeader, header, options);
		CheckMatchBlockHeadersByName(match, foundHeader, header, options);
		CheckMatchBlockHeadersByExt(match, foundHeader, header, options);

		if (match)
		{
			offset = currOffset;
			break;
		}

		currOffset += foundHeader.size + sizeof(foundHeader);
	}

	return offset;
}

size_t FindFileByName(void *diskData, const string &fileName)
{
	BlockHeader header;
	ParseFileNameAndSaveInHeader(fileName, header);

	uint32_t options = FIND_BY_NAME | FIND_BY_EXT;
	size_t offset = FindFileByHeader(diskData, header, options);

	if (offset == INVALID_OFFSET_VALUE)
	{
		throw logic_error("File not found");
	}

	return offset;
}

void CheckMatchBlockHeadersBySize(bool &match, const BlockHeader &found, const BlockHeader &source, uint32_t options)
{
	if (match && options & FIND_BY_SIZE)
	{
		match = false;

		if ((options & FIND_SIZE_LESS && found.size < source.size) ||
			(options & FIND_SIZE_EQUAL && found.size == source.size) ||
			(options & FIND_SIZE_MORE && found.size > source.size))
		{
			match = true;
		}
	}
}

void CheckMatchBlockHeadersByAttrib(bool &match, const BlockHeader &found, const BlockHeader &source, uint32_t options)
{
	if (match && options & FIND_BY_ATTRIB)
	{
		match = false;

		if ((source.attrib & found.attrib) == source.attrib)
		{
			match = true;
		}
	}
}

void CheckMatchBlockHeadersByName(bool &match, const BlockHeader &found, const BlockHeader &source, uint32_t options)
{
	if (match && options & FIND_BY_NAME)
	{
		match = false;

		if (!memcmp(found.name, source.name, 9))
		{
			match = true;
		}
	}
}

void CheckMatchBlockHeadersByExt(bool &match, const BlockHeader &found, const BlockHeader &source, uint32_t options)
{
	if (match && options & FIND_BY_EXT)
	{
		match = false;

		if (!memcmp(found.ext, source.ext, 4))
		{
			match = true;
		}
	}
}

void Dir(void *diskData)
{
	AssertDiskFormat(diskData);

	size_t offset = START_DATA_OFFSET;
	size_t filesCount = 0;
	size_t filesSize = 0;
	size_t freeSpaceSize = 0;
	size_t maxAvailBlockSize = 0;

	g_strm << endl;

	do
	{
		BlockHeader header = ReadBlockHeader(diskData, offset);
		offset = header.next;

		if (BlockIsEmpty(header))
		{
			freeSpaceSize += header.size;
			maxAvailBlockSize = (header.size > maxAvailBlockSize) ? header.size : maxAvailBlockSize;

			continue;
		}

		++filesCount;
		filesSize += header.size;

		g_strm << setw(15) << left << GetFileNameFromHeader(header);
		g_strm << header.size << endl;

	} while (offset != INVALID_OFFSET_VALUE);

	g_strm << endl << right << filesCount << " files   ";
	g_strm << filesSize << " bytes" << endl;
	g_strm << freeSpaceSize << " bytes free" << endl;
	g_strm << "Maximum available memory block " << maxAvailBlockSize << " bytes" << endl;
}

void DeleteFileFromDisk(const string &fileName, void *diskData)
{
	AssertDiskFormat(diskData);

	size_t offset = FindFileByName(diskData, fileName);

	BlockHeader header = ReadBlockHeader(diskData, offset);
	header.attrib |= FILE_NOT_EXIST;

	WriteBlockHeader(diskData, header, offset);
}

void SqueezeDiskData(void *diskData)
{
	AssertDiskFormat(diskData);

	size_t offset = DISK_HEADER_SIZE;
	BlockHeader header = ReadBlockHeader(diskData, offset);

	while (header.next != INVALID_OFFSET_VALUE)
	{
		BlockHeader nextHeader = ReadBlockHeader(diskData, header.next);

		if (BlockIsNotEmpty(header) && IsFileLessThanBlock(diskData, offset))
		{
			ReduceBlockAndMoveNextBlockUp(diskData, offset, header, nextHeader);
		}

		if (BlockIsEmpty(header))
		{
			BlockMoveUp(diskData, nextHeader, offset, header.next);
			header = ReadBlockHeader(diskData, offset);

			continue;
		}

		offset = header.next;
		header = ReadBlockHeader(diskData, offset);
	}
}

void ReduceBlockAndMoveNextBlockUp(void *diskData, size_t offset, BlockHeader &header, BlockHeader &nextHeader)
{
	size_t newOffset = offset + GetFileSizeByHeader(header);
	size_t oldOffset = header.next;

	BlockMoveUp(diskData, nextHeader, newOffset, oldOffset);

	header.next = newOffset;
	WriteBlockHeader(diskData, header, offset);
}

void BlockMoveUp(void *diskData, BlockHeader &header, size_t newOffset, size_t oldOffset)
{
	char *data = static_cast<char*>(diskData);

	memcpy(&data[newOffset], &data[oldOffset], GetFileSizeByHeader(header));

	if (BlockIsEmpty(header))
	{
		header.size += oldOffset - newOffset;
		WriteBlockHeader(diskData, header, newOffset);
	}
}

BlockHeader ReadBlockHeader(void *diskData, size_t offset)
{
	char *data = static_cast<char*>(diskData);

	BlockHeader header;
	memcpy(&header, &data[offset], sizeof(BlockHeader));

	return header;
}

void WriteBlockHeader(void *diskData, const BlockHeader &header, size_t offset)
{
	char *data = static_cast<char*>(diskData);
	memcpy(&data[offset], &header, sizeof(BlockHeader));
}

size_t GetBlockSize(void* diskData, size_t offset)
{
	BlockHeader header = ReadBlockHeader(diskData, offset);

	if (header.next != INVALID_OFFSET_VALUE)
	{
		return header.next - offset;
	}

	return GetDiskSize(diskData) - offset;
}

size_t GetDiskSize(void* diskData)
{
	uint32_t *data = static_cast<uint32_t*>(diskData);

	return data[0]; // The first four bytes are the size of the disk
}

bool BlockIsEmpty(const BlockHeader &header)
{
	return header.attrib & FILE_NOT_EXIST;
}

bool BlockIsNotEmpty(const BlockHeader &header)
{
	return !(header.attrib & FILE_NOT_EXIST);
}

bool IsFileLessThanBlock(void* diskData, size_t offset)
{
	BlockHeader header = ReadBlockHeader(diskData, offset);

	return GetFileSizeByHeader(header) < GetBlockSize(diskData, offset);
}

size_t GetFileSizeByHeader(const BlockHeader &header)
{
	return header.size + sizeof(BlockHeader);
}

string GetFileNameFromHeader(const BlockHeader &header)
{
	string name(header.name);
	string ext(header.ext);

	if (ext.length())
	{
		name += "." + ext;
	}

	return name;
}

void AssertDiskMounted(void *diskData)
{
	if (diskData == nullptr)
	{
		throw logic_error("Disk is not mounted!");
	}
}

void AssertDiskFormat(void *diskData)
{
	AssertDiskMounted(diskData);

	uint32_t *data = static_cast<uint32_t*>(diskData);

	if (data[1] != 0xFFFFFFFF) // Проверяем флаг, показывающий, что диск отформатирован
	{
		throw logic_error("Disk is not formatted!");
	}
}

void ShowDiskMap(void* diskData)
{
	AssertDiskFormat(diskData);

	unsigned char diskHeadCh = 253;
	unsigned char fileHeadCh = 4;
	unsigned char existCh = 219;
	unsigned char emptyCh = 176;
	unsigned char unusedCh = 249;

	g_strm << endl;
	PrintSymbol(diskHeadCh, DISK_HEADER_SIZE);

	size_t offset = START_DATA_OFFSET;

	do
	{
		BlockHeader header = ReadBlockHeader(diskData, offset);

		size_t fileSize = GetFileSizeByHeader(header);
		size_t blockSize = GetBlockSize(diskData, offset);

		char ch = header.attrib & FILE_NOT_EXIST ? emptyCh : existCh;
		PrintSymbol(fileHeadCh, sizeof(BlockHeader));
		PrintSymbol(ch, header.size);

		if (fileSize < blockSize)
		{
			PrintSymbol(unusedCh, blockSize - fileSize);
		}

		offset = header.next;
	} while (offset != INVALID_OFFSET_VALUE);

	g_strm << endl << endl << diskHeadCh << " - disk header   ";
	g_strm << fileHeadCh << " - block header   ";
	g_strm << existCh << " - file data" << endl;
	g_strm << emptyCh << " - empty space   ";
	g_strm << unusedCh << " - unused space" << endl;
}

void PrintSymbol(char symbol, size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		g_strm << symbol;
	}
}
