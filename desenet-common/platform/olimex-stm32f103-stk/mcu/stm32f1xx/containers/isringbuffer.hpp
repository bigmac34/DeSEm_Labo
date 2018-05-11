#ifndef CONTAINER_ISRINGBUFFER_H
#define CONTAINER_ISRINGBUFFER_H

#include <stdint.h>
#include <assert.h>

inline void isRingBufferEnterCritical() {}
inline void isRingBufferExitCritical() {}

/**
 * @brief An Interrupt Safe (IS) ring buffer.
 */
template <class data_type = uint8_t, void enterCritical() = isRingBufferEnterCritical, void exitCritical() = isRingBufferExitCritical>
class IsRingBuffer
{
public:
    typedef data_type tData;		///< @brief data_type template parameter replacement.
    typedef uint16_t tSize;			///< @brief Type to store size values.
    typedef uint16_t tIndex;		///< @brief Type to handle array index values (may be compatible with tSize).

public:
    IsRingBuffer(tSize size)
     : _array(NULL), MAX_BUFFER_SIZE(size), _count(0), _popIndex(0), _pushIndex(0)
    {
        assert(size);

        _array = new tData[MAX_BUFFER_SIZE];

        assert(_array);
    }

    IsRingBuffer(data_type externBuffer[])
     : MAX_BUFFER_SIZE(0), _count(0), _popIndex(0), _pushIndex(0)
    {
        _array = externBuffer;
        assert(_array);
    }

    ~IsRingBuffer()
    {
        if (_array)
        {
            delete [] _array;
            _array = NULL;
        }
    }

    inline tSize maxBufferSize() const { return (MAX_BUFFER_SIZE != 0) ? MAX_BUFFER_SIZE : sizeof(_array); }
    inline bool isEmpty() const { return ((_count) ? false : true); }
    inline bool empty() const { return isEmpty(); }
    inline tSize size() const { return _count; }
    inline tSize length() const { return _count; }
    inline tSize count() const { return _count; }

    void clear();				///< Empties content of the buffer

    bool push(tData value);
    bool pushFromIsr(tData value);

    bool pushMultiple(tData * pBuffer, tSize byteCount);
    bool pushMultipleFromIsr(tData * pBuffer, tSize byteCount);

    tSize getData(tData * pData, tSize dataMaxSize);
    data_type operator [](tIndex index);
    bool pop(tData & value);
    tSize popMultiple(tData * pBuffer, tSize bufferMaxSize);

    void remove(tIndex pos, tSize len);

private:
    tData * _array;					///< Pointer to real data.
    const tSize MAX_BUFFER_SIZE;
    tSize _count;					///< Size of data hold by the buffer.
    tIndex _popIndex;				///< Index where to get the data.
    tIndex _pushIndex;				///< Index where to put the data.
};

template <class data_type, void enterCritical(), void exitCritical()>
IsRingBuffer<>::tSize IsRingBuffer<data_type, enterCritical, exitCritical>::getData(tData * pData, tSize dataMaxSize)
{
    tSize count = _count;
    tSize sizeToArrayBorder, copySize;

    if (isEmpty() || dataMaxSize <= 0)
    {
        return 0;
    }

    // Calculate the amount we can really copy
    count = (dataMaxSize < count) ? dataMaxSize : count;

    // Calculate space until the bottom of the array
    sizeToArrayBorder = maxBufferSize() - _popIndex;

    // copy first only the amount until the bottom of the array
    copySize = (sizeToArrayBorder < count) ? sizeToArrayBorder : count;

    memcpy(pData, _array + _popIndex, copySize);

    if (copySize < count)
    {
        // Go to beginning of array and copy the rest
        memcpy(pData + copySize, _array, count - copySize);
    }

    return count;
}

template <class data_type, void enterCritical(), void exitCritical()>
data_type IsRingBuffer<data_type, enterCritical, exitCritical>::operator [](tIndex index)
{
    if (index >= maxBufferSize())
    {
        assert(false);	// Index was too big
    }
    return _array[((_popIndex + index) % maxBufferSize())];
}

