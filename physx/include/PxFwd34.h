// PxFwd34.h
// Forward declarations and typedefs for core PhysX 3.4 types in a PhysX 5.6 environment.

#ifndef PX_FWD_34_H
#define PX_FWD_34_H

#include "foundation/PxSimpleTypes.h"

#ifdef check
    #pragma push_macro("check")
    #undef check
    #define PX_RESTORE_CHECK
#endif

namespace physx
{
    template<class Type> class PxVec2T;
    typedef PxVec2T<float> PxVec2;

    template<class Type> class PxVec3T;
    typedef PxVec3T<float> PxVec3;

    template<class Type> class PxVec4T;
    typedef PxVec4T<float> PxVec4;

    template<class Type> class PxQuatT;
    typedef PxQuatT<float> PxQuat;

    template<class Type> class PxMat33T;
    typedef PxMat33T<float> PxMat33;

    template<class Type> class PxMat44T;
    typedef PxMat44T<float> PxMat44;

    template<class Type> class PxTransformT;
    typedef PxTransformT<float> PxTransform;
    
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

#ifdef PX_RESTORE_CHECK
    #pragma pop_macro("check")
    #undef PX_RESTORE_CHECK
#endif

#endif // PX_FWD_34_H
