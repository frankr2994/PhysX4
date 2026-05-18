// PxCompatibility34.h
// This header provides a compatibility layer to bridge PhysX 3.4 API expectations
// with the modern PhysX 5.6 implementation.

#ifndef PX_COMPATIBILITY_34_H
#define PX_COMPATIBILITY_34_H

// Protect PhysX 5.6 headers from Unreal's 'check' macro collision
#define PX_COMPAT_PUSHED_CHECK 0
#ifdef check
    #pragma push_macro("check")
    #undef check
    #undef PX_COMPAT_PUSHED_CHECK
    #define PX_COMPAT_PUSHED_CHECK 1
#endif

#include "PxPhysicsAPI.h"
#include "extensions/PxSceneQueryExt.h"
#include "cooking/PxCooking.h"

#if PX_COMPAT_PUSHED_CHECK
    #pragma pop_macro("check")
#endif
#undef PX_COMPAT_PUSHED_CHECK

namespace physx
{

// -------------------------------------------------------------------------
// 1. Foundation & Legacy Types
// -------------------------------------------------------------------------

#define PX_FOUNDATION_VERSION PX_PHYSICS_VERSION

struct PxPlatform
{
    enum Enum
    {
        ePC
    };
};

// -------------------------------------------------------------------------
// 2. Scene Flags & Enums
// -------------------------------------------------------------------------

struct PxActiveTransform
{
    PxRigidActor* actor;
    void* userData;
    PxTransform actor2World;
};

#define eENABLE_ACTIVETRANSFORMS eENABLE_ACTIVE_ACTORS

// Missing Platform Macros for APEX
#ifndef PX_ANDROID
#define PX_ANDROID 0
#endif
#ifndef PX_PS4
#define PX_PS4 0
#endif
#ifndef PX_APPLE
#define PX_APPLE 0
#endif

// -------------------------------------------------------------------------
// 3. Cooking (PhysX 5.6 replaced the class with global functions)
// -------------------------------------------------------------------------

class PxCooking
{
public:
    virtual void release() { delete this; }
    virtual void setParams(const PxCookingParams& params) { mParams = params; }
    virtual const PxCookingParams& getParams() const { return mParams; }
    
    virtual PxTriangleMesh* createTriangleMesh(const PxTriangleMeshDesc& desc, PxInsertionCallback& insertionCallback, PxTriangleMeshCookingResult::Enum* condition = NULL)
    {
        return PxCreateTriangleMesh(mParams, desc, insertionCallback, condition);
    }
    
    virtual PxConvexMesh* createConvexMesh(const PxConvexMeshDesc& desc, PxInsertionCallback& insertionCallback, PxConvexMeshCookingResult::Enum* condition = NULL)
    {
        return PxCreateConvexMesh(mParams, desc, insertionCallback, condition);
    }
    
    virtual PxHeightField* createHeightField(const PxHeightFieldDesc& desc, PxInsertionCallback& insertionCallback)
    {
        return PxCreateHeightField(desc, insertionCallback);
    }

    virtual bool validateConvexMesh(const PxConvexMeshDesc& desc)
    {
        return PxValidateConvexMesh(mParams, desc);
    }

    virtual bool computeHullPolygons(const PxSimpleTriangleMesh& mesh, PxAllocatorCallback& inCallback, PxU32& nbVerts, PxVec3*& vertices,
														PxU32& nbIndices, PxU32*& indices, PxU32& nbPolygons, PxHullPolygon*& hullPolygons)
    {
        return PxComputeHullPolygons(mParams, mesh, inCallback, nbVerts, vertices, nbIndices, indices, nbPolygons, hullPolygons);
    }

    virtual bool cookConvexMesh(const PxConvexMeshDesc& desc, PxOutputStream& stream, PxConvexMeshCookingResult::Enum* condition = NULL)
    {
        return PxCookConvexMesh(mParams, desc, stream, condition);
    }

    virtual bool cookTriangleMesh(const PxTriangleMeshDesc& desc, PxOutputStream& stream, PxTriangleMeshCookingResult::Enum* condition = NULL)
    {
        return PxCookTriangleMesh(mParams, desc, stream, condition);
    }

    virtual bool cookHeightField(const PxHeightFieldDesc& desc, PxOutputStream& stream)
    {
        return PxCookHeightField(desc, stream);
    }

private:
    PxCookingParams mParams;
    PxCooking(const PxCookingParams& params) : mParams(params) {}
    friend PxCooking* PxCreateCooking(PxU32 version, PxFoundation& foundation, const PxCookingParams& params);
};

inline PxCooking* PxCreateCooking(PxU32 /*version*/, PxFoundation& /*foundation*/, const PxCookingParams& params)
{
    return new PxCooking(params);
}

inline void PxRegisterUnifiedHeightFields(PxPhysics&) {}
inline void PxRegisterHeightFields(PxPhysics&) {}

// -------------------------------------------------------------------------
// 4. Batch Queries
// -------------------------------------------------------------------------

typedef PxBatchQueryExt PxBatchQuery;

// -------------------------------------------------------------------------
// 5. Articulations
// -------------------------------------------------------------------------

typedef PxArticulationReducedCoordinate PxArticulation;
typedef PxArticulationJointReducedCoordinate PxArticulationJoint;

// -------------------------------------------------------------------------
// 6. Vehicle Legacy Types & Macros
// -------------------------------------------------------------------------

#ifndef PX_DEBUG_VEHICLE_ON
#define PX_DEBUG_VEHICLE_ON 0
#endif

struct PxVehicleWheelQueryResult
{
    void* ptr; // Stub for TArray usage
};

struct PxRaycastQueryResult
{
    void* ptr; // Stub for TArray usage
};

} // namespace physx

// -------------------------------------------------------------------------
// 7. APEX Legacy Namespaces and Methods
// -------------------------------------------------------------------------

namespace nvidia
{
namespace apex
{
    struct ApexSDKDesc
    {
        void* physXSDK;
        void* cooking;
        ApexSDKDesc() : physXSDK(NULL), cooking(NULL) {}
    };

    class Scene
    {
    public:
        void lockRead(const char*, PxU32) {}
        void unlockRead() {}
        void lockWrite(const char*, PxU32) {}
        void unlockWrite() {}
    };
}
}

#endif // PX_COMPATIBILITY_34_H
