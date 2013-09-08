//
// HTTPSSessionInstantiator.h
//
// $Id: //poco/1.4/NetSSL_OpenSSL/include/Poco/Net/HTTPSSessionInstantiator.h#2 $
//
// Library: NetSSL_OpenSSL
// Package: HTTPSClient
// Module:  HTTPSSessionInstantiator
//
// Definition of the HTTPSSessionInstantiator class.
//
// Copyright (c) 2006-2009, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Net_HTTPSSessionInstantiator_INCLUDED
#define Net_HTTPSSessionInstantiator_INCLUDED


#include "Poco/Net/NetSSL.h"
#include "Poco/Net/Context.h"
#include "Poco/Net/Utility.h"
#include "Poco/Net/HTTPSessionInstantiator.h"
#include "Poco/URI.h"


namespace Poco {
namespace Net {


class NetSSL_API HTTPSSessionInstantiator: public HTTPSessionInstantiator
	/// The HTTPSessionInstantiator for HTTPSClientSession.
{
public:
	HTTPSSessionInstantiator();
		/// Creates the HTTPSSessionInstantiator.

	HTTPSSessionInstantiator(Context::Ptr pContext);
		/// Creates the HTTPSSessionInstantiator using the given SSL context.

	~HTTPSSessionInstantiator();
		/// Destroys the HTTPSSessionInstantiator.

	HTTPClientSession* createClientSession(const Poco::URI& uri);
		/// Creates a HTTPSClientSession for the given URI.

	static void registerInstantiator();
		/// Registers the instantiator with the global HTTPSessionFactory.

	static void registerInstantiator(Context::Ptr pContext);
		/// Registers the instantiator with the global HTTPSessionFactory using the given SSL context.

	static void unregisterInstantiator();
		/// Unregisters the factory with the global HTTPSessionFactory.

private:
	Context::Ptr _pContext;
};


} } // namespace Poco::Net


#endif // Net_HTTPSSessionInstantiator_INCLUDED
