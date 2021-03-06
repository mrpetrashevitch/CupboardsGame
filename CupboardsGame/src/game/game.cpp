#include "game.h"
#include "thread_pool/thread_pool.h"
#include <limits>

namespace game
{
	sf::Color g_colors[]{
		sf::Color::Color(0xFF,0x00,0x00), //RED
		sf::Color::Color(0x00,0xFF,0x00), //GREEN
		sf::Color::Color(0x00,0x00,0xFF), //BLUE
		sf::Color::Color(0xFF,0xFF,0x00), //YELLOW
		sf::Color::Color(0xFF,0x00,0xFF), //MAGENTA
		sf::Color::Color(0x00,0xFF,0xFF), //CYAN

		sf::Color::Color(0x8D,0x6F,0x47), //BROWN
		sf::Color::Color(0x4E,0x5D,0x6C), //CHARCOAL
		sf::Color::Color(0x86,0x5A,0x5A), //CHESTNUT
		sf::Color::Color(0x5A,0x69,0x86), //GRAY
		sf::Color::Color(0x52,0x29,0xA3), //INDIGO
		sf::Color::Color(0x52,0x88,0x00), //LIME
		sf::Color::Color(0x88,0x88,0x0E), //MUSTARD
		sf::Color::Color(0x6E,0x6E,0x41), //OLIVE
		sf::Color::Color(0xBE,0x6D,0x00), //ORANGE
		sf::Color::Color(0xB1,0x36,0x5F), //PINK
		sf::Color::Color(0x70,0x57,0x70), //PLUM
		sf::Color::Color(0x7A,0x36,0x7A), //PURPLE
		sf::Color::Color(0xB1,0x44,0x0E), //RED_ORANGE
		sf::Color::Color(0x29,0x52,0x7A), //SEA_BLUE
		sf::Color::Color(0x4A,0x71,0x6C), //SLATE
		sf::Color::Color(0x28,0x75,0x4E), //TEAL
		sf::Color::Color(0x1B,0x88,0x7A), //TURQOISE
	};

	enum class game_state
	{
		main_menu,
		level_loading,
		level_complete,
		level_on,
		game_over,
	};

	game::game() :
		_inited(false),
#ifdef _DEBUG
		_window(sf::VideoMode(1200, 800), "Cupboards", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(0, 0, 16))
#else
		_window(sf::VideoMode(1200, 800), "Cupboards", sf::Style::Fullscreen, sf::ContextSettings(0, 0, 16))
#endif // _DEBUG
	{
		_window.setVerticalSyncEnabled(true);
		_window.setFramerateLimit(120);
	}

	game::~game()
	{

	}

