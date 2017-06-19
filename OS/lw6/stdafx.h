#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iterator>
#include <string>
#include <regex>

#include <boost/config.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>

typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS,
        boost::property<boost::vertex_name_t, std::string>> Graph;
