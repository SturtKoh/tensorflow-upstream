<<<<<<< HEAD
/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.
=======
/* Copyright 2021 The TensorFlow Authors. All Rights Reserved.
>>>>>>> upstream/master

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_CORE_PROFILER_INTERNAL_GPU_ROCM_TRACER_H_
#define TENSORFLOW_CORE_PROFILER_INTERNAL_GPU_ROCM_TRACER_H_

#include "absl/container/fixed_array.h"
#include "absl/container/flat_hash_map.h"
<<<<<<< HEAD
=======
#include "absl/container/flat_hash_set.h"
>>>>>>> upstream/master
#include "absl/container/node_hash_set.h"
#include "absl/types/optional.h"
#include "tensorflow/core/lib/core/errors.h"
#include "tensorflow/core/lib/core/status.h"
#include "tensorflow/core/platform/macros.h"
#include "tensorflow/core/platform/types.h"
#include "tensorflow/stream_executor/rocm/roctracer_wrapper.h"

namespace tensorflow {
namespace profiler {

struct MemcpyDetails {
  // The amount of data copied for memcpy events.
  size_t num_bytes;
  // The destination device for peer-2-peer communication (memcpy). The source
  // device is implicit: its the current device.
<<<<<<< HEAD
  uint32 destination;
=======
  uint32_t destination;
>>>>>>> upstream/master
  // Whether or not the memcpy is asynchronous.
  bool async;
};

struct MemsetDetails {
  // The number of memory elements getting set
  size_t num_elements;
  // Whether or not the memset is asynchronous.
  bool async;
};

struct MemAllocDetails {
  // The amount of data requested for cudaMalloc events.
<<<<<<< HEAD
  uint64 num_bytes;
=======
  uint64_t num_bytes;
>>>>>>> upstream/master
};

struct KernelDetails {
  // The number of registers used in this kernel.
<<<<<<< HEAD
  uint64 registers_per_thread;
  // The amount of shared memory space used by a thread block.
  uint64 static_shared_memory_usage;
  // The amount of dynamic memory space used by a thread block.
  uint64 dynamic_shared_memory_usage;
  // X-dimension of a thread block.
  uint64 block_x;
  // Y-dimension of a thread block.
  uint64 block_y;
  // Z-dimension of a thread block.
  uint64 block_z;
  // X-dimension of a grid.
  uint64 grid_x;
  // Y-dimension of a grid.
  uint64 grid_y;
  // Z-dimension of a grid.
  uint64 grid_z;
};

//TODO(rocm-profiler): do we support other event types such as memfree in CUPTI? 
=======
  uint32_t registers_per_thread;
  // The amount of shared memory space used by a thread block.
  uint32_t static_shared_memory_usage;
  // The amount of dynamic memory space used by a thread block.
  uint32_t dynamic_shared_memory_usage;
  // X-dimension of a thread block.
  uint32_t block_x;
  // Y-dimension of a thread block.
  uint32_t block_y;
  // Z-dimension of a thread block.
  uint32_t block_z;
  // X-dimension of a grid.
  uint32_t grid_x;
  // Y-dimension of a grid.
  uint32_t grid_y;
  // Z-dimension of a grid.
  uint32_t grid_z;
};

>>>>>>> upstream/master
enum class RocmTracerEventType {
  Unsupported = 0,
  Kernel,
  MemcpyH2D,
  MemcpyD2H,
  MemcpyD2D,
  MemcpyP2P,
  MemcpyOther,
  MemoryAlloc,
  Memset,
  StreamSynchronize,
  Generic,
};

const char* GetRocmTracerEventTypeName(const RocmTracerEventType& type);

enum class RocmTracerEventSource {
  ApiCallback = 0,
  Activity,
};

const char* GetRocmTracerEventSourceName(const RocmTracerEventSource& source);

enum class RocmTracerEventDomain {
  HIP_API = 0,
  HCC_OPS,
};

const char* GetRocmTracerEventDomainName(const RocmTracerEventDomain& domain);

struct RocmTracerEvent {
<<<<<<< HEAD
  static constexpr uint32 kInvalidDeviceId =
      std::numeric_limits<uint32_t>::max();
  static constexpr uint32 kInvalidThreadId =
      std::numeric_limits<uint32_t>::max();
  static constexpr uint32 kInvalidCorrelationId =
      std::numeric_limits<uint32_t>::max();
  static constexpr uint64 kInvalidStreamId =
=======
  static constexpr uint32_t kInvalidDeviceId =
      std::numeric_limits<uint32_t>::max();
  static constexpr uint32_t kInvalidThreadId =
      std::numeric_limits<uint32_t>::max();
  static constexpr uint32_t kInvalidCorrelationId =
      std::numeric_limits<uint32_t>::max();
  static constexpr uint64_t kInvalidStreamId =
>>>>>>> upstream/master
      std::numeric_limits<uint64_t>::max();
  RocmTracerEventType type;
  RocmTracerEventSource source;
  RocmTracerEventDomain domain;
  std::string name;
  // This points to strings in AnnotationMap, which should outlive the point
  // where serialization happens.
  absl::string_view annotation;
<<<<<<< HEAD
  absl::string_view roctx_range;
  uint64 start_time_ns;
  uint64 end_time_ns;
  uint32 device_id = kInvalidDeviceId;
  uint32 correlation_id = kInvalidCorrelationId;
  uint32 thread_id = kInvalidThreadId;
  int64 stream_id = kInvalidStreamId;
=======
  uint64_t start_time_ns;
  uint64_t end_time_ns;
  uint32_t device_id = kInvalidDeviceId;
  uint32_t correlation_id = kInvalidCorrelationId;
  uint32_t thread_id = kInvalidThreadId;
  int64_t stream_id = kInvalidStreamId;
>>>>>>> upstream/master
  union {
    MemcpyDetails memcpy_info;      // If type == Memcpy*
    MemsetDetails memset_info;      // If type == Memset*
    MemAllocDetails memalloc_info;  // If type == MemoryAlloc
    KernelDetails kernel_info;      // If type == Kernel
  };
};

<<<<<<< HEAD
void DumpRocmTracerEvent(const RocmTracerEvent& event, uint64 start_walltime_ns,
                         uint64 start_gputime_ns);
=======
void DumpRocmTracerEvent(const RocmTracerEvent& event,
                         uint64_t start_walltime_ns, uint64_t start_gputime_ns);
>>>>>>> upstream/master

struct RocmTracerOptions {
  // map of domain --> ops for which we need to enable the API callbacks
  // If the ops vector is empty, then enable API callbacks for entire domain
<<<<<<< HEAD
  std::map<activity_domain_t, std::vector<uint32_t> > api_callbacks;

  // map of domain --> ops for which we need to enable the Activity records
  // If the ops vector is empty, then enable Activity records for entire domain
  std::map<activity_domain_t, std::vector<uint32_t> > activity_tracing;
=======
  absl::flat_hash_map<activity_domain_t, std::vector<uint32_t> > api_callbacks;

  // map of domain --> ops for which we need to enable the Activity records
  // If the ops vector is empty, then enable Activity records for entire domain
  absl::flat_hash_map<activity_domain_t, std::vector<uint32_t> >
      activity_tracing;
>>>>>>> upstream/master
};

struct RocmTraceCollectorOptions {
  // Maximum number of events to collect from callback API; if -1, no limit.
  // if 0, the callback API is enabled to build a correlation map, but no
  // events are collected.
<<<<<<< HEAD
  uint64 max_callback_api_events;
  // Maximum number of events to collect from activity API; if -1, no limit.
  uint64 max_activity_api_events;
  // Maximum number of annotation strings that we can accommodate.
  uint64 max_annotation_strings;
  // Number of GPUs involved.
  uint32 num_gpus;
=======
  uint64_t max_callback_api_events;
  // Maximum number of events to collect from activity API; if -1, no limit.
  uint64_t max_activity_api_events;
  // Maximum number of annotation strings that we can accommodate.
  uint64_t max_annotation_strings;
  // Number of GPUs involved.
  uint32_t num_gpus;
>>>>>>> upstream/master
};

class AnnotationMap {
 public:
<<<<<<< HEAD
  explicit AnnotationMap(uint64 max_size) : max_size_(max_size) {}
  void Add(uint32 correlation_id, const std::string& annotation);
  absl::string_view LookUp(uint32 correlation_id);
=======
  explicit AnnotationMap(uint64_t max_size) : max_size_(max_size) {}
  void Add(uint32_t correlation_id, const std::string& annotation);
  absl::string_view LookUp(uint32_t correlation_id);
>>>>>>> upstream/master

 private:
  struct AnnotationMapImpl {
    // The population/consumption of annotations might happen from multiple
    // callback/activity api related threads.
    absl::Mutex mutex;
    // Annotation tends to be repetitive, use a hash_set to store the strings,
    // an use the reference to the string in the map.
    absl::node_hash_set<std::string> annotations;
<<<<<<< HEAD
    absl::flat_hash_map<uint32, absl::string_view> correlation_map;
  };
  const uint64 max_size_;
  AnnotationMapImpl map_;

  TF_DISALLOW_COPY_AND_ASSIGN(AnnotationMap);
=======
    absl::flat_hash_map<uint32_t, absl::string_view> correlation_map;
  };
  const uint64_t max_size_;
  AnnotationMapImpl map_;

 public:
  // Disable copy and move.
  AnnotationMap(const AnnotationMap&) = delete;
  AnnotationMap& operator=(const AnnotationMap&) = delete;
>>>>>>> upstream/master
};

class RocmTraceCollector {
 public:
  explicit RocmTraceCollector(const RocmTraceCollectorOptions& options)
      : options_(options), annotation_map_(options.max_annotation_strings) {}
  virtual ~RocmTraceCollector() {}

  virtual void AddEvent(RocmTracerEvent&& event) = 0;
  virtual void OnEventsDropped(const std::string& reason,
<<<<<<< HEAD
                               uint32 num_events) = 0;
=======
                               uint32_t num_events) = 0;
>>>>>>> upstream/master
  virtual void Flush() = 0;

  AnnotationMap* annotation_map() { return &annotation_map_; }

 protected:
  RocmTraceCollectorOptions options_;

 private:
  AnnotationMap annotation_map_;

<<<<<<< HEAD
  TF_DISALLOW_COPY_AND_ASSIGN(RocmTraceCollector);
};

// forward declarations for callback functors
class RocmApiCallbackImpl;
class RocmActivityCallbackImpl;
=======
 public:
  // Disable copy and move.
  RocmTraceCollector(const RocmTraceCollector&) = delete;
  RocmTraceCollector& operator=(const RocmTraceCollector&) = delete;
};

class RocmTracer;

class RocmApiCallbackImpl {
 public:
  RocmApiCallbackImpl(const RocmTracerOptions& options, RocmTracer* tracer,
                      RocmTraceCollector* collector)
      : options_(options), tracer_(tracer), collector_(collector) {}

  Status operator()(uint32_t domain, uint32_t cbid, const void* cbdata);

 private:
  void AddKernelEventUponApiExit(uint32_t cbid, const hip_api_data_t* data);
  void AddMemcpyEventUponApiExit(uint32_t cbid, const hip_api_data_t* data);
  void AddMemsetEventUponApiExit(uint32_t cbid, const hip_api_data_t* data);
  void AddMallocEventUponApiExit(uint32_t cbid, const hip_api_data_t* data);
  void AddStreamSynchronizeEventUponApiExit(uint32_t cbid,
                                            const hip_api_data_t* data);
  void AddGenericEventUponApiExit(uint32_t cbid, const hip_api_data_t* data);

  RocmTracerOptions options_;
  RocmTracer* tracer_ = nullptr;
  RocmTraceCollector* collector_ = nullptr;
};

class RocmActivityCallbackImpl {
 public:
  RocmActivityCallbackImpl(const RocmTracerOptions& options, RocmTracer* tracer,
                           RocmTraceCollector* collector)
      : options_(options), tracer_(tracer), collector_(collector) {}

  Status operator()(const char* begin, const char* end);

 private:
  void AddHipKernelActivityEvent(const roctracer_record_t* record);
  void AddHipMemcpyActivityEvent(const roctracer_record_t* record);
  void AddHipMemsetActivityEvent(const roctracer_record_t* record);
  void AddHipMallocEvent(const roctracer_record_t* record);
  void AddHipStreamSynchronizeEvent(const roctracer_record_t* record);
  void AddHccKernelActivityEvent(const roctracer_record_t* record);
  void AddHccMemcpyActivityEvent(const roctracer_record_t* record);

  RocmTracerOptions options_;
  RocmTracer* tracer_ = nullptr;
  RocmTraceCollector* collector_ = nullptr;
};
>>>>>>> upstream/master

// The class use to enable cupti callback/activity API and forward the collected
// trace events to RocmTraceCollector. There should be only one RocmTracer
// per process.
class RocmTracer {
 public:
  // Returns a pointer to singleton RocmTracer.
  static RocmTracer* GetRocmTracerSingleton();

  // Only one profile session can be live in the same time.
  bool IsAvailable() const;

  void Enable(const RocmTracerOptions& options, RocmTraceCollector* collector);
  void Disable();

  void ApiCallbackHandler(uint32_t domain, uint32_t cbid, const void* cbdata);
  void ActivityCallbackHandler(const char* begin, const char* end);

<<<<<<< HEAD
  static uint64 GetTimestamp();
  static int NumGpus();

  void AddToPendingActivityRecords(uint32 correlation_id) {
    pending_activity_records_.Add(correlation_id);
  }

  void RemoveFromPendingActivityRecords(uint32 correlation_id) {
=======
  static uint64_t GetTimestamp();
  static int NumGpus();

  void AddToPendingActivityRecords(uint32_t correlation_id) {
    pending_activity_records_.Add(correlation_id);
  }

  void RemoveFromPendingActivityRecords(uint32_t correlation_id) {
>>>>>>> upstream/master
    pending_activity_records_.Remove(correlation_id);
  }

  void ClearPendingActivityRecordsCount() { pending_activity_records_.Clear(); }

  size_t GetPendingActivityRecordsCount() {
    return pending_activity_records_.Count();
  }

 protected:
  // protected constructor for injecting mock cupti interface for testing.
  explicit RocmTracer() : num_gpus_(NumGpus()) {}

 private:
  Status EnableApiTracing();
  Status DisableApiTracing();

  Status EnableActivityTracing();
  Status DisableActivityTracing();

  int num_gpus_;
  absl::optional<RocmTracerOptions> options_;
  RocmTraceCollector* collector_ = nullptr;

  bool api_tracing_enabled_ = false;
  bool activity_tracing_enabled_ = false;

  RocmApiCallbackImpl* api_cb_impl_;
  RocmActivityCallbackImpl* activity_cb_impl_;

  class PendingActivityRecords {
   public:
    // add a correlation id to the pending set
<<<<<<< HEAD
    void Add(uint32 correlation_id) {
=======
    void Add(uint32_t correlation_id) {
>>>>>>> upstream/master
      absl::MutexLock lock(&mutex);
      pending_set.insert(correlation_id);
    }
    // remove a correlation id from the pending set
<<<<<<< HEAD
    void Remove(uint32 correlation_id) {
=======
    void Remove(uint32_t correlation_id) {
>>>>>>> upstream/master
      absl::MutexLock lock(&mutex);
      pending_set.erase(correlation_id);
    }
    // clear the pending set
    void Clear() {
      absl::MutexLock lock(&mutex);
      pending_set.clear();
    }
    // count the number of correlation ids in the pending set
    size_t Count() {
      absl::MutexLock lock(&mutex);
      return pending_set.size();
    }

   private:
    // set of co-relation ids for which the hcc activity record is pending
<<<<<<< HEAD
    std::set<uint32> pending_set;
=======
    absl::flat_hash_set<uint32_t> pending_set;
>>>>>>> upstream/master
    // the callback which processes the activity records (and consequently
    // removes items from the pending set) is called in a separate thread
    // from the one that adds item to the list.
    absl::Mutex mutex;
  };
  PendingActivityRecords pending_activity_records_;

<<<<<<< HEAD
  TF_DISALLOW_COPY_AND_ASSIGN(RocmTracer);
=======
 public:
  // Disable copy and move.
  RocmTracer(const RocmTracer&) = delete;
  RocmTracer& operator=(const RocmTracer&) = delete;
>>>>>>> upstream/master
};

}  // namespace profiler
}  // namespace tensorflow
#endif  // TENSORFLOW_CORE_PROFILER_INTERNAL_GPU_ROCM_TRACER_H_
