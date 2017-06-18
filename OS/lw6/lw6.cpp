#include "stdafx.h"
#include "GraphUtilits.h"

using namespace std;
using namespace boost;

typedef vector<vector<string>> LockList;

void SearchInterLock(LockList &lockList, Graph &graph);
void PrintInterlock(LockList &lockList);

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << endl << "Invalid arguments count" << endl
			<< "Usage: interlocks.exe <graph file>" << endl;
		return 1;
	}

	Graph graph;
	LockList lockList;

	if (!LoadGraphFromFile(static_cast<string>(argv[1]), graph))
	{
		return 1;
	}

	print_graph(graph, get(vertex_name, graph));
	SearchInterLock(lockList, graph);

	if (lockList.size())
	{
		PrintInterlock(lockList);
	}
	else
	{
		cout << endl << "There are no interlocks" << endl;
	}

	return 0;
}

void SearchInterLock(LockList &lockList, Graph &graph)
{
	lockList.clear();

	vector<unsigned> strong(num_vertices(graph));
	auto num = strong_components(graph, make_iterator_property_map(strong.begin(), get(vertex_index, graph), strong[0]));

	if (num < num_vertices(graph))
	{
		lockList.resize(num);

		for (size_t i = 0; i < strong.size(); ++i)
		{
			lockList[strong[i]].push_back(GetVertexNameByIndex(i));
		}
	}
}

void PrintInterlock(LockList &lockList)
{
	size_t lockCount = 0;

	auto PrintInterlockGroup = [](vector<string> group) {
		for (size_t i = 0; i < group.size(); ++i)
		{
			cout << group[i] << " ";
		}
		cout << endl;
	};

	cout << endl << "Interlock(s):" << endl << endl;

	for (size_t i = 0; i < lockList.size(); ++i)
	{
		if (lockList[i].size() > 1)
		{
			++lockCount;
			PrintInterlockGroup(lockList[i]);
		}
	}

	cout << endl << "Found " << lockCount << " interlock group(s)" << endl;
}

