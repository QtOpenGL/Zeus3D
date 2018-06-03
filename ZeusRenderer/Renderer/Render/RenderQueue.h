#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H
#include "Render.h"
#include "../Mesh/InstanceBatch.h"
#include "../Entity/Entity.h"
/*
 * RenderQueue.h
 *
 *  Created on: 2018-5-25
 *      Author: Zeus
 */
class RenderQueue
{
public:

    RenderQueue();
    ~RenderQueue();
    void copyData(RenderQueue* src);
    void renderStaticEntity(Camera3D* camera, Render* render, RenderState* state);
    void renderInstanceEntity(Camera3D* camera, Render* render, RenderState* state);
    void renderAnimateEntity(Camera3D* camera, Render* render, RenderState* state);
    void animate(long startTime, long currentTime);

    void pushEntityToQueue(Entity* entity);
    void pushEntityToInstanceQueue(Entity* entity);
    void pushEntityToAnimateQueue(Entity* entity);

    void clearQueue();

private:
    std::vector<Entity*> queue;
    std::vector<Entity*> instance_queue;
    std::vector<Entity*> animation_queue;
};

#endif // RENDERQUEUE_H
