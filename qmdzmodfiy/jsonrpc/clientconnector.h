/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    clientconnector.h
 * @date    02.01.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#ifndef CLIENTCONNECTOR_H_
#define CLIENTCONNECTOR_H_

#include <string>
#include "exception.h"

namespace jsonrpc
{
    class AbstractClientConnector
    {
        public:
            virtual ~AbstractClientConnector();

            /**
             * This method should take the message and send it via the concrete connector.
             * The result of the request must be returned as string.
             */
            virtual std::string SendRQMessage(const std::string& message,const std::string &agent) throw(JsonRpcException);

            virtual void SendRQMessage(const std::string& message,const std::string &agent,std::string& result) throw(JsonRpcException) = 0;
    };
} /* namespace jsonrpc */
#endif /* CLIENTCONNECTOR_H_ */
