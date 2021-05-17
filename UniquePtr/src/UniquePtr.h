/*
    UniquePtr: Takes unique ownership of a dynamically allocated resource.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

template <typename T>
class UniquePtr final
{
public:
	UniquePtr(T* rawPtr) : m_raw(rawPtr) {}
	~UniquePtr() { if (m_raw) delete m_raw; }

	void Reset(T* newPtr) noexcept
	{
		if (m_raw)
			delete m_raw;

		m_raw = newPtr;
	}

	T& operator* () { return *m_raw; }
	T* operator-> () { return m_raw; }

	explicit operator bool() const noexcept { return (m_raw != nullptr); }

	// only movable
	UniquePtr(UniquePtr&& toMove) noexcept
	{
		m_raw = toMove.m_raw;
		toMove.m_raw = nullptr;
	}

	UniquePtr& operator=(UniquePtr&& toMove)
	{
		if (this != &toMove)
		{
			m_raw = toMove.m_raw;
			toMove.m_raw = nullptr;
		}

		return *this;
	}

	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator=(const UniquePtr&) = delete;

private:
	T* m_raw = nullptr;
};