#pragma once

#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include "AbstractTask.h"


class ThreadManager
{
public:
	ThreadManager() { done = false; }
	~ThreadManager() {}

	void add_task(AbstractTask* t)
	{
		{
			std::lock_guard<std::mutex> gaurd(_mu_1);
			tasks.push(t);
		}
	};

	void clear_tasks() {
		{
			std::lock_guard<std::mutex> gaurd(_mu_1);
			while (!tasks.empty())
				tasks.pop();
		}
	};

	bool is_done() const
	{
		return tasks.empty();
	};

	void create_workers(int num_workers)
	{
		join_workers();
		for (int t = 0; t < num_workers; t++) {
			create_worker();
		}
	};

	void join_workers() {

		done = true;

		for (auto& t : threads) {
			t->join();
		}

		threads.clear();
	};

private:
	std::vector<std::thread*> threads;

	std::queue<AbstractTask*> tasks;

	std::mutex _mu_1;

	void create_worker()
	{
		done = false;
		threads.push_back(new std::thread(std::mem_fun(&ThreadManager::run), this));
	};

	void run() {
		while (!done)
		{
			std::lock_guard<std::mutex> gaurd(_mu_1);
			{
				if (!tasks.empty())
				{
					AbstractTask* t;

						t = tasks.front();
						tasks.pop();

					if (t)
						t->run();

					delete t;
				}
			}
		}
	};

	std::atomic_bool done;
};