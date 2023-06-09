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

#ifndef __OBSERVER_H
#define __OBSERVER_H

/** include files **/
#include "atomic.h"     // class Atomic

/** declarations **/
class Observer : public Atomic
{
public:
	Observer( const std::string &name = "Observer" ); //Default constructor
	virtual std::string className() const {  return "Observer" ;}
	~Observer();

protected:

	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	//if we use a different robot, we will need more (or less) input/output ports
	const Port &in1_in, &in2_in, &in3_in, &in4_in, &out1_in, &out2_in, &out3_in;
	Port &in1_out, &in2_out, &in3_out, &in4_out, &out1_out, &out2_out, &out3_out;

	Value v_in1, v_in2, v_in3, v_in4, v_out1, v_out2, v_out3;
	int lastUpdated;

};	// class Observer

#endif   //__Observer_H
