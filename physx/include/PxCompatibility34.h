// PxCompatibility34.h
// This header provides a compatibility layer to bridge PhysX 3.4 API expectations
// with the modern PhysX 5.6 implementation.

#ifndef PX_COMPATIBILITY_34_H
#define PX_COMPATIBILITY_34_H

#include "PxPhysicsAPI.h"
#include "extensions/PxSceneQueryExt.h"

namespace physx
{

// -------------------------------------------------------------------------
// 1. Foundation & Legacy Types
// -------------------------------------------------------------------------

// PxReal remains float in 5.6 by default, so no mapping needed.

// -------------------------------------------------------------------------
// 2. Scene Flags & Enums
// -------------------------------------------------------------------------

// eENABLE_ACTIVETRANSFORMS was deprecated in 3.4 and removed in 4.0+.
// We map it to eENABLE_ACTIVE_ACTORS via macro so that code referencing
// PxSceneFlag::eENABLE_ACTIVETRANSFORMS compiles correctly.
#define eENABLE_ACTIVETRANSFORMS eENABLE_ACTIVE_ACTORS

// -------------------------------------------------------------------------
// 3. Batch Queries (Deprecated in 3.4, moved to Ext in 5.6)
// -------------------------------------------------------------------------

// In 3.4, PxBatchQueryStatus had ePENDING, eSUCCESS, eOVERFLOW.
// In 5.6, PxBatchQueryExt returns these as PxBatchQueryStatus::Enum.
// We can just typedef the 5.6 status if it matches, but 5.6 uses a struct wrapper.
typedef PxBatchQueryStatus PxBatchQueryStatus34; // Avoid naming conflict if necessary.

// Define the memory descriptor expected by 3.4
struct PxBatchQueryMemory
{
    void* userRaycastResultBuffer;
    void* userRaycastTouchBuffer;
    void* userSweepResultBuffer;
    void* userSweepTouchBuffer;
    void* userOverlapResultBuffer;
    void* userOverlapTouchBuffer;
    
    // We use void* here because PxRaycastQueryResult etc. changed significantly.
    // In a full integration, these would be casted to 5.6 buffers.
};

struct PxBatchQueryDesc
{
    PxBatchQueryMemory queryMemory;
    void* filterShaderData;
    PxU32 filterShaderDataSize;
    void* preFilterShader;
    void* postFilterShader;
    
    PxBatchQueryDesc(PxU32 maxRaycastsPerExecute, PxU32 maxSweepsPerExecute, PxU32 maxOverlapsPerExecute)
    {
        (void)maxRaycastsPerExecute;
        (void)maxSweepsPerExecute;
        (void)maxOverlapsPerExecute;
    }
};

// Map PxBatchQuery to PxBatchQueryExt
typedef PxBatchQueryExt PxBatchQuery;

// Helper to create a batch query compatibly. 
// Note: If UE4 calls scene->createBatchQuery(desc), that call in UE4 will need to be 
// replaced with PxCreateBatchQueryCompat(scene, desc).
static inline PxBatchQuery* PxCreateBatchQueryCompat(PxScene* scene, const PxBatchQueryDesc& /*desc*/)
{
    // In a real scenario, we would map the 3.4 desc buffers to the 5.6 buffers here.
    // For now, we return a newly allocated Ext query with default parameters 
    // to satisfy the signature.
    return PxCreateBatchQueryExt(*scene, NULL, 0, 0, 0, 0, 0, 0);
}

// -------------------------------------------------------------------------
// 4. Articulations
// -------------------------------------------------------------------------

// PxArticulation was replaced by PxArticulationReducedCoordinate in 4.0+.
typedef PxArticulationReducedCoordinate PxArticulation;
typedef PxArticulationJointReducedCoordinate PxArticulationJoint;

// -------------------------------------------------------------------------
// 5. Physics Initialization
// -------------------------------------------------------------------------

// PxCreatePhysics in 3.4: PxCreatePhysics(version, foundation, scale, trackAllocations, pvd)
// PxCreatePhysics in 5.6: PxCreatePhysics(version, foundation, scale, trackAllocations, pvd)
// The signature is largely the same, but the TolerancesScale might differ slightly.
// No adapter needed immediately.

} // namespace physx

#endif // PX_COMPATIBILITY_34_H
