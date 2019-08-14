/*
 Copyright (c) 2016 DenshiKousakuSenka
 This software is released under the MIT License.
 http://opensource.org/licenses/mit-license.php
 */

#pragma once

#include <string.h>
#include "stm32l4xx_hal.h"

namespace DKS
{

	template<typename T, uint16_t Capacity>
	class CircularBuffer
	{
	private:
		T buffer[Capacity];
		const uint16_t m_mask;
		uint16_t m_head, m_tail;	//pointer to start, end
		uint16_t m_size;//Size should count internally to distinguish size is zero or full capacity.
		uint16_t m_capacity;

		inline void MovePointer(uint16_t &pointer, const int16_t &step)
		{
			pointer = (pointer + step) & m_mask;
		}
		inline uint16_t emptySize() const
		{
			return Capacity - m_size;
		}

	public:
		volatile bool isLocked;
		explicit CircularBuffer() :
				 m_mask(Capacity - 1), m_head(0), m_tail(0), m_size(0), m_capacity(Capacity), isLocked(false)
		{
			if ((Capacity & (Capacity - 1)) != 0) while (true)
				;	//confirm that capacity is power of 2 or not.
		}

		virtual ~CircularBuffer()
		{
		//	delete[] buffer;
		}

		// Add a value to the front
		void push_front(const T &value)
		{
			if (isLocked) while (true)
				;
			isLocked = true;

			MovePointer(m_head, -1);
			buffer[m_head] = value;
			if (m_size == Capacity) //overwrite
				MovePointer(m_tail, -1);
			else m_size++;

			isLocked = false;
		}
		// Add multiple values to the front
		void push_front(const T* src, const uint16_t &length)
		{
			if (isLocked) while (true)
				;
			isLocked = true;

			const int16_t overwriteSize = length - emptySize();
			if (overwriteSize > 0)
			{
				MovePointer(m_tail, -overwriteSize);
				m_size -= overwriteSize;
			}

			if (m_head > length)
			{
				memcpy(&buffer[m_head - length], src, length * sizeof(T));
			}
			else
			{
				const uint16_t len = length - m_head;
				memcpy(buffer, &src[len], m_head * sizeof(T));
				memcpy(&buffer[Capacity - len], src, len * sizeof(T));
			}
			MovePointer(m_head, -length);
			m_size += length;

			isLocked = false;
		}
		//Add a value to the rear.
		void push_back(const T &value)
		{
			if (isLocked) while (true)
				;
			isLocked = true;

			buffer[m_tail] = value;
			MovePointer(m_tail, 1);
			if (m_size == Capacity) //overwrite
				MovePointer(m_head, 1);
			else m_size++;

			isLocked = false;
		}
		//Add multiple values to the rear.
		void push_back(const T* src, const uint16_t &length)
		{
			if (isLocked) while (true)
				;
			isLocked = true;

			const int16_t overwriteSize = length - emptySize();
			if (overwriteSize > 0)	//overwrite
			{
				MovePointer(m_head, overwriteSize);
				m_size -= overwriteSize;
			}

			if (m_tail + length < Capacity)
			{
				memcpy(&buffer[m_tail], src, length * sizeof(T));
			}
			else
			{
				const uint16_t len1(Capacity - m_tail);
				const uint16_t len2(length - len1);
				memcpy(&buffer[m_tail], &src[0], len1 * sizeof(T));
				memcpy(&buffer[0], &src[len1], len2 * sizeof(T));
			}
			MovePointer(m_tail, length);
			m_size += length;

			isLocked = false;
		}
		//delete a element by the front
		void pop_front()
		{
			if (isLocked) while (true)
				;
			isLocked = true;

			if (m_size == 0) while (true)
				;
			MovePointer(m_head, 1);
			m_size--;

			isLocked = false;
		}
		//delete multiple elements by the front
		void pop_front(const uint16_t &length)
		{
			if (isLocked) while (true)
				;
			isLocked = true;

			if (length > m_size) while (true)
				;
			MovePointer(m_head, length);
			m_size -= length;

			isLocked = false;
		}
		//delete a element by the rear
		void pop_back()
		{
			if (isLocked) while (true)
				;
			isLocked = true;

			if (m_size == 0) while (true)
				;
			MovePointer(m_tail, -1);
			m_size--;

			isLocked = false;
		}
		// delete multiple elements by the rear.
		void pop_back(const uint16_t &length)
		{
			if (isLocked) while (true)
				;
			isLocked = true;

			if (length > m_size) while (true)
				;
			MovePointer(m_tail, -length);
			m_size -= length;

			isLocked = false;
		}

		// get legacy C array.
		// outArray must be allocated before calling.
		// Buffer will not change.
		void GetArray(const uint16_t &start, const uint16_t &length, T* outArray) const
		{
			if (m_head + start + length < Capacity)
			{
				memcpy(outArray, buffer[m_head + start], length * sizeof(T));
			}
			else
			{
				const uint16_t len = Capacity - (m_head + start);
				memcpy(outArray, buffer[m_head + start], len * sizeof(T));
				memcpy(&outArray[len], buffer, length - len * sizeof(T));
			}
		}
		// get legacy C array.
		// outArray must be allocated before calling.
		// Buffer will not change.
		void GetArray(T* outArray) const
		{
			memset(outArray, 0x00, Capacity);
			if (m_tail > m_head)
				memcpy(outArray, &buffer[m_head], m_size * sizeof(T));
			else
			{
				const uint16_t len = Capacity - m_head;
				memcpy(outArray, &buffer[m_head], len * sizeof(T));
				memcpy(&outArray[len], buffer, m_tail * sizeof(T));
			}
		}

		// Get a data from the front. Buffer will detele after reading
		T pull()
		{
			if (isLocked) while (true)
				;
			isLocked = true;

			const T res = buffer[m_head];
			MovePointer(m_head, 1);
			m_size--;
			isLocked = false;

			return res;
		}
		// Get multiple data form the front. Buffer will delete after reading.
		// outArray must be allocated before calling.
		void pull(T* outArray, const uint16_t &length)
		{
			if (isLocked) while (true)
				;
			isLocked = true;

			if (length > m_size) while (true)
				;

			if (m_head + length < Capacity)
			{
				memcpy(outArray, &buffer[m_head], length * sizeof(T));
			}
			else
			{
				const uint16_t len = Capacity - m_head;
				memcpy(outArray, &buffer[m_head], len * sizeof(T));
				memcpy(&outArray[len], buffer, (length - len) * sizeof(T));
			}
			m_size -= length;
			MovePointer(m_head, length);

			isLocked = false;
		}

		uint16_t size() const
		{
			return m_size;
		}

		uint16_t BufferCapacity() const
		{
			return m_capacity;
		}

		void clear()
		{
			if (isLocked) while (true)
				;
			isLocked = true;

			m_head = 0;
			m_tail = 0;
			m_size = 0;

			isLocked = false;
		}

		T &operator[ ](const uint16_t &n)
		{
			return buffer[(m_head + n) & m_mask];
		}
	};

}
;
