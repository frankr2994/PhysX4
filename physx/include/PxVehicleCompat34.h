// PxVehicleCompat34.h
// This header provides a thick compatibility layer to bridge PhysX 3.4 Vehicle API 
// expectations with the modern PhysX 5.6 Vehicle2 modular implementation.

#ifndef PX_VEHICLE_COMPAT_34_H
#define PX_VEHICLE_COMPAT_34_H

#include "PxPhysicsAPI.h"
#include "vehicle2/PxVehicleAPI.h"

namespace physx
{

// -------------------------------------------------------------------------
// 1. Core Component Data (3.4)
// -------------------------------------------------------------------------

class PxVehicleChassisData
{
public:
    PxVec3 mMOI;
    PxReal mMass;
    PxVec3 mCMOffset;

    PxVehicleChassisData() : mMOI(0,0,0), mMass(1500.0f), mCMOffset(0,0,0) {}
};

class PxVehicleEngineData
{
public:
    enum { eMAX_NB_ENGINE_TORQUE_CURVE_ENTRIES = 8 };
    PxFixedSizeLookupTable<eMAX_NB_ENGINE_TORQUE_CURVE_ENTRIES> mTorqueCurve;
    PxReal mMOI;
    PxReal mPeakTorque;
    PxReal mMaxOmega;
    PxReal mDampingRateFullThrottle;
    PxReal mDampingRateZeroThrottleClutchEngaged;
    PxReal mDampingRateZeroThrottleClutchDisengaged;

    PxVehicleEngineData() : mMOI(1.0f), mPeakTorque(500.0f), mMaxOmega(600.0f),
        mDampingRateFullThrottle(0.15f), mDampingRateZeroThrottleClutchEngaged(2.0f), mDampingRateZeroThrottleClutchDisengaged(0.35f) 
    {
        mTorqueCurve.addPair(0.0f, 0.8f);
        mTorqueCurve.addPair(0.33f, 1.0f);
        mTorqueCurve.addPair(1.0f, 0.8f);
    }
};

class PxVehicleGearsData
{
public:
    enum Enum
    {
        eREVERSE=0, eNEUTRAL, eFIRST, eSECOND, eTHIRD, eFOURTH, eFIFTH, eSIXTH, eGEARSRATIO_COUNT = 32
    };
    PxReal mRatios[eGEARSRATIO_COUNT];
    PxReal mFinalRatio;
    PxU32 mNbRatios;
    PxReal mSwitchTime;

    PxVehicleGearsData() : mFinalRatio(4.0f), mNbRatios(7), mSwitchTime(0.5f)
    {
        mRatios[eREVERSE] = -4.0f; mRatios[eNEUTRAL] = 0.0f; mRatios[eFIRST] = 4.0f;
        mRatios[eSECOND] = 2.0f; mRatios[eTHIRD] = 1.5f; mRatios[eFOURTH] = 1.1f; mRatios[eFIFTH] = 1.0f;
    }
};

struct PxVehicleClutchAccuracyMode { enum Enum { eESTIMATE = 0, eBEST_POSSIBLE }; };

class PxVehicleClutchData
{
public:
    PxReal mStrength;
    PxVehicleClutchAccuracyMode::Enum mAccuracyMode;
    PxU32 mEstimateIterations;

    PxVehicleClutchData() : mStrength(10.0f), mAccuracyMode(PxVehicleClutchAccuracyMode::eBEST_POSSIBLE), mEstimateIterations(5) {}
};

class PxVehicleAutoBoxData
{
public:
    PxReal mUpRatios[PxVehicleGearsData::eGEARSRATIO_COUNT];
    PxReal mDownRatios[PxVehicleGearsData::eGEARSRATIO_COUNT];
    PxVehicleAutoBoxData() { for(int i=0; i<PxVehicleGearsData::eGEARSRATIO_COUNT; ++i) { mUpRatios[i] = 0.65f; mDownRatios[i] = 0.50f; } }
};

class PxVehicleDifferential4WData
{
public:
    enum Enum { eDIFF_TYPE_LS_4WD, eDIFF_TYPE_LS_FRONTWD, eDIFF_TYPE_LS_REARWD, eDIFF_TYPE_OPEN_4WD, eDIFF_TYPE_OPEN_FRONTWD, eDIFF_TYPE_OPEN_REARWD, eMAX_NB_DIFF_TYPES };
    PxReal mFrontRearSplit;
    PxReal mFrontLeftRightSplit;
    PxReal mRearLeftRightSplit;
    PxReal mCentreBias;
    PxReal mFrontBias;
    PxReal mRearBias;
    Enum mType;

    PxVehicleDifferential4WData() : mFrontRearSplit(0.45f), mFrontLeftRightSplit(0.5f), mRearLeftRightSplit(0.5f), mCentreBias(1.3f), mFrontBias(1.3f), mRearBias(1.3f), mType(eDIFF_TYPE_LS_4WD) {}
};

class PxVehicleAckermannGeometryData
{
public:
    PxReal mAccuracy;
    PxReal mFrontWidth;
    PxReal mRearWidth;
    PxReal mAxleSeparation;

    PxVehicleAckermannGeometryData() : mAccuracy(1.0f), mFrontWidth(0.0f), mRearWidth(0.0f), mAxleSeparation(0.0f) {}
};

// -------------------------------------------------------------------------
// 2. Wheel & Suspension Data (3.4)
// -------------------------------------------------------------------------

class PxVehicleWheelData
{
public:
    PxReal mRadius;
    PxReal mWidth;
    PxReal mMass;
    PxReal mMOI;
    PxReal mDampingRate;
    PxReal mMaxBrakeTorque;
    PxReal mMaxHandBrakeTorque;
    PxReal mMaxSteer;
    PxReal mToeAngle;

