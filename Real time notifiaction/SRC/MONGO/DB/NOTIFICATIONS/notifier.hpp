
#pragma once

#include "../../pch.h"
#include "../jsobj.h"
#include <zmq.hpp>
#include <boost/thread.hpp>

namespace mongo{

	typedef enum _op { INSERT = 0, UPDATE = 1, DELETE = 2} op;
  
	class MongodbChangeNotifier : private boost::noncopyable {
    
	public:
		static MongodbChangeNotifier* Instance();
    
		void start(const std::string& proto);
		void stop(void);
		void postNotification(const op operation, const std::string& ns, const BSONObj& id,const BSONObj& update);
    
	protected:
		MongodbChangeNotifier();
		~MongodbChangeNotifier();
    

	private:
		zmq::context_t context_;
		zmq::socket_t publisher_;
    
		int started_;
	};

	void postNotification( const char *opstr, const char *ns, const BSONObj& obj, BSONObj *patt = 0, const BSONObj* fullObj = NULL);

}
