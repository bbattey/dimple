
//===========================================================================
/*
    This file is part of a proof-of-concept implementation for using
    Open SoundControl to interact with a haptic virtual environment.

    stephen.sinclair@mail.mcgill.ca
*/
//===========================================================================

//---------------------------------------------------------------------------
#ifndef CODEPrimitiveH
#define CODEPrimitiveH

//---------------------------------------------------------------------------
#include "CGenericObject.h"
#include "CMaterial.h"
#include "CTexture2D.h"
#include "CColor.h"

//---------------------------------------------------------------------------
#include "GL/glu.h"
#include <vector>
#include <list>
//---------------------------------------------------------------------------
#include "ode/ode.h"
#include <string>
#include <map>
//---------------------------------------------------------------------------


//Geometry type to use for the mesh.
enum geomType{
	TRIMESH,
	BOX,
	SPHERE
};

enum objectType {
	STATIC_OBJECT,
	DYNAMIC_OBJECT
};

typedef int odeVector3[3];
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class cWorld;
class cTriangle;
class cVertex;
class cODEWorld;
//---------------------------------------------------------------------------


//===========================================================================
/*!
      \class      cODEPrimitive
      \brief      cODEPrimitive extends cMesh, connecting the CHAI mesh to an ODE
	              object.
*/
//===========================================================================
class cODEPrimitive
{
  public:
    // CONSTRUCTOR & DESTRUCTOR:
    //! Constructor of cODEPrimitive.
    cODEPrimitive(cWorld* a_parent, dWorldID a_odeWorld, dSpaceID a_odeSpace);
    //! Destructor of cODEPrimitive.
    ~cODEPrimitive();

    //! Called by destructor in ODE thread
    static void destroyCallback(cODEPrimitive *self);

    // METHODS:
	  //! Initialize the dynamic object.
	  virtual void initDynamic(geomType a_type = TRIMESH,objectType a_objType = DYNAMIC_OBJECT,
								float a_x = 0.0, float a_y = 0.0, float a_z = 0.0,
								float a_density = 1.0) {};
	  //! Update the position of the dynamic object.
	  void updateDynamicPosition();
	  //! Set the position of the dynamic object.
	  void setDynamicPosition(cVector3d &a_pos);
	  //! Set the mass of the dynamic object.
	  void setMass(float a_mass);
	  //! Sync the pose of the ODE object with the pose of the CHAI object
	  void syncPose();
  
 	  //! List of names of the joints.
	  std::map<std::string ,dJointID> m_Joint;
	  //! Create a ball linkage.
	  void ballLink     (string id,cODEPrimitive *meshLinked, cVector3d &anchor);
	  //! Created a hinged linkage.
	  void hingeLink    (string id,cODEPrimitive *meshLinked, cVector3d &anchor, cVector3d &axis);
	  //! Create a double hinged linkage.
	  void hinge2Link   (string id,cODEPrimitive *meshLinked, cVector3d &anchor, cVector3d &axis1, cVector3d &axis2);
	  //! Create a slider linkage.
	  void sliderLink   (string id,cODEPrimitive *meshLinked, cVector3d &anchor, cVector3d &axis);
	  //! Create a universal linkage.
	  void universalLink(string id,cODEPrimitive *meshLinked, cVector3d &anchor, cVector3d &axis1, cVector3d &axis2);
	  //! Create a fixed linkage.
	  void fixedLink    (string id,cODEPrimitive *meshLinked);
    //! Destroy a joint.
	  bool destroyJoint(string id);
	  //! Get one of the body's joints.
	  bool getJoint(string id,dJointID* &pJoint);

    // MEMBERS:
	  //! List of vertices for ODE.
	  float	*m_odeVertex;
	  //! List of vertex indices for ODE.
	  odeVector3 *m_odeIndices;
	
	  //! Geometry for ODE.
	  dGeomID m_odeGeom;
	  //! TriMesh data for ODE.
	  dTriMeshDataID  m_odeTriMeshData;
	  //! Body id for ODE.
	  dBodyID	m_odeBody;
	  //! Mass for ODE.
	  dMass	m_odeMass;
    //! Pointer to ODE world in which this mesh lives.
	  dWorldID m_odeWorld;
	  //! ODE space.
	  dSpaceID m_odeSpace;
	  //! Mass.
	  float			m_Mass;
	  //! Object type.
	  objectType		m_objType;

      //!This is specific to the OSC-Haptics application
      enum objectClass {
          CLASS_SPHERE,
          CLASS_PRISM,
          CLASS_MESH
      } m_objClass;
};

//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------



