#include "faceenginebuilder.h"
FaceAlgInterface * FaceEngineBuilder::faInstance = NULL;
FaceEngineBuilder::FaceEngineBuilder()
{

}

FaceAlgInterface * FaceEngineBuilder::getEngine(ENGINE_TYPE type){
        if(!faInstance){
            if(type == ENGINE_NEURO){
                faInstance = new NeuroAlg();
            } else {
                faInstance = new NeoFaceAlg();
            }
        }
        return faInstance;
}

