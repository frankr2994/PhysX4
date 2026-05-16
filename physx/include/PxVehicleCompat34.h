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

class PxVehicleTireLoadFilterData
{
public:
    PxReal mMinNormalisedLoad;
    PxReal mMinFilteredNormalisedLoad;
    PxReal mMaxNormalisedLoad;
    PxReal mMaxFilteredNormalisedLoad;

    PxVehicleTireLoadFilterData() : mMinNormalisedLoad(0.0f), mMinFilteredNormalisedLoad(1.0f), mMaxNormalisedLoad(2.0f), mMaxFilteredNormalisedLoad(0.7f) {}
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

    PxReal getRecipLongitudinalStiffnessPerUnitGravity() const { return 1.0f / mLongitudinalStiffnessPerUnitGravity; }
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
    
    PxU32 getNbWheels() const { return mNbWheels; }
    void setWheelData(const PxU32 id, const PxVehicleWheelData& wheel);
    void setSuspensionData(const PxU32 id, const PxVehicleSuspensionData& suspension);
    void setTireData(const PxU32 id, const PxVehicleTireData& tire);
    void setWheelCentreOffset(const PxU32 id, const PxVec3& offset);
    void setSuspTravelDirection(const PxU32 id, const PxVec3& dir);
    void setSuspensionTravelDir(const PxU32 id, const PxVec3& dir) { setSuspTravelDirection(id, dir); }
    void setWheelShapeMapping(const PxU32 id, const PxI32 shapeId);
    void setSceneQueryFilterData(const PxU32 id, const PxFilterData& sqFilterData);

    void setSuspForceAppPointOffset(const PxU32 id, const PxVec3& offset);
    void setTireForceAppPointOffset(const PxU32 id, const PxVec3& offset);
    void setSubStepCount(const PxReal speedThreshold, const PxU32 lowForwardSpeedSubStepCount, const PxU32 highForwardSpeedSubStepCount);
    void setMinLongSlipDenominator(const PxReal minLongSlipDenominator);
    void setTireLoadFilterData(const PxVehicleTireLoadFilterData& tireLoadFilter);

    const PxVec3& getSuspTravelDirection(const PxU32 id) const;
    const PxVec3& getSuspForceAppPointOffset(const PxU32 id) const;
    const PxVec3& getTireForceAppPointOffset(const PxU32 id) const;
    const PxVec3& getWheelCentreOffset(const PxU32 id) const;
    const PxVehicleSuspensionData& getSuspensionData(const PxU32 id) const;
    const PxVehicleWheelData& getWheelData(const PxU32 id) const;
    const PxVehicleTireData& getTireData(const PxU32 id) const;
    PxI32 getWheelShapeMapping(const PxU32 id) const;

    PxU32 mNbWheels;
};

class PxVehicleWheelsDynData
{
public:
    void setToRestState();
    void setTireForceShaderData(const PxU32 wheelId, const void* tireForceShaderData);
    void setTireForceShaderFunction(void* tireForceShaderFn);
    PxReal getWheelRotationSpeed(const PxU32 wheelId) const;
};

class PxVehicleDriveSimData
{
public:
    void setEngineData(const PxVehicleEngineData& engine);
    void setGearsData(const PxVehicleGearsData& gears);
    void setClutchData(const PxVehicleClutchData& clutch);
    void setAutoBoxData(const PxVehicleAutoBoxData& autobox);

    PxVehicleEngineData mEngine;
    PxVehicleGearsData mGears;
    PxVehicleClutchData mClutch;
    PxVehicleAutoBoxData mAutoBox;
};

class PxVehicleDriveSimData4W : public PxVehicleDriveSimData
{
public:
    void setDiffData(const PxVehicleDifferential4WData& diff);
    void setAckermannGeometryData(const PxVehicleAckermannGeometryData& ackermannData);

    PxVehicleDifferential4WData mDiff;
    PxVehicleAckermannGeometryData mAckermann;
};

class PxVehicleDriveDynData
{
public:
    PxU32 getTargetGear() const { return 0; }
    PxU32 getCurrentGear() const { return 0; }
    void forceGearChange(const PxU32 gear) {}
    void startGearChange(const PxU32 gear) {}
    void setUseAutoGears(const bool useAutoGears) {}
    bool getUseAutoGears() const { return true; }
    PxReal getEngineRotationSpeed() const { return 0.0f; }
};

