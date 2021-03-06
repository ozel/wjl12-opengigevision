//-----------------------------------------------------------------------------
//  (c) 2006 by Basler Vision Technologies
//  Section: Vision Components
//  Project: GenApi
//  Author:  Hartmut Nebelung
//  $Header: /cvs/genicam/genicam/library/CPP/include/GenApi/ICommand.h,v 1.11 2007/08/16 13:56:39 hartmut_nebelung Exp $
//
//  License: This file is published under the license of the EMVA GenICam  Standard Group. 
//  A text file describing the legal terms is included in  your installation as 'GenICam_license.pdf'. 
//  If for some reason you are missing  this file please contact the EMVA or visit the website
//  (http://www.genicam.org) for a full copy.
// 
//  THIS SOFTWARE IS PROVIDED BY THE EMVA GENICAM STANDARD GROUP "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,  
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR  
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE EMVA GENICAM STANDARD  GROUP 
//  OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  SPECIAL, 
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT  LIMITED TO, 
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  DATA, OR PROFITS; 
//  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  THEORY OF LIABILITY, 
//  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE) 
//  ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
//  POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------
/*!
\file     
\brief    Definition of ICommand interface
\ingroup GenApi_PublicInterface
*/

#ifndef GENAPI_ICOMMAND_H
#define GENAPI_ICOMMAND_H

#include "GenApiDll.h"
#include "Types.h"
#include "IValue.h"

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace GenApi
{
    //*************************************************************
    // ICommand interface
    //*************************************************************

    //! Interface for command like  properties
    //! \ingroup GenApi_PublicInterface
    interface ICommand   : virtual public IValue
    {
    public:

        //! Execute the command
        virtual void Execute() = 0;

        //! Execute the command
        virtual void operator()() = 0;

        //! Query whether the command is executed
        virtual bool IsDone() const = 0;


    };


    //*************************************************************
    // CCommandRef class
    //*************************************************************

    /**
    \internal
    \brief Reference to an IInteger pointer
    \ingroup GenApi_PublicImpl
    */
    template <class T>
    class CCommandRefT : public CValueRefT<T>
    {
    	typedef CValueRefT<T> ref;

    public:
        /*--------------------------------------------------------*/
        // ICommand
        /*--------------------------------------------------------*/

        //! Execute the command
        virtual void Execute()
        {
            if(ref::m_Ptr)
                return ref::m_Ptr->Execute();
            else
                throw ACCESS_EXCEPTION("Feature not present (reference not valid)");
        }

        //! Execute the command
        virtual void operator()()
        {
            if(ref::m_Ptr)
                ref::m_Ptr->operator()();
            else
                throw ACCESS_EXCEPTION("Feature not present (reference not valid)");
        }

        //! Query whether the command is executed
        virtual bool IsDone() const
        {
            if(ref::m_Ptr)
                return ref::m_Ptr->IsDone();
            else
                throw ACCESS_EXCEPTION("Feature not present (reference not valid)");
        }


    };

    //! Reference to an ICommand pointer
    //! \ingroup GenApi_PublicImpl
    typedef CCommandRefT<ICommand> CCommandRef;  



}

#pragma warning ( pop )

#endif // ifndef GENAPI_ICOMMAND_H