    PxVehicleWheelData() : mRadius(0.3f), mWidth(0.3f), mMass(20.0f), mMOI(0.5f), mDampingRate(0.25f), mMaxBrakeTorque(1500.0f), mMaxHandBrakeTorque(0.0f), mMaxSteer(0.0f), mToeAngle(0.0f) {}
};

class PxVehicleSuspensionData
{
public:
    PxReal mSpringStrength;
    PxReal mSpringDamperRate;
    PxReal mMaxCompression;
    PxReal mMaxDroop;
    PxReal mSprungMass;
    PxReal mCamberAtRest;
    PxReal mCamberAtMaxCompression;
    PxReal mCamberAtMaxDroop;

    PxVehicleSuspensionData() : mSpringStrength(35000.0f), mSpringDamperRate(4500.0f), mMaxCompression(0.3f), mMaxDroop(0.1f), mSprungMass(0.0f), mCamberAtRest(0.0f), mCamberAtMaxCompression(0.0f), mCamberAtMaxDroop(0.0f) {}
};

class PxVehicleTireData
{
public:
    PxReal mLatStiffX;
    PxReal mLatStiffY;
    PxReal mLongitudinalStiffnessPerUnitGravity;
    PxReal mCamberStiffnessPerUnitGravity;
    PxReal mFrictionVsSlipGraph[3][2];
    PxU32 mType;

    PxVehicleTireData() : mLatStiffX(2.0f), mLatStiffY(18.0f), mLongitudinalStiffnessPerUnitGravity(1000.0f), mCamberStiffnessPerUnitGravity(5.0f), mType(0) 
    {
        mFrictionVsSlipGraph[0][0]=0.0f; mFrictionVsSlipGraph[0][1]=1.0f;
        mFrictionVsSlipGraph[1][0]=0.1f; mFrictionVsSlipGraph[1][1]=1.0f;
        mFrictionVsSlipGraph[2][0]=1.0f; mFrictionVsSlipGraph[2][1]=1.0f;
    }
};

// -------------------------------------------------------------------------
// 3. Container Objects (3.4)
// -------------------------------------------------------------------------

class PxVehicleWheelsSimData
{
public:
    static PxVehicleWheelsSimData* allocate(const PxU32 nbWheels);
    void setChassisMass(const PxF32 chassisMass);
    void free();
    
    void setWheelData(const PxU32 id, const PxVehicleWheelData& wheel);
    void setSuspensionData(const PxU32 id, const PxVehicleSuspensionData& suspension);
    void setTireData(const PxU32 id, const PxVehicleTireData& tire);
    void setWheelCentreOffset(const PxU32 id, const PxVec3& offset);
    void setSuspensionTravelDir(const PxU32 id, const PxVec3& dir);
    void setWheelShapeMapping(const PxU32 id, const PxI32 shapeId);
    void setSceneQueryFilterData(const PxU32 id, const PxFilterData& sqFilterData);

    // Internal mapping to Vehicle2 params will go here
};

class PxVehicleWheelsDynData
{
public:
    void setToRestState();
    void setTireForceShaderData(const void* tireForceShaderData);
};

class PxVehicleDriveSimData
{
public:
    void setEngineData(const PxVehicleEngineData& engine);
    void setGearsData(const PxVehicleGearsData& gears);
    void setClutchData(const PxVehicleClutchData& clutch);
    void setAutoBoxData(const PxVehicleAutoBoxData& autobox);
};

class PxVehicleDriveSimData4W : public PxVehicleDriveSimData
{
public:
    void setDiffData(const PxVehicleDifferential4WData& diff);
    void setAckermannGeometryData(const PxVehicleAckermannGeometryData& ackermannData);
};

// -------------------------------------------------------------------------
// 4. Main Vehicle Classes (3.4)
// -------------------------------------------------------------------------

class PxVehicleWheels : public PxBase
{
public:
    virtual void release() { PxBase::release(); }
    PxRigidDynamic* getRigidDynamicActor() { return mActor; }
    
    PxVehicleWheelsSimData mSimData;
    PxVehicleWheelsDynData mDynData;
    PxRigidDynamic* mActor;
};

class PxVehicleDrive : public PxVehicleWheels
{
public:
    PxVehicleDriveSimData mDriveSimData;
};

class PxVehicleDrive4W : public PxVehicleDrive
{
public:
    static PxVehicleDrive4W* allocate(const PxU32 nbWheels);
    void setup(PxPhysics* physics, PxRigidDynamic* vehActor, const PxVehicleWheelsSimData& wheelsData, const PxVehicleDriveSimData4W& driveData, const PxU32 nbNonDrivenWheels);
    
    PxVehicleDriveSimData4W mDriveSimData4W;
};

// -------------------------------------------------------------------------
// 5. Update Namespace (3.4)
// -------------------------------------------------------------------------

namespace PxVehicleUpdate
{
    struct PxVehicleWheelQueryResult { PxWheelQueryResult* wheelQueryResults; PxU32 nbWheelQueryResults; };
    void update(PxReal timestep, const PxVec3& gravity, const class PxVehicleDrivableSurfaceToTireFrictionPairs& frictionPairs, PxU32 nbVehicles, PxVehicleWheels** vehicles, PxVehicleWheelQueryResult* vehicleResults = NULL);
}

} // namespace physx

#endif // PX_VEHICLE_COMPAT_34_H
