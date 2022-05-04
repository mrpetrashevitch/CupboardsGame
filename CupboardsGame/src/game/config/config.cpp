#include "config.h"

config::config()
{
}

config::~config()
{
}

std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string& s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

std::optional<game_config> config::load_from_file(const char* path)
{
	game_config conf{};

	_file.open(path, std::ios::in);
	if (!_file.is_open()) 
	{
		std::printf("failed to open file: %s\n", path);
		return{};
	}

	try
	{
		std::string shaps_count;
		_file >> shaps_count;
		conf.ship_count = std::stoi(shaps_count);
		std::string vertex_count;
		_file >> vertex_count;
		conf.vertex_count = std::stoi(vertex_count);
	
		for (int i = 0; i < conf.vertex_count; i++)
		{
			std::string vertex_pos;
			_file >> vertex_pos;
			auto v = split(vertex_pos, ',');
			conf.vertex_pos.push_back({ (float)std::stoi(v[0]) , (float)std::stoi(v[1]) });
		}

		std::string shape_pos;
		_file >> shape_pos;
		auto s_col = split(shape_pos, ',');
		if (s_col.size() != conf.ship_count)
			throw "wrong number of ships";

		for (auto& i : s_col)
			conf.chip_pos.push_back(std::stoi(i) - 1);

		std::string shape_pos_win;
		_file >> shape_pos_win;

		auto v_col = split(shape_pos_win, ',');
		if (v_col.size() != conf.ship_count)
			throw "wrong number of ships";

		for (auto& i : v_col)
			conf.chip_pos_win.push_back(std::stoi(i) - 1);


		std::string edge_count;
		_file >> edge_count;
		int ed_count = std::stoi(edge_count);

		for (int i = 0; i < ed_count; i++)
		{
			std::string edge_pos;
			_file >> edge_pos;
			auto v = split(edge_pos, ',');
			conf.edge_pos.push_back({ std::stoi(v[0]) - 1 ,std::stoi(v[1]) - 1 });
		}
	}
	catch (const std::exception& ex)
	{
		std::printf("failed to load configuration: %s, file: %s", ex.what(), path);
	}
	_file.close();
	return { conf };
}
