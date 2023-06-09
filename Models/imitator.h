/*******************************************************************
*
*  DESCRIPTION: Imitator - This model imitates the behaviour of a
*   model that was logged with the Observer model. This model is currently
*   designed to be used with the Lego NXT mobile robotics platform.
*
*  AUTHOR: Michael W. Floyd
*
*  EMAIL: mfloyd@sce.carleton.ca
*
*  DATE: 01/12/2009
*******************************************************************/

#ifndef __IMITATOR_H
#define __IMITATOR_H

/** include files **/
#include "atomic.h"     // class Atomic
#include <list.h>
#include <vector.h>

/** declarations **/
class Imitator : public Atomic
{
public:
	Imitator( const std::string &name = "Imitator" ); //Default constructor
	virtual std::string className() const {  return "Imitator" ;}
	~Imitator();

	struct InputArray{
		Value in1;
		Value in2;
		Value in3;
		Value in4;
	};

protected:

	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	//if we use a different robot, we will need more (or less) input/output ports
	const Port &in1, &in2, &in3, &in4;
	Port &out1, &out2, &out3;

	vector<InputArray> inputlist;
	vector<vector<std::string> > actionlist;

	vector<std::string> currentActions;

	Value nextAction;
	int nextActionPort;

	Value norm1, norm2, norm3, norm4;


};	// class Imitator

#endif   //__IMITATOR_H
