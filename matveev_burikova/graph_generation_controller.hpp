#pragma once

#include "graph.hpp"
#include "graph_generator.hpp"
#include "interfaces/i_worker.hpp"

#include <atomic>
#include <functional>
#include <list>
#include <optional>
#include <thread>

namespace uni_course_cpp {
class GraphGenerationController {
 public:
  using GenStartedCallback = std::function<void(int index)>;
  using GenFinishedCallback =
      std::function<void(int index, std::unique_ptr<IGraph> graph)>;

  GraphGenerationController(int threads_count,
                            int graphs_count,
                            GraphGenerator::Params&& graph_generator_params);

  void generate(const GenStartedCallback& gen_started_callback,
                const GenFinishedCallback& gen_finished_callback);

 private:
  class Worker : public IWorker {
   public:
    explicit Worker(const GetJobCallback& get_job_callback)
        : IWorker(get_job_callback), get_job_callback_(get_job_callback) {}

    ~Worker();

    void start();
    void stop();

   private:
    enum class State { Idle, Working, ShouldTerminate };

    std::thread thread_;
    GetJobCallback get_job_callback_;
    State state_ = State::Idle;
  };

  JobCallback get_job();

  std::atomic<int> waiting_jobs_count_;
  std::list<IWorker*> workers_;
  std::list<JobCallback> jobs_;
  int threads_count_;
  int graphs_count_;
  GraphGenerator graph_generator_;
};
}  // namespace uni_course_cpp
