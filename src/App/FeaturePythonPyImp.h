/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#ifndef APP_FEATUREPYTHONPYIMP_H
#define APP_FEATUREPYTHONPYIMP_H

#include <Base/BaseClass.h>
#include <Base/Interpreter.h>
#include <App/PropertyContainerPy.h>

#define PYTHON_TYPE_DEF(_class_, _subclass_) \
    class _class_ : public _subclass_ \
    { \
    public: \
        static PyTypeObject Type; \
    public: \
        _class_(Base::BaseClass *pcObject, PyTypeObject *T = &Type); \
        virtual ~_class_(); \
    };

#define PYTHON_TYPE_IMP(_class_, _subclass_) \
    PyTypeObject _class_::Type = { \
        PyObject_HEAD_INIT(&PyType_Type) \
        0, \
        ""#_class_"",  \
        sizeof(_class_),  \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_CLASS, \
        ""#_class_"", \
        0, 0, 0, 0, 0, 0, 0, 0, 0, \
        &_subclass_::Type, \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 \
    }; \
    _class_::_class_(Base::BaseClass *pcObject, PyTypeObject *T) \
        : _subclass_(reinterpret_cast<_subclass_::PointerType>(pcObject), T) \
    { \
    } \
    _class_::~_class_() \
    { \
    }

namespace App
{

/**
 * @author Werner Mayer
 */
template <class FeaturePyT>
class FeaturePythonPyT : public FeaturePyT
{
public:
    static PyTypeObject   Type;

public:
    FeaturePythonPyT(Base::BaseClass *pcObject, PyTypeObject *T = &Type);
    virtual ~FeaturePythonPyT();

    /** @name callbacks and implementers for the python object methods */
    //@{
    static  int __setattr(PyObject *PyObj, char *attr, PyObject *value);
    //@}
    PyObject *_getattr(char *attr);              // __getattr__ function
    int _setattr(char *attr, PyObject *value);        // __setattr__ function

protected:
    PyObject * dict_methods;

private:
};

} //namespace App

#include "FeaturePythonPyImp.inl"

#endif // APP_FEATUREPYTHONPYIMP_H
