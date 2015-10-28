#ifndef __STREAM_H__
#define __STREAM_H__

#include <string>
#include <memory.h>

class Stream
{
public:
	Stream();
protected:
	int pos = 0;
	char* stream;
public:
	char* GetStream();
	int GetLength();
	void Clear();
};

class WriteStream : public Stream
{
public:
	WriteStream();
	~WriteStream();
public:
	void WriteByte(unsigned char data);
	void WriteShort(short data);
	void WriteInt(int data);
	void WriteLong(long data);
	void WriteString(std::string data);
	void WriteObjPointer(void* ptrData);
};

class ReadStream : public Stream
{
public:
	ReadStream(char* message);
	~ReadStream();
public:
	unsigned char ReadByte();
	short ReadShort();
	int ReadInt();
	long ReadLong();
	std::string ReadString();
	void* ReadObjPointer();
};

#endif