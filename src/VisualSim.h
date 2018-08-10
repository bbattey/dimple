// -*- mode:c++; indent-tabs-mode:nil; c-basic-offset:4; -*-

#ifndef _VISUAL_SIM_H_
#define _VISUAL_SIM_H_

#include "Simulation.h"
#include "HapticsSim.h"

#include <world/CWorld.h>
#include <display/CCamera.h>
#include <lighting/CSpotLight.h>

class OscCameraCHAI;

class VisualSim : public Simulation
{
  public:
    VisualSim(const char *port);
    virtual ~VisualSim();

    cWorld *world() { return m_chaiWorld; }
    OscCameraCHAI *camera() { return m_camera; }
    cSpotLight *light(unsigned int i);

    virtual void on_clear();

  protected:
    virtual void initialize();
    virtual void step();

    void initGlutWindow();
    static void updateDisplay(int data);
    static void draw();
    static void key(unsigned char key, int x, int y);
    static void reshape(int w, int h);

    int m_nWidth, m_nHeight;

    cWorld* m_chaiWorld;            //! the world in which we will create our environment
    cSpotLight *m_chaiLight0;       //! a light source
    cSpotLight *m_chaiLight1;       //! a light source

    OscCameraCHAI *m_camera;        //! an OSC-controllable camera

    /** GLUT callback functions require a pointer to the VisualSim
     ** object, but do not have a user-specified data parameter.  On
     ** the assumption that all callback functions are called
     ** subsquently after the timer callback, this static pointer is
     ** used to point to the one and only VisualSim instance to give
     ** the callback functions context. */
    static VisualSim *m_pGlobalContext;

    bool m_bFullScreen;
};

class VisualPrismFactory : public PrismFactory
{
public:
    VisualPrismFactory(Simulation *parent) : PrismFactory(parent) {}
    virtual ~VisualPrismFactory() {}

    virtual VisualSim* simulation() { return static_cast<VisualSim*>(m_parent); }

protected:
    bool create(const char *name, float x, float y, float z);
};

class VisualSphereFactory : public SphereFactory
{
public:
    VisualSphereFactory(Simulation *parent) : SphereFactory(parent) {}
    virtual ~VisualSphereFactory() {}

    virtual VisualSim* simulation() { return static_cast<VisualSim*>(m_parent); }

protected:
    bool create(const char *name, float x, float y, float z);
};

class VisualMeshFactory : public MeshFactory
{
public:
    VisualMeshFactory(Simulation *parent) : MeshFactory(parent) {}
    virtual ~VisualMeshFactory() {}

    virtual VisualSim* simulation() { return static_cast<VisualSim*>(m_parent); }

protected:
    bool create(const char *name, const char *filename,
                float x, float y, float z);
};

class OscCameraCHAI : public OscCamera
{
public:
    OscCameraCHAI(cWorld *world, const char *name, OscBase *parent=NULL);
    virtual ~OscCameraCHAI();

    virtual cCamera *object() { return m_pCamera; }

    virtual void on_position() { m_pCamera->set(m_position, m_lookat, m_up); }
    virtual void on_lookat()   { m_pCamera->set(m_position, m_lookat, m_up); }
    virtual void on_up()       { m_pCamera->set(m_position, m_lookat, m_up); }

protected:
    cCamera *m_pCamera;
};

#endif // _VISUAL_SIM_H_
