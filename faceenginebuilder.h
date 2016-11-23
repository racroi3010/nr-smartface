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
    static FaceAlgInterface * getEngine(ENGINE_TYPE type){
        if(faInstance){
            if(type == ENGINE_NEURO){
                faInstance = new NeuroAlg();
            } else {
                faInstance = new NeoFaceAlg();
            }
        }
        return faInstance;
    }

private:
    static FaceAlgInterface * faInstance;
};

#endif // FACEENGINEBUILDER_H
