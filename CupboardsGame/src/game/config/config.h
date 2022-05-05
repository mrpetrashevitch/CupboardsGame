#pragma once
#include <optional>

#include <fstream>
#include <sstream>
#include <vector>

namespace game::config
{
	struct vertex_position
	{
		float x;
		float y;
	};

	struct edge_position
	{
		int f;
		int s;
	};

	struct game_config
	{
		int ship_count;
		int vertex_count;
		std::vector<vertex_position> vertex_pos;
		std::vector<int> chip_pos;
		std::vector<int> chip_pos_win;
		std::vector<edge_position> edge_pos;
	};

	class config
	{
	public:
		config();
		~config();

		std::optional<game_config> load_from_file(const char* path);
	private:
		std::fstream _file;
	};
}