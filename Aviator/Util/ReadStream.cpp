#include "Stream.h"

ReadStream::ReadStream(char* message)
{
	stream = message;
}

ReadStream::~ReadStream()
{
}

unsigned char ReadStream::ReadByte()
{
	unsigned char data;
	memcpy(&data, stream + pos, sizeof(unsigned char));
	pos += sizeof(unsigned char);

	return data;
}

short ReadStream::ReadShort()
{
	short data;
	memcpy(&data, stream + pos, sizeof(short));
	pos += sizeof(short);

	return data;
}

int ReadStream::ReadInt()
{
	int data;
	memcpy(&data, stream + pos, sizeof(int));
	pos += sizeof(int);

	return data;
}

long ReadStream::ReadLong()
{
	long data;
	memcpy(&data, stream + pos, sizeof(long));
	pos += sizeof(long);

	return data;
}

std::string ReadStream::ReadString()
{
	std::string data;
	short length = ReadShort();
	for (int i = 0; i < length; i++)
	{
		data.push_back(*(stream + pos));
		pos++;
	}

	return data;
}

void* ReadStream::ReadObjPointer()
{
	void* data = NULL;
	memcpy(&data, stream + pos, sizeof(void*));
	pos += sizeof(void*);

	return data;
}