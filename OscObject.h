
#ifndef _OSC_OBJECT_H_
#define _OSC_OBJECT_H_

#include <lo/lo.h>
#include <string>
#include "CODEPrism.h"
#include "CODESphere.h"

class OscObject
{
  public:
	OscObject(cGenericObject* p, const char *name);
    virtual ~OscObject();

	virtual cODEPrimitive*  odePrimitive() { return dynamic_cast<cODEPrimitive*>(m_objChai); }
	virtual cGenericObject* chaiObject()   { return m_objChai; }

  protected:
	cGenericObject* m_objChai;
    std::string m_name;
};

class OscConstraint
{
  public:
};

class OscPrism : public OscObject
{
  public:
	OscPrism(cGenericObject* p, const char *name);
    virtual ~OscPrism();

	virtual cODEPrism* odePrimitive() { return dynamic_cast<cODEPrism*>(m_objChai); }
	virtual cMesh*     chaiObject()   { return dynamic_cast<cMesh*>(m_objChai); }

  protected:
    static int size_handler(const char *path, const char *types, lo_arg **argv,
                            int argc, void *data, void *user_data);
};

class OscSphere : public OscObject
{
  public:
	OscSphere(cGenericObject* p, const char *name);
    virtual ~OscSphere();

	virtual cODESphere*   odePrimitive() { return dynamic_cast<cODESphere*>(m_objChai); }
	virtual cShapeSphere* chaiObject()   { return dynamic_cast<cShapeSphere*>(m_objChai); }

  protected:
    static int radius_handler(const char *path, const char *types, lo_arg **argv,
                              int argc, void *data, void *user_data);
};

#endif // _OSC_OBJECT_H_