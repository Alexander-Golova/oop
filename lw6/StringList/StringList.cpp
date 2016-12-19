#include "stdafx.h"
#include "StringList.h"
#include <cassert>

using namespace std;

void CStringList::Insert(const CIterator & it, const string & data)
{
	if (it == begin())
	{
		PushFront(data);
	}
	else if (it == end())
	{
		Append(data);
	}
	else
	{
		auto newNode = make_unique<Node>(data, it->prev, move(it->prev->next));
		it->prev = move(newNode.get());
		newNode->prev->next = move(newNode);
	}
}

void CStringList::PushFront(const string & data)
{
	auto newNode = make_unique<Node>(data, nullptr, move(m_firstNode));
	if (newNode->next)
	{
		newNode->next->prev = newNode.get();
	}
	else
	{
		m_lastNode = newNode.get();
	}
	m_firstNode = move(newNode);
	m_firstNode->prev = nullptr;
	++m_size;
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return m_size == 0u;
}

void CStringList::Clear()
{
	while (m_lastNode)
	{
		m_lastNode->next = nullptr;
		m_lastNode = m_lastNode->prev;
	}
	m_firstNode = nullptr;
	m_size = 0;
}

void CStringList::Append(const string & data)
{
	auto newNode = make_unique<Node>(data, m_lastNode, nullptr);
	Node *newLastNode = newNode.get();
	if (m_lastNode)
	{
		m_lastNode->next = move(newNode);
	}
	else
	{
		m_firstNode = move(newNode);
	}
	m_lastNode = newLastNode;
	++m_size;
}

string & CStringList::GetBackElement()
{
	assert(m_lastNode);
	return m_lastNode->data;
}

string const & CStringList::GetBackElement() const
{
	assert(m_lastNode);
	return m_lastNode->data;
}

string & CStringList::GetFrontElement()
{
	assert(m_firstNode);
	return m_firstNode->data;
}

string const& CStringList::GetFrontElement()const
{
	assert(m_firstNode);
	return m_firstNode->data;
}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get());
}

CStringList::CIterator CStringList::end()
{
	return CIterator(m_lastNode);
}

CStringList::CIterator const CStringList::cbegin() const
{
	return CIterator(m_firstNode.get());
}

CStringList::CIterator const CStringList::cend() const
{
	return CIterator(m_lastNode);
}

bool CStringList::CIterator::operator==(const CIterator & other)const
{
	return m_node == other.m_node;
}

bool CStringList::CIterator::operator!=(const CIterator & other)const
{
	return m_node != other.m_node;
}

CStringList::CIterator::CIterator(Node * node)
	:m_node(node)
{
}

string & CStringList::CIterator::operator*() const
{
	return m_node->data;
}

CStringList::CIterator & CStringList::CIterator::operator++()
{
	m_node = m_node->next.get();
	return *this;
}

CStringList::Node * CStringList::CIterator::operator->() const
{
	return m_node;
}
