// PxVehicleCompat34.cpp
// Implementation of the thick compatibility layer for PhysX 3.4 Vehicle SDK.

#include "PxVehicleCompat34.h"
#include <vector>

namespace physx
{

// -------------------------------------------------------------------------
// PxVehicleWheelsSimData Implementation
// -------------------------------------------------------------------------

PxVehicleWheelsSimData* PxVehicleWheelsSimData::allocate(const PxU32 nbWheels)
{
    PxVehicleWheelsSimData* data = new PxVehicleWheelsSimData();
    data->mNbWheels = nbWheels;
    return data;
}

void PxVehicleWheelsSimData::setChassisMass(const PxF32 /*chassisMass*/) {}
void PxVehicleWheelsSimData::free() { delete this; }
void PxVehicleWheelsSimData::setWheelData(const PxU32 /*id*/, const PxVehicleWheelData& /*wheel*/) {}
void PxVehicleWheelsSimData::setSuspensionData(const PxU32 /*id*/, const PxVehicleSuspensionData& /*suspension*/) {}
void PxVehicleWheelsSimData::setTireData(const PxU32 /*id*/, const PxVehicleTireData& /*tire*/) {}
void PxVehicleWheelsSimData::setWheelCentreOffset(const PxU32 /*id*/, const PxVec3& /*offset*/) {}
void PxVehicleWheelsSimData::setSuspTravelDirection(const PxU32 /*id*/, const PxVec3& /*dir*/) {}
void PxVehicleWheelsSimData::setWheelShapeMapping(const PxU32 /*id*/, const PxI32 /*shapeId*/) {}
void PxVehicleWheelsSimData::setSceneQueryFilterData(const PxU32 /*id*/, const PxFilterData& /*sqFilterData*/) {}
void PxVehicleWheelsSimData::setSuspForceAppPointOffset(const PxU32 /*id*/, const PxVec3& /*offset*/) {}
void PxVehicleWheelsSimData::setTireForceAppPointOffset(const PxU32 /*id*/, const PxVec3& /*offset*/) {}
void PxVehicleWheelsSimData::setSubStepCount(const PxReal /*speedThreshold*/, const PxU32 /*lowForwardSpeedSubStepCount*/, const PxU32 /*highForwardSpeedSubStepCount*/) {}
void PxVehicleWheelsSimData::setMinLongSlipDenominator(const PxReal /*minLongSlipDenominator*/) {}
void PxVehicleWheelsSimData::setTireLoadFilterData(const PxVehicleTireLoadFilterData& /*tireLoadFilter*/) {}

static const PxVec3 gDefaultVec3(0,0,0);
static const PxVehicleSuspensionData gDefaultSuspensionData;
static const PxVehicleWheelData gDefaultWheelData;
static const PxVehicleTireData gDefaultTireData;

const PxVec3& PxVehicleWheelsSimData::getSuspTravelDirection(const PxU32 /*id*/) const { return gDefaultVec3; }
const PxVec3& PxVehicleWheelsSimData::getSuspForceAppPointOffset(const PxU32 /*id*/) const { return gDefaultVec3; }
const PxVec3& PxVehicleWheelsSimData::getTireForceAppPointOffset(const PxU32 /*id*/) const { return gDefaultVec3; }
const PxVec3& PxVehicleWheelsSimData::getWheelCentreOffset(const PxU32 /*id*/) const { return gDefaultVec3; }
const PxVehicleSuspensionData& PxVehicleWheelsSimData::getSuspensionData(const PxU32 /*id*/) const { return gDefaultSuspensionData; }
const PxVehicleWheelData& PxVehicleWheelsSimData::getWheelData(const PxU32 /*id*/) const { return gDefaultWheelData; }
const PxVehicleTireData& PxVehicleWheelsSimData::getTireData(const PxU32 /*id*/) const { return gDefaultTireData; }
PxI32 PxVehicleWheelsSimData::getWheelShapeMapping(const PxU32 /*id*/) const { return -1; }

// -------------------------------------------------------------------------
// PxVehicleWheelsDynData Implementation
// -------------------------------------------------------------------------

void PxVehicleWheelsDynData::setToRestState() {}
void PxVehicleWheelsDynData::setTireForceShaderData(const PxU32 /*wheelId*/, const void* /*tireForceShaderData*/) {}
void PxVehicleWheelsDynData::setTireForceShaderFunction(void* /*tireForceShaderFn*/) {}
PxReal PxVehicleWheelsDynData::getWheelRotationSpeed(const PxU32 /*wheelId*/) const { return 0.0f; }

// -------------------------------------------------------------------------
// PxVehicleDriveSimData Implementation
// -------------------------------------------------------------------------

void PxVehicleDriveSimData::setEngineData(const PxVehicleEngineData& engine) { mEngine = engine; }
void PxVehicleDriveSimData::setGearsData(const PxVehicleGearsData& gears) { mGears = gears; }
void PxVehicleDriveSimData::setClutchData(const PxVehicleClutchData& clutch) { mClutch = clutch; }
void PxVehicleDriveSimData::setAutoBoxData(const PxVehicleAutoBoxData& autobox) { mAutoBox = autobox; }

void PxVehicleDriveSimData4W::setDiffData(const PxVehicleDifferential4WData& diff) { mDiff = diff; }
void PxVehicleDriveSimData4W::setAckermannGeometryData(const PxVehicleAckermannGeometryData& ackermannData) { mAckermann = ackermannData; }

// -------------------------------------------------------------------------
// PxVehicleDrive4W Implementation
// -------------------------------------------------------------------------

PxVehicleDrive4W* PxVehicleDrive4W::allocate(const PxU32 /*nbWheels*/)
{
    return new PxVehicleDrive4W();
}

void PxVehicleDrive4W::setup(
    PxPhysics* /*physics*/, 
    PxRigidDynamic* vehActor, 
    const PxVehicleWheelsSimData& wheelsData, 
    const PxVehicleDriveSimData4W& driveData, 
    const PxU32 /*nbNonDrivenWheels*/)
{
    mActor = vehActor;
    mWheelsSimData = wheelsData;
    mDriveSimData4W = driveData;
}

// -------------------------------------------------------------------------
// PxVehicleUpdate Implementation
// -------------------------------------------------------------------------

namespace PxVehicleUpdate
{
    void update(
        PxReal /*timestep*/, 
        const PxVec3& /*gravity*/, 
        const class PxVehicleDrivableSurfaceToTireFrictionPairs& /*frictionPairs*/, 
        PxU32 nbVehicles, 
        PxVehicleWheels** vehicles, 
        PxVehicleWheelQueryResult* /*vehicleResults*/)
    {
        for(PxU32 i = 0; i < nbVehicles; ++i)
        {
            PxVehicleWheels* v = vehicles[i];
            PX_UNUSED(v);
        }
    }
}

// -------------------------------------------------------------------------
// Global Implementation
// -------------------------------------------------------------------------

void PxVehicleComputeSprungMasses(PxU32 nbWheels, const PxVec3* /*wheelOffsets*/, const PxVec3& /*com*/, PxReal totalMass, PxU32 /*gravityDirection*/, PxReal* sprungMasses)
{
    // Dummy: distribute evenly
    PxReal evenMass = totalMass / (PxReal)nbWheels;
    for(PxU32 i=0; i<nbWheels; ++i) sprungMasses[i] = evenMass;
}

} // namespace physx
