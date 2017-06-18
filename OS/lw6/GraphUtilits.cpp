#include "stdafx.h"
#include "GraphUtilits.h"

using namespace std;
using namespace boost;

static vector<string> g_vertexNames;

void ParseGraphTextString(string &line, string &vertex);
void AddVertexIntoGraph(string vertex, Graph &graph);
void AddEdgeIntoGraph(string vertexFrom, string vertexTo, Graph &graph);
size_t GetVertexIndexByName(string vertexName);

bool LoadGraphFromFile(const string &fileName, Graph &graph)
{
	ifstream input(fileName);

	if (!input.is_open())
	{
		cout << "Failed to open " << fileName << " for reading" << endl;
		return false;
	}

	return LoadGraphFromStream(input, graph);
}

bool LoadGraphFromStream(istream &stream, Graph &graph)
{
	string line;
	g_vertexNames.clear();

	while (getline(stream, line))
	{
		if (line.find_first_of(";", 0) != string::npos)
		{
			continue;
		}

		string vertex1, vertex2;

		ParseGraphTextString(line, vertex1);
		ParseGraphTextString(line, vertex2);

		AddVertexIntoGraph(vertex1, graph);
		AddVertexIntoGraph(vertex2, graph);

		if (vertex1.size() && vertex2.size())
		{
			AddEdgeIntoGraph(vertex1, vertex2, graph);
		}
	}

	return g_vertexNames.size() ? true : false;
}

void ParseGraphTextString(string &line, string &vertex)
{
	smatch searchResult;
	regex rgx("[R|P]{1,1}[A-Za-z0-9]+");

	if (regex_search(line, searchResult, rgx))
	{
		vertex = searchResult.str();
		line = searchResult.suffix().str();
	}
}

void AddVertexIntoGraph(string vertexName, Graph &graph)
{
	if (!vertexName.size())
	{
		return;
	}

	vector<string>::iterator it = find(g_vertexNames.begin(), g_vertexNames.end(), vertexName);

	if (it == g_vertexNames.end())
	{
		g_vertexNames.insert(g_vertexNames.end(), vertexName);

		auto vertex = add_vertex(graph);
		put(vertex_name, graph, vertex, vertexName);
	}
}

void AddEdgeIntoGraph(string vertexFrom, string vertexTo, Graph &graph)
{
	size_t from = GetVertexIndexByName(vertexFrom);
	size_t to = GetVertexIndexByName(vertexTo);

	add_edge(from, to, graph);
}

size_t GetVertexIndexByName(string vertexName)
{
	vector<string>::iterator it = find(g_vertexNames.begin(), g_vertexNames.end(), vertexName);

	if (it == g_vertexNames.end())
	{
		throw invalid_argument("Vertex by name " + vertexName + " do not exist");
	}

	return distance(g_vertexNames.begin(), it);
}

string GetVertexNameByIndex(size_t index)
{
	return g_vertexNames[index];
}
