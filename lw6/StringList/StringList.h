#pragma once
#include <string>
#include <memory>

class CStringList
{
	struct Node
	{
		Node(const std::string & data, Node * prev, std::unique_ptr<Node> && next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		std::string data;
		Node *prev;
		std::unique_ptr<Node> next;
	};
public:
	void Append(const std::string & data);
	void PushFront(const std::string & data);

	size_t GetSize()const;
	bool IsEmpty() const;

	void Clear();

	class CIterator
	{
		friend CStringList;
		CIterator(Node *node);
	public:
		CIterator() = default;
		std::string & operator*()const;
		CIterator & operator++();
		Node * operator->()const;

		bool operator==(CIterator const & other) const;
		bool operator!=(CIterator const& other) const;
	private:
		Node *m_node = nullptr;
	};

	void Insert(const CIterator & it, const std::string & data);

	CIterator begin();
	CIterator end();
	CIterator const cbegin() const;
	CIterator const cend() const;

	std::string & GetBackElement();
	std::string const& GetBackElement()const;
	std::string & GetFrontElement();
	std::string const& GetFrontElement()const;
private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node * m_lastNode = nullptr;
};
