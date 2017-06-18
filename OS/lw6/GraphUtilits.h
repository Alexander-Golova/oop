#pragma once

bool LoadGraphFromFile(const std::string &fileName, Graph &graph);
bool LoadGraphFromStream(std::istream &stream, Graph &graph);
std::string GetVertexNameByIndex(size_t index);
