#include "RenderQueue.h"
#include <QMatrix4x4>
#include "../Entity/AnimationEntity.h"
#include "../SceneNode/AnimationEntityNode.h"

RenderQueue::RenderQueue()
{
    queue.clear();
    instance_queue.clear();
}

RenderQueue::~RenderQueue()
{
    queue.clear();
    instance_queue.clear();
}

void RenderQueue::copyData(RenderQueue *src)
{
    queue.assign(src->queue.begin(), src->queue.end());
}

void RenderQueue::renderStaticEntity(Camera3D *camera, Render *render, RenderState *state)
{
    auto it = queue.begin();
    // draw each entity in the queue
    while(it != queue.end()){
        Entity* current = *it;
        //state->shader = render->getDrawcall(current->drawcall);
        render->render(camera,current,state);
        ++ it;
    }
}

void RenderQueue::renderInstanceEntity(Camera3D *camera, Render *render, RenderState *state)
{
    // drwa instance entity in the queue
    auto ins_it = instance_queue.begin();
    while(ins_it != instance_queue.end()){
        Entity* current = *ins_it;
        //state->shader = render->getDrawcall(current->drawcall);
        render->render(camera,current,state);
        ++ins_it;
    }
}

void RenderQueue::renderAnimateEntity(Camera3D *camera, Render *render, RenderState *state)
{
    auto ani_it = animation_queue.begin();
    while(ani_it != animation_queue.end()){
        Entity* current = *ani_it;
        //state->shader = render->getDrawcall(current->drawcall);
        render->render(camera,current,state);
        ++ ani_it;
    }
}

void RenderQueue::animate(long startTime, long currentTime)
{
    // performan animation
    auto it = animation_queue.begin();
    while(it != animation_queue.end()){
        Entity* current = *it;
        AnimationEntity *animateEntity = static_cast<AnimationEntity*>(current);
        animateEntity->animate(0, startTime, currentTime);
        ++it;
    }
}

void RenderQueue::pushEntityToQueue(Entity *entity)
{
    queue.push_back(entity);
}

void RenderQueue::pushEntityToInstanceQueue(Entity *entity)
{
    instance_queue.push_back(entity);
}

void RenderQueue::pushEntityToAnimateQueue(Entity *entity)
{
    animation_queue.push_back(entity);
}

void RenderQueue::clearQueue()
{
    queue.clear();
    instance_queue.clear();
}
