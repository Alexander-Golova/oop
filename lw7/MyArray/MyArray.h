#pragma once

#include <new>
#include <algorithm>

template <typename T>
class CMyArray
{
public:
	CMyArray() = default;

	CMyArray(const CMyArray& arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}

	CMyArray(CMyArray && arr)
		:m_begin(arr.m_begin)
		, m_end(arr.m_end)
		, m_endOfCapacity(arr.m_endOfCapacity)
	{
		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_endOfCapacity = nullptr;
	}

	void Append(const T & value)
	{
		if (m_end == m_endOfCapacity) // no free space
		{
			size_t newCapacity = std::max(1u, GetCapacity() * 2);

			auto newBegin = RawAlloc(newCapacity);
			T *newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				// Конструируем копию value по адресу newItemLocation
				new (newEnd)T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			// Переключаемся на использование нового хранилища элементов
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else // has free space
		{
			new (m_end) T(value);
			++m_end;
		}
	}

	T & GetBack()
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	const T & GetBack()const
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	size_t GetSize()const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity()const
	{
		return m_endOfCapacity - m_begin;
	}

	T& operator[](size_t position)
	{
		if (position >= GetSize())
		{
			throw std::out_of_range("Element is out of range");
		}
		return m_begin[position];
	}

	const T& operator[](size_t position) const
	{
		if (position >= GetSize())
		{
			throw std::out_of_range("Element is out of range");
		}
		return m_begin[position];
	}

	void Resize(size_t newSize)
	{
		size_t currentSize = GetSize();

		if (newSize < currentSize)
		{
			DestroyItems(m_begin + newSize, m_end);
			m_end -= (currentSize - newSize);
		}
		else if (newSize > currentSize && newSize <= GetCapacity())
		{
			for (size_t i = 0; i < newSize - currentSize; ++i)
			{
				Append(T());
			}
		}
		else if (newSize > GetCapacity())
		{
			auto newBegin = RawAlloc(newSize);
			T *newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newSize;
			for (size_t i = GetSize(); i < GetCapacity(); ++i)
			{
				Append(T());
			}
		}
	}

	void Clear()
	{
		DestroyItems(m_begin, m_end);
		m_end = m_begin;
	}

	CMyArray& operator = (CMyArray const & rhs)
	{
		if (std::addressof(*this) != std::addressof(rhs))
		{
			CMyArray newArray(rhs);

			std::swap(m_begin, newArray.m_begin);
			std::swap(m_end, newArray.m_end);
			std::swap(m_endOfCapacity, newArray.m_endOfCapacity);
		}
		return *this;
	}

	CMyArray& operator = (CMyArray && rhs)
	{
		if (std::addressof(*this) != std::addressof(rhs))
		{
			Clear();
			m_begin = rhs.m_begin;
			m_end = rhs.m_end;
			m_endOfCapacity = rhs.m_endOfCapacity;

			rhs.m_begin = nullptr;
			rhs.m_end = nullptr;
			rhs.m_endOfCapacity = nullptr;
		}
		return *this;
	}

	template<typename T>
	class CMyIterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
		template <typename> friend class CMyArray;
		CMyIterator(T* p)
			: m_pointer(p)
		{}
	public:

		CMyIterator() = default;

		T & CMyIterator<T>::operator*() const
		{
			return *m_pointer;
		}

		CMyIterator<T> &CMyIterator<T>::operator++()
		{
			++m_pointer;
			return *this;
		}

		CMyIterator<T> &CMyIterator<T>::operator--()
		{
			--m_pointer;
			return *this;
		}

		bool CMyIterator<T>::operator==(CMyIterator const& rhs) const
		{
			return m_pointer == rhs.m_pointer;
		}

		bool CMyIterator<T>::operator!=(CMyIterator const& rhs) const
		{
			return m_pointer != rhs.m_pointer;
		}

	private:
		T* m_pointer;
	};

	CMyIterator<T> begin()
	{
		return CMyIterator<T>(m_begin);
	}

	CMyIterator<T> end()
	{
		return CMyIterator<T>(m_end);
	}

	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}

private:
	static void DeleteItems(T *begin, T *end)
	{
		// Разрушаем старые элементы
		DestroyItems(begin, end);
		// Освобождаем область памяти для их хранения
		RawDealloc(begin);
	}

	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T *srcBegin, T *srcEnd, T * const dstBegin, T * & dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			new (dstEnd)T(*srcBegin);
		}
	}

	static void DestroyItems(T *from, T *to)
	{
		// dst - адрес объект, при конструирование которого было выброшено исключение
		// to - первый сконструированный объект
		while (to != from)
		{
			--to;
			// явно вызываем деструктор для шаблонного типа T
			to->~T();
		}
	}

	static T *RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T *p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T *p)
	{
		free(p);
	}

private:
	T *m_begin = nullptr;
	T *m_end = nullptr;
	T *m_endOfCapacity = nullptr;
};
