#include "StdAfx.h"
#include "gkhy/mfcminus/HugeRingBuffer.hpp"
#include <string>
#include <strstream>
#include <afxmt.h>

using namespace std;
using namespace gkhy::MfcMinus;

HugeRingBufferLocker::HugeRingBufferLocker(HugeRingBuffer* p) : buffer(p)
{
	buffer->lock();
}

HugeRingBufferLocker::~HugeRingBufferLocker()
{
	buffer->unlock();
}


HugeRingBuffer::HugeRingBuffer(int blockSize) : blockSize(blockSize), cs(new CCriticalSection)
{ 
	resize(blockSize);
	clear();
}

HugeRingBuffer::~HugeRingBuffer()
{
	for (int i = 0; i < int(fifoList.size()); ++i)
	{
		delete fifoList[i];
	}

	delete cs;
}

void HugeRingBuffer::lock()
{
	cs->Lock();
}

void HugeRingBuffer::unlock()
{
	cs->Unlock();
}

void HugeRingBuffer::resize(int newSize)
{
	fifoSize = 0;		
	dataCount = 0;
	peakDataCount = 0;

	unsigned blocks = (newSize + (blockSize - 1)) / blockSize;		
	if(blocks <= 0)	blocks = 1;	 	 

	
	if (blocks < fifoList.size())
	{
		for (int i = blocks; i < int(fifoList.size()); ++i)
		{
			delete fifoList[i];
		}

		fifoList.resize(blocks);
	}
	else if (blocks > fifoList.size())
	{
		while (fifoList.size() < blocks)
		{			
			RingBuffer* blk = 0;
			blk = new gkhy::MfcMinus::RingBuffer(blockSize);
			fifoList.push_back(blk);		
		}
	}

	assert(blocks == fifoList.size());

	head = tail = 0;
	fifoSize = 0;
	for (int i = 0; i < int(fifoList.size()); ++i)
	{
		fifoList[i]->clear();
		fifoSize += fifoList[i]->totalWritableSize();
	}
	
}

void HugeRingBuffer::clear()
{
	chop(count());
	peakDataCount = 0;
}

int HugeRingBuffer::commit(int len)
{	
	int totalWritable = totalWritableSize();
	int toCommit = qMin(len, totalWritable);
	int done = 0;
	while (done != toCommit)
	{
		if (0 == fifoList[tail]->totalWritableSize())
			advanceHeadTailPtr(tail);		
		done += fifoList[tail]->commit(toCommit - done);
	}

	dataCount += done;
	peakDataCount = qMax(peakDataCount, dataCount);

	return toCommit;
}


int HugeRingBuffer::write(const char* data, int maxLen)
{
	int totalWritable = totalWritableSize();
	int bytesToWrite = qMin(maxLen, totalWritable);
	int written = 0;	
	while (written != bytesToWrite)
	{
		int a = nextWriteBlockSize();
		int b = bytesToWrite - written;
		int subWrite = qMin(a, b);
		memcpy(nextWriteBlock(), data + written, subWrite);
		written += commit(subWrite);
	}

	return written;
}

int HugeRingBuffer::chop(int len)
{
	int cnt = count();
	int toChop = qMin(len, cnt);
	int done = 0;
	while (done < toChop)
	{
		if (0 == fifoList[head]->count())
			advanceHeadTailPtr(head);		
		// chop as much as possible.
		done += fifoList[head]->chop(toChop - done);
	}

	dataCount -= done;

	return done;
}

int HugeRingBuffer::read(char *data, int maxLen)
{
	int cnt = count();
	int toRead = qMin(maxLen,  cnt);
	int done = 0;
	while(done != toRead)
	{
		int a = nextReadBlockSize();
		int b = toRead - done;
		int subRead = qMin(a, b);
		memcpy(data + done, nextReadBlock(), subRead);
		int chopped = chop(subRead);
		assert(chopped == subRead);
		done += subRead;
	}

	return done;
}