	bool game::init()
	{
		if (_inited)
			return false;

		if (!_load_res())
			return false;

		sf::Vector2f win_size{ (float)_window.getSize().x , (float)_window.getSize().y };

		_music.setLoop(true);

		sf::Sprite background;
		background.setTexture(_background_texture);
		background.setPosition(0, 0);
		auto back_size = _background_texture.getSize();
		float scale_background = win_size.x / back_size.x > win_size.y / back_size.y ? win_size.x / back_size.x : win_size.y / back_size.y;
		background.scale(scale_background, scale_background);
		_background.set_sprite(background);

		_text_game_name.setFont(_font);
		_text_game_name.setCharacterSize(100);
		_text_game_name.setString("Cupboards");
		_text_game_name.setFillColor(sf::Color::White);
		_text_game_name.setOrigin(_text_game_name.findCharacterPos(9).x / 2, 100);
		_text_game_name.setPosition(win_size.x / 2, win_size.y / 2);

		_text_game_over.setFont(_font);
		_text_game_over.setCharacterSize(100);
		_text_game_over.setString("Game over");
		_text_game_over.setFillColor(sf::Color::White);
		_text_game_over.setOrigin(_text_game_over.findCharacterPos(9).x / 2, 100);
		_text_game_over.setPosition(win_size.x / 2, win_size.y / 2);

		_text_press_start.setFont(_font);
		_text_press_start.setCharacterSize(40);
		_text_press_start.setString("Press space to start");
		_text_press_start.setFillColor(sf::Color::White);
		_text_press_start.setOrigin(_text_press_start.findCharacterPos(100).x / 2, 0);
		_text_press_start.setPosition(win_size.x / 2, win_size.y / 2);

		_text_next_level.setFont(_font);
		_text_next_level.setCharacterSize(40);
		_text_next_level.setString("Press space to continue");
		_text_next_level.setFillColor(sf::Color::White);
		_text_next_level.setOrigin(_text_next_level.findCharacterPos(100).x / 2, 0);
		_text_next_level.setPosition(win_size.x / 2, win_size.y / 2);

		_text_loading.setFont(_font);
		_text_loading.setCharacterSize(40);
		_text_loading.setString("Loading...");
		_text_loading.setFillColor(sf::Color::White);
		_text_loading.setOrigin(_text_loading.findCharacterPos(100).x / 2, (float)_text_loading.getCharacterSize());
		_text_loading.setPosition(win_size.x / 2, win_size.y - 20);

		_text_total_step.setFont(_font);
		_text_total_step.setCharacterSize(40);
		_text_total_step.setFillColor(sf::Color::White);
		_text_total_step.setString("Steps: 0");

		_text_level.setFont(_font);
		_text_level.setCharacterSize(40);
		_text_level.setFillColor(sf::Color::White);
		_text_level.setString("Level: 0");
		_text_level.setOrigin(_text_level.findCharacterPos(100).x / 2, 0);
		_text_level.setPosition(win_size.x / 2, 0.f);

		_inited = true;
		return _inited;
	}

