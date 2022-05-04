#pragma once
#include <vector>
#include <list>
#include <queue>

class graph
{
public:
	graph();
	void set_vertex(int vertices);
	void add_edge(int src, int dest);
	void set_lock(int index, bool lock);
	std::vector<int> get_dest_bfs(int s);
	std::vector<int> get_path_bfs(int s, int t);
	std::vector<int> get_dest_bfs_ex(int s);
	std::vector<int> get_path_bfs_ex(int s, int t);
	std::vector<int> get_dest_dijkstra(int s);
	std::vector<int> get_path_dijkstra(int s, int t);
	std::vector<int> get_dest_dijkstra_ex(int s);
	std::vector<int> get_path_dijkstra_ex(int s, int t);
private:
	int _n_vertex;
	std::vector <std::list<int>> _adj_vertex;
	std::vector<bool> _lock;
};
