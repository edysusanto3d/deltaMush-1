#include <maya/MPxGPUDeformer.h>
#include <maya/MGPUDeformerRegistry.h>
#include <maya/MOpenCLInfo.h>
#include <clew/clew_cl.h>

#ifndef __DELTA_MUSH_OPENCL__
#define __DELTA_MUSH_OPENCL__
// The GPU override implementation of the identityNode
//
class DeltaMushOpencl: public MPxGPUDeformer
{
public:
    static MGPUDeformerRegistrationInfo* getGPUDeformerInfo();
    static bool validateNode(MDataBlock& block, const MEvaluationNode&, 
                             const MPlug& plug, MStringArray* messages);
    // Virtual methods from MPxGPUDeformer
    DeltaMushOpencl();
    virtual ~DeltaMushOpencl();
    // Implementation of MPxGPUDeformer.
    virtual MPxGPUDeformer::DeformerStatus evaluate(MDataBlock&, const MEvaluationNode&, 
                                                    const MPlug& plug, unsigned int, const MAutoCLMem, 
                                                    const MAutoCLEvent, MAutoCLMem, MAutoCLEvent&);
    virtual void terminate();
private:
    // Kernel
    MAutoCLKernel fKernel;
    size_t fLocalWorkSize;
    size_t fGlobalWorkSize;
};


// registration information for the identity GPU deformer.
class DeltaMushOpenclInfo : public MGPUDeformerRegistrationInfo
{
public:
    DeltaMushOpenclInfo(){}
    virtual ~DeltaMushOpenclInfo(){}
    virtual MPxGPUDeformer* createGPUDeformer()
    {
        return new DeltaMushOpencl();
    }
    virtual bool validateNode(MDataBlock& block, const MEvaluationNode& evaluationNode, const MPlug& plug, MStringArray* messages)
    {
        return DeltaMushOpencl::validateNode(block, evaluationNode, plug, messages);
    }
};
#endif
