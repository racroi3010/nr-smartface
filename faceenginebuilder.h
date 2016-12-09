#ifndef FACEENGINEBUILDER_H
#define FACEENGINEBUILDER_H
#include "facealginterface.h"
#include "neofacealg.h"
#include "neuroalg.h"

class FaceEngineBuilder
{


public:
    enum ENGINE_TYPE{
        ENGINE_NEOFACE,
        ENGINE_NEURO
    };
    FaceEngineBuilder();
    static FaceAlgInterface * getEngine(ENGINE_TYPE type);

private:
    static FaceAlgInterface * faInstance;
};

#endif // FACEENGINEBUILDER_H
