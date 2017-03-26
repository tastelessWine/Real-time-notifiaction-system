//
//  Mongodb update notifier in C++
//  Binds PUB socket to tcp://*:5556
//
//  Meng Zhang <mzhang@yottaa.com>
//
#include "pch.h"
#include "notifier.hpp"
#include <zmq.hpp>

namespace mongo{

	MongodbChangeNotifier* MongodbChangeNotifier::Instance()
	{
		static MongodbChangeNotifier notifier;
		return &notifier;
	}

	MongodbChangeNotifier::MongodbChangeNotifier()
		:context_(1),publisher_(context_,ZMQ_PUB),started_(0)
	{

	}

	MongodbChangeNotifier::~MongodbChangeNotifier()
	{

	}
	
	void MongodbChangeNotifier::stop()
	{
		if(!started_)
			return;
	}

	void MongodbChangeNotifier::start(const std::string& proto)
	{
		if(proto.empty())
			return;

		publisher_.bind(proto.c_str());
		started_ = 1;
	}

	void MongodbChangeNotifier::postNotification(const op operation, const std::string& ns, const BSONObj& id,const BSONObj& update)
	{
		if(!started_){
			log() << "not started yet." << std::endl;
			return;
		}
		BSONElement idElement = id["_id"];
		if(idElement.eoo()){
			log() << "no _id specified." << std::endl;
			return;
		}

		BSONObjBuilder b;
		b.append("ns",ns);
		b.append(idElement);		
		b.append("op",(int)operation);
		b.append("change",update);
		std::string msg = b.obj().jsonString(Strict,0);
		zmq::message_t message(msg.size());
		memcpy(message.data(),msg.data(),msg.size());
		publisher_.send(message);
		log() << "[notifier]\t"<< msg <<std::endl;

	}

	void postNotification( const char *opstr, const char *ns, const BSONObj& obj, BSONObj *patt, const BSONObj* fullObj){
		switch(*opstr){
		case 'i':
			MongodbChangeNotifier::Instance()->postNotification(INSERT,ns,obj,obj);
			break;
		case 'u':
			if(patt)
				MongodbChangeNotifier::Instance()->postNotification(UPDATE,ns,*patt,fullObj ? *fullObj : obj); 
			
			break;
		case 'd':
			MongodbChangeNotifier::Instance()->postNotification(DELETE,ns,obj,BSONObj()); 
			break;
		default:
			break;
		}

	}

}