// -------------------------------------------------------------------------
// 4. Main Vehicle Classes (3.4)
// -------------------------------------------------------------------------

class PxVehicleWheels : public PxBase
{
public:
    virtual void release() override { delete this; }
    virtual const char* getConcreteTypeName() const override { return "PxVehicleWheels"; }
    PxRigidDynamic* getRigidDynamicActor() { return mActor; }
    PxReal computeForwardSpeed() const { return 0.0f; }
    
    PxVehicleWheelsSimData mWheelsSimData;
    PxVehicleWheelsDynData mWheelsDynData;
    PxRigidDynamic* mActor;

protected:
    PxVehicleWheels() : PxBase(0, PxBaseFlag::eIS_RELEASABLE) {}
};

class PxVehicleDrive : public PxVehicleWheels
{
public:
    PxVehicleDriveSimData mDriveSimData;
    PxVehicleDriveDynData mDriveDynData;
};

class PxVehicleDrive4W : public PxVehicleDrive
{
public:
    static PxVehicleDrive4W* allocate(const PxU32 nbWheels);
    void setup(PxPhysics* physics, PxRigidDynamic* vehActor, const PxVehicleWheelsSimData& wheelsData, const PxVehicleDriveSimData4W& driveData, const PxU32 nbNonDrivenWheels);
    
    PxVehicleDriveSimData4W mDriveSimData4W;
};

// -------------------------------------------------------------------------
// 5. Query & Update Structures (3.4)
// -------------------------------------------------------------------------

struct PxWheelQueryResult
{
    PxVec3 suspLineStart;
    PxVec3 suspLineDir;
    PxReal suspLineLength;
    bool isInAir;
    PxActor* tireContactActor;
    PxShape* tireContactShape;
    PxVec3 tireContactPoint;
    PxVec3 tireContactNormal;
    PxReal tireFriction;
    PxU32 tireSurfaceType;
    PxTransform localPose;

    PxReal longitudinalSlip;
    PxReal lateralSlip;
    PxReal suspSpringForce;
    PxMaterial* tireSurfaceMaterial;

    PxWheelQueryResult() { PxMemZero(this, sizeof(PxWheelQueryResult)); isInAir=true; localPose=PxTransform(PxIdentity); }
};

class PxVehicleGraph
{
public:
    enum { eMAX_NB_SAMPLES = 256, eMAX_NB_TITLE_CHARS = 256 };
    void computeGraphChannel(const PxU32 channel, PxReal* xy, PxVec3* colors, char* title) const {}
};

struct PxVehicleTelemetryData
{
    const PxVec3* getTireforceAppPoints() const { return NULL; }
    const PxVec3* getSuspforceAppPoints() const { return NULL; }
    const PxVehicleGraph& getWheelGraph(const PxU32 wheelId) const { static PxVehicleGraph g; return g; }
};

struct PxVehicleWheelGraphChannel
{
    enum Enum
    {
        eJOUNCE=0,
        eSUSPFORCE,
        eTIRELOAD,
        eNORMALIZED_TIRELOAD,
        eWHEEL_OMEGA,
        eTIRE_FRICTION,
        eTIRE_LONG_SLIP,
        eNORM_TIRE_LONG_FORCE,
        eTIRE_LAT_SLIP,
        eNORM_TIRE_LAT_FORCE,
        eNORM_TIRE_ALIGNING_MOMENT,
        eMAX_NB_WHEEL_CHANNELS
    };
};

namespace PxVehicleUpdate
{
    struct PxVehicleWheelQueryResult { PxWheelQueryResult* wheelQueryResults; PxU32 nbWheelQueryResults; };
    void update(PxReal timestep, const PxVec3& gravity, const class PxVehicleDrivableSurfaceToTireFrictionPairs& frictionPairs, PxU32 nbVehicles, PxVehicleWheels** vehicles, PxVehicleWheelQueryResult* vehicleResults = NULL);
}

// Global functions
void PxVehicleComputeSprungMasses(PxU32 nbWheels, const PxVec3* wheelOffsets, const PxVec3& com, PxReal totalMass, PxU32 gravityDirection, PxReal* sprungMasses);

} // namespace physx

#endif // PX_VEHICLE_COMPAT_34_H
