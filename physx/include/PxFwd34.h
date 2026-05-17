// PxFwd34.h
// Forward declarations and typedefs for core PhysX 3.4 types in a PhysX 5.6 environment.

#ifndef PX_FWD_34_H
#define PX_FWD_34_H

#include "foundation/PxSimpleTypes.h"

// Protect PhysX 5.6 headers from Unreal's 'check' macro collision
#ifdef check
    #pragma push_macro("check")
    #undef check
    #define PX_RESTORE_CHECK
#endif

// Include the actual definitions for math types because legacy code (APEX) 
// uses them as values in structs, which doesn't work with just forward declarations.
#include "foundation/PxVec2.h"
#include "foundation/PxVec3.h"
#include "foundation/PxVec4.h"
#include "foundation/PxQuat.h"
#include "foundation/PxMat33.h"
#include "foundation/PxMat44.h"
#include "foundation/PxTransform.h"
#include "foundation/PxBounds3.h"
#include "foundation/PxPlane.h"
#include "geomutils/PxContactPoint.h"

namespace physx
{
    // Classes that are still classes
    class PxScene;
    class PxPhysics;
    class PxRigidActor;
    class PxShape;
    class PxGeometry;
    class PxCapsuleGeometry;
    class PxMaterial;
    class PxRigidDynamic;
    class PxRigidStatic;
    class PxBase;

    // Structs that are still structs
    struct PxLocationHit;
    struct PxSweepHit;
    struct PxRaycastHit;
    struct PxOverlapHit;
    struct PxQueryHit;
    struct PxQueryFlag;
    
    template<typename T> struct PxHitBuffer;
    template<typename T> struct PxHitCallback;
}

// Legacy Gu namespace for contact generation
namespace Gu
{
    typedef physx::PxContactPoint ContactPoint;
}

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
#ifndef PX_SWITCH
#define PX_SWITCH 0
#endif

#ifdef PX_RESTORE_CHECK
    #pragma pop_macro("check")
    #undef PX_RESTORE_CHECK
#endif

#endif // PX_FWD_34_H