template <class data_type, void enterCritical(), void exitCritical()>
bool IsRingBuffer<data_type, enterCritical, exitCritical>::pop(tData & value)
{
    bool retValue = false;
    const tIndex nextPopIndex = ((_popIndex + 1) % maxBufferSize());

    if (_count)
    {
        value = _array[_popIndex];

        enterCritical();
        // Decrement count
        _count--;
        // Increment _pushIndex
        _popIndex = nextPopIndex;
        exitCritical();

        retValue = true;
    }

    return retValue;
}

template <class data_type, void enterCritical(), void exitCritical()>
IsRingBuffer<>::tSize IsRingBuffer<data_type, enterCritical, exitCritical>::popMultiple(tData * pBuffer, tSize bufferMaxSize)
{
    tSize count = _count;
    tSize sizeToArrayBorder, copySize;

    if (isEmpty() || bufferMaxSize <= 0)
    {
        return 0;
    }

    // Calculate the amount we can really copy
    count = (bufferMaxSize < count) ? bufferMaxSize : count;

    // Calculate space until the bottom of the array
    sizeToArrayBorder = maxBufferSize() - _popIndex;

    // copy first only the amount until the bottom of the array
    copySize = (sizeToArrayBorder < count) ? sizeToArrayBorder : count;

    if (pBuffer)
    {
		memcpy(pBuffer, _array + _popIndex, copySize);

		if (copySize < count)
		{
			// Go to beginning of array and copy the rest
			memcpy(pBuffer + copySize, _array, count - copySize);
		}
    }

    enterCritical();

    // Adjust attributes
    _popIndex = ((_popIndex + count) % maxBufferSize());

    _count -= count;

    exitCritical();

    return count;
}

template <class data_type, void enterCritical(), void exitCritical()>
void IsRingBuffer<data_type, enterCritical, exitCritical>::clear()
{
	enterCritical();
	_count = _popIndex = _pushIndex = 0;
	exitCritical();
}

template <class data_type, void enterCritical(), void exitCritical()>
bool IsRingBuffer<data_type, enterCritical, exitCritical>::push(tData value)
{
    bool retValue = false;
    const tIndex nextPushIndex = ((_pushIndex + 1) % maxBufferSize());

    enterCritical();

    if (_count < maxBufferSize())
    {
        _array[_pushIndex] = value;
        _count++;

        // Increment _pushIndex
        _pushIndex = nextPushIndex;

        retValue = true;
    }

    exitCritical();

    return retValue;
}

template <class data_type, void enterCritical(), void exitCritical()>
bool IsRingBuffer<data_type, enterCritical, exitCritical>::pushFromIsr(tData value)
{
	const tIndex nextPushIndex = ((_pushIndex + 1) % maxBufferSize());

	if (_count < maxBufferSize())
	{
		_array[_pushIndex] = value;
		_count++;

		// Increment _pushIndex
		_pushIndex = nextPushIndex;

		return true;
	}
	return false;
}

template <class data_type, void enterCritical(), void exitCritical()>
bool IsRingBuffer<data_type, enterCritical, exitCritical>::pushMultiple(tData * pBuffer, tSize byteCount)
{
    bool retValue = false;

    // TODO: Replace while loop with a memcpy
    if (pBuffer && byteCount > 0)
    {
        data_type * pPtr = pBuffer;

        for (tSize i = byteCount; i; i--)
        {
            retValue = push(*pPtr++);

            if (!retValue)
            {
                break;
            }
        }
    }
    return retValue;
}

template <class data_type, void enterCritical(), void exitCritical()>
bool IsRingBuffer<data_type, enterCritical, exitCritical>::pushMultipleFromIsr(tData * pBuffer, tSize byteCount)
{
    bool retValue = false;

    // TODO: Replace while loop with a memcpy
    if (pBuffer && byteCount > 0)
    {
        data_type * pPtr = pBuffer;

        for (tSize i = byteCount; i; i--)
        {
            retValue = pushFromIsr(*pPtr++);

            if (!retValue)
            {
                break;
            }
        }
    }
    return retValue;
}

template <class data_type, void enterCritical(), void exitCritical()>
void IsRingBuffer<data_type, enterCritical, exitCritical>::remove(tIndex pos, tSize len)
{
    assert(pos == 0);	// Can only remove from the beginning of the array

    enterCritical();

    // Adjust attributes
    _popIndex = ((_popIndex + len) % maxBufferSize());

    assert(len <= _count);
    _count -= len;

    exitCritical();
}

#endif // CONTAINER_ISRINGBUFFER_H
