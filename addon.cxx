#include <addon.hxx>
#include <iostream>
#include <DocumentCreator.hxx>
#include <TableFunctional.hxx>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/frame/XFrame.hpp>
#include <com/sun/star/frame/XController.hpp>
#include <com/sun/star/awt/Toolkit.hpp>
#include <com/sun/star/awt/XWindowPeer.hpp>
#include <com/sun/star/awt/WindowAttribute.hpp>
#include <com/sun/star/awt/XMessageBox.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <cppuhelper/supportsservice.hxx>
#include <com/sun/star/text/XTextDocument.hpp>
#include <rtl/ustring.hxx>

using rtl::OUString;
using namespace com::sun::star::uno;
using namespace com::sun::star::frame;
using namespace com::sun::star::text;
using namespace com::sun::star::awt;
using com::sun::star::beans::PropertyValue;
using com::sun::star::util::URL;

// This is the service name an Add-On has to implement
#define SERVICE_NAME "com.sun.star.frame.ProtocolHandler"


/**
  * Called by the Office framework.
  * One-time initialization. We have to store the context information
  * given, like the frame we are bound to, into our members.
  */
void SAL_CALL Addon::initialize( const Sequence< Any >& aArguments ) throw ( Exception, RuntimeException)
{
    Reference < XFrame > xFrame;
    if ( aArguments.getLength() )
    {
        aArguments[0] >>= xFrame;
        mxFrame = xFrame;
    }

    // Create the toolkit to have access to it later
    mxToolkit = Reference< XToolkit >( Toolkit::create(mxContext), UNO_QUERY_THROW );
}

/**
  * Called by the Office framework.
  * We are ask to query the given URL and return a dispatch object if the URL
  * contains an Add-On command.
  */
Reference< XDispatch > SAL_CALL Addon::queryDispatch( const URL& aURL, const ::rtl::OUString& sTargetFrameName, sal_Int32 nSearchFlags )
                throw( RuntimeException )
{
    Reference < XDispatch > xRet;
    if ( aURL.Protocol.equalsAscii("org.openoffice.Office.addon.example:") )
    {
        if ( aURL.Path.equalsAscii( "Function1" ) )
            xRet = this;
        else if ( aURL.Path.equalsAscii( "Function2" ) )
            xRet = this;
        else if ( aURL.Path.equalsAscii( "Help" ) )
            xRet = this;
    }

    return xRet;
}

/**
  * Called by the Office framework.
  * We are ask to execute the given Add-On command URL.
  */
void SAL_CALL Addon::dispatch( const URL& aURL, const Sequence < PropertyValue >& lArgs ) throw (RuntimeException)
{
    if ( aURL.Protocol.equalsAscii("org.openoffice.Office.addon.example:") )
    {
        if ( aURL.Path.equalsAscii( "Function1" ) )
        {
            FullTableTransposition(mxFrame);
        }
        else if ( aURL.Path.equalsAscii( "Function2" ) )
        {
            DocumentCreator(mxContext); 
        }
   }
}

/**
  * Called by the Office framework.
  * We are ask to query the given sequence of URLs and return dispatch objects if the URLs
  * contain Add-On commands.
  */
Sequence < Reference< XDispatch > > SAL_CALL Addon::queryDispatches( const Sequence < DispatchDescriptor >& seqDescripts )
            throw( RuntimeException )
{
    sal_Int32 nCount = seqDescripts.getLength();
    Sequence < Reference < XDispatch > > lDispatcher( nCount );

    for( sal_Int32 i=0; i<nCount; ++i )
        lDispatcher[i] = queryDispatch( seqDescripts[i].FeatureURL, seqDescripts[i].FrameName, seqDescripts[i].SearchFlags );

    return lDispatcher;
}

/**
  * Called by the Office framework.
  * We are ask to query the given sequence of URLs and return dispatch objects if the URLs
  * contain Add-On commands.
  */
void SAL_CALL Addon::addStatusListener( const Reference< XStatusListener >& xControl, const URL& aURL ) throw (RuntimeException)
{
}

/**
  * Called by the Office framework.
  * We are ask to query the given sequence of URLs and return dispatch objects if the URLs
  * contain Add-On commands.
  */
void SAL_CALL Addon::removeStatusListener( const Reference< XStatusListener >& xControl, const URL& aURL ) throw (RuntimeException)
{
}

// Helper functions for the implementation of UNO component interfaces.
OUString Addon_getImplementationName()
throw (RuntimeException)
{
    return OUString ( IMPLEMENTATION_NAME );
}

Sequence< ::rtl::OUString > SAL_CALL Addon_getSupportedServiceNames()
throw (RuntimeException)
{
    Sequence < ::rtl::OUString > aRet(1);
    ::rtl::OUString* pArray = aRet.getArray();
    pArray[0] =  OUString ( SERVICE_NAME );
    return aRet;
}

Reference< XInterface > SAL_CALL Addon_createInstance( const Reference< XComponentContext > & rContext)
    throw( Exception )
{
    return (cppu::OWeakObject*) new Addon( rContext );
}

// Implementation of the recommended/mandatory interfaces of a UNO component.
// XServiceInfo
::rtl::OUString SAL_CALL Addon::getImplementationName(  )
    throw (RuntimeException)
{
    return Addon_getImplementationName();
}

sal_Bool SAL_CALL Addon::supportsService( const ::rtl::OUString& rServiceName )
    throw (RuntimeException)
{
    return cppu::supportsService(this, rServiceName);
}

Sequence< ::rtl::OUString > SAL_CALL Addon::getSupportedServiceNames(  )
    throw (RuntimeException)
{
    return Addon_getSupportedServiceNames();
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
