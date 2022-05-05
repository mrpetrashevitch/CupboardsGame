#include "graph.h"
namespace game::graph
{
	graph::graph()
	{
	}

	void graph::set_vertex(int vertices)
	{
		_adj_vertex.clear();
		_lock.clear();

		_n_vertex = vertices;
		_adj_vertex.resize(_n_vertex);
		_lock.resize(_n_vertex, false);
	}

	void graph::add_edge(int src, int dest)
	{
		_adj_vertex[src].push_back(dest);
		_adj_vertex[dest].push_back(src);
	}

	void graph::set_lock(int index, bool lock)
	{
		_lock[index] = lock;
	}

	std::vector<int> graph::get_path_bfs(int s, int t)
	{
		std::vector<int> dist(_n_vertex, _n_vertex);
		std::vector<int> p(_n_vertex, -1);
		std::queue<int> q;
		dist[s] = 0;
		q.push(s);

		while (!q.empty())
		{
			int v = q.front();
			q.pop();
			for (int u : _adj_vertex[v])
			{
				if (dist[u] > dist[v] + 1)
				{
					p[u] = v;
					dist[u] = dist[v] + 1;
					q.push(u);
				}
			}
		}

		if (dist[t] == _n_vertex)
			return {};

		std::vector<int> path;
		while (t != -1)
		{
			path.push_back(t);
			t = p[t];
		}

		reverse(path.begin(), path.end());
		return path;
	}

	std::vector<int> graph::get_dest_bfs(int s)
	{
		std::vector<int> dist(_n_vertex, _n_vertex);
		std::queue<int> q;
		dist[s] = 0;
		q.push(s);

		while (!q.empty())
		{
			int v = q.front();
			q.pop();
			for (int u : _adj_vertex[v])
			{
				if (dist[u] > dist[v] + 1)
				{
					dist[u] = dist[v] + 1;
					q.push(u);
				}
			}
		}

		return dist;
	}

	std::vector<int> graph::get_path_bfs_ex(int s, int t)
	{
		std::vector<int> dist(_n_vertex, _n_vertex);
		std::vector<int> p(_n_vertex, -1);
		std::queue<int> q;
		dist[s] = 0;
		q.push(s);

		while (!q.empty())
		{
			int v = q.front();
			q.pop();
			for (int u : _adj_vertex[v])
			{
				if (dist[u] > dist[v] + 1 && !_lock[u])
				{
					p[u] = v;
					dist[u] = dist[v] + 1;
					q.push(u);
				}
			}
		}

		if (dist[t] == _n_vertex)
			return {};

		std::vector<int> path;
		while (t != -1)
		{
			path.push_back(t);
			t = p[t];
		}
		path.pop_back();

		reverse(path.begin(), path.end());
		return path;
	}

	std::vector<int> graph::get_dest_bfs_ex(int s)
	{
		std::vector<int> dist(_n_vertex, _n_vertex);
		std::queue<int> q;
		dist[s] = 0;
		q.push(s);
		std::vector<int> ret;

		while (!q.empty())
		{
			int v = q.front();
			q.pop();
			for (int u : _adj_vertex[v])
			{
				if (dist[u] > dist[v] + 1 && !_lock[u])
				{
					dist[u] = dist[v] + 1;
					ret.push_back(u);
					q.push(u);
				}
			}
		}
		return ret;
	}

	std::vector<int> graph::get_dest_dijkstra(int s)
	{
		std::vector<int> dist(_n_vertex, _n_vertex);
		std::vector<bool> used(_n_vertex);
		dist[s] = 0;

		while (true)
		{
			int v = -1;
			for (int i = 0; i < _n_vertex; i++) {
				if (!used[i] && (v == -1 || dist[i] < dist[v]))
				{
					v = i;
				}
			}

			if (v == -1)
				break;

			used[v] = true;

			for (auto& e : _adj_vertex[v])
			{
				int u = e;
				int len = 1;
				if (dist[u] > dist[v] + len)
				{
					dist[u] = dist[v] + len;
				}
			}
		}
		return dist;
	}

	std::vector<int> graph::get_path_dijkstra(int s, int t)
	{
		std::vector<int> dist(_n_vertex, _n_vertex);
		std::vector<bool> used(_n_vertex);
		std::vector<int> p(_n_vertex, -1);
		dist[s] = 0;

		while (true)
		{
			int v = -1;
			for (int i = 0; i < _n_vertex; i++) {
				if (!used[i] && (v == -1 || dist[i] < dist[v]))
				{
					v = i;
				}
			}

			if (v == -1)
				break;

			used[v] = true;
			for (auto& e : _adj_vertex[v])
			{
				int u = e;
				int len = 1;
				if (dist[u] > dist[v] + len)
				{
					dist[u] = dist[v] + len;
					p[u] = v;
				}
			}
		}

		if (dist[t] == _n_vertex)
			return {};

		std::vector<int> path;
		while (t != -1)
		{
			path.push_back(t);
			t = p[t];
		}

		reverse(path.begin(), path.end());
		return path;
	}

	std::vector<int> graph::get_dest_dijkstra_ex(int s)
	{
		std::vector<int> dist(_n_vertex, _n_vertex);
		std::vector<bool> used(_n_vertex);
		dist[s] = 0;
		std::vector<int> ret;
		while (true)
		{
			int v = -1;
			for (int i = 0; i < _n_vertex; i++) {
				if (!used[i] && (v == -1 || dist[i] < dist[v]))
				{
					v = i;
				}
			}

			if (v == -1)
				break;

			used[v] = true;

			for (auto& e : _adj_vertex[v])
			{
				int u = e;
				int len = 1;
				if (dist[u] > dist[v] + len && !_lock[u])
				{
					ret.push_back(u);
					dist[u] = dist[v] + len;
				}
			}
		}
		dist.erase(std::remove(dist.begin(), dist.end(), _n_vertex), dist.end());
		return dist;
	}

	std::vector<int> graph::get_path_dijkstra_ex(int s, int t)
	{
		std::vector<int> dist(_n_vertex, _n_vertex);
		std::vector<bool> used(_n_vertex);
		std::vector<int> p(_n_vertex, -1);
		dist[s] = 0;

		while (true)
		{
			int v = -1;
			for (int i = 0; i < _n_vertex; i++) {
				if (!used[i] && (v == -1 || dist[i] < dist[v]))
				{
					v = i;
				}
			}

			if (v == -1)
				break;

			used[v] = true;
			for (auto& e : _adj_vertex[v])
			{
				int u = e;
				int len = 1;
				if (dist[u] > dist[v] + len && !_lock[u])
				{
					dist[u] = dist[v] + len;
					p[u] = v;
				}
			}
		}

		if (dist[t] == _n_vertex)
			return {};

		std::vector<int> path;
		while (t != -1)
		{
			path.push_back(t);
			t = p[t];
		}

		reverse(path.begin(), path.end());
		return path;
	}
}