	void game::run()
	{
		if (!_inited) return;

		sf::Sound sound_level_complete(_sound_level_complete_buffer);
		sound_level_complete.setVolume(30.f);

		thread_pool thread_pool(1);
		sf::Clock clock;

		_music.play();

		int level = 1;
		int total_step = 0;
		int chip_selected = -1;
		std::atomic<game_state> game_state = game_state::main_menu;

		while (_window.isOpen())
		{
			sf::Vector2f pos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
			sf::Event event;
			while (_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed ||
					(event.type == sf::Event::KeyPressed &&
						event.key.code == sf::Keyboard::Escape))
				{
					_window.close();
					break;
				}

				if ((game_state == game_state::main_menu ||
					game_state == game_state::level_complete ||
					game_state == game_state::game_over) &&
					event.type == sf::Event::KeyPressed &&
					event.key.code == sf::Keyboard::Space)
				{
					if (game_state != game_state::game_over)
					{
						game_state = game_state::level_loading;
						thread_pool.push_task([&]()
							{
								//loading simulation
								std::this_thread::sleep_for(std::chrono::seconds(1));

								std::ostringstream path;
								path << "resources/level" << level << ".txt";
								if (_load_level(path.str().c_str()))
								{
									path.str("");
									path << "Level " << level;
									_text_level.setString(path.str());

									total_step = 0;
									level++;

									path.str("");
									path << total_step;
									_text_total_step.setString("Steps: " + path.str());

									clock.restart();
									game_state = game_state::level_on;
								}
								else
								{
									level = 1;
									game_state = game_state::game_over;
									//
								}
							});
					}
					else
					{
						game_state = game_state::main_menu;
					}

				}

				if (game_state == game_state::level_on &&
					event.type == sf::Event::MouseButtonPressed &&
					event.key.code == sf::Mouse::Left)
				{
					int t_chip_select = chip_selected;
					chip_selected = _on_chip_click(pos);

					if (chip_selected == -1 && t_chip_select != -1 && _on_vertex_click(pos, t_chip_select))
					{
						std::ostringstream stream;
						stream << ++total_step;
						_text_total_step.setString("Steps: " + stream.str());
					}
				}

			}

			float dt_time = clock.restart().asSeconds();
			_window.clear();
			_background.update(dt_time);
			_background.on_drow(_window);
			switch (game_state)
			{
			case game_state::main_menu:
				_window.draw(_text_game_name);
				_window.draw(_text_press_start);
				break;
			case game_state::level_loading:
				_window.draw(_text_loading);
				break;
			case game_state::level_complete:
				for (auto& i : _chips)
					i.update(dt_time);
				for (auto& i : _edges)
					i.on_drow(_window);
				for (auto& i : _vertexes)
					i.on_drow(_window);
				for (auto& i : _chips)
					i.on_drow(_window);
				_window.draw(_text_total_step);
				_window.draw(_text_level);
				_window.draw(_text_next_level);
				break;
			case game_state::level_on:
				if (_check_win())
				{
					game_state = game_state::level_complete;
					sound_level_complete.play();
				}
				for (auto& i : _vertexes)
					i.on_entered(pos);
				for (auto& i : _chips)
					i.on_entered(pos);
				for (auto& i : _chips)
					i.update(dt_time);
				for (auto& i : _edges)
					i.on_drow(_window);
				for (auto& i : _vertexes)
					i.on_drow(_window);
				for (auto& i : _chips)
					i.on_drow(_window);
				_window.draw(_text_total_step);
				_window.draw(_text_level);
				break;
			case game_state::game_over:
				_window.draw(_text_game_over);
				_window.draw(_text_next_level);
				break;
			default:
				break;
			}
			_window.display();
		}
	}

	bool game::_load_res()
	{
		try
		{
			std::string path_hex("resources/hex.png");
			if (!_chip_texture.loadFromFile(path_hex.c_str()))
				throw path_hex.c_str();

			std::string path_hex_back("resources/hex_back.png");
			if (!_chip_back_texture.loadFromFile(path_hex_back.c_str()))
				throw path_hex_back.c_str();

			std::string path_font("resources/sansation.ttf");
			if (!_font.loadFromFile(path_font.c_str()))
				throw path_font.c_str();

			std::string path_back("resources/game_back.jpg");
			if (!_background_texture.loadFromFile(path_back.c_str()))
				throw path_back.c_str();

			std::string path_music("resources/back_music.ogg");
			if (!_music.openFromFile(path_music.c_str()))
				throw path_music.c_str();

			std::string path_sound_select("resources/sound_select.wav");
			if (!_sound_select_buffer.loadFromFile(path_sound_select.c_str()))
				throw path_sound_select.c_str();

			std::string path_sound_level_complete("resources/sound_level_complete.wav");
			if (!_sound_level_complete_buffer.loadFromFile(path_sound_level_complete.c_str()))
				throw path_sound_level_complete.c_str();
		}
		catch (const std::exception& ex)
		{
			printf("faild to laod: %s", ex.what());
			return false;
		}
		return true;
	}

	bool game::_load_level(const char* path_config_level)
	{
		_vertexes.clear();
		_chips.clear();
		_edges.clear();

		config::config config;
		auto opt_con = config.load_from_file(path_config_level);
		if (!opt_con) return false;

		config::game_config& g_con = opt_con.value();

		_graph.set_vertex(g_con.vertex_count);

		auto mult = _set_scale(g_con, _window.getSize());
		if (mult > 2.2f) mult = 2.2f;

		sf::Sprite s_chip_back;
		s_chip_back.setTexture(_chip_back_texture);
		sf::Sound sound_select_vertex(_sound_select_buffer);
		for (auto& i : g_con.vertex_pos)
			_vertexes.push_back({ {i.x, i.y},mult ,s_chip_back,sound_select_vertex });

		for (auto& i : g_con.chip_pos_win)
			_vertexes[i].set_color(g_colors[i]);

		sf::Sprite s_chip;
		s_chip.setTexture(_chip_texture);

		for (size_t i = 0; i < g_con.chip_pos.size(); i++)
		{
			int index = g_con.chip_pos[i];
			int index_win = g_con.chip_pos_win[i];
			_chips.push_back({ {_vertexes[index].get_pos().x ,_vertexes[index].get_pos().y }, mult, s_chip, _vertexes[index_win].get_color() });
			_chips[_chips.size() - 1].set_vertex_index(index);
			_chips[_chips.size() - 1].set_vertex_dest(index_win);
			_graph.set_lock(index, true);
		}

		for (auto& i : g_con.edge_pos)
		{
			_graph.add_edge(i.f, i.s);

			_edges.push_back({
				{_vertexes[i.f].get_pos().x ,_vertexes[i.f].get_pos().y},
				{_vertexes[i.s].get_pos().x ,_vertexes[i.s].get_pos().y},
				mult });
		}
		return true;
	}

	bool game::_check_win()
	{
		bool win = true;
		for (auto& i : _chips)
			if (i.get_vertex_dest() != i.get_vertex_index())
			{
				win = false;
				break;
			}
		return win;
	}

	float game::_set_scale(config::game_config& config, const sf::Vector2u& window_size)
	{
		const float border_left = 100.f;
		const float border_right = 100.f;
		const float border_top = 100.f;
		const float border_bottom = 100.f;

		float max_x = 0.f;
		float max_y = 0.f;
		float min_x = std::numeric_limits<float>::max();
		float min_y = std::numeric_limits<float>::max();

		for (auto& i : config.vertex_pos)
		{
			if (i.x > max_x) max_x = i.x;
			if (i.y > max_y) max_y = i.y;
			if (i.x < min_x) min_x = i.x;
			if (i.y < min_y) min_y = i.y;
		}

		float dx = max_x - min_x;
		float dy = max_y - min_y;
		float w_screen = window_size.x - (border_left + border_right);
		float h_screen = window_size.y - (border_top + border_bottom);
		float mult_x = w_screen / dx;
		float mult_y = h_screen / dy;
		float mult = mult_x < mult_y ? mult_x : mult_y;
		float of_x = (w_screen - mult * dx) / 2.f;
		float of_y = (h_screen - mult * dy) / 2.f;

		for (auto& i : config.vertex_pos)
		{
			i.x = (i.x - min_x) * mult + border_left + of_x;
			i.y = (i.y - min_y) * mult + border_top + of_y;
		}
		return mult;
	}

	int game::_on_chip_click(const sf::Vector2f& pos)
	{
		int index = -1;
		for (size_t i = 0; i < _chips.size(); i++)
		{
			if (_chips[i].on_select(pos))
			{
				index = (int)i;
				auto can_move = _graph.get_dest_bfs_ex(_chips[index].get_vertex_index());
				for (size_t j = 0; j < can_move.size(); j++)
					_vertexes[can_move[j]].set_flash(true);
			}
		}
		return index;
	}

	bool game::_on_vertex_click(const sf::Vector2f& pos, int chip_index)
	{
		bool moved = false;
		for (size_t i = 0; i < _vertexes.size(); i++)
		{
			_vertexes[i].set_flash(false);
			if (_vertexes[i].on_select(pos))
			{
				auto v_path = _graph.get_path_bfs_ex(_chips[chip_index].get_vertex_index(), (int)i);
				if (v_path.empty())
					continue;

				std::vector<sf::Vector2f> path;
				for (size_t j = 0; j < v_path.size(); j++)
					path.push_back(_vertexes[v_path[j]].get_pos());

				_graph.set_lock(_chips[chip_index].get_vertex_index(), false);
				_graph.set_lock((int)i, true);
				_chips[chip_index].move_to_dest(path);
				_chips[chip_index].set_vertex_index((int)i);
				moved = true;
			}
		}
		return moved;
	}
}