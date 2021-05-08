/*
Copyright (c) 2015 - present Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "CUDA2HIP.h"

// Maps the names of CUDA DRIVER API types to the corresponding HIP types
const std::map<llvm::StringRef, hipCounter> CUDA_DRIVER_TYPE_NAME_MAP {

  // 1. Structs

  {"CUDA_ARRAY3D_DESCRIPTOR_st",                                       {"HIP_ARRAY3D_DESCRIPTOR",                                   "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_ARRAY3D_DESCRIPTOR",                                          {"HIP_ARRAY3D_DESCRIPTOR",                                   "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_ARRAY3D_DESCRIPTOR_v2",                                       {"HIP_ARRAY3D_DESCRIPTOR",                                   "", CONV_TYPE, API_DRIVER, 1}},

  {"CUDA_ARRAY_DESCRIPTOR_st",                                         {"HIP_ARRAY_DESCRIPTOR",                                     "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_ARRAY_DESCRIPTOR_v1_st",                                      {"HIP_ARRAY_DESCRIPTOR",                                     "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_ARRAY_DESCRIPTOR",                                            {"HIP_ARRAY_DESCRIPTOR",                                     "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_ARRAY_DESCRIPTOR_v1",                                         {"HIP_ARRAY_DESCRIPTOR",                                     "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_ARRAY_DESCRIPTOR_v2",                                         {"HIP_ARRAY_DESCRIPTOR",                                     "", CONV_TYPE, API_DRIVER, 1}},

  // cudaExternalMemoryBufferDesc
  {"CUDA_EXTERNAL_MEMORY_BUFFER_DESC_st",                              {"HIP_EXTERNAL_MEMORY_BUFFER_DESC",                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXTERNAL_MEMORY_BUFFER_DESC",                                 {"HIP_EXTERNAL_MEMORY_BUFFER_DESC",                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXTERNAL_MEMORY_BUFFER_DESC_v1",                              {"HIP_EXTERNAL_MEMORY_BUFFER_DESC",                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaExternalMemoryHandleDesc
  {"CUDA_EXTERNAL_MEMORY_HANDLE_DESC_st",                              {"HIP_EXTERNAL_MEMORY_HANDLE_DESC",                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXTERNAL_MEMORY_HANDLE_DESC",                                 {"HIP_EXTERNAL_MEMORY_HANDLE_DESC",                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXTERNAL_MEMORY_HANDLE_DESC_v1",                              {"HIP_EXTERNAL_MEMORY_HANDLE_DESC",                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaExternalMemoryMipmappedArrayDesc
  {"CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC_st",                     {"HIP_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC",                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC",                        {"HIP_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC",                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC_v1",                     {"HIP_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC",                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaExternalSemaphoreHandleDesc
  {"CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC_st",                           {"HIP_EXTERNAL_SEMAPHORE_HANDLE_DESC",                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC",                              {"HIP_EXTERNAL_SEMAPHORE_HANDLE_DESC",                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC_v1",                           {"HIP_EXTERNAL_SEMAPHORE_HANDLE_DESC",                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaExternalSemaphoreSignalParams
  {"CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS_st",                         {"HIP_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS",                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS",                            {"HIP_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS",                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS_v1",                         {"HIP_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS",                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaExternalSemaphoreWaitParams
  {"CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS_st",                           {"HIP_EXTERNAL_SEMAPHORE_WAIT_PARAMS",                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS",                              {"HIP_EXTERNAL_SEMAPHORE_WAIT_PARAMS",                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS_v1",                           {"HIP_EXTERNAL_SEMAPHORE_WAIT_PARAMS",                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaHostNodeParams
  {"CUDA_HOST_NODE_PARAMS_st",                                         {"hipHostNodeParams",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_HOST_NODE_PARAMS",                                            {"hipHostNodeParams",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_HOST_NODE_PARAMS_v1",                                         {"hipHostNodeParams",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaKernelNodeParams
  {"CUDA_KERNEL_NODE_PARAMS_st",                                       {"hipKernelNodeParams",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_KERNEL_NODE_PARAMS",                                          {"hipKernelNodeParams",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_KERNEL_NODE_PARAMS_v1",                                       {"hipKernelNodeParams",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // no analogue
  // NOTE: cudaLaunchParams struct differs
  {"CUDA_LAUNCH_PARAMS_st",                                            {"hipLaunchParams",                                          "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_LAUNCH_PARAMS",                                               {"hipLaunchParams",                                          "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_LAUNCH_PARAMS_v1",                                            {"hipLaunchParams",                                          "", CONV_TYPE, API_DRIVER, 1}},

  {"CUDA_MEMCPY2D_st",                                                 {"hip_Memcpy2D",                                             "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_MEMCPY2D_v1_st",                                              {"hip_Memcpy2D",                                             "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_MEMCPY2D",                                                    {"hip_Memcpy2D",                                             "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_MEMCPY2D_v1",                                                 {"hip_Memcpy2D",                                             "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_MEMCPY2D_v2",                                                 {"hip_Memcpy2D",                                             "", CONV_TYPE, API_DRIVER, 1}},

  // no analogue
  {"CUDA_MEMCPY3D_st",                                                 {"HIP_MEMCPY3D",                                             "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_MEMCPY3D_v1_st",                                              {"HIP_MEMCPY3D",                                             "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_MEMCPY3D",                                                    {"HIP_MEMCPY3D",                                             "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_MEMCPY3D_v1",                                                 {"HIP_MEMCPY3D",                                             "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_MEMCPY3D_v2",                                                 {"HIP_MEMCPY3D",                                             "", CONV_TYPE, API_DRIVER, 1}},

  {"CUDA_MEMCPY3D_PEER_st",                                            {"hip_Memcpy3D_Peer",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_MEMCPY3D_PEER",                                               {"hip_Memcpy3D_Peer",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_MEMCPY3D_PEER_v1",                                            {"hip_Memcpy3D_Peer",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaMemsetParams
  {"CUDA_MEMSET_NODE_PARAMS_st",                                       {"hipMemsetParams",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_MEMSET_NODE_PARAMS",                                          {"hipMemsetParams",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_MEMSET_NODE_PARAMS_v1",                                       {"hipMemsetParams",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  {"CUDA_POINTER_ATTRIBUTE_P2P_TOKENS_st",                             {"HIP_POINTER_ATTRIBUTE_P2P_TOKENS",                         "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_POINTER_ATTRIBUTE_P2P_TOKENS",                                {"HIP_POINTER_ATTRIBUTE_P2P_TOKENS",                         "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_POINTER_ATTRIBUTE_P2P_TOKENS_v1",                             {"HIP_POINTER_ATTRIBUTE_P2P_TOKENS",                         "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // no analogue
  // NOTE: cudaResourceDesc struct differs
  {"CUDA_RESOURCE_DESC_st",                                            {"HIP_RESOURCE_DESC_st",                                     "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_RESOURCE_DESC",                                               {"HIP_RESOURCE_DESC",                                        "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_RESOURCE_DESC_v1",                                            {"HIP_RESOURCE_DESC",                                        "", CONV_TYPE, API_DRIVER, 1}},

  // cudaResourceViewDesc
  // NOTE: cudaResourceViewDesc hasn't reserved bytes in the end
  {"CUDA_RESOURCE_VIEW_DESC_st",                                       {"HIP_RESOURCE_VIEW_DESC_st",                                "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_RESOURCE_VIEW_DESC",                                          {"HIP_RESOURCE_VIEW_DESC",                                   "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_RESOURCE_VIEW_DESC_v1",                                       {"HIP_RESOURCE_VIEW_DESC",                                   "", CONV_TYPE, API_DRIVER, 1}},

  // no analogue
  // NOTE: cudaTextureDesc differs
  {"CUDA_TEXTURE_DESC_st",                                             {"HIP_TEXTURE_DESC_st",                                      "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_TEXTURE_DESC",                                                {"HIP_TEXTURE_DESC",                                         "", CONV_TYPE, API_DRIVER, 1}},
  {"CUDA_TEXTURE_DESC_v1",                                             {"HIP_TEXTURE_DESC",                                         "", CONV_TYPE, API_DRIVER, 1}},

  // no analogue
  // NOTE: cudaDeviceProp differs
  {"CUdevprop_st",                                                     {"hipDevprop",                                               "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUdevprop",                                                        {"hipDevprop",                                               "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUdevprop_v1",                                                     {"hipDevprop",                                               "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaIpcEventHandle_st
  {"CUipcEventHandle_st",                                              {"hipIpcEventHandle_st",                                     "", CONV_TYPE, API_DRIVER, 1}},
  // cudaIpcEventHandle_t
  {"CUipcEventHandle",                                                 {"hipIpcEventHandle_t",                                      "", CONV_TYPE, API_DRIVER, 1}},
  {"CUipcEventHandle_v1",                                              {"hipIpcEventHandle_t",                                      "", CONV_TYPE, API_DRIVER, 1}},

  // cudaIpcMemHandle_st
  {"CUipcMemHandle_st",                                                {"hipIpcMemHandle_st",                                       "", CONV_TYPE, API_DRIVER, 1}},
  // cudaIpcMemHandle_t
  {"CUipcMemHandle",                                                   {"hipIpcMemHandle_t",                                        "", CONV_TYPE, API_DRIVER, 1}},
  {"CUipcMemHandle_v1",                                                {"hipIpcMemHandle_t",                                        "", CONV_TYPE, API_DRIVER, 1}},

  // CUDA: "The types CUarray and cudaArray * represent the same data type and may be used interchangeably by casting the two types between each other."
  // cudaArray
  {"CUarray_st",                                                       {"hipArray",                                                 "", CONV_TYPE, API_DRIVER, 1}},
  // cudaArray_t
  {"CUarray",                                                          {"hipArray *",                                               "", CONV_TYPE, API_DRIVER, 1}},

  // no analogue
  {"CUctx_st",                                                         {"ihipCtx_t",                                                "", CONV_TYPE, API_DRIVER, 1}},
  {"CUcontext",                                                        {"hipCtx_t",                                                 "", CONV_TYPE, API_DRIVER, 1}},

  // CUeglStreamConnection_st
  {"CUeglStreamConnection_st",                                         {"hipEglStreamConnection",                                   "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaEglStreamConnection
  {"CUeglStreamConnection",                                            {"hipEglStreamConnection *",                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // the same - CUevent_st
  {"CUevent_st",                                                       {"ihipEvent_t",                                              "", CONV_TYPE, API_DRIVER, 1}},
  // cudaEvent_t
  {"CUevent",                                                          {"hipEvent_t",                                               "", CONV_TYPE, API_DRIVER, 1}},

  // CUexternalMemory_st
  {"CUextMemory_st",                                                   {"hipExtMemory_st",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaExternalMemory_t
  {"CUexternalMemory",                                                 {"hipExternalMemory",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // CUexternalSemaphore_st
  {"CUextSemaphore_st",                                                {"hipExtSemaphore_st",                                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaExternalSemaphore_t
  {"CUexternalSemaphore",                                              {"hipExternalSemaphore",                                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // no analogue
  {"CUfunc_st",                                                        {"ihipModuleSymbol_t",                                       "", CONV_TYPE, API_DRIVER, 1}},
  // cudaFunction_t
  {"CUfunction",                                                       {"hipFunction_t",                                            "", CONV_TYPE, API_DRIVER, 1}},

  // the same - CUgraph_st
  {"CUgraph_st",                                                       {"hipGraph_st",                                              "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaGraph_t
  {"CUgraph",                                                          {"hipGraph",                                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // the same -CUgraphExec_st
  {"CUgraphExec_st",                                                   {"hipGraphExec_st",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaGraphExec_t
  {"CUgraphExec",                                                      {"hipGraphExec",                                             "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaGraphicsResource
  {"CUgraphicsResource_st",                                            {"hipGraphicsResource_st",                                   "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaGraphicsResource_t
  {"CUgraphicsResource",                                               {"hipGraphicsResource_t",                                    "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // the same - CUgraphNode_st
  {"CUgraphNode_st",                                                   {"hipGraphNode_st",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaGraphNode_t
  {"CUgraphNode",                                                      {"hipGraphNode",                                             "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaMipmappedArray
  {"CUmipmappedArray_st",                                              {"hipMipmappedArray",                                        "", CONV_TYPE, API_DRIVER, 1}},
  // cudaMipmappedArray_t
  {"CUmipmappedArray",                                                 {"hipMipmappedArray_t",                                      "", CONV_TYPE, API_DRIVER, 1}},

  // no analogue
  {"CUmod_st",                                                         {"ihipModule_t",                                             "", CONV_TYPE, API_DRIVER, 1}},
  {"CUmodule",                                                         {"hipModule_t",                                              "", CONV_TYPE, API_DRIVER, 1}},

  // the same - CUstream_st
  {"CUstream_st",                                                      {"ihipStream_t",                                             "", CONV_TYPE, API_DRIVER, 1}},
  // cudaStream_t
  {"CUstream",                                                         {"hipStream_t",                                              "", CONV_TYPE, API_DRIVER, 1}},

  // NOTE: possibly surfaceReference is analogue
  {"CUsurfref_st",                                                     {"ihipSurfaceReference_t",                                   "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUsurfref",                                                        {"hipSurfaceReference_t",                                    "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // textureReference
  {"CUtexref_st",                                                      {"textureReference",                                         "", CONV_TYPE, API_DRIVER, 1}},
  {"CUtexref",                                                         {"hipTextureReference_t",                                    "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // CUuuid_st
  // NOTE: the same struct and its name
  {"CUuuid_st",                                                        {"hipUUID",                                                  "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUuuid",                                                           {"hipUUID",                                                  "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaMemLocation
  {"CUmemLocation_st",                                                 {"hipMemoryLocation",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemLocation",                                                    {"hipMemoryLocation",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemLocation_v1",                                                 {"hipMemoryLocation",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // no analogue
  {"CUmemAllocationProp_st",                                           {"hipMemoryAllocationProperties",                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemAllocationProp",                                              {"hipMemoryAllocationProperties",                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemAllocationProp_v1",                                           {"hipMemoryAllocationProperties",                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaMemAccessDesc
  {"CUmemAccessDesc_st",                                               {"hipMemoryAccessDescription",                               "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemAccessDesc",                                                  {"hipMemoryAccessDescription",                               "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemAccessDesc_v1",                                               {"hipMemoryAccessDescription",                               "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaAccessPolicyWindow
  {"CUaccessPolicyWindow_st",                                          {"hipAccessPolicyWindow",                                    "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUaccessPolicyWindow",                                             {"hipAccessPolicyWindow",                                    "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaArraySparseProperties
  {"CUDA_ARRAY_SPARSE_PROPERTIES_st",                                  {"hipArraySparseProperties",                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_ARRAY_SPARSE_PROPERTIES",                                     {"hipArraySparseProperties",                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_ARRAY_SPARSE_PROPERTIES_v1",                                  {"hipArraySparseProperties",                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  {"CUarrayMapInfo_st",                                                {"hipArrayMapInfo",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUarrayMapInfo",                                                   {"hipArrayMapInfo",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUarrayMapInfo_v1",                                                {"hipArrayMapInfo",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  //
  {"CUmemPoolHandle_st",                                               {"hipMemPoolHandle_st",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaMemPool_t
  {"CUmemoryPool",                                                     {"hipMemoryPool",                                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaExternalSemaphoreSignalNodeParams
  {"CUDA_EXT_SEM_SIGNAL_NODE_PARAMS_st",                               {"hipExternalSemaphoreSignalNodeParams",                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXT_SEM_SIGNAL_NODE_PARAMS",                                  {"hipExternalSemaphoreSignalNodeParams",                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXT_SEM_SIGNAL_NODE_PARAMS_v1",                               {"hipExternalSemaphoreSignalNodeParams",                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaExternalSemaphoreWaitNodeParams
  {"CUDA_EXT_SEM_WAIT_NODE_PARAMS_st",                                 {"hipExternalSemaphoreWaitNodeParams",                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXT_SEM_WAIT_NODE_PARAMS",                                    {"hipExternalSemaphoreWaitNodeParams",                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_EXT_SEM_WAIT_NODE_PARAMS_v1",                                 {"hipExternalSemaphoreWaitNodeParams",                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaMemPoolProps
  {"CUmemPoolProps_st",                                                {"hipMemPoolProps",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemPoolProps",                                                   {"hipMemPoolProps",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemPoolProps_v1",                                                {"hipMemPoolProps",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaMemPoolPtrExportData
  {"CUmemPoolPtrExportData_st",                                        {"hipMemPoolPtrExportData",                                  "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemPoolPtrExportData",                                           {"hipMemPoolPtrExportData",                                  "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemPoolPtrExportData_v1",                                        {"hipMemPoolPtrExportData",                                  "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  //
  {"CUuserObject_st",                                                  {"hipUserObject",                                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaUserObject_t
  {"CUuserObject",                                                     {"hipUserObject_t",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // 2. Unions

  {"CUstreamBatchMemOpParams",                                         {"hipStreamBatchMemOpParams",                                "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUstreamBatchMemOpParams_v1",                                      {"hipStreamBatchMemOpParams",                                "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUstreamBatchMemOpParams_union",                                   {"hipStreamBatchMemOpParams",                                "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  {"CUkernelNodeAttrValue",                                            {"hipKernelNodeAttrValue",                                   "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUkernelNodeAttrValue_v1",                                         {"hipKernelNodeAttrValue",                                   "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUkernelNodeAttrValue_union",                                      {"hipKernelNodeAttrValue",                                   "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  {"CUstreamAttrValue",                                                {"hipStreamAttrValue",                                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUstreamAttrValue_v1",                                             {"hipStreamAttrValue",                                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUstreamAttrValue_union",                                          {"hipStreamAttrValue",                                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // 3. Enums
  // TODO: HIPaddress_mode_enum and all its values should be hipTextureAddressMode as long as they are equal.
  {"CUaddress_mode",                                                   {"HIPaddress_mode",                                          "", CONV_TYPE, API_DRIVER, 1}},
  {"CUaddress_mode_enum",                                              {"HIPaddress_mode_enum",                                     "", CONV_TYPE, API_DRIVER, 1}},
  // CUaddress_mode enum values
  // cudaAddressModeWrap
  {"CU_TR_ADDRESS_MODE_WRAP",                                          {"HIP_TR_ADDRESS_MODE_WRAP",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0
  // cudaAddressModeClamp
  {"CU_TR_ADDRESS_MODE_CLAMP",                                         {"HIP_TR_ADDRESS_MODE_CLAMP",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 1
  // cudaAddressModeMirror
  {"CU_TR_ADDRESS_MODE_MIRROR",                                        {"HIP_TR_ADDRESS_MODE_MIRROR",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 2
  // cudaAddressModeBorder
  {"CU_TR_ADDRESS_MODE_BORDER",                                        {"HIP_TR_ADDRESS_MODE_BORDER",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 3

  {"CUarray_cubemap_face",                                             {"hipGraphicsCubeFace",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUarray_cubemap_face_enum",                                        {"hipGraphicsCubeFace",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUarray_cubemap_face enum values
  // cudaGraphicsCubeFacePositiveX
  {"CU_CUBEMAP_FACE_POSITIVE_X",                                       {"hipGraphicsCubeFacePositiveX",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x00
  // cudaGraphicsCubeFaceNegativeX
  {"CU_CUBEMAP_FACE_NEGATIVE_X",                                       {"hipGraphicsCubeFaceNegativeX",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01
  // cudaGraphicsCubeFacePositiveY
  {"CU_CUBEMAP_FACE_POSITIVE_Y",                                       {"hipGraphicsCubeFacePositiveY",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x02
  // cudaGraphicsCubeFaceNegativeY
  {"CU_CUBEMAP_FACE_NEGATIVE_Y",                                       {"hipGraphicsCubeFaceNegativeY",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x03
  // cudaGraphicsCubeFacePositiveZ
  {"CU_CUBEMAP_FACE_POSITIVE_Z",                                       {"hipGraphicsCubeFacePositiveZ",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x04
  // cudaGraphicsCubeFaceNegativeZ
  {"CU_CUBEMAP_FACE_NEGATIVE_Z",                                       {"hipGraphicsCubeFaceNegativeZ",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x05

  {"CUarray_format",                                                   {"hipArray_Format",                                          "", CONV_TYPE, API_DRIVER, 1}},
  {"CUarray_format_enum",                                              {"hipArray_Format",                                          "", CONV_TYPE, API_DRIVER, 1}},
  // CUarray_format enum values
  {"CU_AD_FORMAT_UNSIGNED_INT8",                                       {"HIP_AD_FORMAT_UNSIGNED_INT8",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x01
  {"CU_AD_FORMAT_UNSIGNED_INT16",                                      {"HIP_AD_FORMAT_UNSIGNED_INT16",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x02
  {"CU_AD_FORMAT_UNSIGNED_INT32",                                      {"HIP_AD_FORMAT_UNSIGNED_INT32",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x03
  {"CU_AD_FORMAT_SIGNED_INT8",                                         {"HIP_AD_FORMAT_SIGNED_INT8",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x08
  {"CU_AD_FORMAT_SIGNED_INT16",                                        {"HIP_AD_FORMAT_SIGNED_INT16",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x09
  {"CU_AD_FORMAT_SIGNED_INT32",                                        {"HIP_AD_FORMAT_SIGNED_INT32",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x0a
  {"CU_AD_FORMAT_HALF",                                                {"HIP_AD_FORMAT_HALF",                                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x10
  {"CU_AD_FORMAT_FLOAT",                                               {"HIP_AD_FORMAT_FLOAT",                                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x20
  {"CU_AD_FORMAT_NV12",                                                {"HIP_AD_FORMAT_NV12",                                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0xb0

  // cudaComputeMode
  {"CUcomputemode",                                                    {"hipComputeMode",                                           "", CONV_TYPE, API_DRIVER, 1}},
  {"CUcomputemode_enum",                                               {"hipComputeMode",                                           "", CONV_TYPE, API_DRIVER, 1}},
  // CUcomputemode enum values
  // cudaComputeModeDefault
  {"CU_COMPUTEMODE_DEFAULT",                                           {"hipComputeModeDefault",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0
  // cudaComputeModeExclusive
  // NOTE: Deprecated since CUDA 8.0
  {"CU_COMPUTEMODE_EXCLUSIVE",                                         {"hipComputeModeExclusive",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, CUDA_REMOVED}}, // 1
  // cudaComputeModeProhibited
  {"CU_COMPUTEMODE_PROHIBITED",                                        {"hipComputeModeProhibited",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 2
  // cudaComputeModeExclusiveProcess
  {"CU_COMPUTEMODE_EXCLUSIVE_PROCESS",                                 {"hipComputeModeExclusiveProcess",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 3

  {"CUctx_flags",                                                      {"hipCctx_flags",                                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUctx_flags_enum",                                                 {"hipCctx_flags",                                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUctx_flags enum values
  // cudaDeviceScheduleAuto
  {"CU_CTX_SCHED_AUTO",                                                {"hipDeviceScheduleAuto",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x00
  // cudaDeviceScheduleSpin
  {"CU_CTX_SCHED_SPIN",                                                {"hipDeviceScheduleSpin",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x01
  // cudaDeviceScheduleYield
  {"CU_CTX_SCHED_YIELD",                                               {"hipDeviceScheduleYield",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x02
  // cudaDeviceScheduleBlockingSync
  {"CU_CTX_SCHED_BLOCKING_SYNC",                                       {"hipDeviceScheduleBlockingSync",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x04
  // cudaDeviceBlockingSync
  // NOTE: Deprecated since CUDA 4.0 and replaced with CU_CTX_SCHED_BLOCKING_SYNC
  {"CU_CTX_BLOCKING_SYNC",                                             {"hipDeviceScheduleBlockingSync",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, CUDA_DEPRECATED}}, // 0x04
  // cudaDeviceScheduleMask
  {"CU_CTX_SCHED_MASK",                                                {"hipDeviceScheduleMask",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x07
  // cudaDeviceMapHost
  {"CU_CTX_MAP_HOST",                                                  {"hipDeviceMapHost",                                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x08
  // cudaDeviceLmemResizeToMax
  {"CU_CTX_LMEM_RESIZE_TO_MAX",                                        {"hipDeviceLmemResizeToMax",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x10
  // cudaDeviceMask
  {"CU_CTX_FLAGS_MASK",                                                {"hipDeviceMask",                                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1f

  // cudaDeviceAttr
  {"CUdevice_attribute",                                               {"hipDeviceAttribute_t",                                     "", CONV_TYPE, API_DRIVER, 1}},
  {"CUdevice_attribute_enum",                                          {"hipDeviceAttribute_t",                                     "", CONV_TYPE, API_DRIVER, 1}},
  // CUdevice_attribute enum values
  // cudaDevAttrMaxThreadsPerBlock
  {"CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_BLOCK",                        {"hipDeviceAttributeMaxThreadsPerBlock",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  1
  // cudaDevAttrMaxBlockDimX
  {"CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_X",                              {"hipDeviceAttributeMaxBlockDimX",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  2
  // cudaDevAttrMaxBlockDimY
  {"CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Y",                              {"hipDeviceAttributeMaxBlockDimY",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  3
  // cudaDevAttrMaxBlockDimZ
  {"CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Z",                              {"hipDeviceAttributeMaxBlockDimZ",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  4
  // cudaDevAttrMaxGridDimX
  {"CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_X",                               {"hipDeviceAttributeMaxGridDimX",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  5
  // cudaDevAttrMaxGridDimY
  {"CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Y",                               {"hipDeviceAttributeMaxGridDimY",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  6
  // cudaDevAttrMaxGridDimZ
  {"CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Z",                               {"hipDeviceAttributeMaxGridDimZ",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  7
  // cudaDevAttrMaxSharedMemoryPerBlock
  {"CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK",                  {"hipDeviceAttributeMaxSharedMemoryPerBlock",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  8
  // no analogue
  // NOTE: Deprecated, use CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK
  {"CU_DEVICE_ATTRIBUTE_SHARED_MEMORY_PER_BLOCK",                      {"hipDeviceAttributeMaxSharedMemoryPerBlock",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, CUDA_DEPRECATED}}, //  8
  // cudaDevAttrTotalConstantMemory
  {"CU_DEVICE_ATTRIBUTE_TOTAL_CONSTANT_MEMORY",                        {"hipDeviceAttributeTotalConstantMemory",                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  9
  // cudaDevAttrWarpSize
  {"CU_DEVICE_ATTRIBUTE_WARP_SIZE",                                    {"hipDeviceAttributeWarpSize",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 10
  // cudaDevAttrMaxPitch
  {"CU_DEVICE_ATTRIBUTE_MAX_PITCH",                                    {"hipDeviceAttributeMaxPitch",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 11
  // cudaDevAttrMaxRegistersPerBlock
  {"CU_DEVICE_ATTRIBUTE_MAX_REGISTERS_PER_BLOCK",                      {"hipDeviceAttributeMaxRegistersPerBlock",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 12
  // no analogue
  {"CU_DEVICE_ATTRIBUTE_REGISTERS_PER_BLOCK",                          {"hipDeviceAttributeMaxRegistersPerBlock",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, CUDA_DEPRECATED}}, // 12
  // cudaDevAttrClockRate
  {"CU_DEVICE_ATTRIBUTE_CLOCK_RATE",                                   {"hipDeviceAttributeClockRate",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 13
  // cudaDevAttrTextureAlignment
  {"CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT",                            {"hipDeviceAttributeTextureAlignment",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 14
  // cudaDevAttrGpuOverlap
  // NOTE: Deprecated, use instead CU_DEVICE_ATTRIBUTE_ASYNC_ENGINE_COUNT
  {"CU_DEVICE_ATTRIBUTE_GPU_OVERLAP",                                  {"hipDeviceAttributeAsyncEngineCount",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED | CUDA_DEPRECATED}}, // 15
  // cudaDevAttrMultiProcessorCount
  {"CU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT",                         {"hipDeviceAttributeMultiprocessorCount",                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 16
  // cudaDevAttrKernelExecTimeout
  {"CU_DEVICE_ATTRIBUTE_KERNEL_EXEC_TIMEOUT",                          {"hipDeviceAttributeKernelExecTimeout",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 17
  // cudaDevAttrIntegrated
  {"CU_DEVICE_ATTRIBUTE_INTEGRATED",                                   {"hipDeviceAttributeIntegrated",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 18
  // cudaDevAttrCanMapHostMemory
  {"CU_DEVICE_ATTRIBUTE_CAN_MAP_HOST_MEMORY",                          {"hipDeviceAttributeCanMapHostMemory",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 19
  // cudaDevAttrComputeMode
  {"CU_DEVICE_ATTRIBUTE_COMPUTE_MODE",                                 {"hipDeviceAttributeComputeMode",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 20
  // cudaDevAttrMaxTexture1DWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_WIDTH",                      {"hipDeviceAttributeMaxTexture1DWidth",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 21
  // cudaDevAttrMaxTexture2DWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_WIDTH",                      {"hipDeviceAttributeMaxTexture2DWidth",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 22
  // cudaDevAttrMaxTexture2DHeight
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_HEIGHT",                     {"hipDeviceAttributeMaxTexture2DHeight",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 23
  // cudaDevAttrMaxTexture3DWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_WIDTH",                      {"hipDeviceAttributeMaxTexture3DWidth",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 24
  // cudaDevAttrMaxTexture3DHeight
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_HEIGHT",                     {"hipDeviceAttributeMaxTexture3DHeight",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 25
  // cudaDevAttrMaxTexture3DDepth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_DEPTH",                      {"hipDeviceAttributeMaxTexture3DDepth",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 26
  // cudaDevAttrMaxTexture2DLayeredWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_WIDTH",              {"hipDeviceAttributeMaxTexture2DLayeredWidth",               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 27
  // cudaDevAttrMaxTexture2DLayeredHeight
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_HEIGHT",             {"hipDeviceAttributeMaxTexture2DLayeredHeight",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 28
  // cudaDevAttrMaxTexture2DLayeredLayers
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_LAYERS",             {"hipDeviceAttributeMaxTexture2DLayeredLayers",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 29
  // cudaDevAttrMaxTexture2DLayeredWidth
  // NOTE: Deprecated, use CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_WIDTH
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_WIDTH",                {"hipDeviceAttributeMaxTexture2DLayeredWidth",               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED | CUDA_DEPRECATED}}, // 27
  // cudaDevAttrMaxTexture2DLayeredHeight
  // NOTE: Deprecated, use CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_HEIGHT
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_HEIGHT",               {"hipDeviceAttributeMaxTexture2DLayeredHeight",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED | CUDA_DEPRECATED}}, // 28
  // cudaDevAttrMaxTexture2DLayeredLayers
  // NOTE: Deprecated, use CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_LAYERS
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_NUMSLICES",            {"hipDeviceAttributeMaxTexture2DLayeredLayers",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED | CUDA_DEPRECATED}}, // 29
  // cudaDevAttrSurfaceAlignment
  {"CU_DEVICE_ATTRIBUTE_SURFACE_ALIGNMENT",                            {"hipDeviceAttributeSurfaceAlignment",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 30
  // cudaDevAttrConcurrentKernels
  {"CU_DEVICE_ATTRIBUTE_CONCURRENT_KERNELS",                           {"hipDeviceAttributeConcurrentKernels",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 31
  // cudaDevAttrEccEnabled
  {"CU_DEVICE_ATTRIBUTE_ECC_ENABLED",                                  {"hipDeviceAttributeEccEnabled",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 32
  // cudaDevAttrPciBusId
  {"CU_DEVICE_ATTRIBUTE_PCI_BUS_ID",                                   {"hipDeviceAttributePciBusId",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 33
  // cudaDevAttrPciDeviceId
  {"CU_DEVICE_ATTRIBUTE_PCI_DEVICE_ID",                                {"hipDeviceAttributePciDeviceId",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 34
  // cudaDevAttrTccDriver
  {"CU_DEVICE_ATTRIBUTE_TCC_DRIVER",                                   {"hipDeviceAttributeTccDriver",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 35
  // cudaDevAttrMemoryClockRate
  {"CU_DEVICE_ATTRIBUTE_MEMORY_CLOCK_RATE",                            {"hipDeviceAttributeMemoryClockRate",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 36
  // cudaDevAttrGlobalMemoryBusWidth
  {"CU_DEVICE_ATTRIBUTE_GLOBAL_MEMORY_BUS_WIDTH",                      {"hipDeviceAttributeMemoryBusWidth",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 37
  // cudaDevAttrL2CacheSize
  {"CU_DEVICE_ATTRIBUTE_L2_CACHE_SIZE",                                {"hipDeviceAttributeL2CacheSize",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 38
  // cudaDevAttrMaxThreadsPerMultiProcessor
  {"CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_MULTIPROCESSOR",               {"hipDeviceAttributeMaxThreadsPerMultiProcessor",            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 39
  // cudaDevAttrAsyncEngineCount
  {"CU_DEVICE_ATTRIBUTE_ASYNC_ENGINE_COUNT",                           {"hipDeviceAttributeAsyncEngineCount",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 40
  // cudaDevAttrUnifiedAddressing
  {"CU_DEVICE_ATTRIBUTE_UNIFIED_ADDRESSING",                           {"hipDeviceAttributeUnifiedAddressing",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 41
  // cudaDevAttrMaxTexture1DLayeredWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LAYERED_WIDTH",              {"hipDeviceAttributeMaxTexture1DLayeredWidth",               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 42
  // cudaDevAttrMaxTexture1DLayeredLayers
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LAYERED_LAYERS",             {"hipDeviceAttributeMaxTexture1DLayeredLayers",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 43
  // no analogue
  // NOTE: Deprecated, do not use
  {"CU_DEVICE_ATTRIBUTE_CAN_TEX2D_GATHER",                             {"hipDeviceAttributeCanTex2DGather",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED | CUDA_DEPRECATED}}, // 44
  // cudaDevAttrMaxTexture2DGatherWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_GATHER_WIDTH",               {"hipDeviceAttributeMaxTexture2DGatherWidth",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 45
  // cudaDevAttrMaxTexture2DGatherHeight
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_GATHER_HEIGHT",              {"hipDeviceAttributeMaxTexture2DGatherHeight",               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 46
  // cudaDevAttrMaxTexture3DWidthAlt
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_WIDTH_ALTERNATE",            {"hipDeviceAttributeMaxTexture3DWidthAlternate",             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 47
  // cudaDevAttrMaxTexture3DHeightAlt
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_HEIGHT_ALTERNATE",           {"hipDeviceAttributeMaxTexture3DHeightAlternate",            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 48
  // cudaDevAttrMaxTexture3DDepthAlt
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_DEPTH_ALTERNATE",            {"hipDeviceAttributeMaxTexture3DDepthAlternate",             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 49
  // cudaDevAttrPciDomainId
  {"CU_DEVICE_ATTRIBUTE_PCI_DOMAIN_ID",                                {"hipDeviceAttributePciDomainId",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 50
  // cudaDevAttrTexturePitchAlignment
  {"CU_DEVICE_ATTRIBUTE_TEXTURE_PITCH_ALIGNMENT",                      {"hipDeviceAttributeTexturePitchAlignment",                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 51
  // cudaDevAttrMaxTextureCubemapWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_WIDTH",                 {"hipDeviceAttributeMaxTextureCubemapWidth",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 52
  // cudaDevAttrMaxTextureCubemapLayeredWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_LAYERED_WIDTH",         {"hipDeviceAttributeMaxTextureCubemapLayeredWidth",          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 53
  // cudaDevAttrMaxTextureCubemapLayeredLayers
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_LAYERED_LAYERS",        {"hipDeviceAttributeMaxTextureCubemapLayeredLayers",         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 54
  // cudaDevAttrMaxSurface1DWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_WIDTH",                      {"hipDeviceAttributeMaxSurface1DWidth",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 55
  // cudaDevAttrMaxSurface2DWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_WIDTH",                      {"hipDeviceAttributeMaxSurface2DWidth",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 56
  // cudaDevAttrMaxSurface2DHeight
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_HEIGHT",                     {"hipDeviceAttributeMaxSurface2DHeight",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 57
  // cudaDevAttrMaxSurface3DWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_WIDTH",                      {"hipDeviceAttributeMaxSurface3DWidth",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 58
  // cudaDevAttrMaxSurface3DHeight
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_HEIGHT",                     {"hipDeviceAttributeMaxSurface3DHeight",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 59
  // cudaDevAttrMaxSurface3DDepth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_DEPTH",                      {"hipDeviceAttributeMaxSurface3DDepth",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 60
  // cudaDevAttrMaxSurface1DLayeredWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_LAYERED_WIDTH",              {"hipDeviceAttributeMaxSurface1DLayeredWidth",               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 61
  // cudaDevAttrMaxSurface1DLayeredLayers
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_LAYERED_LAYERS",             {"hipDeviceAttributeMaxSurface1DLayeredLayers",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 62
  // cudaDevAttrMaxSurface2DLayeredWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_WIDTH",              {"hipDeviceAttributeMaxSurface2DLayeredWidth",               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 63
  // cudaDevAttrMaxSurface2DLayeredHeight
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_HEIGHT",             {"hipDeviceAttributeMaxSurface2DLayeredHeight",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 64
  // cudaDevAttrMaxSurface2DLayeredLayers
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_LAYERS",             {"hipDeviceAttributeMaxSurface2DLayeredLayers",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 65
  // cudaDevAttrMaxSurfaceCubemapWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_WIDTH",                 {"hipDeviceAttributeMaxSurfaceCubemapWidth",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 66
  // cudaDevAttrMaxSurfaceCubemapLayeredWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_LAYERED_WIDTH",         {"hipDeviceAttributeMaxSurfaceCubemapLayeredWidth",          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 67
  // cudaDevAttrMaxSurfaceCubemapLayeredLayers
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_LAYERED_LAYERS",        {"hipDeviceAttributeMaxSurfaceCubemapLayeredLayers",         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 68
  // cudaDevAttrMaxTexture1DLinearWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LINEAR_WIDTH",               {"hipDeviceAttributeMaxTexture1DLinearWidth",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED | CUDA_DEPRECATED}}, // 69
  // cudaDevAttrMaxTexture2DLinearWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_WIDTH",               {"hipDeviceAttributeMaxTexture2DLinearWidth",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 70
  // cudaDevAttrMaxTexture2DLinearHeight
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_HEIGHT",              {"hipDeviceAttributeMaxTexture2DLinearHeight",               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 71
  // cudaDevAttrMaxTexture2DLinearPitch
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_PITCH",               {"hipDeviceAttributeMaxTexture2DLinearPitch",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 72
  // cudaDevAttrMaxTexture2DMipmappedWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_MIPMAPPED_WIDTH",            {"hipDeviceAttributeMaxTexture2DMipmappedWidth",             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 73
  // cudaDevAttrMaxTexture2DMipmappedHeight
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_MIPMAPPED_HEIGHT",           {"hipDeviceAttributeMaxTexture2DMipmappedHeight",            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 74
  // cudaDevAttrComputeCapabilityMajor
  {"CU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MAJOR",                     {"hipDeviceAttributeComputeCapabilityMajor",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 75
  // cudaDevAttrComputeCapabilityMinor
  {"CU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MINOR",                     {"hipDeviceAttributeComputeCapabilityMinor",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 76
  // cudaDevAttrMaxTexture1DMipmappedWidth
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_MIPMAPPED_WIDTH",            {"hipDeviceAttributeMaxTexture1DMipmappedWidth",             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 77
  // cudaDevAttrStreamPrioritiesSupported
  {"CU_DEVICE_ATTRIBUTE_STREAM_PRIORITIES_SUPPORTED",                  {"hipDeviceAttributeStreamPrioritiesSupported",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 78
  // cudaDevAttrGlobalL1CacheSupported
  {"CU_DEVICE_ATTRIBUTE_GLOBAL_L1_CACHE_SUPPORTED",                    {"hipDeviceAttributeGlobalL1CacheSupported",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 79
  // cudaDevAttrLocalL1CacheSupported
  {"CU_DEVICE_ATTRIBUTE_LOCAL_L1_CACHE_SUPPORTED",                     {"hipDeviceAttributeLocalL1CacheSupported",                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 80
  // cudaDevAttrMaxSharedMemoryPerMultiprocessor
  {"CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_MULTIPROCESSOR",         {"hipDeviceAttributeMaxSharedMemoryPerMultiprocessor",       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 81
  // cudaDevAttrMaxRegistersPerMultiprocessor
  {"CU_DEVICE_ATTRIBUTE_MAX_REGISTERS_PER_MULTIPROCESSOR",             {"hipDeviceAttributeMaxRegistersPerMultiprocessor",          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 82
  // cudaDevAttrManagedMemory
  {"CU_DEVICE_ATTRIBUTE_MANAGED_MEMORY",                               {"hipDeviceAttributeManagedMemory",                          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 83
  // cudaDevAttrIsMultiGpuBoard
  {"CU_DEVICE_ATTRIBUTE_MULTI_GPU_BOARD",                              {"hipDeviceAttributeIsMultiGpuBoard",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 84
  // cudaDevAttrMultiGpuBoardGroupID
  {"CU_DEVICE_ATTRIBUTE_MULTI_GPU_BOARD_GROUP_ID",                     {"hipDeviceAttributeMultiGpuBoardGroupId",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 85
  // cudaDevAttrHostNativeAtomicSupported
  {"CU_DEVICE_ATTRIBUTE_HOST_NATIVE_ATOMIC_SUPPORTED",                 {"hipDeviceAttributeHostNativeAtomicSupported",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 86
  // cudaDevAttrSingleToDoublePrecisionPerfRatio
  {"CU_DEVICE_ATTRIBUTE_SINGLE_TO_DOUBLE_PRECISION_PERF_RATIO",        {"hipDeviceAttributeSingleToDoublePrecisionPerfRatio",       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 87
  // cudaDevAttrPageableMemoryAccess
  {"CU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS",                       {"hipDeviceAttributePageableMemoryAccess",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 88
  // cudaDevAttrConcurrentManagedAccess
  {"CU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS",                    {"hipDeviceAttributeConcurrentManagedAccess",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 89
  // cudaDevAttrComputePreemptionSupported
  {"CU_DEVICE_ATTRIBUTE_COMPUTE_PREEMPTION_SUPPORTED",                 {"hipDeviceAttributeComputePreemptionSupported",             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 90
  // cudaDevAttrCanUseHostPointerForRegisteredMem
  {"CU_DEVICE_ATTRIBUTE_CAN_USE_HOST_POINTER_FOR_REGISTERED_MEM",      {"hipDeviceAttributeCanUseHostPointerForRegisteredMem",      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 91
  // no analogue: cudaDevAttrReserved92
  {"CU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_MEM_OPS",                       {"hipDeviceAttributeCanUseStreamMemOps",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 92
  // no analogue: cudaDevAttrReserved93
  {"CU_DEVICE_ATTRIBUTE_CAN_USE_64_BIT_STREAM_MEM_OPS",                {"hipDeviceAttributeCanUse64BitStreamMemOps",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 93
  // no analogue: cudaDevAttrReserved94
  {"CU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_WAIT_VALUE_NOR",                {"hipDeviceAttributeCanUseStreamWaitValueNor",               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 94
  // cudaDevAttrCooperativeLaunch
  {"CU_DEVICE_ATTRIBUTE_COOPERATIVE_LAUNCH",                           {"hipDeviceAttributeCooperativeLaunch",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 95
  // cudaDevAttrCooperativeMultiDeviceLaunch
  {"CU_DEVICE_ATTRIBUTE_COOPERATIVE_MULTI_DEVICE_LAUNCH",              {"hipDeviceAttributeCooperativeMultiDeviceLaunch",           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 96
  // cudaDevAttrMaxSharedMemoryPerBlockOptin
  {"CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK_OPTIN",            {"hipDeviceAttributeMaxSharedMemoryPerBlockOptin",           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 97
  // cudaDevAttrCanFlushRemoteWrites
  {"CU_DEVICE_ATTRIBUTE_CAN_FLUSH_REMOTE_WRITES",                      {"hipDeviceAttributeCanFlushRemoteWrites",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 98
  // cudaDevAttrHostRegisterSupported
  {"CU_DEVICE_ATTRIBUTE_HOST_REGISTER_SUPPORTED",                      {"hipDeviceAttributeHostRegisterSupported",                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 99
  // cudaDevAttrPageableMemoryAccessUsesHostPageTables
  {"CU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS_USES_HOST_PAGE_TABLES", {"hipDeviceAttributePageableMemoryAccessUsesHostPageTables", "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 100
  // cudaDevAttrDirectManagedMemAccessFromHost
  {"CU_DEVICE_ATTRIBUTE_DIRECT_MANAGED_MEM_ACCESS_FROM_HOST",          {"hipDeviceAttributeDirectManagedMemAccessFromHost",         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 101
  // no analogue
  {"CU_DEVICE_ATTRIBUTE_VIRTUAL_ADDRESS_MANAGEMENT_SUPPORTED",         {"hipDeviceAttributeVirtualMemoryManagementSupported",       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED | CUDA_DEPRECATED}}, // 102
  // no analogue
  {"CU_DEVICE_ATTRIBUTE_VIRTUAL_MEMORY_MANAGEMENT_SUPPORTED",          {"hipDeviceAttributeVirtualMemoryManagementSupported",       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 102
  // no analogue
  {"CU_DEVICE_ATTRIBUTE_HANDLE_TYPE_POSIX_FILE_DESCRIPTOR_SUPPORTED",  {"hipDeviceAttributeHandleTypePosixFileDescriptorSupported", "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 103
  // no analogue
  {"CU_DEVICE_ATTRIBUTE_HANDLE_TYPE_WIN32_HANDLE_SUPPORTED",           {"hipDeviceAttributeHandleTypeWin32HandleSupported",         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 104
  // no analogue
  {"CU_DEVICE_ATTRIBUTE_HANDLE_TYPE_WIN32_KMT_HANDLE_SUPPORTED",       {"hipDeviceAttributeHandleTypeWin32KmtHandleSupported",      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 105
  // cudaDevAttrMaxBlocksPerMultiprocessor
  {"CU_DEVICE_ATTRIBUTE_MAX_BLOCKS_PER_MULTIPROCESSOR",                {"hipDeviceAttributeMaxBlocksPerMultiprocessor",             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 106
  // no analogue
  {"CU_DEVICE_ATTRIBUTE_GENERIC_COMPRESSION_SUPPORTED",                {"hipDeviceAttributeGenericCompressionSupported",            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 107
  // cudaDevAttrMaxPersistingL2CacheSize
  {"CU_DEVICE_ATTRIBUTE_MAX_PERSISTING_L2_CACHE_SIZE",                 {"hipDeviceAttributeMaxPersistingL2CacheSize",               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 108
  // cudaDevAttrMaxAccessPolicyWindowSize
  {"CU_DEVICE_ATTRIBUTE_MAX_ACCESS_POLICY_WINDOW_SIZE",                {"hipDeviceAttributeMaxAccessPolicyWindowSize",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 109
  // no analogue
  {"CU_DEVICE_ATTRIBUTE_GPU_DIRECT_RDMA_WITH_CUDA_VMM_SUPPORTED",      {"hipDeviceAttributeGpuDirectRdmaWithCudaVmmSupported",      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 110
  // cudaDevAttrReservedSharedMemoryPerBlock
  {"CU_DEVICE_ATTRIBUTE_RESERVED_SHARED_MEMORY_PER_BLOCK",             {"hipDeviceAttributeReservedSharedMemoryPerBlock",           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 111
  // cudaDevAttrSparseCudaArraySupported
  {"CU_DEVICE_ATTRIBUTE_SPARSE_CUDA_ARRAY_SUPPORTED",                  {"hipDeviceAttributeSparseCudaArraySupported",               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 112
  // cudaDevAttrHostRegisterReadOnlySupported
  {"CU_DEVICE_ATTRIBUTE_READ_ONLY_HOST_REGISTER_SUPPORTED",            {"hipDeviceAttributeReadOnlyHostRestigerSupported",          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 113
  // cudaDevAttrMaxTimelineSemaphoreInteropSupported
  {"CU_DEVICE_ATTRIBUTE_TIMELINE_SEMAPHORE_INTEROP_SUPPORTED",         {"hipDeviceAttributeMaxTimelineSemaphoreInteropSupported",   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 114
  // cudaDevAttrMemoryPoolsSupported
  {"CU_DEVICE_ATTRIBUTE_MEMORY_POOLS_SUPPORTED",                       {"hipDeviceAttributeMemoryPoolsSupported",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 115
  // cudaDevAttrGPUDirectRDMASupported
  {"CU_DEVICE_ATTRIBUTE_GPU_DIRECT_RDMA_SUPPORTED",                    {"hipDeviceAttributeGpuDirectRdmaSupported",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 116
  // cudaDevAttrGPUDirectRDMAFlushWritesOptions
  {"CU_DEVICE_ATTRIBUTE_GPU_DIRECT_RDMA_FLUSH_WRITES_OPTIONS",         {"hipDeviceAttributeGpuDirectRdmaFlushWritesOptions",        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 117
  // cudaDevAttrGPUDirectRDMAWritesOrdering
  {"CU_DEVICE_ATTRIBUTE_GPU_DIRECT_RDMA_WRITES_ORDERING",              {"hipDeviceAttributeGpuDirectRdmaWritesOrdering",            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 118
  // cudaDevAttrMemoryPoolSupportedHandleTypes
  {"CU_DEVICE_ATTRIBUTE_MEMPOOL_SUPPORTED_HANDLE_TYPES",               {"hipDeviceAttributeMempoolSupportedHandleTypes",            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 119
  // no analogue
  {"CU_DEVICE_ATTRIBUTE_MAX",                                          {"hipDeviceAttributeMax",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 120

  // cudaDeviceP2PAttr
  {"CUdevice_P2PAttribute",                                            {"hipDeviceP2PAttr",                                         "", CONV_TYPE, API_DRIVER, 1}},
  {"CUdevice_P2PAttribute_enum",                                       {"hipDeviceP2PAttr",                                         "", CONV_TYPE, API_DRIVER, 1}},
  // CUdevice_P2PAttribute enum values
  // cudaDevP2PAttrPerformanceRank = 1
  {"CU_DEVICE_P2P_ATTRIBUTE_PERFORMANCE_RANK",                         {"hipDevP2PAttrPerformanceRank",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x01
  // cudaDevP2PAttrAccessSupported = 2
  {"CU_DEVICE_P2P_ATTRIBUTE_ACCESS_SUPPORTED",                         {"hipDevP2PAttrAccessSupported",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x02
  // cudaDevP2PAttrNativeAtomicSupported = 3
  {"CU_DEVICE_P2P_ATTRIBUTE_NATIVE_ATOMIC_SUPPORTED",                  {"hipDevP2PAttrNativeAtomicSupported",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x03
  // cudaDevP2PAttrCudaArrayAccessSupported = 4
  // NOTE" deprecated, use CU_DEVICE_P2P_ATTRIBUTE_CUDA_ARRAY_ACCESS_SUPPORTED instead
  {"CU_DEVICE_P2P_ATTRIBUTE_ACCESS_ACCESS_SUPPORTED",                  {"hipDevP2PAttrHipArrayAccessSupported",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, CUDA_DEPRECATED}}, // 0x04
  // NOTE" deprecated, use CU_DEVICE_P2P_ATTRIBUTE_CUDA_ARRAY_ACCESS_SUPPORTED instead
  {"CU_DEVICE_P2P_ATTRIBUTE_ARRAY_ACCESS_ACCESS_SUPPORTED",            {"hipDevP2PAttrHipArrayAccessSupported",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, CUDA_DEPRECATED | CUDA_REMOVED}}, // 0x04
  // cudaDevP2PAttrCudaArrayAccessSupported = 4
  {"CU_DEVICE_P2P_ATTRIBUTE_CUDA_ARRAY_ACCESS_SUPPORTED",              {"hipDevP2PAttrHipArrayAccessSupported",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x04

  // cudaEGL.h - presented only on Linux in nvidia-cuda-dev package
  // cudaEglColorFormat
  {"CUeglColorFormat",                                                 {"hipEglColorFormat",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUeglColorFormate_enum",                                           {"hipEglColorFormat",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUeglColorFormat enum values
  // cudaEglColorFormatYUV420Planar = 0
  {"CU_EGL_COLOR_FORMAT_YUV420_PLANAR",                                {"hipEglColorFormatYUV420Planar",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x00
  // cudaEglColorFormatYUV420SemiPlanar = 1
  {"CU_EGL_COLOR_FORMAT_YUV420_SEMIPLANAR",                            {"hipEglColorFormatYUV420SemiPlanar",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01
  // cudaEglColorFormatYUV422Planar = 2
  {"CU_EGL_COLOR_FORMAT_YUV422_PLANAR",                                {"hipEglColorFormatYUV422Planar",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x02
  // cudaEglColorFormatYUV422SemiPlanar = 3
  {"CU_EGL_COLOR_FORMAT_YUV422_SEMIPLANAR",                            {"hipEglColorFormatYUV422SemiPlanar",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x03
  // cudaEglColorFormatRGB = 4
  {"CU_EGL_COLOR_FORMAT_RGB",                                          {"hipEglColorFormatRGB",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x04
  // cudaEglColorFormatBGR = 5
  {"CU_EGL_COLOR_FORMAT_BGR",                                          {"hipEglColorFormatBGR",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x05
  // cudaEglColorFormatARGB = 6
  {"CU_EGL_COLOR_FORMAT_ARGB",                                         {"hipEglColorFormatARGB",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x06
  // cudaEglColorFormatRGBA = 7
  {"CU_EGL_COLOR_FORMAT_RGBA",                                         {"hipEglColorFormatRGBA",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x07
  // cudaEglColorFormatL = 8
  {"CU_EGL_COLOR_FORMAT_L",                                            {"hipEglColorFormatL",                                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x08
  // cudaEglColorFormatR = 9
  {"CU_EGL_COLOR_FORMAT_R",                                            {"hipEglColorFormatR",                                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x09
  // cudaEglColorFormatYUV444Planar = 10
  {"CU_EGL_COLOR_FORMAT_YUV444_PLANAR",                                {"hipEglColorFormatYUV444Planar",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0A
  // cudaEglColorFormatYUV444SemiPlanar = 11
  {"CU_EGL_COLOR_FORMAT_YUV444_SEMIPLANAR",                            {"hipEglColorFormatYUV444SemiPlanar",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0B
  // cudaEglColorFormatYUYV422 = 12
  {"CU_EGL_COLOR_FORMAT_YUYV_422",                                     {"hipEglColorFormatYUYV422",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0C
  // cudaEglColorFormatUYVY422 = 13
  {"CU_EGL_COLOR_FORMAT_UYVY_422",                                     {"hipEglColorFormatUYVY422",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0D
  // cudaEglColorFormatABGR = 14
  {"CU_EGL_COLOR_FORMAT_ABGR",                                         {"hipEglColorFormatABGR",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0E
  // cudaEglColorFormatBGRA = 15
  {"CU_EGL_COLOR_FORMAT_BGRA",                                         {"hipEglColorFormatBGRA",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0F
  // cudaEglColorFormatA = 16
  {"CU_EGL_COLOR_FORMAT_A",                                            {"hipEglColorFormatA",                                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x10
  // cudaEglColorFormatRG = 17
  {"CU_EGL_COLOR_FORMAT_RG",                                           {"hipEglColorFormatRG",                                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x11
  // cudaEglColorFormatAYUV = 18
  {"CU_EGL_COLOR_FORMAT_AYUV",                                         {"hipEglColorFormatAYUV",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x12
  // cudaEglColorFormatYVU444SemiPlanar = 19
  {"CU_EGL_COLOR_FORMAT_YVU444_SEMIPLANAR",                            {"hipEglColorFormatYVU444SemiPlanar",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x13
  // cudaEglColorFormatYVU422SemiPlanar = 20
  {"CU_EGL_COLOR_FORMAT_YVU422_SEMIPLANAR",                            {"hipEglColorFormatYVU422SemiPlanar",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x14
  // cudaEglColorFormatYVU420SemiPlanar = 21
  {"CU_EGL_COLOR_FORMAT_YVU420_SEMIPLANAR",                            {"hipEglColorFormatYVU420SemiPlanar",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x15
  // cudaEglColorFormatYVU420SemiPlanar = 22
  {"CU_EGL_COLOR_FORMAT_Y10V10U10_444_SEMIPLANAR",                     {"hipEglColorFormatY10V10U10_444SemiPlanar",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x16
  // cudaEglColorFormatY10V10U10_420SemiPlanar = 23
  {"CU_EGL_COLOR_FORMAT_Y10V10U10_420_SEMIPLANAR",                     {"hipEglColorFormatY10V10U10_420SemiPlanar",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x17
  // cudaEglColorFormatY12V12U12_444SemiPlanar = 24
  {"CU_EGL_COLOR_FORMAT_Y12V12U12_444_SEMIPLANAR",                     {"hipEglColorFormatY12V12U12_444SemiPlanar",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x18
  // cudaEglColorFormatY12V12U12_420SemiPlanar = 25
  {"CU_EGL_COLOR_FORMAT_Y12V12U12_420_SEMIPLANAR",                     {"hipEglColorFormatY12V12U12_420SemiPlanar",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x19
  // cudaEglColorFormatVYUY_ER = 26
  {"CU_EGL_COLOR_FORMAT_VYUY_ER",                                      {"hipEglColorFormatVYUY_ER",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1A
  // cudaEglColorFormatUYVY_ER = 27
  {"CU_EGL_COLOR_FORMAT_UYVY_ER",                                      {"hipEglColorFormatUYVY_ER",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1B
  // cudaEglColorFormatYUYV_ER = 28
  {"CU_EGL_COLOR_FORMAT_YUYV_ER",                                      {"hipEglColorFormatYUYV_ER",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1C
  // cudaEglColorFormatYVYU_ER = 29
  {"CU_EGL_COLOR_FORMAT_YVYU_ER",                                      {"hipEglColorFormatYVYU_ER",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1D
  // cudaEglColorFormatYUV_ER = 30
  {"CU_EGL_COLOR_FORMAT_YUV_ER",                                       {"hipEglColorFormatYUV_ER",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1E
  // cudaEglColorFormatYUVA_ER = 31
  {"CU_EGL_COLOR_FORMAT_YUVA_ER",                                      {"hipEglColorFormatYUVA_ER",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1F
  // cudaEglColorFormatAYUV_ER = 32
  {"CU_EGL_COLOR_FORMAT_AYUV_ER",                                      {"hipEglColorFormatAYUV_ER",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x20
  // cudaEglColorFormatYUV444Planar_ER = 33
  {"CU_EGL_COLOR_FORMAT_YUV444_PLANAR_ER",                             {"hipEglColorFormatYUV444Planar_ER",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x21
  // cudaEglColorFormatYUV422Planar_ER = 34
  {"CU_EGL_COLOR_FORMAT_YUV422_PLANAR_ER",                             {"hipEglColorFormatYUV422Planar_ER",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x22
  // cudaEglColorFormatYUV420Planar_ER = 35
  {"CU_EGL_COLOR_FORMAT_YUV420_PLANAR_ER",                             {"hipEglColorFormatYUV420Planar_ER",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x23
  // cudaEglColorFormatYUV444SemiPlanar_ER = 36
  {"CU_EGL_COLOR_FORMAT_YUV444_SEMIPLANAR_ER",                         {"hipEglColorFormatYUV444SemiPlanar_ER",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x24
  // cudaEglColorFormatYUV422SemiPlanar_ER = 37
  {"CU_EGL_COLOR_FORMAT_YUV422_SEMIPLANAR_ER",                         {"hipEglColorFormatYUV422SemiPlanar_ER",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x25
  // cudaEglColorFormatYUV420SemiPlanar_ER = 38
  {"CU_EGL_COLOR_FORMAT_YUV420_SEMIPLANAR_ER",                         {"hipEglColorFormatYUV420SemiPlanar_ER",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x26
  // cudaEglColorFormatYVU444Planar_ER = 39
  {"CU_EGL_COLOR_FORMAT_YVU444_PLANAR_ER",                             {"hipEglColorFormatYVU444Planar_ER",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x27
  // cudaEglColorFormatYVU422Planar_ER = 40
  {"CU_EGL_COLOR_FORMAT_YVU422_PLANAR_ER",                             {"hipEglColorFormatYVU422Planar_ER",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x28
  // cudaEglColorFormatYVU420Planar_ER = 41
  {"CU_EGL_COLOR_FORMAT_YVU420_PLANAR_ER",                             {"hipEglColorFormatYVU420Planar_ER",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x29
  // cudaEglColorFormatYVU444SemiPlanar_ER = 42
  {"CU_EGL_COLOR_FORMAT_YVU444_SEMIPLANAR_ER",                         {"hipEglColorFormatYVU444SemiPlanar_ER",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x2A
  // cudaEglColorFormatYVU422SemiPlanar_ER = 43
  {"CU_EGL_COLOR_FORMAT_YVU422_SEMIPLANAR_ER",                         {"hipEglColorFormatYVU422SemiPlanar_ER",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x2B
  // cudaEglColorFormatYVU420SemiPlanar_ER = 44
  {"CU_EGL_COLOR_FORMAT_YVU420_SEMIPLANAR_ER",                         {"hipEglColorFormatYVU420SemiPlanar_ER",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x2C
  // cudaEglColorFormatBayerRGGB = 45
  {"CU_EGL_COLOR_FORMAT_BAYER_RGGB",                                   {"hipEglColorFormatBayerRGGB",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x2D
  // cudaEglColorFormatBayerBGGR = 46
  {"CU_EGL_COLOR_FORMAT_BAYER_BGGR",                                   {"hipEglColorFormatBayerBGGR",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x2E
  // cudaEglColorFormatBayerGRBG = 47
  {"CU_EGL_COLOR_FORMAT_BAYER_GRBG",                                   {"hipEglColorFormatBayerGRBG",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x2F
  // cudaEglColorFormatBayerGBRG = 48
  {"CU_EGL_COLOR_FORMAT_BAYER_GBRG",                                   {"hipEglColorFormatBayerGBRG",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x30
  // cudaEglColorFormatBayer10RGGB = 49
  {"CU_EGL_COLOR_FORMAT_BAYER10_RGGB",                                 {"hipEglColorFormatBayer10RGGB",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x31
  // cudaEglColorFormatBayer10BGGR = 50
  {"CU_EGL_COLOR_FORMAT_BAYER10_BGGR",                                 {"hipEglColorFormatBayer10BGGR",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x32
  // cudaEglColorFormatBayer10GRBG = 51
  {"CU_EGL_COLOR_FORMAT_BAYER10_GRBG",                                 {"hipEglColorFormatBayer10GRBG",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x33
  // cudaEglColorFormatBayer10GBRG = 52
  {"CU_EGL_COLOR_FORMAT_BAYER10_GBRG",                                 {"hipEglColorFormatBayer10GBRG",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x34
  // cudaEglColorFormatBayer12RGGB = 53
  {"CU_EGL_COLOR_FORMAT_BAYER12_RGGB",                                 {"hipEglColorFormatBayer12RGGB",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x35
  // cudaEglColorFormatBayer12BGGR = 54
  {"CU_EGL_COLOR_FORMAT_BAYER12_BGGR",                                 {"hipEglColorFormatBayer12BGGR",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x36
  // cudaEglColorFormatBayer12GRBG = 55
  {"CU_EGL_COLOR_FORMAT_BAYER12_GRBG",                                 {"hipEglColorFormatBayer12GRBG",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x37
  // cudaEglColorFormatBayer12GBRG = 56
  {"CU_EGL_COLOR_FORMAT_BAYER12_GBRG",                                 {"hipEglColorFormatBayer12GBRG",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x38
  // cudaEglColorFormatBayer14RGGB = 57
  {"CU_EGL_COLOR_FORMAT_BAYER14_RGGB",                                 {"hipEglColorFormatBayer14RGGB",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x39
  // cudaEglColorFormatBayer14BGGR = 58
  {"CU_EGL_COLOR_FORMAT_BAYER14_BGGR",                                 {"hipEglColorFormatBayer14BGGR",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x3A
  // cudaEglColorFormatBayer14GRBG = 59
  {"CU_EGL_COLOR_FORMAT_BAYER14_GRBG",                                 {"hipEglColorFormatBayer14GRBG",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x3B
  // cudaEglColorFormatBayer14GBRG = 60
  {"CU_EGL_COLOR_FORMAT_BAYER14_GBRG",                                 {"hipEglColorFormatBayer14GBRG",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x3C
  // cudaEglColorFormatBayer20RGGB = 61
  {"CU_EGL_COLOR_FORMAT_BAYER20_RGGB",                                 {"hipEglColorFormatBayer20RGGB",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x3D
  // cudaEglColorFormatBayer20BGGR = 62
  {"CU_EGL_COLOR_FORMAT_BAYER20_BGGR",                                 {"hipEglColorFormatBayer20BGGR",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x3E
  // cudaEglColorFormatBayer20GRBG = 63
  {"CU_EGL_COLOR_FORMAT_BAYER20_GRBG",                                 {"hipEglColorFormatBayer20GRBG",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x3F
  // cudaEglColorFormatBayer20GBRG = 64
  {"CU_EGL_COLOR_FORMAT_BAYER20_GBRG",                                 {"hipEglColorFormatBayer20GBRG",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x40
  // cudaEglColorFormatYVU444Planar = 65
  {"CU_EGL_COLOR_FORMAT_YVU444_PLANAR",                                {"hipEglColorFormatYVU444Planar",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x41
  // cudaEglColorFormatYVU422Planar = 66
  {"CU_EGL_COLOR_FORMAT_YVU422_PLANAR",                                {"hipEglColorFormatYVU422Planar",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x42
  // cudaEglColorFormatYVU420Planar = 67
  {"CU_EGL_COLOR_FORMAT_YVU420_PLANAR",                                {"hipEglColorFormatYVU420Planar",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x43
  // cudaEglColorFormatBayerIspRGGB = 68
  {"CU_EGL_COLOR_FORMAT_BAYER_ISP_RGGB",                               {"hipEglColorFormatBayerIspRGGB",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x44
  // cudaEglColorFormatBayerIspBGGR = 69
  {"CU_EGL_COLOR_FORMAT_BAYER_ISP_BGGR",                               {"hipEglColorFormatBayerIspBGGR",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x45
  // cudaEglColorFormatBayerIspGRBG = 70
  {"CU_EGL_COLOR_FORMAT_BAYER_ISP_GRBG",                               {"hipEglColorFormatBayerIspGRBG",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x46
  // cudaEglColorFormatBayerIspGBRG = 71
  {"CU_EGL_COLOR_FORMAT_BAYER_ISP_GBRG",                               {"hipEglColorFormatBayerIspGBRG",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x47
  // no analogue
  {"CU_EGL_COLOR_FORMAT_MAX",                                          {"hipEglColorFormatMax",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x48

  // cudaEglFrameType
  {"CUeglFrameType",                                                   {"hipEglFrameType",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUeglFrameType_enum",                                              {"hipEglFrameType",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUeglFrameType enum values
  // cudaEglFrameTypeArray
  {"CU_EGL_FRAME_TYPE_ARRAY",                                          {"hipEglFrameTypeArray",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0
  // cudaEglFrameTypePitch
  {"CU_EGL_FRAME_TYPE_PITCH",                                          {"hipEglFrameTypePitch",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1

  // cudaEglResourceLocationFlags
  {"CUeglResourceLocationFlags",                                       {"hipEglResourceLocationFlags",                              "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUeglResourceLocationFlags_enum",                                  {"hipEglResourceLocationFlags",                              "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUeglResourceLocationFlags enum values
  // cudaEglResourceLocationSysmem
  {"CU_EGL_RESOURCE_LOCATION_SYSMEM",                                  {"hipEglResourceLocationSysmem",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x00
  // cudaEglResourceLocationVidmem
  {"CU_EGL_RESOURCE_LOCATION_VIDMEM",                                  {"hipEglResourceLocationVidmem",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01

  // no analogue
  {"CUevent_flags",                                                    {"hipEventFlags",                                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUevent_flags_enum",                                               {"hipEventFlags",                                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUevent_flags enum values
  // cudaEventDefault
  {"CU_EVENT_DEFAULT",                                                 {"hipEventDefault",                                          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x00
  // cudaEventBlockingSync
  {"CU_EVENT_BLOCKING_SYNC",                                           {"hipEventBlockingSync",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x01
  // cudaEventDisableTiming
  {"CU_EVENT_DISABLE_TIMING",                                          {"hipEventDisableTiming",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x02
  // cudaEventInterprocess
  {"CU_EVENT_INTERPROCESS",                                            {"hipEventInterprocess",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x04

  // cudaExternalMemoryHandleType
  {"CUexternalMemoryHandleType",                                       {"hipExternalMemoryHandleType",                              "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUexternalMemoryHandleType_enum",                                  {"hipExternalMemoryHandleType",                              "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUexternalMemoryHandleType enum values
  // cudaExternalMemoryHandleTypeOpaqueFd
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD",                         {"hipExternalMemoryHandleTypeOpaqueFD",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1
  // cudaExternalMemoryHandleTypeOpaqueWin32
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32",                      {"hipExternalMemoryHandleTypeOpaqueWin32",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 2
  // cudaExternalMemoryHandleTypeOpaqueWin32Kmt
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT",                  {"hipExternalMemoryHandleTypeOpaqueWin32KMT",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 3
  // cudaExternalMemoryHandleTypeD3D12Heap
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP",                        {"hipExternalMemoryHandleTypeD3D12Heap",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 4
  // cudaExternalMemoryHandleTypeD3D12Resource
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE",                    {"hipExternalMemoryHandleTypeD3D12Resource",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 5
  // cudaExternalMemoryHandleTypeD3D11Resource
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_RESOURCE",                    {"hipExternalMemoryHandleTypeD3D11Resource",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 6
  // cudaExternalMemoryHandleTypeD3D11ResourceKmt
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_RESOURCE_KMT",                {"hipExternalMemoryHandleTypeD3D11ResourceKmt",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 7
  // cudaExternalMemoryHandleTypeNvSciBuf
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_NVSCIBUF",                          {"hipExternalMemoryHandleTypeNvSciBuf",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 8

  // cudaExternalSemaphoreHandleType
  {"CUexternalSemaphoreHandleType",                                    {"hipExternalSemaphoreHandleType",                           "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUexternalSemaphoreHandleType_enum",                               {"hipExternalSemaphoreHandleType",                           "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUexternalSemaphoreHandleType enum values
  // cudaExternalSemaphoreHandleTypeOpaqueFd
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD",                      {"hipExternalSemaphoreHandleTypeOpaqueFD",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1
  // cudaExternalSemaphoreHandleTypeOpaqueWin32
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32",                   {"hipExternalSemaphoreHandleTypeOpaqueWin32",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 2
  // cudaExternalSemaphoreHandleTypeOpaqueWin32Kmt
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT",               {"hipExternalSemaphoreHandleTypeOpaqueWin32KMT",             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 3
  // cudaExternalSemaphoreHandleTypeD3D12Fence
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D12_FENCE",                    {"hipExternalSemaphoreHandleTypeD3D12Fence",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 4
  // cudaExternalSemaphoreHandleTypeD3D11Fence
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D11_FENCE",                    {"hipExternalSemaphoreHandleTypeD3D11Fence",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 5
  // cudaExternalSemaphoreHandleTypeNvSciSync
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_NVSCISYNC",                      {"hipExternalSemaphoreHandleTypeNvSciSync",                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 6
  // cudaExternalSemaphoreHandleTypeKeyedMutex
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D11_KEYED_MUTEX",              {"hipExternalSemaphoreHandleTypeKeyedMutex",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 7
  // cudaExternalSemaphoreHandleTypeKeyedMutexKmt
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D11_KEYED_MUTEX_KMT",          {"hipExternalSemaphoreHandleTypeKeyedMutexKmt",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 8
  // cudaExternalSemaphoreHandleTypeTimelineSemaphoreFd
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_FD",          {"hipExternalSemaphoreHandleTypeTimelineSemaphoreFd",        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 9
  // cudaExternalSemaphoreHandleTypeTimelineSemaphoreWin32
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_WIN32",       {"hipExternalSemaphoreHandleTypeTimelineSemaphoreWin32",     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 10

  // TODO: HIPfilter_mode_enum and all its values should be hipTextureFilterMode as long as they are equal.
  // cudaTextureFilterMode
  {"CUfilter_mode",                                                    {"HIPfilter_mode",                                           "", CONV_TYPE, API_DRIVER, 1}},
  {"CUfilter_mode_enum",                                               {"HIPfilter_mode_enum",                                      "", CONV_TYPE, API_DRIVER, 1}},
  // CUfilter_mode enum values
  // cudaFilterModePoint
  {"CU_TR_FILTER_MODE_POINT",                                          {"HIP_TR_FILTER_MODE_POINT",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0
  // cudaFilterModeLinear
  {"CU_TR_FILTER_MODE_LINEAR",                                         {"HIP_TR_FILTER_MODE_LINEAR",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 1

  // cudaFuncCache
  {"CUfunc_cache",                                                     {"hipFuncCache_t",                                           "", CONV_TYPE, API_DRIVER, 1}},
  {"CUfunc_cache_enum",                                                {"hipFuncCache_t",                                           "", CONV_TYPE, API_DRIVER, 1}},
  // CUfunc_cache enum values
  // cudaFilterModePoint = 0
  {"CU_FUNC_CACHE_PREFER_NONE",                                        {"hipFuncCachePreferNone",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x00
  // cudaFuncCachePreferShared = 1
  {"CU_FUNC_CACHE_PREFER_SHARED",                                      {"hipFuncCachePreferShared",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x01
  // cudaFuncCachePreferL1 = 2
  {"CU_FUNC_CACHE_PREFER_L1",                                          {"hipFuncCachePreferL1",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x02
  // cudaFuncCachePreferEqual = 3
  {"CU_FUNC_CACHE_PREFER_EQUAL",                                       {"hipFuncCachePreferEqual",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x03

  // cudaFuncAttribute
  {"CUfunction_attribute",                                             {"hipFunction_attribute",                                    "", CONV_TYPE, API_DRIVER, 1}},
  {"CUfunction_attribute_enum",                                        {"hipFunction_attribute",                                    "", CONV_TYPE, API_DRIVER, 1}},
  // CUfunction_attribute enum values
  // no analogue
  {"CU_FUNC_ATTRIBUTE_MAX_THREADS_PER_BLOCK",                          {"HIP_FUNC_ATTRIBUTE_MAX_THREADS_PER_BLOCK",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  0
  // no analogue
  {"CU_FUNC_ATTRIBUTE_SHARED_SIZE_BYTES",                              {"HIP_FUNC_ATTRIBUTE_SHARED_SIZE_BYTES",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  1
  // no analogue
  {"CU_FUNC_ATTRIBUTE_CONST_SIZE_BYTES",                               {"HIP_FUNC_ATTRIBUTE_CONST_SIZE_BYTES",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  2
  // no analogue
  {"CU_FUNC_ATTRIBUTE_LOCAL_SIZE_BYTES",                               {"HIP_FUNC_ATTRIBUTE_LOCAL_SIZE_BYTES",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  3
  // no analogue
  {"CU_FUNC_ATTRIBUTE_NUM_REGS",                                       {"HIP_FUNC_ATTRIBUTE_NUM_REGS",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  4
  // no analogue
  {"CU_FUNC_ATTRIBUTE_PTX_VERSION",                                    {"HIP_FUNC_ATTRIBUTE_PTX_VERSION",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  5
  // no analogue
  {"CU_FUNC_ATTRIBUTE_BINARY_VERSION",                                 {"HIP_FUNC_ATTRIBUTE_BINARY_VERSION",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  6
  // no analogue
  {"CU_FUNC_ATTRIBUTE_CACHE_MODE_CA",                                  {"HIP_FUNC_ATTRIBUTE_CACHE_MODE_CA",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  7
  // cudaFuncAttributeMaxDynamicSharedMemorySize
  {"CU_FUNC_ATTRIBUTE_MAX_DYNAMIC_SHARED_SIZE_BYTES",                  {"HIP_FUNC_ATTRIBUTE_MAX_DYNAMIC_SHARED_SIZE_BYTES",         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  8
  // cudaFuncAttributePreferredSharedMemoryCarveout
  {"CU_FUNC_ATTRIBUTE_PREFERRED_SHARED_MEMORY_CARVEOUT",               {"HIP_FUNC_ATTRIBUTE_PREFERRED_SHARED_MEMORY_CARVEOUT",      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, //  9
  // cudaFuncAttributeMax
  {"CU_FUNC_ATTRIBUTE_MAX",                                            {"HIP_FUNC_ATTRIBUTE_MAX",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 10

  // cudaGraphicsMapFlags
  {"CUgraphicsMapResourceFlags",                                       {"hipGraphicsMapFlags",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUgraphicsMapResourceFlags_enum",                                  {"hipGraphicsMapFlags",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUgraphicsMapResourceFlags enum values
  // cudaGraphicsMapFlagsNone = 0
  {"CU_GRAPHICS_MAP_RESOURCE_FLAGS_NONE",                              {"hipGraphicsMapFlagsNone",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x00
  // cudaGraphicsMapFlagsReadOnly = 1
  {"CU_GRAPHICS_MAP_RESOURCE_FLAGS_READ_ONLY",                         {"hipGraphicsMapFlagsReadOnly",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01
  // cudaGraphicsMapFlagsWriteDiscard = 2
  {"CU_GRAPHICS_MAP_RESOURCE_FLAGS_WRITE_DISCARD",                     {"hipGraphicsMapFlagsWriteDiscard",                          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x02

  // cudaGraphicsRegisterFlags
  {"CUgraphicsRegisterFlags",                                          {"hipGraphicsRegisterFlags",                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUgraphicsRegisterFlags_enum",                                     {"hipGraphicsRegisterFlags",                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaGraphicsRegisterFlags enum values
  // cudaGraphicsRegisterFlagsNone = 0
  {"CU_GRAPHICS_REGISTER_FLAGS_NONE",                                  {"hipGraphicsRegisterFlagsNone",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x00
  // cudaGraphicsRegisterFlagsReadOnly = 1
  {"CU_GRAPHICS_REGISTER_FLAGS_READ_ONLY",                             {"hipGraphicsRegisterFlagsReadOnly",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01
  // cudaGraphicsRegisterFlagsWriteDiscard = 2
  {"CU_GRAPHICS_REGISTER_FLAGS_WRITE_DISCARD",                         {"hipGraphicsRegisterFlagsWriteDiscard",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x02
  // cudaGraphicsRegisterFlagsSurfaceLoadStore = 4
  {"CU_GRAPHICS_REGISTER_FLAGS_SURFACE_LDST",                          {"hipGraphicsRegisterFlagsSurfaceLoadStore",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x04
  // cudaGraphicsRegisterFlagsTextureGather = 8
  {"CU_GRAPHICS_REGISTER_FLAGS_TEXTURE_GATHER",                        {"hipGraphicsRegisterFlagsTextureGather",                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x08

  // cudaGraphNodeType
  {"CUgraphNodeType",                                                  {"hipGraphNodeType",                                         "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUgraphNodeType_enum",                                             {"hipGraphNodeType",                                         "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaGraphNodeType enum values
  // cudaGraphNodeTypeKernel = 0x00
  {"CU_GRAPH_NODE_TYPE_KERNEL",                                        {"hipGraphNodeTypeKernel",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0
  // cudaGraphNodeTypeMemcpy = 0x01
  {"CU_GRAPH_NODE_TYPE_MEMCPY",                                        {"hipGraphNodeTypeMemcpy",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1
  // cudaGraphNodeTypeMemset = 0x02
  {"CU_GRAPH_NODE_TYPE_MEMSET",                                        {"hipGraphNodeTypeMemset",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 2
  // cudaGraphNodeTypeHost = 0x03
  {"CU_GRAPH_NODE_TYPE_HOST",                                          {"hipGraphNodeTypeHost",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 3
  // cudaGraphNodeTypeGraph = 0x04
  {"CU_GRAPH_NODE_TYPE_GRAPH",                                         {"hipGraphNodeTypeGraph",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 4
  // cudaGraphNodeTypeEmpty = 0x05
  {"CU_GRAPH_NODE_TYPE_EMPTY",                                         {"hipGraphNodeTypeEmpty",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 5
  // cudaGraphNodeTypeWaitEvent = 0x06
  {"CU_GRAPH_NODE_TYPE_WAIT_EVENT",                                    {"hipGraphNodeTypeWaitEvent",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 6
  // cudaGraphNodeTypeEventRecord = 0x07
  {"CU_GRAPH_NODE_TYPE_EVENT_RECORD",                                  {"hipGraphNodeTypeEventRecord",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 7
  //
  {"CU_GRAPH_NODE_TYPE_EXT_SEMAS_SIGNAL",                              {"hipGraphNodeTypeExtSemasSignal",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 8
  //
  {"CU_GRAPH_NODE_TYPE_EXT_SEMAS_WAIT",                                {"hipGraphNodeTypeExtSemasWait",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 9
  // cudaGraphNodeTypeCount
  {"CU_GRAPH_NODE_TYPE_COUNT",                                         {"hipGraphNodeTypeCount",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED | CUDA_REMOVED}}, // 8

  // cudaGraphExecUpdateResult
  {"CUgraphExecUpdateResult",                                          {"hipGraphExecUpdateResult",                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUgraphExecUpdateResult_enum",                                     {"hipGraphExecUpdateResult",                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUgraphExecUpdateResult enum values
  // cudaGraphExecUpdateSuccess
  {"CU_GRAPH_EXEC_UPDATE_SUCCESS",                                     {"hipGraphExecUpdateSuccess",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0
  // cudaGraphExecUpdateError
  {"CU_GRAPH_EXEC_UPDATE_ERROR",                                       {"hipGraphExecUpdateError",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1
  // cudaGraphExecUpdateErrorTopologyChanged
  {"CU_GRAPH_EXEC_UPDATE_ERROR_TOPOLOGY_CHANGED",                      {"hipGraphExecUpdateErrorTopologyChanged",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x2
  // cudaGraphExecUpdateErrorNodeTypeChanged
  {"CU_GRAPH_EXEC_UPDATE_ERROR_NODE_TYPE_CHANGED",                     {"hipGraphExecUpdateErrorNodeTypeChanged",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x3
  // cudaGraphExecUpdateErrorFunctionChanged
  {"CU_GRAPH_EXEC_UPDATE_ERROR_FUNCTION_CHANGED",                      {"hipGraphExecUpdateErrorFunctionChanged",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x4
  // cudaGraphExecUpdateErrorParametersChanged
  {"CU_GRAPH_EXEC_UPDATE_ERROR_PARAMETERS_CHANGED",                    {"hipGraphExecUpdateErrorParametersChanged",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x5
  // cudaGraphExecUpdateErrorNotSupported
  {"CU_GRAPH_EXEC_UPDATE_ERROR_NOT_SUPPORTED",                         {"hipGraphExecUpdateErrorNotSupported",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x6
  // cudaGraphExecUpdateErrorUnsupportedFunctionChange
  {"CU_GRAPH_EXEC_UPDATE_ERROR_UNSUPPORTED_FUNCTION_CHANGE",           {"hipGraphExecUpdateErrorUnsupportedFunctionChange",         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x7

  // no analogue
  {"CUipcMem_flags",                                                   {"hipIpcMemFlags",                                           "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUipcMem_flags_enum",                                              {"hipIpcMemFlags",                                           "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUipcMem_flags enum values
  // cudaIpcMemLazyEnablePeerAccess
  {"CU_IPC_MEM_LAZY_ENABLE_PEER_ACCESS",                               {"hipIpcMemLazyEnablePeerAccess",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x1

  // no analogue
  {"CUjit_cacheMode",                                                  {"hipJitCacheMode",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUjit_cacheMode_enum",                                             {"hipJitCacheMode",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUjit_cacheMode enum values
  // no analogue
  {"CU_JIT_CACHE_OPTION_NONE",                                         {"hipJitCacheModeOptionNone",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0
  // no analogue
  {"CU_JIT_CACHE_OPTION_CG",                                           {"hipJitCacheModeOptionCG",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // no analogue
  {"CU_JIT_CACHE_OPTION_CA",                                           {"hipJitCacheModeOptionCA",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // no analogue
  {"CUjit_fallback",                                                   {"hipJitFallback",                                           "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUjit_fallback_enum",                                              {"hipJitFallback",                                           "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUjit_fallback enum values
  {"CU_PREFER_PTX",                                                    {"hipJitFallbackPreferPtx",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0
  {"CU_PREFER_BINARY",                                                 {"hipJitFallbackPreferBinary",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // no analogue
  // NOTE: is not used by HIP, as it has no JIT, thus just a dummy enum
  {"CUjit_option",                                                     {"hipJitOption",                                             "", CONV_TYPE, API_DRIVER, 1}},
  {"CUjit_option_enum",                                                {"hipJitOption",                                             "", CONV_TYPE, API_DRIVER, 1}},
  // CUjit_option enum values
  {"CU_JIT_MAX_REGISTERS",                                             {"hipJitOptionMaxRegisters",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0
  {"CU_JIT_THREADS_PER_BLOCK",                                         {"hipJitOptionThreadsPerBlock",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_WALL_TIME",                                                 {"hipJitOptionWallTime",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_INFO_LOG_BUFFER",                                           {"hipJitOptionInfoLogBuffer",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_INFO_LOG_BUFFER_SIZE_BYTES",                                {"hipJitOptionInfoLogBufferSizeBytes",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_ERROR_LOG_BUFFER",                                          {"hipJitOptionErrorLogBuffer",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES",                               {"hipJitOptionErrorLogBufferSizeBytes",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_OPTIMIZATION_LEVEL",                                        {"hipJitOptionOptimizationLevel",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_TARGET_FROM_CUCONTEXT",                                     {"hipJitOptionTargetFromContext",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_TARGET",                                                    {"hipJitOptionTarget",                                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_FALLBACK_STRATEGY",                                         {"hipJitOptionFallbackStrategy",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_GENERATE_DEBUG_INFO",                                       {"hipJitOptionGenerateDebugInfo",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_LOG_VERBOSE",                                               {"hipJitOptionLogVerbose",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_GENERATE_LINE_INFO",                                        {"hipJitOptionGenerateLineInfo",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_CACHE_MODE",                                                {"hipJitOptionCacheMode",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_NEW_SM3X_OPT",                                              {"hipJitOptionSm3xOpt",                                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_FAST_COMPILE",                                              {"hipJitOptionFastCompile",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},
  {"CU_JIT_GLOBAL_SYMBOL_NAMES",                                       {"hipJitGlobalSymbolNames",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CU_JIT_GLOBAL_SYMBOL_ADDRESSES",                                   {"hipJitGlobalSymbolAddresses",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CU_JIT_GLOBAL_SYMBOL_COUNT",                                       {"hipJitGlobalSymbolCount",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CU_JIT_NUM_OPTIONS",                                               {"hipJitOptionNumOptions",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}},

  // no analogue
  {"CUjit_target",                                                     {"hipJitTarget",                                             "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUjit_target_enum",                                                {"hipJitTarget",                                             "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUjit_target enum values
  // NOTE: Deprecated since CUDA 9.0
  {"CU_TARGET_COMPUTE_10",                                             {"hipJitTargetCompute10",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED | CUDA_REMOVED}}, // 10
  // NOTE: Deprecated since CUDA 9.0
  {"CU_TARGET_COMPUTE_11",                                             {"hipJitTargetCompute11",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED | CUDA_REMOVED}}, // 11
  // NOTE: Deprecated since CUDA 9.0
  {"CU_TARGET_COMPUTE_12",                                             {"hipJitTargetCompute12",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED | CUDA_REMOVED}}, // 12
  // NOTE: Deprecated since CUDA 9.0
  {"CU_TARGET_COMPUTE_13",                                             {"hipJitTargetCompute13",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED | CUDA_REMOVED}}, // 13
  {"CU_TARGET_COMPUTE_20",                                             {"hipJitTargetCompute20",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 20
  {"CU_TARGET_COMPUTE_21",                                             {"hipJitTargetCompute21",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 21
  {"CU_TARGET_COMPUTE_30",                                             {"hipJitTargetCompute30",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 20
  {"CU_TARGET_COMPUTE_32",                                             {"hipJitTargetCompute32",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 32
  {"CU_TARGET_COMPUTE_35",                                             {"hipJitTargetCompute35",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 35
  {"CU_TARGET_COMPUTE_37",                                             {"hipJitTargetCompute37",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 37
  {"CU_TARGET_COMPUTE_50",                                             {"hipJitTargetCompute50",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 50
  {"CU_TARGET_COMPUTE_52",                                             {"hipJitTargetCompute52",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 52
  {"CU_TARGET_COMPUTE_53",                                             {"hipJitTargetCompute53",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 53
  {"CU_TARGET_COMPUTE_60",                                             {"hipJitTargetCompute60",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 60
  {"CU_TARGET_COMPUTE_61",                                             {"hipJitTargetCompute61",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 61
  {"CU_TARGET_COMPUTE_62",                                             {"hipJitTargetCompute62",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 62
  {"CU_TARGET_COMPUTE_70",                                             {"hipJitTargetCompute70",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 70
  {"CU_TARGET_COMPUTE_72",                                             {"hipJitTargetCompute72",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 70
  // NOTE: Deprecated since CUDA 10.0
  {"CU_TARGET_COMPUTE_73",                                             {"hipJitTargetCompute73",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED | CUDA_REMOVED}}, // 73
  {"CU_TARGET_COMPUTE_75",                                             {"hipJitTargetCompute75",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 75
  {"CU_TARGET_COMPUTE_80",                                             {"hipJitTargetCompute80",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 80
  {"CU_TARGET_COMPUTE_86",                                             {"hipJitTargetCompute86",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 86

  // no analogue
  {"CUjitInputType",                                                   {"hipJitInputType",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUjitInputType_enum",                                              {"hipJitInputType",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUjitInputType enum values
  {"CU_JIT_INPUT_CUBIN",                                               {"hipJitInputTypeBin",                                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0
  {"CU_JIT_INPUT_PTX",                                                 {"hipJitInputTypePtx",                                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CU_JIT_INPUT_FATBINARY",                                           {"hipJitInputTypeFatBinary",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CU_JIT_INPUT_OBJECT",                                              {"hipJitInputTypeObject",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CU_JIT_INPUT_LIBRARY",                                             {"hipJitInputTypeLibrary",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CU_JIT_NUM_INPUT_TYPES",                                           {"hipJitInputTypeNumInputTypes",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaLimit
  {"CUlimit",                                                          {"hipLimit_t",                                               "", CONV_TYPE, API_DRIVER, 1}},
  {"CUlimit_enum",                                                     {"hipLimit_t",                                               "", CONV_TYPE, API_DRIVER, 1}},
  // CUlimit enum values
  // cudaLimitStackSize
  {"CU_LIMIT_STACK_SIZE",                                              {"hipLimitStackSize",                                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x00
  // cudaLimitPrintfFifoSize
  {"CU_LIMIT_PRINTF_FIFO_SIZE",                                        {"hipLimitPrintfFifoSize",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01
  // cudaLimitMallocHeapSize
  {"CU_LIMIT_MALLOC_HEAP_SIZE",                                        {"hipLimitMallocHeapSize",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x02
  // cudaLimitDevRuntimeSyncDepth
  {"CU_LIMIT_DEV_RUNTIME_SYNC_DEPTH",                                  {"hipLimitDevRuntimeSyncDepth",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x03
  // cudaLimitDevRuntimePendingLaunchCount
  {"CU_LIMIT_DEV_RUNTIME_PENDING_LAUNCH_COUNT",                        {"hipLimitDevRuntimePendingLaunchCount",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x04
  // cudaLimitMaxL2FetchGranularity
  {"CU_LIMIT_MAX_L2_FETCH_GRANULARITY",                                {"hipLimitMaxL2FetchGranularity",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x05
  // cudaLimitPersistingL2CacheSize
  {"CU_LIMIT_PERSISTING_L2_CACHE_SIZE",                                {"hipLimitPersistingL2CacheSize",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x06
  // no analogue
  {"CU_LIMIT_MAX",                                                     {"hipLimitMax",                                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaMemoryAdvise
  {"CUmem_advise",                                                     {"hipMemoryAdvise",                                          "", CONV_TYPE, API_DRIVER, 1}},
  {"CUmem_advise_enum",                                                {"hipMemoryAdvise",                                          "", CONV_TYPE, API_DRIVER, 1}},
  // CUmem_advise enum values
  // cudaMemAdviseSetReadMostly
  {"CU_MEM_ADVISE_SET_READ_MOSTLY",                                    {"hipMemAdviseSetReadMostly",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 1
  // cudaMemAdviseUnsetReadMostly
  {"CU_MEM_ADVISE_UNSET_READ_MOSTLY",                                  {"hipMemAdviseUnsetReadMostly",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 2
  // cudaMemAdviseSetPreferredLocation
  {"CU_MEM_ADVISE_SET_PREFERRED_LOCATION",                             {"hipMemAdviseSetPreferredLocation",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 3
  // cudaMemAdviseUnsetPreferredLocation
  {"CU_MEM_ADVISE_UNSET_PREFERRED_LOCATION",                           {"hipMemAdviseUnsetPreferredLocation",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 4
  // cudaMemAdviseSetAccessedBy
  {"CU_MEM_ADVISE_SET_ACCESSED_BY",                                    {"hipMemAdviseSetAccessedBy",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 5
  // cudaMemAdviseUnsetAccessedBy
  {"CU_MEM_ADVISE_UNSET_ACCESSED_BY",                                  {"hipMemAdviseUnsetAccessedBy",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 6

  // no analogue
  {"CUmemAttach_flags",                                                {"hipMemAttachFlags_t",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemAttach_flags_enum",                                           {"hipMemAttachFlags_t",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUmemAttach_flags enum values
  // cudaMemAttachGlobal
  {"CU_MEM_ATTACH_GLOBAL",                                             {"hipMemAttachGlobal",                                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x1
  // cudaMemAttachHost
  {"CU_MEM_ATTACH_HOST",                                               {"hipMemAttachHost",                                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x2
  // cudaMemAttachSingle
  {"CU_MEM_ATTACH_SINGLE",                                             {"hipMemAttachSingle",                                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x4

  // no analogue
  // NOTE: cudaMemoryType is partial analogue
  {"CUmemorytype",                                                     {"hipMemoryType",                                            "", CONV_TYPE, API_DRIVER, 1}},
  {"CUmemorytype_enum",                                                {"hipMemoryType",                                            "", CONV_TYPE, API_DRIVER, 1}},
  // CUmemorytype enum values
  {"CU_MEMORYTYPE_HOST",                                               {"hipMemoryTypeHost",                                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x01
  {"CU_MEMORYTYPE_DEVICE",                                             {"hipMemoryTypeDevice",                                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x02
  {"CU_MEMORYTYPE_ARRAY",                                              {"hipMemoryTypeArray",                                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x03
  {"CU_MEMORYTYPE_UNIFIED",                                            {"hipMemoryTypeUnified",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x04

  // cudaMemRangeAttribute
  {"CUmem_range_attribute",                                            {"hipMemRangeAttribute",                                     "", CONV_TYPE, API_DRIVER, 1}},
  {"CUmem_range_attribute_enum",                                       {"hipMemRangeAttribute",                                     "", CONV_TYPE, API_DRIVER, 1}},
  // CUmem_range_attribute enum values
  // cudaMemRangeAttributeReadMostly
  {"CU_MEM_RANGE_ATTRIBUTE_READ_MOSTLY",                               {"hipMemRangeAttributeReadMostly",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 1
  // cudaMemRangeAttributePreferredLocation
  {"CU_MEM_RANGE_ATTRIBUTE_PREFERRED_LOCATION",                        {"hipMemRangeAttributePreferredLocation",                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 2
  // cudaMemRangeAttributeAccessedBy
  {"CU_MEM_RANGE_ATTRIBUTE_ACCESSED_BY",                               {"hipMemRangeAttributeAccessedBy",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 3
  // cudaMemRangeAttributeLastPrefetchLocation
  {"CU_MEM_RANGE_ATTRIBUTE_LAST_PREFETCH_LOCATION",                    {"hipMemRangeAttributeLastPrefetchLocation",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 4

  // no analogue
  {"CUoccupancy_flags",                                                {"hipOccupancyFlags",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUoccupancy_flags_enum",                                           {"hipOccupancyFlags",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUoccupancy_flags enum values
  // cudaOccupancyDefault
  {"CU_OCCUPANCY_DEFAULT",                                             {"hipOccupancyDefault",                                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x00
  // cudaOccupancyDisableCachingOverride
  {"CU_OCCUPANCY_DISABLE_CACHING_OVERRIDE",                            {"hipOccupancyDisableCachingOverride",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01

  // no analogue
  // TODO: Analogous enum is needed in HIP. Couldn't map enum to struct hipPointerAttribute_t.
  // TODO: Do the same for Pointer Attributes as for Device Attributes.
  {"CUpointer_attribute",                                              {"hipPointerAttribute",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUpointer_attribute_enum",                                         {"hipPointerAttribute",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUpointer_attribute enum values
  {"CU_POINTER_ATTRIBUTE_CONTEXT",                                     {"hipPointerAttributeContext",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1
  {"CU_POINTER_ATTRIBUTE_MEMORY_TYPE",                                 {"hipPointerAttributeMemoryType",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 2
  {"CU_POINTER_ATTRIBUTE_DEVICE_POINTER",                              {"hipPointerAttributeDevicePointer",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 3
  {"CU_POINTER_ATTRIBUTE_HOST_POINTER",                                {"hipPointerAttributeHostPointer",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 4
  {"CU_POINTER_ATTRIBUTE_P2P_TOKENS",                                  {"hipPointerAttributeP2pTokens",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 5
  {"CU_POINTER_ATTRIBUTE_SYNC_MEMOPS",                                 {"hipPointerAttributeSyncMemops",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 6
  {"CU_POINTER_ATTRIBUTE_BUFFER_ID",                                   {"hipPointerAttributeBufferId",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 7
  {"CU_POINTER_ATTRIBUTE_IS_MANAGED",                                  {"hipPointerAttributeIsManaged",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 8
  {"CU_POINTER_ATTRIBUTE_DEVICE_ORDINAL",                              {"hipPointerAttributeDeviceOrdinal",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 9
  {"CU_POINTER_ATTRIBUTE_IS_LEGACY_CUDA_IPC_CAPABLE",                  {"hipPointerAttributeIsLegacyCudaIpcCapable",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 10
  {"CU_POINTER_ATTRIBUTE_RANGE_START_ADDR",                            {"hipPointerAttributeRangeStartAddress",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 11
  {"CU_POINTER_ATTRIBUTE_RANGE_SIZE",                                  {"hipPointerAttributeRangeSize",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 12
  {"CU_POINTER_ATTRIBUTE_MAPPED",                                      {"hipPointerAttributeMapped",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 13
  {"CU_POINTER_ATTRIBUTE_ALLOWED_HANDLE_TYPES",                        {"hipPointerAttributeAllowedHandleTypes",                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 14
  {"CU_POINTER_ATTRIBUTE_IS_GPU_DIRECT_RDMA_CAPABLE",                  {"hipPointerAttributeIsGpuDirectRdmaCapable",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 15
  {"CU_POINTER_ATTRIBUTE_ACCESS_FLAGS",                                {"hipPointerAttributeAccessFlags",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 16
  {"CU_POINTER_ATTRIBUTE_MEMPOOL_HANDLE",                              {"hipPointerAttributeMempoolHandle",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 17

  // TODO: HIPresourcetype_enum and all its values should be hipResourceType as long as they are equal
  // cudaResourceType
  {"CUresourcetype",                                                   {"HIPresourcetype",                                          "", CONV_TYPE, API_DRIVER, 1}},
  {"CUresourcetype_enum",                                              {"HIPresourcetype_enum",                                     "", CONV_TYPE, API_DRIVER, 1}},
  // CUresourcetype enum values
  // cudaResourceTypeArray
  {"CU_RESOURCE_TYPE_ARRAY",                                           {"HIP_RESOURCE_TYPE_ARRAY",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x00
  // cudaResourceTypeMipmappedArray
  {"CU_RESOURCE_TYPE_MIPMAPPED_ARRAY",                                 {"HIP_RESOURCE_TYPE_MIPMAPPED_ARRAY",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x01
  // cudaResourceTypeLinear
  {"CU_RESOURCE_TYPE_LINEAR",                                          {"HIP_RESOURCE_TYPE_LINEAR",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x02
  // cudaResourceTypePitch2D
  {"CU_RESOURCE_TYPE_PITCH2D",                                         {"HIP_RESOURCE_TYPE_PITCH2D",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x03

  // TODO: HIPresourceViewFormat_enum and all its values should be hipResourceViewFormat as long as they are equal
  // cudaResourceViewFormat
  {"CUresourceViewFormat",                                             {"HIPresourceViewFormat",                                    "", CONV_TYPE, API_DRIVER, 1}},
  {"CUresourceViewFormat_enum",                                        {"HIPresourceViewFormat_enum",                               "", CONV_TYPE, API_DRIVER, 1}},
  // CUresourceViewFormat enum values
  // cudaResViewFormatNone
  {"CU_RES_VIEW_FORMAT_NONE",                                          {"HIP_RES_VIEW_FORMAT_NONE",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x00
  // cudaResViewFormatUnsignedChar1
  {"CU_RES_VIEW_FORMAT_UINT_1X8",                                      {"HIP_RES_VIEW_FORMAT_UINT_1X8",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x01
  // cudaResViewFormatUnsignedChar2
  {"CU_RES_VIEW_FORMAT_UINT_2X8",                                      {"HIP_RES_VIEW_FORMAT_UINT_2X8",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x02
  // cudaResViewFormatUnsignedChar4
  {"CU_RES_VIEW_FORMAT_UINT_4X8",                                      {"HIP_RES_VIEW_FORMAT_UINT_4X8",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x03
  // cudaResViewFormatSignedChar1
  {"CU_RES_VIEW_FORMAT_SINT_1X8",                                      {"HIP_RES_VIEW_FORMAT_SINT_1X8",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x04
  // cudaResViewFormatSignedChar2
  {"CU_RES_VIEW_FORMAT_SINT_2X8",                                      {"HIP_RES_VIEW_FORMAT_SINT_2X8",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x05
  // cudaResViewFormatSignedChar4
  {"CU_RES_VIEW_FORMAT_SINT_4X8",                                      {"HIP_RES_VIEW_FORMAT_SINT_4X8",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x06
  // cudaResViewFormatUnsignedShort1
  {"CU_RES_VIEW_FORMAT_UINT_1X16",                                     {"HIP_RES_VIEW_FORMAT_UINT_1X16",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x07
  // cudaResViewFormatUnsignedShort2
  {"CU_RES_VIEW_FORMAT_UINT_2X16",                                     {"HIP_RES_VIEW_FORMAT_UINT_2X16",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x08
  // cudaResViewFormatUnsignedShort4
  {"CU_RES_VIEW_FORMAT_UINT_4X16",                                     {"HIP_RES_VIEW_FORMAT_UINT_4X16",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x09
  // cudaResViewFormatSignedShort1
  {"CU_RES_VIEW_FORMAT_SINT_1X16",                                     {"HIP_RES_VIEW_FORMAT_SINT_1X16",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x0a
  // cudaResViewFormatSignedShort2
  {"CU_RES_VIEW_FORMAT_SINT_2X16",                                     {"HIP_RES_VIEW_FORMAT_SINT_2X16",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x0b
  // cudaResViewFormatSignedShort4
  {"CU_RES_VIEW_FORMAT_SINT_4X16",                                     {"HIP_RES_VIEW_FORMAT_SINT_4X16",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x0c
  // cudaResViewFormatUnsignedInt1
  {"CU_RES_VIEW_FORMAT_UINT_1X32",                                     {"HIP_RES_VIEW_FORMAT_UINT_1X32",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x0d
  // cudaResViewFormatUnsignedInt2
  {"CU_RES_VIEW_FORMAT_UINT_2X32",                                     {"HIP_RES_VIEW_FORMAT_UINT_2X32",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x0e
  // cudaResViewFormatUnsignedInt4
  {"CU_RES_VIEW_FORMAT_UINT_4X32",                                     {"HIP_RES_VIEW_FORMAT_UINT_4X32",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x0f
  // cudaResViewFormatSignedInt1
  {"CU_RES_VIEW_FORMAT_SINT_1X32",                                     {"HIP_RES_VIEW_FORMAT_SINT_1X32",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x10
  // cudaResViewFormatSignedInt2
  {"CU_RES_VIEW_FORMAT_SINT_2X32",                                     {"HIP_RES_VIEW_FORMAT_SINT_2X32",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x11
  // cudaResViewFormatSignedInt4
  {"CU_RES_VIEW_FORMAT_SINT_4X32",                                     {"HIP_RES_VIEW_FORMAT_SINT_4X32",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x12
  // cudaResViewFormatHalf1
  {"CU_RES_VIEW_FORMAT_FLOAT_1X16",                                    {"HIP_RES_VIEW_FORMAT_FLOAT_1X16",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x13
  // cudaResViewFormatHalf2
  {"CU_RES_VIEW_FORMAT_FLOAT_2X16",                                    {"HIP_RES_VIEW_FORMAT_FLOAT_2X16",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x14
  // cudaResViewFormatHalf4
  {"CU_RES_VIEW_FORMAT_FLOAT_4X16",                                    {"HIP_RES_VIEW_FORMAT_FLOAT_4X16",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x15
  // cudaResViewFormatFloat1
  {"CU_RES_VIEW_FORMAT_FLOAT_1X32",                                    {"HIP_RES_VIEW_FORMAT_FLOAT_1X32",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x16
  // cudaResViewFormatFloat2
  {"CU_RES_VIEW_FORMAT_FLOAT_2X32",                                    {"HIP_RES_VIEW_FORMAT_FLOAT_2X32",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x17
  // cudaResViewFormatFloat4
  {"CU_RES_VIEW_FORMAT_FLOAT_4X32",                                    {"HIP_RES_VIEW_FORMAT_FLOAT_4X32",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x18
  // cudaResViewFormatUnsignedBlockCompressed1
  {"CU_RES_VIEW_FORMAT_UNSIGNED_BC1",                                  {"HIP_RES_VIEW_FORMAT_UNSIGNED_BC1",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x19
  // cudaResViewFormatUnsignedBlockCompressed2
  {"CU_RES_VIEW_FORMAT_UNSIGNED_BC2",                                  {"HIP_RES_VIEW_FORMAT_UNSIGNED_BC2",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x1a
  // cudaResViewFormatUnsignedBlockCompressed3
  {"CU_RES_VIEW_FORMAT_UNSIGNED_BC3",                                  {"HIP_RES_VIEW_FORMAT_UNSIGNED_BC3",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x1b
  // cudaResViewFormatUnsignedBlockCompressed4
  {"CU_RES_VIEW_FORMAT_UNSIGNED_BC4",                                  {"HIP_RES_VIEW_FORMAT_UNSIGNED_BC4",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x1c
  // cudaResViewFormatSignedBlockCompressed4
  {"CU_RES_VIEW_FORMAT_SIGNED_BC4",                                    {"HIP_RES_VIEW_FORMAT_SIGNED_BC4",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x1d
  // cudaResViewFormatUnsignedBlockCompressed5
  {"CU_RES_VIEW_FORMAT_UNSIGNED_BC5",                                  {"HIP_RES_VIEW_FORMAT_UNSIGNED_BC5",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x1e
  // cudaResViewFormatSignedBlockCompressed5
  {"CU_RES_VIEW_FORMAT_SIGNED_BC5",                                    {"HIP_RES_VIEW_FORMAT_SIGNED_BC5",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x1f
  // cudaResViewFormatUnsignedBlockCompressed6H
  {"CU_RES_VIEW_FORMAT_UNSIGNED_BC6H",                                 {"HIP_RES_VIEW_FORMAT_UNSIGNED_BC6H",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x20
  // cudaResViewFormatSignedBlockCompressed6H
  {"CU_RES_VIEW_FORMAT_SIGNED_BC6H",                                   {"HIP_RES_VIEW_FORMAT_SIGNED_BC6H",                          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x21
  // cudaResViewFormatUnsignedBlockCompressed7
  {"CU_RES_VIEW_FORMAT_UNSIGNED_BC7",                                  {"HIP_RES_VIEW_FORMAT_UNSIGNED_BC7",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x22

  // cudaError
  {"CUresult",                                                         {"hipError_t",                                               "", CONV_TYPE, API_DRIVER, 1}},
  {"cudaError_enum",                                                   {"hipError_t",                                               "", CONV_TYPE, API_DRIVER, 1}},
  // CUresult enum values
  // cudaSuccess
  {"CUDA_SUCCESS",                                                     {"hipSuccess",                                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0
  // cudaErrorInvalidValue
  {"CUDA_ERROR_INVALID_VALUE",                                         {"hipErrorInvalidValue",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 1
  // cudaErrorMemoryAllocation
  {"CUDA_ERROR_OUT_OF_MEMORY",                                         {"hipErrorOutOfMemory",                                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 2
  // cudaErrorInitializationError
  {"CUDA_ERROR_NOT_INITIALIZED",                                       {"hipErrorNotInitialized",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 3
  // cudaErrorCudartUnloading
  {"CUDA_ERROR_DEINITIALIZED",                                         {"hipErrorDeinitialized",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 4
  // cudaErrorProfilerDisabled
  {"CUDA_ERROR_PROFILER_DISABLED",                                     {"hipErrorProfilerDisabled",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 5
  // cudaErrorProfilerNotInitialized
  // NOTE: Deprecated since CUDA 5.0
  {"CUDA_ERROR_PROFILER_NOT_INITIALIZED",                              {"hipErrorProfilerNotInitialized",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, CUDA_DEPRECATED}}, // 6
  // NOTE: Deprecated since CUDA 5.0
  // cudaErrorProfilerAlreadyStarted
  {"CUDA_ERROR_PROFILER_ALREADY_STARTED",                              {"hipErrorProfilerAlreadyStarted",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, CUDA_DEPRECATED}}, // 7
  // cudaErrorProfilerAlreadyStopped
  // NOTE: Deprecated since CUDA 5.0
  {"CUDA_ERROR_PROFILER_ALREADY_STOPPED",                              {"hipErrorProfilerAlreadyStopped",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, CUDA_DEPRECATED}}, // 8
  // cudaErrorStubLibrary
  {"CUDA_ERROR_STUB_LIBRARY",                                          {"hipErrorStubLibrary",                                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 34
  // cudaErrorNoDevice
  {"CUDA_ERROR_NO_DEVICE",                                             {"hipErrorNoDevice",                                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 100
  // cudaErrorInvalidDevice
  {"CUDA_ERROR_INVALID_DEVICE",                                        {"hipErrorInvalidDevice",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 101
  // cudaErrorDeviceNotLicensed
  {"CUDA_ERROR_DEVICE_NOT_LICENSED",                                   {"hipErrorDeviceNotLicensed",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 102
  // cudaErrorInvalidKernelImage
  {"CUDA_ERROR_INVALID_IMAGE",                                         {"hipErrorInvalidImage",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 200
  // cudaErrorDeviceUninitilialized
  {"CUDA_ERROR_INVALID_CONTEXT",                                       {"hipErrorInvalidContext",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 201
  // no analogue
  // NOTE: Deprecated since CUDA 3.2
  {"CUDA_ERROR_CONTEXT_ALREADY_CURRENT",                               {"hipErrorContextAlreadyCurrent",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, CUDA_DEPRECATED}}, // 202
  // cudaErrorMapBufferObjectFailed
  {"CUDA_ERROR_MAP_FAILED",                                            {"hipErrorMapFailed",                                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 205
  // cudaErrorUnmapBufferObjectFailed
  {"CUDA_ERROR_UNMAP_FAILED",                                          {"hipErrorUnmapFailed",                                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 206
  // cudaErrorArrayIsMapped
  {"CUDA_ERROR_ARRAY_IS_MAPPED",                                       {"hipErrorArrayIsMapped",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 207
  // cudaErrorAlreadyMapped
  {"CUDA_ERROR_ALREADY_MAPPED",                                        {"hipErrorAlreadyMapped",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 208
  // cudaErrorNoKernelImageForDevice
  {"CUDA_ERROR_NO_BINARY_FOR_GPU",                                     {"hipErrorNoBinaryForGpu",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 209
  // cudaErrorAlreadyAcquired
  {"CUDA_ERROR_ALREADY_ACQUIRED",                                      {"hipErrorAlreadyAcquired",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 210
  // cudaErrorNotMapped
  {"CUDA_ERROR_NOT_MAPPED",                                            {"hipErrorNotMapped",                                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 211
  // cudaErrorNotMappedAsArray
  {"CUDA_ERROR_NOT_MAPPED_AS_ARRAY",                                   {"hipErrorNotMappedAsArray",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 212
  // cudaErrorNotMappedAsPointer
  {"CUDA_ERROR_NOT_MAPPED_AS_POINTER",                                 {"hipErrorNotMappedAsPointer",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 213
  // cudaErrorECCUncorrectable
  {"CUDA_ERROR_ECC_UNCORRECTABLE",                                     {"hipErrorECCNotCorrectable",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 214
  // cudaErrorUnsupportedLimit
  {"CUDA_ERROR_UNSUPPORTED_LIMIT",                                     {"hipErrorUnsupportedLimit",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 215
  // cudaErrorDeviceAlreadyInUse
  {"CUDA_ERROR_CONTEXT_ALREADY_IN_USE",                                {"hipErrorContextAlreadyInUse",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 216
  // cudaErrorPeerAccessUnsupported
  {"CUDA_ERROR_PEER_ACCESS_UNSUPPORTED",                               {"hipErrorPeerAccessUnsupported",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 217
  // cudaErrorInvalidPtx
  {"CUDA_ERROR_INVALID_PTX",                                           {"hipErrorInvalidKernelFile",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 218
  // cudaErrorInvalidGraphicsContext
  {"CUDA_ERROR_INVALID_GRAPHICS_CONTEXT",                              {"hipErrorInvalidGraphicsContext",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 219
  // cudaErrorNvlinkUncorrectable
  {"CUDA_ERROR_NVLINK_UNCORRECTABLE",                                  {"hipErrorNvlinkUncorrectable",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 220
  // cudaErrorJitCompilerNotFound
  {"CUDA_ERROR_JIT_COMPILER_NOT_FOUND",                                {"hipErrorJitCompilerNotFound",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 221
  // cudaErrorUnsupportedPtxVersion
  {"CUDA_ERROR_UNSUPPORTED_PTX_VERSION",                               {"hipErrorUnsupportedPtxVersion",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 222
  // cudaErrorJitCompilationDisabled
  {"CUDA_ERROR_JIT_COMPILATION_DISABLED",                              {"hipErrorJitCompilationDisabled",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 223
  // cudaErrorInvalidSource
  {"CUDA_ERROR_INVALID_SOURCE",                                        {"hipErrorInvalidSource",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 300
  // cudaErrorFileNotFound
  {"CUDA_ERROR_FILE_NOT_FOUND",                                        {"hipErrorFileNotFound",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 301
  // cudaErrorSharedObjectSymbolNotFound
  {"CUDA_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND",                        {"hipErrorSharedObjectSymbolNotFound",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 302
  // cudaErrorSharedObjectInitFailed
  {"CUDA_ERROR_SHARED_OBJECT_INIT_FAILED",                             {"hipErrorSharedObjectInitFailed",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 303
  // cudaErrorOperatingSystem
  {"CUDA_ERROR_OPERATING_SYSTEM",                                      {"hipErrorOperatingSystem",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 304
  // cudaErrorInvalidResourceHandle
  {"CUDA_ERROR_INVALID_HANDLE",                                        {"hipErrorInvalidHandle",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 400
  // cudaErrorIllegalState
  {"CUDA_ERROR_ILLEGAL_STATE",                                         {"hipErrorIllegalState",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 401
  // cudaErrorSymbolNotFound
  {"CUDA_ERROR_NOT_FOUND",                                             {"hipErrorNotFound",                                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 500
  // cudaErrorNotReady
  {"CUDA_ERROR_NOT_READY",                                             {"hipErrorNotReady",                                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 600
  // cudaErrorIllegalAddress
  {"CUDA_ERROR_ILLEGAL_ADDRESS",                                       {"hipErrorIllegalAddress",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 700
  // cudaErrorLaunchOutOfResources
  {"CUDA_ERROR_LAUNCH_OUT_OF_RESOURCES",                               {"hipErrorLaunchOutOfResources",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 701
  // cudaErrorLaunchTimeout
  {"CUDA_ERROR_LAUNCH_TIMEOUT",                                        {"hipErrorLaunchTimeOut",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 702
  // cudaErrorLaunchIncompatibleTexturing
  {"CUDA_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING",                         {"hipErrorLaunchIncompatibleTexturing",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 703
  // cudaErrorPeerAccessAlreadyEnabled
  {"CUDA_ERROR_PEER_ACCESS_ALREADY_ENABLED",                           {"hipErrorPeerAccessAlreadyEnabled",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 704
  // cudaErrorPeerAccessNotEnabled
  {"CUDA_ERROR_PEER_ACCESS_NOT_ENABLED",                               {"hipErrorPeerAccessNotEnabled",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 705
  // cudaErrorSetOnActiveProcess
  {"CUDA_ERROR_PRIMARY_CONTEXT_ACTIVE",                                {"hipErrorSetOnActiveProcess",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 708
  // cudaErrorContextIsDestroyed
  {"CUDA_ERROR_CONTEXT_IS_DESTROYED",                                  {"hipErrorContextIsDestroyed",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 709
  // cudaErrorAssert
  {"CUDA_ERROR_ASSERT",                                                {"hipErrorAssert",                                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 710
  // cudaErrorTooManyPeers
  {"CUDA_ERROR_TOO_MANY_PEERS",                                        {"hipErrorTooManyPeers",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 711
  // cudaErrorHostMemoryAlreadyRegistered
  {"CUDA_ERROR_HOST_MEMORY_ALREADY_REGISTERED",                        {"hipErrorHostMemoryAlreadyRegistered",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 712
  // cudaErrorHostMemoryNotRegistered
  {"CUDA_ERROR_HOST_MEMORY_NOT_REGISTERED",                            {"hipErrorHostMemoryNotRegistered",                          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 713
  // cudaErrorHardwareStackError
  {"CUDA_ERROR_HARDWARE_STACK_ERROR",                                  {"hipErrorHardwareStackError",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 714
  // cudaErrorIllegalInstruction
  {"CUDA_ERROR_ILLEGAL_INSTRUCTION",                                   {"hipErrorIllegalInstruction",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 715
  // cudaErrorMisalignedAddress
  {"CUDA_ERROR_MISALIGNED_ADDRESS",                                    {"hipErrorMisalignedAddress",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 716
  // cudaErrorInvalidAddressSpace
  {"CUDA_ERROR_INVALID_ADDRESS_SPACE",                                 {"hipErrorInvalidAddressSpace",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 717
  // cudaErrorInvalidPc
  {"CUDA_ERROR_INVALID_PC",                                            {"hipErrorInvalidPc",                                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 718
  // cudaErrorLaunchFailure
  {"CUDA_ERROR_LAUNCH_FAILED",                                         {"hipErrorLaunchFailure",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 719
  // cudaErrorCooperativeLaunchTooLarge
  {"CUDA_ERROR_COOPERATIVE_LAUNCH_TOO_LARGE",                          {"hipErrorCooperativeLaunchTooLarge",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 720
  // cudaErrorNotPermitted
  {"CUDA_ERROR_NOT_PERMITTED",                                         {"hipErrorNotPermitted",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 800
  // cudaErrorNotSupported
  {"CUDA_ERROR_NOT_SUPPORTED",                                         {"hipErrorNotSupported",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 801
  // cudaErrorSystemNotReady
  {"CUDA_ERROR_SYSTEM_NOT_READY",                                      {"hipErrorSystemNotReady",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 802
  // cudaErrorSystemDriverMismatch
  {"CUDA_ERROR_SYSTEM_DRIVER_MISMATCH",                                {"hipErrorSystemDriverMismatch",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 803
  // cudaErrorCompatNotSupportedOnDevice
  {"CUDA_ERROR_COMPAT_NOT_SUPPORTED_ON_DEVICE",                        {"hipErrorCompatNotSupportedOnDevice",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 804
  // cudaErrorStreamCaptureUnsupported
  {"CUDA_ERROR_STREAM_CAPTURE_UNSUPPORTED",                            {"hipErrorStreamCaptureUnsupported",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 900
  // cudaErrorStreamCaptureInvalidated
  {"CUDA_ERROR_STREAM_CAPTURE_INVALIDATED",                            {"hipErrorStreamCaptureInvalidated",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 901
  // cudaErrorStreamCaptureMerge
  {"CUDA_ERROR_STREAM_CAPTURE_MERGE",                                  {"hipErrorStreamCaptureMerge",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 902
  // cudaErrorStreamCaptureUnmatched
  {"CUDA_ERROR_STREAM_CAPTURE_UNMATCHED",                              {"hipErrorStreamCaptureUnmatched",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 903
  // cudaErrorStreamCaptureUnjoined
  {"CUDA_ERROR_STREAM_CAPTURE_UNJOINED",                               {"hipErrorStreamCaptureUnjoined",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 904
  // cudaErrorStreamCaptureIsolation
  {"CUDA_ERROR_STREAM_CAPTURE_ISOLATION",                              {"hipErrorStreamCaptureIsolation",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 905
  // cudaErrorStreamCaptureImplicit
  {"CUDA_ERROR_STREAM_CAPTURE_IMPLICIT",                               {"hipErrorStreamCaptureImplicit",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 906
  // cudaErrorCapturedEvent
  {"CUDA_ERROR_CAPTURED_EVENT",                                        {"hipErrorCapturedEvent",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 907
  // cudaErrorStreamCaptureWrongThread
  {"CUDA_ERROR_STREAM_CAPTURE_WRONG_THREAD",                           {"hipErrorStreamCaptureWrongThread",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 908
  // cudaErrorTimeout
  {"CUDA_ERROR_TIMEOUT",                                               {"hipErrorTimeout",                                          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 909
  // cudaErrorGraphExecUpdateFailure
  {"CUDA_ERROR_GRAPH_EXEC_UPDATE_FAILURE",                             {"hipErrorGraphExecUpdateFailure",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 910
  // cudaErrorUnknown
  {"CUDA_ERROR_UNKNOWN",                                               {"hipErrorUnknown",                                          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 999

  // cudaSharedMemConfig
  {"CUsharedconfig",                                                   {"hipSharedMemConfig",                                       "", CONV_TYPE, API_DRIVER, 1}},
  {"CUsharedconfig_enum",                                              {"hipSharedMemConfig",                                       "", CONV_TYPE, API_DRIVER, 1}},
  // CUsharedconfig enum values
  // cudaSharedMemBankSizeDefault = 0
  {"CU_SHARED_MEM_CONFIG_DEFAULT_BANK_SIZE",                           {"hipSharedMemBankSizeDefault",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x00
  // cudaSharedMemBankSizeFourByte = 1
  {"CU_SHARED_MEM_CONFIG_FOUR_BYTE_BANK_SIZE",                         {"hipSharedMemBankSizeFourByte",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x01
  // cudaSharedMemBankSizeEightByte = 2
  {"CU_SHARED_MEM_CONFIG_EIGHT_BYTE_BANK_SIZE",                        {"hipSharedMemBankSizeEightByte",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x02

  // cudaSharedCarveout
  {"CUshared_carveout",                                                {"hipSharedCarveout",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUshared_carveout_enum",                                           {"hipSharedCarveout",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUshared_carveout enum values
  // cudaSharedmemCarveoutDefault
  {"CU_SHAREDMEM_CARVEOUT_DEFAULT",                                    {"hipSharedmemCarveoutDefault",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // -1
  // cudaSharedmemCarveoutMaxShared
  {"CU_SHAREDMEM_CARVEOUT_MAX_SHARED",                                 {"hipSharedmemCarveoutMaxShared",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 100
  // cudaSharedmemCarveoutMaxShared
  {"CU_SHAREDMEM_CARVEOUT_MAX_L1",                                     {"hipSharedmemCarveoutMaxL1",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0

  // no analogue
  {"CUstream_flags",                                                   {"hipStreamFlags",                                           "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUstream_flags_enum",                                              {"hipStreamFlags",                                           "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUstream_flags enum values
  // cudaStreamDefault = 0x00
  {"CU_STREAM_DEFAULT",                                                {"hipStreamDefault",                                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x0
  // cudaStreamNonBlocking = 0x01
  {"CU_STREAM_NON_BLOCKING",                                           {"hipStreamNonBlocking",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x1

  // no analogue
  {"CUstreamBatchMemOpType",                                           {"hipStreamBatchMemOpType",                                  "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUstreamBatchMemOpType_enum",                                      {"hipStreamBatchMemOpType",                                  "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUstreamBatchMemOpType enum values
  {"CU_STREAM_MEM_OP_WAIT_VALUE_32",                                   {"hipStreamBatchMemOpWaitValue32",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1
  {"CU_STREAM_MEM_OP_WRITE_VALUE_32",                                  {"hipStreamBatchMemOpWriteValue32",                          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 2
  {"CU_STREAM_MEM_OP_FLUSH_REMOTE_WRITES",                             {"hipStreamBatchMemOpFlushRemoteWrites",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 3
  {"CU_STREAM_MEM_OP_WAIT_VALUE_64",                                   {"hipStreamBatchMemOpWaitValue64",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 4
  {"CU_STREAM_MEM_OP_WRITE_VALUE_64",                                  {"hipStreamBatchMemOpWriteValue64",                          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 5

  // cudaStreamCaptureStatus
  {"CUstreamCaptureStatus",                                            {"hipStreamCaptureStatus",                                   "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUstreamCaptureStatus_enum",                                       {"hipStreamCaptureStatus",                                   "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUstreamCaptureStatus enum values
  // cudaStreamCaptureStatusNone
  {"CU_STREAM_CAPTURE_STATUS_NONE",                                    {"hipStreamCaptureStatusNone",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0
  // cudaStreamCaptureStatusActive
  {"CU_STREAM_CAPTURE_STATUS_ACTIVE",                                  {"hipStreamCaptureStatusActive",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1
  // cudaStreamCaptureStatusInvalidated
  {"CU_STREAM_CAPTURE_STATUS_INVALIDATED",                             {"hipStreamCaptureStatusInvalidated",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 2

  // cudaStreamCaptureMode
  {"CUstreamCaptureMode",                                              {"hipStreamCaptureMode",                                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUstreamCaptureMode_enum",                                         {"hipStreamCaptureMode",                                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUstreamCaptureMode enum values
  // cudaStreamCaptureModeGlobal
  {"CU_STREAM_CAPTURE_MODE_GLOBAL",                                    {"hipStreamCaptureModeGlobal",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0
  // cudaStreamCaptureModeThreadLocal
  {"CU_STREAM_CAPTURE_MODE_THREAD_LOCAL",                              {"hipStreamCaptureModeThreadLocal",                          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1
  // cudaStreamCaptureModeRelaxed
  {"CU_STREAM_CAPTURE_MODE_RELAXED",                                   {"hipStreamCaptureModeRelaxed",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 2

  // no analogue
  {"CUstreamWaitValue_flags",                                          {"hipStreamWaitValueFlags",                                  "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUstreamWaitValue_flags_enum",                                     {"hipStreamWaitValueFlags",                                  "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUstreamWaitValue_flags enum values
  {"CU_STREAM_WAIT_VALUE_GEQ",                                         {"hipStreamWaitValueGte",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x0
  {"CU_STREAM_WAIT_VALUE_EQ",                                          {"hipStreamWaitValueEq",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x1
  {"CU_STREAM_WAIT_VALUE_AND",                                         {"hipStreamWaitValueAnd",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x2
  {"CU_STREAM_WAIT_VALUE_NOR",                                         {"hipStreamWaitValueNor",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1}}, // 0x3
  {"CU_STREAM_WAIT_VALUE_FLUSH",                                       {"hipStreamWaitValueFlush",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1<<30

  // no analogue
  {"CUstreamWriteValue_flags",                                         {"hipStreamWriteValueFlags",                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUstreamWriteValue_flags_enum",                                    {"hipStreamWriteValueFlags",                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUstreamWriteValue_flags enum values
  {"CU_STREAM_WRITE_VALUE_DEFAULT",                                    {"hipStreamWriteValueDefault",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0
  {"CU_STREAM_WRITE_VALUE_NO_MEMORY_BARRIER",                          {"hipStreamWriteValueNoMemoryBarrier",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1

  // cudaGLDeviceList
  {"CUGLDeviceList",                                                   {"hipGLDeviceList",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUGLDeviceList_enum",                                              {"hipGLDeviceList",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUGLDeviceList enum values
  // cudaGLDeviceListAll = 1
  {"CU_GL_DEVICE_LIST_ALL",                                            {"hipGLDeviceListAll",                                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01
  // cudaGLDeviceListCurrentFrame = 2
  {"CU_GL_DEVICE_LIST_CURRENT_FRAME",                                  {"hipGLDeviceListCurrentFrame",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x02
  // cudaGLDeviceListNextFrame = 3
  {"CU_GL_DEVICE_LIST_NEXT_FRAME",                                     {"hipGLDeviceListNextFrame",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x03

  // cudaGLMapFlags
  {"CUGLmap_flags",                                                    {"hipGLMapFlags",                                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUGLmap_flags_enum",                                               {"hipGLMapFlags",                                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUGLmap_flags enum values
  // cudaGLMapFlagsNone = 0
  {"CU_GL_MAP_RESOURCE_FLAGS_NONE",                                    {"hipGLMapFlagsNone",                                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x00
  // cudaGLMapFlagsReadOnly = 1
  {"CU_GL_MAP_RESOURCE_FLAGS_READ_ONLY",                               {"hipGLMapFlagsReadOnly",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01
  // cudaGLMapFlagsWriteDiscard = 2
  {"CU_GL_MAP_RESOURCE_FLAGS_WRITE_DISCARD",                           {"hipGLMapFlagsWriteDiscard",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x02

  // cudaD3D9DeviceList
  {"CUd3d9DeviceList",                                                 {"hipD3D9DeviceList",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUd3d9DeviceList_enum",                                            {"hipD3D9DeviceList",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUd3d9DeviceList enum values
  // cudaD3D9DeviceListAll = 1
  {"CU_D3D9_DEVICE_LIST_ALL",                                          {"HIP_D3D9_DEVICE_LIST_ALL",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01
  // cudaD3D9DeviceListCurrentFrame = 2
  {"CU_D3D9_DEVICE_LIST_CURRENT_FRAME",                                {"HIP_D3D9_DEVICE_LIST_CURRENT_FRAME",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x02
  // cudaD3D9DeviceListNextFrame = 3
  {"CU_D3D9_DEVICE_LIST_NEXT_FRAME",                                   {"HIP_D3D9_DEVICE_LIST_NEXT_FRAME",                          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x03

  // cudaD3D9MapFlags
  // NOTE: Deprecated
  {"CUd3d9map_flags",                                                  {"hipD3D9MapFlags",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUd3d9map_flags_enum",                                             {"hipD3D9MapFlags",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUd3d9map_flags enum values
  // cudaD3D9MapFlagsNone = 0
  {"CU_D3D9_MAPRESOURCE_FLAGS_NONE",                                   {"HIP_D3D9_MAPRESOURCE_FLAGS_NONE",                          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x00
  // cudaD3D9MapFlagsReadOnly = 1
  {"CU_D3D9_MAPRESOURCE_FLAGS_READONLY",                               {"HIP_D3D9_MAPRESOURCE_FLAGS_READONLY",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01
  // cudaD3D9MapFlagsWriteDiscard = 2
  {"CU_D3D9_MAPRESOURCE_FLAGS_WRITEDISCARD",                           {"HIP_D3D9_MAPRESOURCE_FLAGS_WRITEDISCARD",                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x02

  // cudaD3D9RegisterFlags
  {"CUd3d9register_flags",                                             {"hipD3D9RegisterFlags",                                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUd3d9register_flags_enum",                                        {"hipD3D9RegisterFlags",                                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUd3d9register_flags enum values
  // cudaD3D9RegisterFlagsNone = 0
  {"CU_D3D9_REGISTER_FLAGS_NONE",                                      {"HIP_D3D9_REGISTER_FLAGS_NONE",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x00
  // cudaD3D9RegisterFlagsArray = 1
  {"CU_D3D9_REGISTER_FLAGS_ARRAY",                                     {"HIP_D3D9_REGISTER_FLAGS_ARRAY",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01

  // cudaD3D10DeviceList
  {"CUd3d10DeviceList",                                                {"hipd3d10DeviceList",                                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUd3d10DeviceList_enum",                                           {"hipD3D10DeviceList",                                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUd3d10DeviceList enum values
  // cudaD3D10DeviceListAll = 1
  {"CU_D3D10_DEVICE_LIST_ALL",                                         {"HIP_D3D10_DEVICE_LIST_ALL",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01
  // cudaD3D10DeviceListCurrentFrame = 2
  {"CU_D3D10_DEVICE_LIST_CURRENT_FRAME",                               {"HIP_D3D10_DEVICE_LIST_CURRENT_FRAME",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x02
  // cudaD3D10DeviceListNextFrame = 3
  {"CU_D3D10_DEVICE_LIST_NEXT_FRAME",                                  {"HIP_D3D10_DEVICE_LIST_NEXT_FRAME",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x03

  // cudaD3D10MapFlags
  {"CUd3d10map_flags",                                                 {"hipD3D10MapFlags",                                         "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUd3d10map_flags_enum",                                            {"hipD3D10MapFlags",                                         "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUd3d10map_flags enum values
  // cudaD3D10MapFlagsNone = 0
  {"CU_D3D10_MAPRESOURCE_FLAGS_NONE",                                  {"HIP_D3D10_MAPRESOURCE_FLAGS_NONE",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x00
  // cudaD3D10MapFlagsReadOnly = 1
  {"CU_D3D10_MAPRESOURCE_FLAGS_READONLY",                              {"HIP_D3D10_MAPRESOURCE_FLAGS_READONLY",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01
  // cudaD3D10MapFlagsWriteDiscard = 2
  {"CU_D3D10_MAPRESOURCE_FLAGS_WRITEDISCARD",                          {"HIP_D3D10_MAPRESOURCE_FLAGS_WRITEDISCARD",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x02

  // cudaD3D10RegisterFlags
  {"CUd3d10register_flags",                                            {"hipD3D10RegisterFlags",                                    "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUd3d10register_flags_enum",                                       {"hipD3D10RegisterFlags",                                    "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUd3d10register_flags enum values
  // cudaD3D10RegisterFlagsNone = 0
  {"CU_D3D10_REGISTER_FLAGS_NONE",                                     {"HIP_D3D10_REGISTER_FLAGS_NONE",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x00
  // cudaD3D10RegisterFlagsArray = 1
  {"CU_D3D10_REGISTER_FLAGS_ARRAY",                                    {"HIP_D3D10_REGISTER_FLAGS_ARRAY",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01

  // cudaD3D11DeviceList
  {"CUd3d11DeviceList",                                                {"hipd3d11DeviceList",                                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUd3d11DeviceList_enum",                                           {"hipD3D11DeviceList",                                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUd3d11DeviceList enum values
  // cudaD3D11DeviceListAll = 1
  {"CU_D3D11_DEVICE_LIST_ALL",                                         {"HIP_D3D11_DEVICE_LIST_ALL",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01
  // cudaD3D11DeviceListCurrentFrame = 2
  {"CU_D3D11_DEVICE_LIST_CURRENT_FRAME",                               {"HIP_D3D11_DEVICE_LIST_CURRENT_FRAME",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x02
  // cudaD3D11DeviceListNextFrame = 3
  {"CU_D3D11_DEVICE_LIST_NEXT_FRAME",                                  {"HIP_D3D11_DEVICE_LIST_NEXT_FRAME",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x03

  // no analogue
  {"CUmemAllocationHandleType",                                        {"hipMemoryAllocationHandleType",                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemAllocationHandleType_enum",                                   {"hipMemoryAllocationHandleType",                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUmemAllocationHandleType enum values
  // cudaMemHandleTypeNone
  {"CU_MEM_HANDLE_TYPE_NONE",                                          {"hipMemoryHandleTypeNone",                                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0
  // cudaMemHandleTypePosixFileDescriptor
  {"CU_MEM_HANDLE_TYPE_POSIX_FILE_DESCRIPTOR",                         {"hipMemoryHandleTypePosixFileDescriptor",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1
  // cudaMemHandleTypeWin32
  {"CU_MEM_HANDLE_TYPE_WIN32",                                         {"hipMemoryHandleTypeWin32",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x2
  // cudaMemHandleTypeWin32Kmt
  {"CU_MEM_HANDLE_TYPE_WIN32_KMT",                                     {"hipMemoryHandleTypeWin32Kmt",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x4
  // no analogue
  {"CU_MEM_HANDLE_TYPE_MAX",                                           {"hipMemoryHandleTypeMax",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x7FFFFFFF

  // cudaMemAccessFlags
  {"CUmemAccess_flags",                                                {"hipMemoryAccessFlags",                                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemAccess_flags_enum",                                           {"hipMemoryAccessFlags",                                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUmemAccess_flags enum values
  // cudaMemAccessFlagsProtNone
  {"CU_MEM_ACCESS_FLAGS_PROT_NONE",                                    {"hipMemoryAccessFlagsProtNone",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0
  // cudaMemAccessFlagsProtRead
  {"CU_MEM_ACCESS_FLAGS_PROT_READ",                                    {"hipMemoryAccessFlagsProtRead",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1
  // cudaMemAccessFlagsProtReadWrite
  {"CU_MEM_ACCESS_FLAGS_PROT_READWRITE",                               {"hipMemoryAccessFlagsProtReadWrite",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x3
  // no analogue
  {"CU_MEM_ACCESS_FLAGS_PROT_MAX",                                     {"hipMemoryAccessFlagsProtMax",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x7FFFFFFF

  // cudaMemLocationType
  {"CUmemLocationType",                                                {"hipMemoryLocationType",                                    "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemLocationType_enum",                                           {"hipMemoryLocationType",                                    "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUmemLocationType enum values
  // cudaMemLocationTypeInvalid
  {"CU_MEM_LOCATION_TYPE_INVALID",                                     {"hipMemoryLocationTypeInvalid",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0
  // cudaMemLocationTypeDevice
  {"CU_MEM_LOCATION_TYPE_DEVICE",                                      {"hipMemoryLocationTypeDevice",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1
  // no analogue
  {"CU_MEM_LOCATION_TYPE_MAX",                                         {"hipMemoryLocationTypeMax",                                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x7FFFFFFF

  // cudaMemAllocationType
  {"CUmemAllocationType",                                              {"hipMemoryAllocationType",                                  "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemAllocationType_enum",                                         {"hipMemoryAllocationType",                                  "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUmemAllocationType enum values
  // cudaMemAllocationTypeInvalid
  {"CU_MEM_ALLOCATION_TYPE_INVALID",                                   {"hipMemoryAllocationTypeInvalid",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0
  // cudaMemAllocationTypePinned
  {"CU_MEM_ALLOCATION_TYPE_PINNED",                                    {"hipMemoryAllocationTypePinned",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1
  // cudaMemAllocationTypeMax
  {"CU_MEM_ALLOCATION_TYPE_MAX",                                       {"hipMemoryAllocationTypeMax",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x7FFFFFFF

  // no analogue
  {"CUmemAllocationGranularity_flags",                                 {"hipMemoryAllocationGranularityFlags",                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemAllocationGranularity_flags_enum",                            {"hipMemoryLocationType",                                    "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUmemAllocationGranularity_flags enum values
  {"CU_MEM_ALLOC_GRANULARITY_MINIMUM",                                 {"HIP_MEM_ALLOC_GRANULARITY_MINIMUM",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0
  {"CU_MEM_ALLOC_GRANULARITY_RECOMMENDED",                             {"HIP_MEM_ALLOC_GRANULARITY_RECOMMENDED",                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1

  //
  {"CUaccessProperty",                                                 {"hipAccessProperty",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUaccessProperty_enum",                                            {"hipAccessProperty",                                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUaccessProperty_enum enum values
  {"CU_ACCESS_PROPERTY_NORMAL",                                        {"HIP_ACCESS_PROPERTY_NORMAL",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0
  {"CU_ACCESS_PROPERTY_STREAMING",                                     {"HIP_ACCESS_PROPERTY_STREAMING",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1
  {"CU_ACCESS_PROPERTY_PERSISTING",                                    {"HIP_ACCESS_PROPERTY_PERSISTING",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 2

  //
  {"CUsynchronizationPolicy",                                          {"hipSynchronizationPolicy",                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUsynchronizationPolicy_enum",                                     {"hipSynchronizationPolicy",                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUsynchronizationPolicy_enum enum values
  {"CU_SYNC_POLICY_AUTO",                                              {"HIP_SYNC_POLICY_AUTO",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1
  {"CU_SYNC_POLICY_SPIN",                                              {"HIP_SYNC_POLICY_SPIN",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 2
  {"CU_SYNC_POLICY_YIELD",                                             {"HIP_SYNC_POLICY_YIELD",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 3
  {"CU_SYNC_POLICY_BLOCKING_SYNC",                                     {"HIP_SYNC_POLICY_BLOCKING_SYNC",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 4

  //
  {"CUkernelNodeAttrID",                                               {"hipKernelNodeAttrID",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUkernelNodeAttrID_enum",                                          {"hipKernelNodeAttrID",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUkernelNodeAttrID_enum enum values
  {"CU_KERNEL_NODE_ATTRIBUTE_ACCESS_POLICY_WINDOW",                    {"HIP_KERNEL_NODE_ATTRIBUTE_ACCESS_POLICY_WINDOW",           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1
  {"CU_KERNEL_NODE_ATTRIBUTE_COOPERATIVE",                             {"HIP_KERNEL_NODE_ATTRIBUTE_COOPERATIVE",                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 2

  //
  {"CUstreamAttrID",                                                   {"hipStreamAttrID",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUstreamAttrID_enum",                                              {"hipStreamAttrID",                                          "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUstreamAttrID_enum enum values
  {"CU_STREAM_ATTRIBUTE_ACCESS_POLICY_WINDOW",                         {"HIP_STREAM_ATTRIBUTE_ACCESS_POLICY_WINDOW",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1
  {"CU_STREAM_ATTRIBUTE_SYNCHRONIZATION_POLICY",                       {"HIP_STREAM_ATTRIBUTE_SYNCHRONIZATION_POLICY",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 3

  // no analogue
  {"CUevent_record_flags",                                             {"hipEvent_record_flags",                                    "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUevent_record_flags_enum",                                        {"hipEvent_record_flags",                                    "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUevent_record_flags enum values
  // cudaEventRecordDefault
  {"CU_EVENT_RECORD_DEFAULT",                                          {"hipEventRecordDefault",                                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0
  // cudaEventRecordExternal
  {"CU_EVENT_RECORD_EXTERNAL",                                         {"hipEventRecordExternal",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1

  // no analogue
  {"CUevent_wait_flags",                                               {"hipEvent_wait_flags",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUevent_wait_flags_enum",                                          {"hipEvent_wait_flags",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUevent_wait_flags enum values
  // cudaEventWaitDefault
  {"CU_EVENT_WAIT_DEFAULT",                                            {"hipEventWaitDefault",                                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0
  // cudaEventWaitExternal
  {"CU_EVENT_WAIT_EXTERNAL",                                           {"hipEventWaitExternal",                                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1

  //
  {"CUDA_POINTER_ATTRIBUTE_ACCESS_FLAGS",                              {"HIP_POINTER_ATTRIBUTE_ACCESS_FLAGS",                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUDA_POINTER_ATTRIBUTE_ACCESS_FLAGS_enum",                         {"HIP_POINTER_ATTRIBUTE_ACCESS_FLAGS",                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUDA_POINTER_ATTRIBUTE_ACCESS_FLAGS enum values
  {"CU_POINTER_ATTRIBUTE_ACCESS_FLAG_NONE",                            {"HIP_POINTER_ATTRIBUTE_ACCESS_FLAG_NONE",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0
  {"CU_POINTER_ATTRIBUTE_ACCESS_FLAG_READ",                            {"HIP_POINTER_ATTRIBUTE_ACCESS_FLAG_READ",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1
  {"CU_POINTER_ATTRIBUTE_ACCESS_FLAG_READWRITE",                       {"HIP_POINTER_ATTRIBUTE_ACCESS_FLAG_READWRITE",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x3

  {"CUarraySparseSubresourceType",                                     {"hipArraySparseSubresourceType",                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUarraySparseSubresourceType_enum",                                {"hipArraySparseSubresourceType",                            "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUarraySparseSubresourceType enum values
  {"CU_ARRAY_SPARSE_SUBRESOURCE_TYPE_SPARSE_LEVEL",                    {"HIP_ARRAY_SPARSE_SUBRESOURCE_TYPE_SPARSE_LEVEL",           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0
  {"CU_ARRAY_SPARSE_SUBRESOURCE_TYPE_MIPTAIL",                         {"HIP_ARRAY_SPARSE_SUBRESOURCE_TYPE_MIPTAIL",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1

  {"CUmemOperationType",                                               {"hipMemOperationType",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemOperationType_enum",                                          {"hipMemOperationType",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUmemOperationType enum values
  {"CU_MEM_OPERATION_TYPE_MAP",                                        {"HIP_MEM_OPERATION_TYPE_MAP",                               "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1
  {"CU_MEM_OPERATION_TYPE_UNMAP",                                      {"HIP_MEM_OPERATION_TYPE_UNMAP",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 2

  {"CUmemHandleType",                                                  {"hipMemHandleType",                                         "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemHandleType_enum",                                             {"hipMemHandleType",                                         "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUmemHandleType enum values
  {"CU_MEM_HANDLE_TYPE_GENERIC",                                       {"HIP_MEM_HANDLE_TYPE_GENERIC",                              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0

  // cudaMemPoolAttr
  {"CUmemPool_attribute",                                              {"hipMemPoolAttr",                                           "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemPool_attribute_enum",                                         {"hipMemPoolAttr",                                           "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUmemPool_attribute enum values
  // cudaMemPoolReuseFollowEventDependencies
  {"CU_MEMPOOL_ATTR_REUSE_FOLLOW_EVENT_DEPENDENCIES",                  {"hipMemPoolReuseFollowEventDependencies",                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1
  // cudaMemPoolReuseAllowOpportunistic
  {"CU_MEMPOOL_ATTR_REUSE_ALLOW_OPPORTUNISTIC",                        {"hipMemPoolReuseAllowOpportunistic",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaMemPoolReuseAllowInternalDependencies
  {"CU_MEMPOOL_ATTR_REUSE_ALLOW_INTERNAL_DEPENDENCIES",                {"hipMemPoolReuseAllowInternalDependencies",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaMemPoolAttrReleaseThreshold
  {"CU_MEMPOOL_ATTR_RELEASE_THRESHOLD",                                {"hipMemPoolAttrReleaseThreshold",                           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaMemPoolAttrReservedMemCurrent
  {"CU_MEMPOOL_ATTR_RESERVED_MEM_CURRENT",                             {"hipMemPoolAttrReservedMemCurrent",                         "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaMemPoolAttrReservedMemHigh
  {"CU_MEMPOOL_ATTR_RESERVED_MEM_HIGH",                                {"hipMemPoolAttrReservedMemHigh",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaMemPoolAttrUsedMemCurrent
  {"CU_MEMPOOL_ATTR_USED_MEM_CURRENT",                                 {"hipMemPoolAttrUsedMemCurrent",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaMemPoolAttrUsedMemHigh
  {"CU_MEMPOOL_ATTR_USED_MEM_HIGH",                                    {"hipMemPoolAttrUsedMemHigh",                                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaStreamUpdateCaptureDependenciesFlags
  {"CUstreamUpdateCaptureDependencies_flags",                          {"hipStreamUpdateCaptureDependenciesFlags",                  "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUstreamUpdateCaptureDependencies_flags_enum",                     {"hipStreamUpdateCaptureDependenciesFlags",                  "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUstreamUpdateCaptureDependencies_flags enum values
  // cudaStreamAddCaptureDependencies
  {"CU_STREAM_ADD_CAPTURE_DEPENDENCIES",                               {"hipStreamAddCaptureDependencies",                          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x0
  // cudaStreamSetCaptureDependencies
  {"CU_STREAM_SET_CAPTURE_DEPENDENCIES",                               {"hipStreamSetCaptureDependencies",                          "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1

  //
  {"CUdriverProcAddress_flags",                                        {"hipDriverProcAddress",                                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUdriverProcAddress_flags_enum",                                   {"hipDriverProcAddress",                                     "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUdriverProcAddress_flags enum values
  //
  {"CU_GET_PROC_ADDRESS_DEFAULT",                                      {"HIP_GET_PROC_ADDRESS_DEFAULT",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0
  //
  {"CU_GET_PROC_ADDRESS_LEGACY_STREAM",                                {"HIP_GET_PROC_ADDRESS_LEGACY_STREAM",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1 << 0
  //
  {"CU_GET_PROC_ADDRESS_PER_THREAD_DEFAULT_STREAM",                    {"HIP_GET_PROC_ADDRESS_PER_THREAD_DEFAULT_STREAM",           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1 << 1

  // cudaFlushGPUDirectRDMAWritesOptions
  {"CUflushGPUDirectRDMAWritesOptions",                                {"hipFlushGPUDirectRDMAWritesOptions",                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUflushGPUDirectRDMAWritesOptions_enum",                           {"hipFlushGPUDirectRDMAWritesOptions",                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUflushGPUDirectRDMAWritesOptions enum values
  // cudaFlushGPUDirectRDMAWritesOptionHost
  {"CU_FLUSH_GPU_DIRECT_RDMA_WRITES_OPTION_HOST",                      {"hipFlushGPUDirectRDMAWritesOptionHost",                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1<<0
  // cudaFlushGPUDirectRDMAWritesOptionMemOps
  {"CU_FLUSH_GPU_DIRECT_RDMA_WRITES_OPTION_MEMOPS",                    {"hipFlushGPUDirectRDMAWritesOptionMemOps",                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1<<1

  // cudaGPUDirectRDMAWritesOrdering
  {"CUGPUDirectRDMAWritesOrdering",                                    {"hipGPUDirectRDMAWritesOrdering",                           "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUGPUDirectRDMAWritesOrdering_enum",                               {"hipGPUDirectRDMAWritesOrdering",                           "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUGPUDirectRDMAWritesOrdering enum values
  // cudaGPUDirectRDMAWritesOrderingNone
  {"CU_GPU_DIRECT_RDMA_WRITES_ORDERING_NONE",                          {"hipGPUDirectRDMAWritesOrderingNone",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0
  // cudaGPUDirectRDMAWritesOrderingOwner
  {"CU_GPU_DIRECT_RDMA_WRITES_ORDERING_OWNER",                         {"hipGPUDirectRDMAWritesOrderingOwner",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 100
  // cudaGPUDirectRDMAWritesOrderingAllDevices
  {"CU_GPU_DIRECT_RDMA_WRITES_ORDERING_ALL_DEVICES",                   {"hipGPUDirectRDMAWritesOrderingAllDevices",                 "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 200

  // cudaFlushGPUDirectRDMAWritesScope
  {"CUflushGPUDirectRDMAWritesScope",                                  {"hipFlushGPUDirectRDMAWritesScope",                         "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUflushGPUDirectRDMAWritesScope_enum",                             {"hipFlushGPUDirectRDMAWritesScope",                         "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUflushGPUDirectRDMAWritesScope enum values
  // cudaFlushGPUDirectRDMAWritesToOwner
  {"CU_FLUSH_GPU_DIRECT_RDMA_WRITES_TO_OWNER",                         {"hipFlushGPUDirectRDMAWritesToOwner",                       "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 100
  // cudaFlushGPUDirectRDMAWritesToAllDevices
  {"CU_FLUSH_GPU_DIRECT_RDMA_WRITES_TO_ALL_DEVICES",                   {"hipFlushGPUDirectRDMAWritesToAllDevices",                  "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 200

  // cudaFlushGPUDirectRDMAWritesTarget
  {"CUflushGPUDirectRDMAWritesTarget",                                 {"hipFlushGPUDirectRDMAWritesTarget",                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUflushGPUDirectRDMAWritesTarget_enum",                            {"hipFlushGPUDirectRDMAWritesTarget",                        "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUflushGPUDirectRDMAWritesTarget enum values
  // cudaFlushGPUDirectRDMAWritesTargetCurrentDevice
  {"CU_FLUSH_GPU_DIRECT_RDMA_WRITES_TARGET_CURRENT_CTX",               {"hipFlushGPUDirectRDMAWritesTargetCurrentDevice",           "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}},

  //
  {"CUgraphDebugDot_flags",                                            {"hipGraphDebugDotFlags",                                    "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUgraphDebugDot_flags_enum",                                       {"hipGraphDebugDotFlags",                                    "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUgraphDebugDot_flags enum values
  // cudaGraphDebugDotFlagsVerbose
  {"CU_GRAPH_DEBUG_DOT_FLAGS_VERBOSE",                                 {"hipGraphDebugDotFlagsVerbose",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1<<0
  // no analogue
  {"CU_GRAPH_DEBUG_DOT_FLAGS_RUNTIME_TYPES",                           {"hipGraphDebugDotFlagsRuntimeTypes",                        "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1<<1
  // cudaGraphDebugDotFlagsKernelNodeParams
  {"CU_GRAPH_DEBUG_DOT_FLAGS_KERNEL_NODE_PARAMS",                      {"hipGraphDebugDotFlagsKernelNodeParams",                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1<<2
  // cudaGraphDebugDotFlagsMemcpyNodeParams
  {"CU_GRAPH_DEBUG_DOT_FLAGS_MEMCPY_NODE_PARAMS",                      {"hipGraphDebugDotFlagsMemcpyNodeParams",                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1<<3
  // cudaGraphDebugDotFlagsMemsetNodeParams
  {"CU_GRAPH_DEBUG_DOT_FLAGS_MEMSET_NODE_PARAMS",                      {"hipGraphDebugDotFlagsMemsetNodeParams",                    "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1<<4
  // cudaGraphDebugDotFlagsHostNodeParams
  {"CU_GRAPH_DEBUG_DOT_FLAGS_HOST_NODE_PARAMS",                        {"hipGraphDebugDotFlagsHostNodeParams",                      "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1<<5
  // cudaGraphDebugDotFlagsEventNodeParams
  {"CU_GRAPH_DEBUG_DOT_FLAGS_EVENT_NODE_PARAMS",                       {"hipGraphDebugDotFlagsEventNodeParams",                     "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1<<6
  // cudaGraphDebugDotFlagsExtSemasSignalNodeParams
  {"CU_GRAPH_DEBUG_DOT_FLAGS_EXT_SEMAS_SIGNAL_NODE_PARAMS",            {"hipGraphDebugDotFlagsExtSemasSignalNodeParams",            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1<<7
  // cudaGraphDebugDotFlagsExtSemasWaitNodeParams
  {"CU_GRAPH_DEBUG_DOT_FLAGS_EXT_SEMAS_WAIT_NODE_PARAMS",              {"hipGraphDebugDotFlagsExtSemasWaitNodeParams",              "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1<<8
  // cudaGraphDebugDotFlagsKernelNodeAttributes
  {"CU_GRAPH_DEBUG_DOT_FLAGS_KERNEL_NODE_ATTRIBUTES",                  {"hipGraphDebugDotFlagsKernelNodeAttributes",                "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1<<9
  // cudaGraphDebugDotFlagsHandles
  {"CU_GRAPH_DEBUG_DOT_FLAGS_HANDLES",                                 {"hipGraphDebugDotFlagsHandles",                             "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1<<10

  // cudaUserObjectFlags
  {"CUuserObject_flags",                                               {"hipUserObjectFlags",                                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUuserObject_flags_enum",                                          {"hipUserObjectFlags",                                       "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUuserObject_flags enum values
  // cudaUserObjectNoDestructorSync
  {"CU_USER_OBJECT_NO_DESTRUCTOR_SYNC",                                {"hipUserObjectNoDestructorSync",                            "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1

  // cudaUserObjectRetainFlags
  {"CUuserObjectRetain_flags",                                         {"hipUserObjectRetainFlags",                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUuserObjectRetain_flags_enum",                                    {"hipUserObjectRetainFlags",                                 "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // CUuserObjectRetain_flags enum values
  // cudaGraphUserObjectMove
  {"CU_GRAPH_USER_OBJECT_MOVE",                                        {"hipGraphUserObjectMove",                                   "", CONV_NUMERIC_LITERAL, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 1

  // 4. Typedefs

  // no analogue
  {"CUdevice",                                                         {"hipDevice_t",                                              "", CONV_TYPE, API_DRIVER, 1}},
  {"CUdevice_v1",                                                      {"hipDevice_t",                                              "", CONV_TYPE, API_DRIVER, 1}},
  {"CUdeviceptr",                                                      {"hipDeviceptr_t",                                           "", CONV_TYPE, API_DRIVER, 1}},
  {"CUdeviceptr_v1",                                                   {"hipDeviceptr_t",                                           "", CONV_TYPE, API_DRIVER, 1}},
  {"CUdeviceptr_v2",                                                   {"hipDeviceptr_t",                                           "", CONV_TYPE, API_DRIVER, 1}},

  // cudaHostFn_t
  {"CUhostFn",                                                         {"hipHostFn",                                                "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // no analogue
  {"CUoccupancyB2DSize",                                               {"hipOccupancyB2DSize",                                      "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaStreamCallback_t
  {"CUstreamCallback",                                                 {"hipStreamCallback_t",                                      "", CONV_TYPE, API_DRIVER, 1}},

  // cudaSurfaceObject_t
  {"CUsurfObject",                                                     {"hipSurfaceObject",                                         "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUsurfObject_v1",                                                  {"hipSurfaceObject",                                         "", CONV_TYPE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // cudaTextureObject_t
  {"CUtexObject",                                                      {"hipTextureObject_t",                                       "", CONV_TYPE, API_DRIVER, 1}},
  {"CUtexObject_v1",                                                   {"hipTextureObject_t",                                       "", CONV_TYPE, API_DRIVER, 1}},

  //
  {"CUmemGenericAllocationHandle",                                     {"hipMemGenericAllocationHandle",                            "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  {"CUmemGenericAllocationHandle_v1",                                  {"hipMemGenericAllocationHandle",                            "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}},

  // 5. Defines

  {"__CUDACC__",                                                       {"__HIPCC__",                                                "", CONV_DEFINE, API_DRIVER, 1}},
  {"CUDA_CB",                                                          {"HIP_CB",                                                   "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}},
  // cudaCpuDeviceId ((int)-1)
  {"CU_DEVICE_CPU",                                                    {"hipCpuDeviceId",                                           "", CONV_DEFINE, API_DRIVER, 1}}, // ((CUdevice)-1)
  // cudaInvalidDeviceId ((int)-1)
  {"CU_DEVICE_INVALID",                                                {"hipInvalidDeviceId",                                       "", CONV_DEFINE, API_DRIVER, 1}}, // ((CUdevice)-2)
  // CUDA_IPC_HANDLE_SIZE
  {"CU_IPC_HANDLE_SIZE",                                               {"HIP_IPC_HANDLE_SIZE",                                      "", CONV_DEFINE, API_DRIVER, 1}}, // 64
  {"CU_LAUNCH_PARAM_BUFFER_POINTER",                                   {"HIP_LAUNCH_PARAM_BUFFER_POINTER",                          "", CONV_DEFINE, API_DRIVER, 1}}, // ((void*)0x01)
  {"CU_LAUNCH_PARAM_BUFFER_SIZE",                                      {"HIP_LAUNCH_PARAM_BUFFER_SIZE",                             "", CONV_DEFINE, API_DRIVER, 1}}, // ((void*)0x02)
  {"CU_LAUNCH_PARAM_END",                                              {"HIP_LAUNCH_PARAM_END",                                     "", CONV_DEFINE, API_DRIVER, 1}}, // ((void*)0x00)
  // cudaHostAllocPortable
  {"CU_MEMHOSTALLOC_PORTABLE",                                         {"hipHostMallocPortable",                                    "", CONV_DEFINE, API_DRIVER, 1}}, // 0x01
  // cudaHostAllocMapped
  {"CU_MEMHOSTALLOC_DEVICEMAP",                                        {"hipHostMallocMapped",                                      "", CONV_DEFINE, API_DRIVER, 1}}, // 0x02
  // cudaHostAllocWriteCombined
  {"CU_MEMHOSTALLOC_WRITECOMBINED",                                    {"hipHostMallocWriteCombined",                               "", CONV_DEFINE, API_DRIVER, 1}}, // 0x04
  // cudaHostRegisterPortable
  {"CU_MEMHOSTREGISTER_PORTABLE",                                      {"hipHostRegisterPortable",                                  "", CONV_DEFINE, API_DRIVER, 1}}, // 0x01
  // cudaHostRegisterMapped
  {"CU_MEMHOSTREGISTER_DEVICEMAP",                                     {"hipHostRegisterMapped",                                    "", CONV_DEFINE, API_DRIVER, 1}}, // 0x02
  // cudaHostRegisterIoMemory
  {"CU_MEMHOSTREGISTER_IOMEMORY",                                      {"hipHostRegisterIoMemory",                                  "", CONV_DEFINE, API_DRIVER, 1}}, // 0x04
  // cudaHostRegisterReadOnly
  {"CU_MEMHOSTREGISTER_READ_ONLY",                                     {"hipHostRegisterReadOnly",                                  "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x08
  //
  {"CU_PARAM_TR_DEFAULT",                                              {"HIP_PARAM_TR_DEFAULT",                                     "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // -1
  // cudaStreamLegacy ((cudaStream_t)0x1)
  {"CU_STREAM_LEGACY",                                                 {"hipStreamLegacy",                                          "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // ((CUstream)0x1)
  // cudaStreamPerThread ((cudaStream_t)0x2)
  {"CU_STREAM_PER_THREAD",                                             {"hipStreamPerThread",                                       "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // ((CUstream)0x2)
  {"CU_TRSA_OVERRIDE_FORMAT",                                          {"HIP_TRSA_OVERRIDE_FORMAT",                                 "", CONV_DEFINE, API_DRIVER, 1}}, // 0x01
  {"CU_TRSF_NORMALIZED_COORDINATES",                                   {"HIP_TRSF_NORMALIZED_COORDINATES",                          "", CONV_DEFINE, API_DRIVER, 1}}, // 0x02
  {"CU_TRSF_READ_AS_INTEGER",                                          {"HIP_TRSF_READ_AS_INTEGER",                                 "", CONV_DEFINE, API_DRIVER, 1}}, // 0x01
  {"CU_TRSF_SRGB",                                                     {"HIP_TRSF_SRGB",                                            "", CONV_DEFINE, API_DRIVER, 1}}, // 0x10
  // no analogue
  // NOTE: Deprecated, use CUDA_ARRAY3D_LAYERED
  {"CUDA_ARRAY3D_2DARRAY",                                             {"HIP_ARRAY3D_2DARRAY",                                      "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED | CUDA_DEPRECATED}}, // 0x01
  // cudaArrayLayered
  {"CUDA_ARRAY3D_LAYERED",                                             {"hipArrayLayered",                                          "", CONV_DEFINE, API_DRIVER, 1}}, // 0x01
  // cudaArraySurfaceLoadStore
  {"CUDA_ARRAY3D_SURFACE_LDST",                                        {"hipArraySurfaceLoadStore",                                 "", CONV_DEFINE, API_DRIVER, 1}}, // 0x02
  // cudaArrayCubemap
  {"CUDA_ARRAY3D_CUBEMAP",                                             {"hipArrayCubemap",                                          "", CONV_DEFINE, API_DRIVER, 1}}, // 0x04
  // cudaArrayTextureGather
  {"CUDA_ARRAY3D_TEXTURE_GATHER",                                      {"hipArrayTextureGather",                                    "", CONV_DEFINE, API_DRIVER, 1}}, // 0x08
  // no analogue
  {"CUDA_ARRAY3D_DEPTH_TEXTURE",                                       {"hipArrayDepthTexture",                                     "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x10
  // cudaArrayColorAttachment
  {"CUDA_ARRAY3D_COLOR_ATTACHMENT",                                    {"hipArrayColorAttachment",                                  "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x20
  // cudaArraySparse
  {"CUDA_ARRAY3D_SPARSE",                                              {"hipArraySparse",                                           "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x40
  // cudaCooperativeLaunchMultiDeviceNoPreSync
  {"CUDA_COOPERATIVE_LAUNCH_MULTI_DEVICE_NO_PRE_LAUNCH_SYNC",          {"hipCooperativeLaunchMultiDeviceNoPreSync",                 "", CONV_DEFINE, API_DRIVER, 1}}, // 0x01
  // cudaCooperativeLaunchMultiDeviceNoPostSync
  {"CUDA_COOPERATIVE_LAUNCH_MULTI_DEVICE_NO_POST_LAUNCH_SYNC",         {"hipCooperativeLaunchMultiDeviceNoPostSync",                "", CONV_DEFINE, API_DRIVER, 1}}, // 0x02
  // cudaExternalMemoryDedicated
  {"CUDA_EXTERNAL_MEMORY_DEDICATED",                                   {"hipExternalMemoryDedicated",                               "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1
  // cudaExternalSemaphoreSignalSkipNvSciBufMemSync
  {"CUDA_EXTERNAL_SEMAPHORE_SIGNAL_SKIP_NVSCIBUF_MEMSYNC",             {"hipExternalSemaphoreSignalSkipNvSciBufMemSync",            "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x01
  // cudaExternalSemaphoreWaitSkipNvSciBufMemSync
  {"CUDA_EXTERNAL_SEMAPHORE_WAIT_SKIP_NVSCIBUF_MEMSYNC",               {"hipExternalSemaphoreWaitSkipNvSciBufMemSync",              "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x02
  // cudaNvSciSyncAttrSignal
  {"CUDA_NVSCISYNC_ATTR_SIGNAL",                                       {"hipNvSciSyncAttrSignal",                                   "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1
  // cudaNvSciSyncAttrWait
  {"CUDA_NVSCISYNC_ATTR_WAIT",                                         {"hipNvSciSyncAttrWait",                                     "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1
  {"CUDA_VERSION",                                                     {"HIP_VERSION",                                              "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 10000
  {"CU_TRSF_DISABLE_TRILINEAR_OPTIMIZATION",                           {"HIP_TRSF_DISABLE_TRILINEAR_OPTIMIZATION",                  "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x20
  // cudaArraySparsePropertiesSingleMipTail
  {"CU_ARRAY_SPARSE_PROPERTIES_SINGLE_MIPTAIL",                        {"HIP_ARRAY_SPARSE_PROPERTIES_SINGLE_MIPTAIL",               "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1
  {"CU_MEM_CREATE_USAGE_TILE_POOL",                                    {"HIP_MEM_CREATE_USAGE_TILE_POOL",                           "", CONV_DEFINE, API_DRIVER, 1, HIP_UNSUPPORTED}}, // 0x1
};

const std::map<llvm::StringRef, cudaAPIversions> CUDA_DRIVER_TYPE_NAME_VER_MAP {
  {"CU_CTX_BLOCKING_SYNC",                                             {CUDA_0,   CUDA_40,  CUDA_0  }},
  {"CUDA_EXTERNAL_MEMORY_BUFFER_DESC_st",                              {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_MEMORY_BUFFER_DESC",                                 {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_MEMORY_HANDLE_DESC_st",                              {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_MEMORY_HANDLE_DESC",                                 {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC_st",                     {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC",                        {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC_st",                           {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC",                              {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS",                            {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS_st",                         {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS",                              {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS_st",                           {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_HOST_NODE_PARAMS",                                            {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_HOST_NODE_PARAMS_st",                                         {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_KERNEL_NODE_PARAMS",                                          {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_KERNEL_NODE_PARAMS_st",                                       {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_LAUNCH_PARAMS",                                               {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUDA_LAUNCH_PARAMS_st",                                            {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUDA_MEMSET_NODE_PARAMS",                                          {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_MEMSET_NODE_PARAMS_st",                                       {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUeglStreamConnection",                                            {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUeglStreamConnection_st",                                         {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUexternalMemory",                                                 {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUextMemory_st",                                                   {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUexternalSemaphore",                                              {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUextSemaphore_st",                                                {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUgraph",                                                          {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUgraph_st",                                                       {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUgraphExec",                                                      {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUgraphExec_st",                                                   {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUgraphNode",                                                      {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUgraphNode_st",                                                   {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUmemLocation",                                                    {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUmemLocation_st",                                                 {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUmemAllocationProp",                                              {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUmemAllocationProp_st",                                           {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUmemAccessDesc",                                                  {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUmemAccessDesc_st",                                               {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUaccessPolicyWindow",                                             {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CUaccessPolicyWindow_st",                                          {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CUstreamBatchMemOpParams",                                         {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CUstreamBatchMemOpParams_union",                                   {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CUkernelNodeAttrValue",                                            {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CUkernelNodeAttrValue_union",                                      {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CUstreamAttrValue",                                                {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CUstreamAttrValue_union",                                          {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_COMPUTEMODE_EXCLUSIVE",                                         {CUDA_0,   CUDA_0,   CUDA_80 }},
  {"CU_DEVICE_ATTRIBUTE_RESERVED_SHARED_MEMORY_PER_BLOCK",             {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_GPU_DIRECT_RDMA_WITH_CUDA_VMM_SUPPORTED",      {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_MAX_ACCESS_POLICY_WINDOW_SIZE",                {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_MAX_PERSISTING_L2_CACHE_SIZE",                 {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_GENERIC_COMPRESSION_SUPPORTED",                {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_MAX_BLOCKS_PER_MULTIPROCESSOR",                {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_HANDLE_TYPE_WIN32_KMT_HANDLE_SUPPORTED",       {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_HANDLE_TYPE_WIN32_HANDLE_SUPPORTED",           {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_HANDLE_TYPE_POSIX_FILE_DESCRIPTOR_SUPPORTED",  {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_VIRTUAL_ADDRESS_MANAGEMENT_SUPPORTED",         {CUDA_102, CUDA_112, CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_DIRECT_MANAGED_MEM_ACCESS_FROM_HOST",          {CUDA_92,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS_USES_HOST_PAGE_TABLES", {CUDA_92,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_HOST_REGISTER_SUPPORTED",                      {CUDA_92,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_CAN_FLUSH_REMOTE_WRITES",                      {CUDA_92,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK_OPTIN",            {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_COOPERATIVE_MULTI_DEVICE_LAUNCH",              {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_COOPERATIVE_LAUNCH",                           {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_WAIT_VALUE_NOR",                {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_CAN_USE_64_BIT_STREAM_MEM_OPS",                {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_MEM_OPS",                       {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_CAN_USE_HOST_POINTER_FOR_REGISTERED_MEM",      {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_COMPUTE_PREEMPTION_SUPPORTED",                 {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS",                    {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS",                       {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_SINGLE_TO_DOUBLE_PRECISION_PERF_RATIO",        {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_HOST_NATIVE_ATOMIC_SUPPORTED",                 {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CUdevice_P2PAttribute",                                            {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CUdevice_P2PAttribute_enum",                                       {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_P2P_ATTRIBUTE_PERFORMANCE_RANK",                         {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_P2P_ATTRIBUTE_ACCESS_SUPPORTED",                         {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_P2P_ATTRIBUTE_NATIVE_ATOMIC_SUPPORTED",                  {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_P2P_ATTRIBUTE_ACCESS_ACCESS_SUPPORTED",                  {CUDA_101, CUDA_101, CUDA_0  }},
  {"CU_DEVICE_P2P_ATTRIBUTE_ARRAY_ACCESS_ACCESS_SUPPORTED",            {CUDA_92,  CUDA_100, CUDA_101}},
  {"CU_DEVICE_P2P_ATTRIBUTE_CUDA_ARRAY_ACCESS_SUPPORTED",              {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUeglColorFormat",                                                 {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUeglColorFormate_enum",                                           {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUV420_PLANAR",                                {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUV420_SEMIPLANAR",                            {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUV422_PLANAR",                                {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUV422_SEMIPLANAR",                            {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_RGB",                                          {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BGR",                                          {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_ARGB",                                         {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_L",                                            {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_R",                                            {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUV444_PLANAR",                                {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUV444_SEMIPLANAR",                            {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUYV_422",                                     {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_UYVY_422",                                     {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_ABGR",                                         {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BGRA",                                         {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_A",                                            {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_RG",                                           {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_AYUV",                                         {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YVU444_SEMIPLANAR",                            {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YVU422_SEMIPLANAR",                            {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YVU420_SEMIPLANAR",                            {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_Y10V10U10_444_SEMIPLANAR",                     {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_Y10V10U10_420_SEMIPLANAR",                     {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_Y12V12U12_444_SEMIPLANAR",                     {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_Y12V12U12_420_SEMIPLANAR",                     {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_VYUY_ER",                                      {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_UYVY_ER",                                      {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUYV_ER",                                      {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YVYU_ER",                                      {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUV_ER",                                       {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUVA_ER",                                      {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_AYUV_ER",                                      {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUV444_PLANAR_ER",                             {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUV422_PLANAR_ER",                             {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUV420_PLANAR_ER",                             {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUV444_SEMIPLANAR_ER",                         {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUV422_SEMIPLANAR_ER",                         {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YUV420_SEMIPLANAR_ER",                         {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YVU444_PLANAR_ER",                             {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YVU422_PLANAR_ER",                             {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YVU420_PLANAR_ER",                             {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YVU444_SEMIPLANAR_ER",                         {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YVU422_SEMIPLANAR_ER",                         {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YVU420_SEMIPLANAR_ER",                         {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER_RGGB",                                   {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER_BGGR",                                   {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER_GRBG",                                   {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER_GBRG",                                   {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER10_RGGB",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER10_BGGR",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER10_GRBG",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER10_GBRG",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER12_RGGB",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER12_BGGR",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER12_GRBG",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER12_GBRG",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER14_RGGB",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER14_BGGR",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER14_GRBG",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER14_GBRG",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER20_RGGB",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER20_BGGR",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER20_GRBG",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER20_GBRG",                                 {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YVU444_PLANAR",                                {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YVU422_PLANAR",                                {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_YVU420_PLANAR",                                {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER_ISP_RGGB",                               {CUDA_92,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER_ISP_BGGR",                               {CUDA_92,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER_ISP_GRBG",                               {CUDA_92,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_BAYER_ISP_GBRG",                               {CUDA_92,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_COLOR_FORMAT_MAX",                                          {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUeglFrameType",                                                   {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUeglFrameType_enum",                                              {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_FRAME_TYPE_ARRAY",                                          {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_FRAME_TYPE_PITCH",                                          {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUeglResourceLocationFlags",                                       {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUeglResourceLocationFlags_enum",                                  {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_RESOURCE_LOCATION_SYSMEM",                                  {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_EGL_RESOURCE_LOCATION_VIDMEM",                                  {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUexternalMemoryHandleType",                                       {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUexternalMemoryHandleType_enum",                                  {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD",                         {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32",                      {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT",                  {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP",                        {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE",                    {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_RESOURCE",                    {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_RESOURCE_KMT",                {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_MEMORY_HANDLE_TYPE_NVSCIBUF",                          {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUexternalSemaphoreHandleType",                                    {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUexternalSemaphoreHandleType_enum",                               {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD",                      {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32",                   {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT",               {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D12_FENCE",                    {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D11_FENCE",                    {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_NVSCISYNC",                      {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D11_KEYED_MUTEX",              {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D11_KEYED_MUTEX_KMT",          {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_FUNC_ATTRIBUTE_MAX_DYNAMIC_SHARED_SIZE_BYTES",                  {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_FUNC_ATTRIBUTE_PREFERRED_SHARED_MEMORY_CARVEOUT",               {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUgraphNodeType",                                                  {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUgraphNodeType_enum",                                             {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_NODE_TYPE_KERNEL",                                        {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_NODE_TYPE_MEMCPY",                                        {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_NODE_TYPE_MEMSET",                                        {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_NODE_TYPE_HOST",                                          {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_NODE_TYPE_GRAPH",                                         {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_NODE_TYPE_EMPTY",                                         {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_NODE_TYPE_COUNT",                                         {CUDA_100, CUDA_0,   CUDA_110}},
  {"CUgraphExecUpdateResult",                                          {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUgraphExecUpdateResult_enum",                                     {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_EXEC_UPDATE_SUCCESS",                                     {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_EXEC_UPDATE_ERROR",                                       {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_EXEC_UPDATE_ERROR_TOPOLOGY_CHANGED",                      {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_EXEC_UPDATE_ERROR_NODE_TYPE_CHANGED",                     {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_EXEC_UPDATE_ERROR_FUNCTION_CHANGED",                      {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_EXEC_UPDATE_ERROR_PARAMETERS_CHANGED",                    {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_EXEC_UPDATE_ERROR_NOT_SUPPORTED",                         {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_TARGET_COMPUTE_80",                                             {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_TARGET_COMPUTE_75",                                             {CUDA_91,  CUDA_0,   CUDA_0  }},
  {"CU_TARGET_COMPUTE_73",                                             {CUDA_91,  CUDA_0,   CUDA_100}},
  {"CU_TARGET_COMPUTE_72",                                             {CUDA_101, CUDA_0,   CUDA_0  }},
  {"CU_TARGET_COMPUTE_70",                                             {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_TARGET_COMPUTE_62",                                             {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_TARGET_COMPUTE_61",                                             {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_TARGET_COMPUTE_60",                                             {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_TARGET_COMPUTE_53",                                             {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_TARGET_COMPUTE_13",                                             {CUDA_0,   CUDA_0,   CUDA_90 }},
  {"CU_TARGET_COMPUTE_12",                                             {CUDA_0,   CUDA_0,   CUDA_90 }},
  {"CU_TARGET_COMPUTE_11",                                             {CUDA_0,   CUDA_0,   CUDA_90 }},
  {"CU_TARGET_COMPUTE_10",                                             {CUDA_0,   CUDA_0,   CUDA_90 }},
  {"CU_LIMIT_MAX_L2_FETCH_GRANULARITY",                                {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_LIMIT_PERSISTING_L2_CACHE_SIZE",                                {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CUmem_advise",                                                     {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CUmem_advise_enum",                                                {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_MEM_ADVISE_SET_READ_MOSTLY",                                    {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_MEM_ADVISE_UNSET_READ_MOSTLY",                                  {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_MEM_ADVISE_SET_PREFERRED_LOCATION",                             {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_MEM_ADVISE_UNSET_PREFERRED_LOCATION",                           {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_MEM_ADVISE_SET_ACCESSED_BY",                                    {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_MEM_ADVISE_UNSET_ACCESSED_BY",                                  {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CUmem_range_attribute",                                            {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CUmem_range_attribute_enum",                                       {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_MEM_RANGE_ATTRIBUTE_READ_MOSTLY",                               {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_MEM_RANGE_ATTRIBUTE_PREFERRED_LOCATION",                        {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_MEM_RANGE_ATTRIBUTE_ACCESSED_BY",                               {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_MEM_RANGE_ATTRIBUTE_LAST_PREFETCH_LOCATION",                    {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_POINTER_ATTRIBUTE_IS_GPU_DIRECT_RDMA_CAPABLE",                  {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_POINTER_ATTRIBUTE_ALLOWED_HANDLE_TYPES",                        {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_POINTER_ATTRIBUTE_MAPPED",                                      {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_POINTER_ATTRIBUTE_RANGE_SIZE",                                  {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_POINTER_ATTRIBUTE_RANGE_START_ADDR",                            {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_POINTER_ATTRIBUTE_IS_LEGACY_CUDA_IPC_CAPABLE",                  {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_POINTER_ATTRIBUTE_DEVICE_ORDINAL",                              {CUDA_92,  CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_PROFILER_NOT_INITIALIZED",                              {CUDA_0,   CUDA_50,  CUDA_0  }},
  {"CUDA_ERROR_PROFILER_ALREADY_STARTED",                              {CUDA_0,   CUDA_50,  CUDA_0  }},
  {"CUDA_ERROR_PROFILER_ALREADY_STOPPED",                              {CUDA_0,   CUDA_50,  CUDA_0  }},
  {"CUDA_ERROR_CONTEXT_ALREADY_CURRENT",                               {CUDA_0,   CUDA_32,  CUDA_0  }},
  {"CUDA_ERROR_NVLINK_UNCORRECTABLE",                                  {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_JIT_COMPILER_NOT_FOUND",                                {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_ILLEGAL_STATE",                                         {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_COOPERATIVE_LAUNCH_TOO_LARGE",                          {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_SYSTEM_NOT_READY",                                      {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_SYSTEM_DRIVER_MISMATCH",                                {CUDA_101, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_COMPAT_NOT_SUPPORTED_ON_DEVICE",                        {CUDA_101, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_STREAM_CAPTURE_UNSUPPORTED",                            {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_STREAM_CAPTURE_INVALIDATED",                            {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_STREAM_CAPTURE_MERGE",                                  {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_STREAM_CAPTURE_UNMATCHED",                              {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_STREAM_CAPTURE_UNJOINED",                               {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_STREAM_CAPTURE_ISOLATION",                              {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_STREAM_CAPTURE_IMPLICIT",                               {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_CAPTURED_EVENT",                                        {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_STREAM_CAPTURE_WRONG_THREAD",                           {CUDA_101, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_TIMEOUT",                                               {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_GRAPH_EXEC_UPDATE_FAILURE",                             {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUshared_carveout",                                                {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUshared_carveout_enum",                                           {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_SHAREDMEM_CARVEOUT_DEFAULT",                                    {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_SHAREDMEM_CARVEOUT_MAX_SHARED",                                 {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_SHAREDMEM_CARVEOUT_MAX_L1",                                     {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUstreamBatchMemOpType",                                           {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CUstreamBatchMemOpType_enum",                                      {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_STREAM_MEM_OP_WAIT_VALUE_32",                                   {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_STREAM_MEM_OP_WRITE_VALUE_32",                                  {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_STREAM_MEM_OP_FLUSH_REMOTE_WRITES",                             {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_STREAM_MEM_OP_WAIT_VALUE_64",                                   {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CU_STREAM_MEM_OP_WRITE_VALUE_64",                                  {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUstreamCaptureStatus",                                            {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUstreamCaptureStatus_enum",                                       {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_STREAM_CAPTURE_STATUS_NONE",                                    {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_STREAM_CAPTURE_STATUS_ACTIVE",                                  {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CU_STREAM_CAPTURE_STATUS_INVALIDATED",                             {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUstreamCaptureMode",                                              {CUDA_101, CUDA_0,   CUDA_0  }},
  {"CUstreamCaptureMode_enum",                                         {CUDA_101, CUDA_0,   CUDA_0  }},
  {"CU_STREAM_CAPTURE_MODE_GLOBAL",                                    {CUDA_101, CUDA_0,   CUDA_0  }},
  {"CU_STREAM_CAPTURE_MODE_THREAD_LOCAL",                              {CUDA_101, CUDA_0,   CUDA_0  }},
  {"CU_STREAM_CAPTURE_MODE_RELAXED",                                   {CUDA_101, CUDA_0,   CUDA_0  }},
  {"CUstreamWaitValue_flags",                                          {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CUstreamWaitValue_flags_enum",                                     {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_STREAM_WAIT_VALUE_GEQ",                                         {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_STREAM_WAIT_VALUE_EQ",                                          {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_STREAM_WAIT_VALUE_AND",                                         {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_STREAM_WAIT_VALUE_FLUSH",                                       {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CUstreamWriteValue_flags",                                         {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CUstreamWriteValue_flags_enum",                                    {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_STREAM_WRITE_VALUE_DEFAULT",                                    {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_STREAM_WRITE_VALUE_NO_MEMORY_BARRIER",                          {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CUmemAllocationHandleType",                                        {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUmemAllocationHandleType_enum",                                   {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_HANDLE_TYPE_POSIX_FILE_DESCRIPTOR",                         {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_HANDLE_TYPE_WIN32",                                         {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_HANDLE_TYPE_WIN32_KMT",                                     {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_HANDLE_TYPE_MAX",                                           {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUmemAccess_flags",                                                {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUmemAccess_flags_enum",                                           {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_ACCESS_FLAGS_PROT_NONE",                                    {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_ACCESS_FLAGS_PROT_READ",                                    {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_ACCESS_FLAGS_PROT_READWRITE",                               {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_ACCESS_FLAGS_PROT_MAX",                                     {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUmemLocationType",                                                {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUmemLocationType_enum",                                           {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_LOCATION_TYPE_INVALID",                                     {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_LOCATION_TYPE_DEVICE",                                      {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_LOCATION_TYPE_MAX",                                         {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUmemAllocationGranularity_flags",                                 {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUmemAllocationGranularity_flags_enum",                            {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_ALLOC_GRANULARITY_MINIMUM",                                 {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_ALLOC_GRANULARITY_RECOMMENDED",                             {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUaccessProperty",                                                 {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CUaccessProperty_enum",                                            {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_ACCESS_PROPERTY_NORMAL",                                        {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_ACCESS_PROPERTY_STREAMING",                                     {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_ACCESS_PROPERTY_PERSISTING",                                    {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CUsynchronizationPolicy",                                          {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CUsynchronizationPolicy_enum",                                     {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_SYNC_POLICY_AUTO",                                              {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_SYNC_POLICY_SPIN",                                              {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_SYNC_POLICY_YIELD",                                             {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_SYNC_POLICY_BLOCKING_SYNC",                                     {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CUkernelNodeAttrID",                                               {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CUkernelNodeAttrID_enum",                                          {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_KERNEL_NODE_ATTRIBUTE_ACCESS_POLICY_WINDOW",                    {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_KERNEL_NODE_ATTRIBUTE_COOPERATIVE",                             {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CUstreamAttrID",                                                   {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CUstreamAttrID_enum",                                              {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_STREAM_ATTRIBUTE_ACCESS_POLICY_WINDOW",                         {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_STREAM_ATTRIBUTE_SYNCHRONIZATION_POLICY",                       {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CUhostFn",                                                         {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUmemGenericAllocationHandle",                                     {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_CPU",                                                    {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_INVALID",                                                {CUDA_80,  CUDA_0,   CUDA_0  }},
  {"CU_MEMHOSTREGISTER_IOMEMORY",                                      {CUDA_75,  CUDA_0,   CUDA_0  }},
  {"CUDA_ARRAY3D_COLOR_ATTACHMENT",                                    {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_COOPERATIVE_LAUNCH_MULTI_DEVICE_NO_PRE_LAUNCH_SYNC",          {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUDA_COOPERATIVE_LAUNCH_MULTI_DEVICE_NO_POST_LAUNCH_SYNC",         {CUDA_90,  CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_MEMORY_DEDICATED",                                   {CUDA_100, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_SEMAPHORE_SIGNAL_SKIP_NVSCIBUF_MEMSYNC",             {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_SEMAPHORE_WAIT_SKIP_NVSCIBUF_MEMSYNC",               {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUDA_NVSCISYNC_ATTR_SIGNAL",                                       {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUDA_NVSCISYNC_ATTR_WAIT",                                         {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_TRSF_DISABLE_TRILINEAR_OPTIMIZATION",                           {CUDA_110, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_SHARED_MEMORY_PER_BLOCK",                      {CUDA_0,   CUDA_50,  CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_GPU_OVERLAP",                                  {CUDA_0,   CUDA_50,  CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_WIDTH",                {CUDA_0,   CUDA_50,  CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_HEIGHT",               {CUDA_0,   CUDA_50,  CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_NUMSLICES",            {CUDA_0,   CUDA_50,  CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_CAN_TEX2D_GATHER",                             {CUDA_0,   CUDA_50,  CUDA_0  }},
  {"CU_DEVICE_P2P_ATTRIBUTE_ARRAY_ACCESS_ACCESS_SUPPORTED",            {CUDA_0,   CUDA_100, CUDA_101}},
  {"CUDA_ARRAY3D_2DARRAY",                                             {CUDA_0,   CUDA_50,  CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_REGISTERS_PER_BLOCK",                          {CUDA_0,   CUDA_50,  CUDA_0  }},
  {"CUevent_record_flags",                                             {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUevent_record_flags_enum",                                        {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_EVENT_RECORD_DEFAULT",                                          {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_EVENT_RECORD_EXTERNAL",                                         {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUevent_wait_flags",                                               {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_EVENT_WAIT_DEFAULT",                                            {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_EVENT_WAIT_EXTERNAL",                                           {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_SPARSE_CUDA_ARRAY_SUPPORTED",                  {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_READ_ONLY_HOST_REGISTER_SUPPORTED",            {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_POINTER_ATTRIBUTE_ACCESS_FLAGS",                                {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_TARGET_COMPUTE_86",                                             {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_NODE_TYPE_WAIT_EVENT",                                    {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_NODE_TYPE_EVENT_RECORD",                                  {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_STUB_LIBRARY",                                          {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_DEVICE_NOT_LICENSED",                                   {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_UNSUPPORTED_PTX_VERSION",                               {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_MEMHOSTREGISTER_READ_ONLY",                                     {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_ARRAY_SPARSE_PROPERTIES_SINGLE_MIPTAIL",                        {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUDA_ARRAY_SPARSE_PROPERTIES_st",                                  {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUDA_ARRAY_SPARSE_PROPERTIES",                                     {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUDA_POINTER_ATTRIBUTE_ACCESS_FLAGS",                              {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUDA_POINTER_ATTRIBUTE_ACCESS_FLAGS_enum",                         {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_POINTER_ATTRIBUTE_ACCESS_FLAG_NONE",                            {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_POINTER_ATTRIBUTE_ACCESS_FLAG_READ",                            {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_POINTER_ATTRIBUTE_ACCESS_FLAG_READWRITE",                       {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUarraySparseSubresourceType",                                     {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUarraySparseSubresourceType_enum",                                {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_ARRAY_SPARSE_SUBRESOURCE_TYPE_SPARSE_LEVEL",                    {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_ARRAY_SPARSE_SUBRESOURCE_TYPE_MIPTAIL",                         {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUmemOperationType",                                               {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUmemOperationType_enum",                                          {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_MEM_OPERATION_TYPE_MAP",                                        {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_MEM_OPERATION_TYPE_UNMAP",                                      {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUmemHandleType",                                                  {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUmemHandleType_enum",                                             {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_MEM_HANDLE_TYPE_GENERIC",                                       {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUarrayMapInfo",                                                   {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUarrayMapInfo_st",                                                {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CU_MEM_CREATE_USAGE_TILE_POOL",                                    {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUDA_ARRAY3D_SPARSE",                                              {CUDA_111, CUDA_0,   CUDA_0  }},
  {"CUmemPoolHandle_st",                                               {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CUmemoryPool",                                                     {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CU_AD_FORMAT_NV12",                                                {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LINEAR_WIDTH",               {CUDA_0,   CUDA_112, CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_VIRTUAL_MEMORY_MANAGEMENT_SUPPORTED",          {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_TIMELINE_SEMAPHORE_INTEROP_SUPPORTED",         {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_MEMORY_POOLS_SUPPORTED",                       {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_NODE_TYPE_EXT_SEMAS_SIGNAL",                              {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_NODE_TYPE_EXT_SEMAS_WAIT",                                {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CUDA_ERROR_JIT_COMPILATION_DISABLED",                              {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_FD",          {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_WIN32",       {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CUDA_EXT_SEM_SIGNAL_NODE_PARAMS_st",                               {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CUDA_EXT_SEM_SIGNAL_NODE_PARAMS",                                  {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CUDA_EXT_SEM_WAIT_NODE_PARAMS_st",                                 {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CUDA_EXT_SEM_WAIT_NODE_PARAMS",                                    {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CU_MEM_HANDLE_TYPE_NONE",                                          {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_EXEC_UPDATE_ERROR_UNSUPPORTED_FUNCTION_CHANGE",           {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CUmemPool_attribute",                                              {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CUmemPool_attribute_enum",                                         {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CU_MEMPOOL_ATTR_REUSE_FOLLOW_EVENT_DEPENDENCIES",                  {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CU_MEMPOOL_ATTR_REUSE_ALLOW_OPPORTUNISTIC",                        {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CU_MEMPOOL_ATTR_REUSE_ALLOW_INTERNAL_DEPENDENCIES",                {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CU_MEMPOOL_ATTR_RELEASE_THRESHOLD",                                {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CUmemPoolProps_st",                                                {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CUmemPoolProps",                                                   {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CUmemPoolPtrExportData_st",                                        {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CUmemPoolPtrExportData",                                           {CUDA_112, CUDA_0,   CUDA_0  }},
  {"CUmemAllocationType",                                              {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUmemAllocationType_enum",                                         {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_ALLOCATION_TYPE_INVALID",                                   {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_ALLOCATION_TYPE_PINNED",                                    {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CU_MEM_ALLOCATION_TYPE_MAX",                                       {CUDA_102, CUDA_0,   CUDA_0  }},
  {"CUdeviceptr_v2",                                                   {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUdevice_v1",                                                      {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUtexObject_v1",                                                   {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUsurfObject_v1",                                                  {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUuserObject_st",                                                  {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUuserObject",                                                     {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUipcEventHandle_v1",                                              {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUipcMemHandle_v1",                                                {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUstreamBatchMemOpParams_v1",                                      {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUstreamUpdateCaptureDependencies_flags",                          {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUstreamUpdateCaptureDependencies_flags_enum",                     {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_STREAM_ADD_CAPTURE_DEPENDENCIES",                               {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_STREAM_SET_CAPTURE_DEPENDENCIES",                               {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_GPU_DIRECT_RDMA_SUPPORTED",                    {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_GPU_DIRECT_RDMA_FLUSH_WRITES_OPTIONS",         {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_GPU_DIRECT_RDMA_WRITES_ORDERING",              {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_DEVICE_ATTRIBUTE_MEMPOOL_SUPPORTED_HANDLE_TYPES",               {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUdevprop_v1",                                                     {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_POINTER_ATTRIBUTE_MEMPOOL_HANDLE",                              {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_KERNEL_NODE_PARAMS_v1",                                       {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_MEMSET_NODE_PARAMS_v1",                                       {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_HOST_NODE_PARAMS_v1",                                         {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUkernelNodeAttrValue_v1",                                         {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUstreamAttrValue_v1",                                             {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUdriverProcAddress_flags",                                        {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUdriverProcAddress_flags_enum",                                   {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GET_PROC_ADDRESS_DEFAULT",                                      {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GET_PROC_ADDRESS_LEGACY_STREAM",                                {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GET_PROC_ADDRESS_PER_THREAD_DEFAULT_STREAM",                    {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_MEMCPY2D_v2",                                                 {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_MEMCPY3D_v2",                                                 {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_MEMCPY3D_PEER_v1",                                            {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_ARRAY_DESCRIPTOR_v2",                                         {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_ARRAY3D_DESCRIPTOR_v2",                                       {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_ARRAY_SPARSE_PROPERTIES_v1",                                  {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_RESOURCE_DESC_v1",                                            {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_TEXTURE_DESC_v1",                                             {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_RESOURCE_VIEW_DESC_v1",                                       {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_POINTER_ATTRIBUTE_P2P_TOKENS_v1",                             {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_LAUNCH_PARAMS_v1",                                            {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_MEMORY_HANDLE_DESC_v1",                              {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_MEMORY_BUFFER_DESC_v1",                              {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC_v1",                     {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC_v1",                           {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS_v1",                         {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS_v1",                           {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_EXT_SEM_SIGNAL_NODE_PARAMS_v1",                               {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUDA_EXT_SEM_WAIT_NODE_PARAMS_v1",                                 {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUmemGenericAllocationHandle_v1",                                  {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUarrayMapInfo_v1",                                                {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUmemLocation_v1",                                                 {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUmemAllocationProp_v1",                                           {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUmemAccessDesc_v1",                                               {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_MEMPOOL_ATTR_RESERVED_MEM_CURRENT",                             {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_MEMPOOL_ATTR_RESERVED_MEM_HIGH",                                {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_MEMPOOL_ATTR_USED_MEM_CURRENT",                                 {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_MEMPOOL_ATTR_USED_MEM_HIGH",                                    {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUmemPoolProps_v1",                                                {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUmemPoolPtrExportData_v1",                                        {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUflushGPUDirectRDMAWritesOptions",                                {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUflushGPUDirectRDMAWritesOptions_enum",                           {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_FLUSH_GPU_DIRECT_RDMA_WRITES_OPTION_HOST",                      {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_FLUSH_GPU_DIRECT_RDMA_WRITES_OPTION_MEMOPS",                    {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUGPUDirectRDMAWritesOrdering",                                    {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUGPUDirectRDMAWritesOrdering_enum",                               {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GPU_DIRECT_RDMA_WRITES_ORDERING_NONE",                          {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GPU_DIRECT_RDMA_WRITES_ORDERING_OWNER",                         {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GPU_DIRECT_RDMA_WRITES_ORDERING_ALL_DEVICES",                   {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUflushGPUDirectRDMAWritesScope",                                  {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUflushGPUDirectRDMAWritesScope_enum",                             {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_FLUSH_GPU_DIRECT_RDMA_WRITES_TO_OWNER",                         {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_FLUSH_GPU_DIRECT_RDMA_WRITES_TO_ALL_DEVICES",                   {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUflushGPUDirectRDMAWritesTarget",                                 {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUflushGPUDirectRDMAWritesTarget_enum",                            {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_FLUSH_GPU_DIRECT_RDMA_WRITES_TARGET_CURRENT_CTX",               {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUgraphDebugDot_flags",                                            {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUgraphDebugDot_flags_enum",                                       {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_DEBUG_DOT_FLAGS_VERBOSE",                                 {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_DEBUG_DOT_FLAGS_RUNTIME_TYPES",                           {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_DEBUG_DOT_FLAGS_KERNEL_NODE_PARAMS",                      {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_DEBUG_DOT_FLAGS_MEMCPY_NODE_PARAMS",                      {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_DEBUG_DOT_FLAGS_MEMSET_NODE_PARAMS",                      {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_DEBUG_DOT_FLAGS_HOST_NODE_PARAMS",                        {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_DEBUG_DOT_FLAGS_EVENT_NODE_PARAMS",                       {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_DEBUG_DOT_FLAGS_EXT_SEMAS_SIGNAL_NODE_PARAMS",            {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_DEBUG_DOT_FLAGS_EXT_SEMAS_WAIT_NODE_PARAMS",              {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_DEBUG_DOT_FLAGS_KERNEL_NODE_ATTRIBUTES",                  {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_DEBUG_DOT_FLAGS_HANDLES",                                 {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUuserObject_flags",                                               {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUuserObject_flags_enum",                                          {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_USER_OBJECT_NO_DESTRUCTOR_SYNC",                                {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUuserObjectRetain_flags",                                         {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CUuserObjectRetain_flags_enum",                                    {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_GRAPH_USER_OBJECT_MOVE",                                        {CUDA_113, CUDA_0,   CUDA_0  }},
  {"CU_STREAM_WAIT_VALUE_NOR",                                         {CUDA_90,  CUDA_0,   CUDA_0  }},
};

const std::map<llvm::StringRef, hipAPIversions> HIP_DRIVER_TYPE_NAME_VER_MAP {
  {"HIP_LAUNCH_PARAM_BUFFER_POINTER",                                  {HIP_1060, HIP_0,    HIP_0   }},
  {"HIP_LAUNCH_PARAM_BUFFER_SIZE",                                     {HIP_1060, HIP_0,    HIP_0   }},
  {"HIP_LAUNCH_PARAM_END",                                             {HIP_1060, HIP_0,    HIP_0   }},
  {"hipCtx_t",                                                         {HIP_1060, HIP_0,    HIP_0   }},
  {"ihipCtx_t",                                                        {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDevice_t",                                                      {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceP2PAttr",                                                 {HIP_3080, HIP_0,    HIP_0   }},
  {"hipDevP2PAttrPerformanceRank",                                     {HIP_3080, HIP_0,    HIP_0   }},
  {"hipDevP2PAttrAccessSupported",                                     {HIP_3080, HIP_0,    HIP_0   }},
  {"hipDevP2PAttrNativeAtomicSupported",                               {HIP_3080, HIP_0,    HIP_0   }},
  {"hipDevP2PAttrHipArrayAccessSupported",                             {HIP_3080, HIP_0,    HIP_0   }},
  {"hipStream_t",                                                      {HIP_1050, HIP_0,    HIP_0   }},
  {"ihipStream_t",                                                     {HIP_1050, HIP_0,    HIP_0   }},
  {"hipIpcMemLazyEnablePeerAccess",                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"HIP_IPC_HANDLE_SIZE",                                              {HIP_1060, HIP_0,    HIP_0   }},
  {"hipIpcMemHandle_st",                                               {HIP_1060, HIP_0,    HIP_0   }},
  {"hipIpcMemHandle_t",                                                {HIP_1060, HIP_0,    HIP_0   }},
  {"hipIpcEventHandle_st",                                             {HIP_3050, HIP_0,    HIP_0   }},
  {"hipIpcEventHandle_t",                                              {HIP_1060, HIP_0,    HIP_0   }},
  {"hipModule_t",                                                      {HIP_1060, HIP_0,    HIP_0   }},
  {"ihipModule_t",                                                     {HIP_1060, HIP_0,    HIP_0   }},
  {"hipFunction_t",                                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"ihipModuleSymbol_t",                                               {HIP_1060, HIP_0,    HIP_0   }},
  {"hipFuncAttributes",                                                {HIP_1090, HIP_0,    HIP_0   }},
  {"hipEvent_t",                                                       {HIP_1060, HIP_0,    HIP_0   }},
  {"ihipEvent_t",                                                      {HIP_1060, HIP_0,    HIP_0   }},
  {"hipLimit_t",                                                       {HIP_1060, HIP_0,    HIP_0   }},
  {"hipLimitMallocHeapSize",                                           {HIP_1060, HIP_0,    HIP_0   }},
  {"hipStreamDefault",                                                 {HIP_1060, HIP_0,    HIP_0   }},
  {"hipStreamNonBlocking",                                             {HIP_1060, HIP_0,    HIP_0   }},
  {"hipEventDefault",                                                  {HIP_1060, HIP_0,    HIP_0   }},
  {"hipEventBlockingSync",                                             {HIP_1060, HIP_0,    HIP_0   }},
  {"hipEventDisableTiming",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipEventInterprocess",                                             {HIP_1060, HIP_0,    HIP_0   }},
  {"hipEventReleaseToDevice",                                          {HIP_1060, HIP_0,    HIP_0   }},
  {"hipEventReleaseToSystem",                                          {HIP_1060, HIP_0,    HIP_0   }},
  {"hipHostMallocDefault",                                             {HIP_1060, HIP_0,    HIP_0   }},
  {"hipHostMallocMapped",                                              {HIP_1060, HIP_0,    HIP_0   }},
  {"hipHostMallocPortable",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipHostMallocWriteCombined",                                       {HIP_1060, HIP_0,    HIP_0   }},
  {"hipMemAttachGlobal",                                               {HIP_2050, HIP_0,    HIP_0   }},
  {"hipMemAttachHost",                                                 {HIP_2050, HIP_0,    HIP_0   }},
  {"hipMemAttachSingle",                                               {HIP_3070, HIP_0,    HIP_0   }},
  {"hipHostRegisterPortable",                                          {HIP_1060, HIP_0,    HIP_0   }},
  {"hipHostRegisterMapped",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipHostRegisterIoMemory",                                          {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceScheduleAuto",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceScheduleSpin",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceScheduleYield",                                           {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceScheduleBlockingSync",                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceScheduleMask",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceMapHost",                                                 {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceLmemResizeToMax",                                         {HIP_1060, HIP_0,    HIP_0   }},
  {"hipArrayLayered",                                                  {HIP_1070, HIP_0,    HIP_0   }},
  {"hipArraySurfaceLoadStore",                                         {HIP_1070, HIP_0,    HIP_0   }},
  {"hipArrayCubemap",                                                  {HIP_1070, HIP_0,    HIP_0   }},
  {"hipArrayTextureGather",                                            {HIP_1070, HIP_0,    HIP_0   }},
  {"hipOccupancyDefault",                                              {HIP_3020, HIP_0,    HIP_0   }},
  {"hipCooperativeLaunchMultiDeviceNoPreSync",                         {HIP_3020, HIP_0,    HIP_0   }},
  {"hipCooperativeLaunchMultiDeviceNoPostSync",                        {HIP_3020, HIP_0,    HIP_0   }},
  {"hipCpuDeviceId",                                                   {HIP_3070, HIP_0,    HIP_0   }},
  {"hipInvalidDeviceId",                                               {HIP_3070, HIP_0,    HIP_0   }},
  {"hipMemoryAdvise",                                                  {HIP_3070, HIP_0,    HIP_0   }},
  {"hipMemAdviseSetReadMostly",                                        {HIP_3070, HIP_0,    HIP_0   }},
  {"hipMemAdviseUnsetReadMostly",                                      {HIP_3070, HIP_0,    HIP_0   }},
  {"hipMemAdviseSetPreferredLocation",                                 {HIP_3070, HIP_0,    HIP_0   }},
  {"hipMemAdviseUnsetPreferredLocation",                               {HIP_3070, HIP_0,    HIP_0   }},
  {"hipMemAdviseSetAccessedBy",                                        {HIP_3070, HIP_0,    HIP_0   }},
  {"hipMemAdviseUnsetAccessedBy",                                      {HIP_3070, HIP_0,    HIP_0   }},
  {"hipMemRangeAttribute",                                             {HIP_3070, HIP_0,    HIP_0   }},
  {"hipMemRangeAttributeReadMostly",                                   {HIP_3070, HIP_0,    HIP_0   }},
  {"hipMemRangeAttributePreferredLocation",                            {HIP_3070, HIP_0,    HIP_0   }},
  {"hipMemRangeAttributeAccessedBy",                                   {HIP_3070, HIP_0,    HIP_0   }},
  {"hipMemRangeAttributeLastPrefetchLocation",                         {HIP_3070, HIP_0,    HIP_0   }},
  {"hipJitOption",                                                     {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionMaxRegisters",                                         {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionThreadsPerBlock",                                      {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionWallTime",                                             {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionInfoLogBuffer",                                        {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionInfoLogBufferSizeBytes",                               {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionErrorLogBuffer",                                       {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionErrorLogBufferSizeBytes",                              {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionOptimizationLevel",                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionTargetFromContext",                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionTarget",                                               {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionFallbackStrategy",                                     {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionGenerateDebugInfo",                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionLogVerbose",                                           {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionGenerateLineInfo",                                     {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionCacheMode",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionSm3xOpt",                                              {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionFastCompile",                                          {HIP_1060, HIP_0,    HIP_0   }},
  {"hipJitOptionNumOptions",                                           {HIP_1060, HIP_0,    HIP_0   }},
  {"hipFuncCache_t",                                                   {HIP_1060, HIP_0,    HIP_0   }},
  {"hipFuncCachePreferNone",                                           {HIP_1060, HIP_0,    HIP_0   }},
  {"hipFuncCachePreferShared",                                         {HIP_1060, HIP_0,    HIP_0   }},
  {"hipFuncCachePreferL1",                                             {HIP_1060, HIP_0,    HIP_0   }},
  {"hipFuncCachePreferEqual",                                          {HIP_1060, HIP_0,    HIP_0   }},
  {"hipSharedMemConfig",                                               {HIP_1060, HIP_0,    HIP_0   }},
  {"hipSharedMemBankSizeDefault",                                      {HIP_1060, HIP_0,    HIP_0   }},
  {"hipSharedMemBankSizeFourByte",                                     {HIP_1060, HIP_0,    HIP_0   }},
  {"hipSharedMemBankSizeEightByte",                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceptr_t",                                                   {HIP_1070, HIP_0,    HIP_0   }},
  {"HIP_TRSA_OVERRIDE_FORMAT",                                         {HIP_1070, HIP_0,    HIP_0   }},
  {"HIP_TRSF_READ_AS_INTEGER",                                         {HIP_1070, HIP_0,    HIP_0   }},
  {"HIP_TRSF_NORMALIZED_COORDINATES",                                  {HIP_1070, HIP_0,    HIP_0   }},
  {"HIP_TRSF_SRGB",                                                    {HIP_3020, HIP_0,    HIP_0   }},
  {"hipArray_Format",                                                  {HIP_1070, HIP_0,    HIP_0   }},
  {"HIP_AD_FORMAT_UNSIGNED_INT8",                                      {HIP_1070, HIP_0,    HIP_0   }},
  {"HIP_AD_FORMAT_UNSIGNED_INT16",                                     {HIP_1070, HIP_0,    HIP_0   }},
  {"HIP_AD_FORMAT_UNSIGNED_INT32",                                     {HIP_1070, HIP_0,    HIP_0   }},
  {"HIP_AD_FORMAT_SIGNED_INT8",                                        {HIP_1070, HIP_0,    HIP_0   }},
  {"HIP_AD_FORMAT_SIGNED_INT16",                                       {HIP_1070, HIP_0,    HIP_0   }},
  {"HIP_AD_FORMAT_SIGNED_INT32",                                       {HIP_1070, HIP_0,    HIP_0   }},
  {"HIP_AD_FORMAT_HALF",                                               {HIP_1070, HIP_0,    HIP_0   }},
  {"HIP_AD_FORMAT_FLOAT",                                              {HIP_1070, HIP_0,    HIP_0   }},
  {"HIP_ARRAY_DESCRIPTOR",                                             {HIP_1070, HIP_0,    HIP_0   }},
  {"HIP_ARRAY3D_DESCRIPTOR",                                           {HIP_2070, HIP_0,    HIP_0   }},
  {"hipArray",                                                         {HIP_1070, HIP_0,    HIP_0   }},
  {"hip_Memcpy2D",                                                     {HIP_1070, HIP_0,    HIP_0   }},
  {"hipArray_t",                                                       {HIP_1070, HIP_0,    HIP_0   }},
  {"hipMipmappedArray",                                                {HIP_1070, HIP_0,    HIP_0   }},
  {"hipMipmappedArray_t",                                              {HIP_1070, HIP_0,    HIP_0   }},
  {"HIPresourcetype_enum",                                             {HIP_3050, HIP_0,    HIP_0   }},
  {"HIPresourcetype",                                                  {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RESOURCE_TYPE_ARRAY",                                          {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RESOURCE_TYPE_MIPMAPPED_ARRAY",                                {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RESOURCE_TYPE_LINEAR",                                         {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RESOURCE_TYPE_PITCH2D",                                        {HIP_3050, HIP_0,    HIP_0   }},
  {"HIPfilter_mode_enum",                                              {HIP_3050, HIP_0,    HIP_0   }},
  {"HIPfilter_mode",                                                   {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_TR_FILTER_MODE_POINT",                                         {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_TR_FILTER_MODE_LINEAR",                                        {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_TEXTURE_DESC",                                                 {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_TEXTURE_DESC_st",                                              {HIP_3050, HIP_0,    HIP_0   }},
  {"HIPresourceViewFormat_enum",                                       {HIP_3050, HIP_0,    HIP_0   }},
  {"HIPresourceViewFormat",                                            {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_NONE",                                         {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UINT_1X8",                                     {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UINT_2X8",                                     {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UINT_4X8",                                     {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_SINT_1X8",                                     {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_SINT_2X8",                                     {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_SINT_4X8",                                     {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UINT_1X16",                                    {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UINT_2X16",                                    {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UINT_4X16",                                    {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_SINT_1X16",                                    {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_SINT_2X16",                                    {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_SINT_4X16",                                    {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_SINT_4X16",                                    {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UINT_1X32",                                    {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UINT_2X32",                                    {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UINT_4X32",                                    {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_SINT_1X32",                                    {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_SINT_2X32",                                    {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_SINT_4X32",                                    {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_FLOAT_1X16",                                   {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_FLOAT_2X16",                                   {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_FLOAT_4X16",                                   {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_FLOAT_1X32",                                   {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_FLOAT_2X32",                                   {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_FLOAT_4X32",                                   {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UNSIGNED_BC1",                                 {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UNSIGNED_BC2",                                 {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UNSIGNED_BC3",                                 {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UNSIGNED_BC4",                                 {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_SIGNED_BC4",                                   {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UNSIGNED_BC5",                                 {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_SIGNED_BC5",                                   {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UNSIGNED_BC6H",                                {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_SIGNED_BC6H",                                  {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RES_VIEW_FORMAT_UNSIGNED_BC7",                                 {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RESOURCE_DESC_st",                                             {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RESOURCE_DESC",                                                {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RESOURCE_VIEW_DESC_st",                                        {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_RESOURCE_VIEW_DESC",                                           {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_MEMCPY3D",                                                     {HIP_3020, HIP_0,    HIP_0   }},
  {"hipFunction_attribute",                                            {HIP_2080, HIP_0,    HIP_0   }},
  {"HIP_FUNC_ATTRIBUTE_MAX_THREADS_PER_BLOCK",                         {HIP_2080, HIP_0,    HIP_0   }},
  {"HIP_FUNC_ATTRIBUTE_SHARED_SIZE_BYTES",                             {HIP_2080, HIP_0,    HIP_0   }},
  {"HIP_FUNC_ATTRIBUTE_CONST_SIZE_BYTES",                              {HIP_2080, HIP_0,    HIP_0   }},
  {"HIP_FUNC_ATTRIBUTE_LOCAL_SIZE_BYTES",                              {HIP_2080, HIP_0,    HIP_0   }},
  {"HIP_FUNC_ATTRIBUTE_NUM_REGS",                                      {HIP_2080, HIP_0,    HIP_0   }},
  {"HIP_FUNC_ATTRIBUTE_PTX_VERSION",                                   {HIP_2080, HIP_0,    HIP_0   }},
  {"HIP_FUNC_ATTRIBUTE_BINARY_VERSION",                                {HIP_2080, HIP_0,    HIP_0   }},
  {"HIP_FUNC_ATTRIBUTE_CACHE_MODE_CA",                                 {HIP_2080, HIP_0,    HIP_0   }},
  {"HIP_FUNC_ATTRIBUTE_MAX_DYNAMIC_SHARED_SIZE_BYTES",                 {HIP_2080, HIP_0,    HIP_0   }},
  {"HIP_FUNC_ATTRIBUTE_PREFERRED_SHARED_MEMORY_CARVEOUT",              {HIP_2080, HIP_0,    HIP_0   }},
  {"HIP_FUNC_ATTRIBUTE_MAX",                                           {HIP_2080, HIP_0,    HIP_0   }},
  {"hipComputeMode",                                                   {HIP_1090, HIP_0,    HIP_0   }},
  {"hipComputeModeDefault",                                            {HIP_1090, HIP_0,    HIP_0   }},
  {"hipComputeModeExclusive",                                          {HIP_1090, HIP_0,    HIP_0   }},
  {"hipComputeModeProhibited",                                         {HIP_1090, HIP_0,    HIP_0   }},
  {"hipComputeModeExclusiveProcess",                                   {HIP_2000, HIP_0,    HIP_0   }},
  {"hipTextureObject_t",                                               {HIP_1070, HIP_0,    HIP_0   }},
  {"hipError_t",                                                       {HIP_1050, HIP_0,    HIP_0   }},
  {"hipDeviceProp_t",                                                  {HIP_1060, HIP_0,    HIP_0   }},
  {"hipMemoryType",                                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipMemoryTypeArray",                                               {HIP_1070, HIP_0,    HIP_0   }},
  {"hipMemoryTypeDevice",                                              {HIP_1060, HIP_0,    HIP_0   }},
  {"hipMemoryTypeHost",                                                {HIP_1060, HIP_0,    HIP_0   }},
  {"hipMemoryTypeUnified",                                             {HIP_1060, HIP_0,    HIP_0   }},
  {"hipSuccess",                                                       {HIP_1050, HIP_0,    HIP_0   }},
  {"hipErrorInvalidValue",                                             {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorOutOfMemory",                                              {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorNotInitialized",                                           {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorDeinitialized",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorProfilerDisabled",                                         {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorProfilerNotInitialized",                                   {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorProfilerAlreadyStarted",                                   {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorProfilerAlreadyStopped",                                   {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorNoDevice",                                                 {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorInvalidDevice",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorInvalidImage",                                             {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorInvalidContext",                                           {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorContextAlreadyCurrent",                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorMapFailed",                                                {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorUnmapFailed",                                              {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorArrayIsMapped",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorAlreadyMapped",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorNoBinaryForGpu",                                           {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorAlreadyAcquired",                                          {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorNotMapped",                                                {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorNotMappedAsArray",                                         {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorNotMappedAsPointer",                                       {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorECCNotCorrectable",                                        {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorUnsupportedLimit",                                         {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorContextAlreadyInUse",                                      {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorPeerAccessUnsupported",                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorInvalidKernelFile",                                        {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorInvalidGraphicsContext",                                   {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorInvalidSource",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorFileNotFound",                                             {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorSharedObjectSymbolNotFound",                               {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorSharedObjectInitFailed",                                   {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorOperatingSystem",                                          {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorInvalidHandle",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorNotFound",                                                 {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorNotReady",                                                 {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorIllegalAddress",                                           {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorLaunchOutOfResources",                                     {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorLaunchTimeOut",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorPeerAccessAlreadyEnabled",                                 {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorPeerAccessNotEnabled",                                     {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorSetOnActiveProcess",                                       {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorAssert",                                                   {HIP_1090, HIP_0,    HIP_0   }},
  {"hipErrorHostMemoryAlreadyRegistered",                              {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorHostMemoryNotRegistered",                                  {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorLaunchFailure",                                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorCooperativeLaunchTooLarge",                                {HIP_3020, HIP_0,    HIP_0   }},
  {"hipErrorNotSupported",                                             {HIP_1060, HIP_0,    HIP_0   }},
  {"hipErrorUnknown",                                                  {HIP_1060, HIP_0,    HIP_0   }},
  {"HIPaddress_mode",                                                  {HIP_3050, HIP_0,    HIP_0   }},
  {"HIPaddress_mode_enum",                                             {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_TR_ADDRESS_MODE_BORDER",                                       {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_TR_ADDRESS_MODE_CLAMP",                                        {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_TR_ADDRESS_MODE_MIRROR",                                       {HIP_3050, HIP_0,    HIP_0   }},
  {"HIP_TR_ADDRESS_MODE_WRAP",                                         {HIP_3050, HIP_0,    HIP_0   }},
  {"textureReference",                                                 {HIP_1060, HIP_0,    HIP_0   }},
  {"__HIPCC__",                                                        {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttribute_t",                                             {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxThreadsPerBlock",                             {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxBlockDimX",                                   {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxBlockDimY",                                   {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxBlockDimZ",                                   {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxGridDimX",                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxGridDimY",                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxGridDimZ",                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxSharedMemoryPerBlock",                        {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeTotalConstantMemory",                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeWarpSize",                                       {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxRegistersPerBlock",                           {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeClockRate",                                      {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMemoryClockRate",                                {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMemoryBusWidth",                                 {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMultiprocessorCount",                            {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeComputeMode",                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeL2CacheSize",                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxThreadsPerMultiProcessor",                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeComputeCapabilityMajor",                         {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeComputeCapabilityMinor",                         {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeConcurrentKernels",                              {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributePciBusId",                                       {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributePciDeviceId",                                    {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxSharedMemoryPerMultiprocessor",               {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeIsMultiGpuBoard",                                {HIP_1060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeIntegrated",                                     {HIP_1090, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeCooperativeLaunch",                              {HIP_2060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeCooperativeMultiDeviceLaunch",                   {HIP_2060, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxTexture1DWidth",                              {HIP_2070, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxTexture2DWidth",                              {HIP_2070, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxTexture2DHeight",                             {HIP_2070, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxTexture3DWidth",                              {HIP_2070, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxTexture3DHeight",                             {HIP_2070, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxTexture3DDepth",                              {HIP_2070, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeMaxPitch",                                       {HIP_2100, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeTextureAlignment",                               {HIP_2100, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeTexturePitchAlignment",                          {HIP_3020, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeKernelExecTimeout",                              {HIP_2100, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeCanMapHostMemory",                               {HIP_2100, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeEccEnabled",                                     {HIP_2100, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeManagedMemory",                                  {HIP_3100, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeDirectManagedMemAccessFromHost",                 {HIP_3100, HIP_0,    HIP_0   }},
  {"hipDeviceAttributeConcurrentManagedAccess",                        {HIP_3100, HIP_0,    HIP_0   }},
  {"hipDeviceAttributePageableMemoryAccess",                           {HIP_3100, HIP_0,    HIP_0   }},
  {"hipDeviceAttributePageableMemoryAccessUsesHostPageTables",         {HIP_3100, HIP_0,    HIP_0   }},
  {"hipStreamWaitValueGte",                                            {HIP_4020, HIP_0,    HIP_0   }},
  {"hipStreamWaitValueEq",                                             {HIP_4020, HIP_0,    HIP_0   }},
  {"hipStreamWaitValueAnd",                                            {HIP_4020, HIP_0,    HIP_0   }},
  {"hipStreamWaitValueNor",                                            {HIP_4020, HIP_0,    HIP_0   }},
};
