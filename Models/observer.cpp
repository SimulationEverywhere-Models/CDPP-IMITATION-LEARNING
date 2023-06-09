/*******************************************************************
*
*  DESCRIPTION: Observer - This model essentially logs the inputs and
*  	outputs of a real-time robot control model. This model is currently
*   designed to be used with the Lego NXT mobile robotics platform.
*
*  AUTHOR: Michael W. Floyd
*
*  EMAIL: mfloyd@sce.carleton.ca
*
*  DATE: 01/12/2009
*******************************************************************/

/** include files **/
#include <fstream.h>
#include "observer.h"     // base header
#include "message.h"     // class InternalMessage
#include "mainsimu.h"	// class Simulator (MainSimulator::Instance().getParameter( ... ))


/*******************************************************************
* Function Name: Observer::Observer()
* Description: Constructor
********************************************************************/
fstream logFile;

Observer::Observer( const std::string &name ) : Atomic( name )
, in1_in( addInputPort( "in1_in" ) )
, in2_in( addInputPort( "in2_in" ) )
, in3_in( addInputPort( "in3_in" ) )
, in4_in( addInputPort( "in4_in" ) )
, out1_in( addInputPort( "out1_in" ) )
, out2_in( addInputPort( "out2_in" ) )
, out3_in( addInputPort( "out3_in" ) )
, in1_out( addOutputPort( "in1_out" ) )
, in2_out( addOutputPort( "in2_out" ) )
, in3_out( addOutputPort( "in3_out" ) )
, in4_out( addOutputPort( "in4_out" ) )
, out1_out( addOutputPort( "out1_out" ) )
, out2_out( addOutputPort( "out2_out" ) )
, out3_out( addOutputPort( "out3_out" ) )
{
	//this is where we record observations
	logFile.open("observer.txt",ios::out);

}

/*******************************************************************
* Function Name: Observer::initFunction()
* Description: Initialization Function
********************************************************************/
Model &Observer::initFunction()
{
	//since no values have been received, we set defaults
	v_in1 = -DBL_MAX;
	v_in2 = -DBL_MAX;
	v_in3 = -DBL_MAX;
	v_in4 = -DBL_MAX;
	v_out1 = -DBL_MAX;
	v_out2 = -DBL_MAX;
	v_out3 = -DBL_MAX;

	this-> passivate();
	return *this;
}

/*******************************************************************
* Function Name: Observer::externalFunction()
* Description: External Function handler
********************************************************************/
Model &Observer::externalFunction( const ExternalMessage &msg )
{

	//all of these just update the last received value
	if(this->state() == passive){
		if(msg.port() == in1_in){
			v_in1 = msg.value();
			lastUpdated = 0;
			holdIn( Atomic::active, Time::Zero );
		}else if(msg.port() == in2_in){
			v_in2 = msg.value();
			lastUpdated = 1;
			holdIn( Atomic::active, Time::Zero );
		}else if(msg.port() == in3_in){
			v_in3 = msg.value();
			lastUpdated = 2;
			holdIn( Atomic::active, Time::Zero );
		}else if(msg.port() == in4_in){
			v_in4 = msg.value();
			lastUpdated = 3;
			holdIn( Atomic::active, Time::Zero );
		}else if(msg.port() == out1_in){
			v_out1 = msg.value();
			lastUpdated = 4;
			holdIn( Atomic::active, Time::Zero );
		}else if(msg.port() == out2_in){
			v_out2 = msg.value();
			lastUpdated = 5;
			holdIn( Atomic::active, Time::Zero );
		}else if(msg.port() == out3_in){
			v_out3 = msg.value();
			lastUpdated = 6;
			holdIn( Atomic::active, Time::Zero );
		}else{
			//we have a problem! Unknown port...
			MException e("Unknown input port!");
			e.print(cerr);
			MTHROW( e ) ;
		}
	}else{
		//we have a problem! Inputs coming too quickly to log properly
		MException e("Inputs coming too quickly!");
		e.print(cerr);
		MTHROW( e ) ;
	}

	return *this;
}

/*******************************************************************
* Function Name: Observer::internalFunction()
* Description: Internal Function handler
********************************************************************/
Model &Observer::internalFunction( const InternalMessage & )
{
	this->passivate();
    return *this ;
}

/*******************************************************************
* Function Name: Observer::outputFunction()
* Description: Output function handler - writes info about time and events
********************************************************************/
Model &Observer::outputFunction( const InternalMessage &msg )
{
	switch(lastUpdated){
		case 0:
			sendOutput(msg.time(), in1_out, v_in1);
			break;
		case 1:
			sendOutput(msg.time(), in2_out, v_in2);
			break;
		case 2:
			sendOutput(msg.time(), in3_out, v_in3);
			break;
		case 3:
			sendOutput(msg.time(), in4_out, v_in4);
			break;
		case 4:
			sendOutput(msg.time(), out1_out, v_out1);
			logFile << msg.time() << "\t"
				<< v_in1 << "\t" << v_in2 << "\t" << v_in3 << "\t" << v_in4 << "\t"
				<< v_out1 <<"\t" << v_out2 << "\t" << v_out3 << endl;
			v_in1 = -DBL_MAX;
			v_in2 = -DBL_MAX;
			v_in3 = -DBL_MAX;
			v_in4 = -DBL_MAX;
			v_out1 = -DBL_MAX;
			v_out2 = -DBL_MAX;
			v_out3 = -DBL_MAX;
			break;
		case 5:
			sendOutput(msg.time(), out2_out, v_out2);
			logFile << msg.time() << "\t"
				<< v_in1 << "\t" << v_in2 << "\t" << v_in3 << "\t" << v_in4 << "\t"
				<< v_out1 <<"\t" << v_out2 << "\t" << v_out3 << endl;
			v_in1 = -DBL_MAX;
			v_in2 = -DBL_MAX;
			v_in3 = -DBL_MAX;
			v_in4 = -DBL_MAX;
			v_out1 = -DBL_MAX;
			v_out2 = -DBL_MAX;
			v_out3 = -DBL_MAX;
			break;
		case 6:
			sendOutput(msg.time(), out3_out, v_out3);
			logFile << msg.time() << "\t"
				<< v_in1 << "\t" << v_in2 << "\t" << v_in3 << "\t" << v_in4 << "\t"
				<< v_out1 <<"\t" << v_out2 << "\t" << v_out3 << endl;
			v_in1 = -DBL_MAX;
			v_in2 = -DBL_MAX;
			v_in3 = -DBL_MAX;
			v_in4 = -DBL_MAX;
			v_out1 = -DBL_MAX;
			v_out2 = -DBL_MAX;
			v_out3 = -DBL_MAX;
			break;
		default:
			MException e("A state variable was set incorrectly!");
			e.print(cerr);
			MTHROW( e ) ;
			break;
	};

	return *this ;
}

Observer::~Observer()
{
	logFile.close();
}
