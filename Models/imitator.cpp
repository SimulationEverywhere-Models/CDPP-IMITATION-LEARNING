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

/** include files **/
//#include <string.h>
//#include <float.h>
#include <math.h>
#include <fstream.h>
#include <iostream.h>
#include "imitator.h"     // base header
#include "message.h"     // class InternalMessage
#include "mainsimu.h"	// class Simulator (MainSimulator::Instance().getParameter( ... ))


/*******************************************************************
* Function Name: Imitator::Imitator()
* Description: Constructor
********************************************************************/
fstream caseFile;

Imitator::Imitator( const std::string &name ) : Atomic( name )
, in1( addInputPort( "in1" ) )
, in2( addInputPort( "in2" ) )
, in3( addInputPort( "in3" ) )
, in4( addInputPort( "in4" ) )
, out1( addOutputPort( "out1" ) )
, out2( addOutputPort( "out2" ) )
, out3( addOutputPort( "out3" ) )
{
	//this is where we record observations
	caseFile.open("cases.txt",ios::in);

	char nextline[1024];
	char delim[] = ",";
	char del2[] = ":";

	caseFile.getline(nextline,1024);
	norm1 = strtod(strtok(nextline,delim),NULL);
	norm2 = strtod(strtok(NULL,delim),NULL);
        norm3 = strtod(strtok(NULL,delim),NULL);
	norm4 = strtod(strtok(NULL,delim),NULL);

	while(!caseFile.eof()){
		caseFile.getline(nextline,1024);
		if(strlen(nextline) > 0){
			InputArray feat;
			feat.in1 = strtod(strtok(nextline,delim),NULL);
			feat.in2 = strtod(strtok(NULL,delim),NULL);
			feat.in3 = strtod(strtok(NULL,delim),NULL);
			feat.in4 = strtod(strtok(NULL,delim),NULL);

			char *act = strtok(NULL,delim);

			vector<std::string> acts;
			char *val = strtok(act,del2);
			while ( val  != NULL){
				acts.push_back(val);
				val = strtok(NULL,del2);
			}

			actionlist.push_back(acts);
			inputlist.push_back(feat);
		}
	}

	caseFile.close();
}

/*******************************************************************
* Function Name: Imitator::initFunction()
* Description: Initialization Function
********************************************************************/
Model &Imitator::initFunction()
{

	this-> passivate();
	return *this;
}

/*******************************************************************
* Function Name: Imitator::externalFunction()
* Description: External Function handler
********************************************************************/
Model &Imitator::externalFunction( const ExternalMessage &msg )
{

	if(this->state() == passive){

		Value in1 = 9999;
		Value in2 = 9999;
		Value in3 = 9999;
		Value in4 = 9999;
		if(msg.port().asString() == "in1"){
			in1 = msg.value();
		}else if(msg.port().asString() == "in2"){
			in2 = msg.value();
		}else if(msg.port().asString() == "in3"){
			in3 = msg.value();
		}else if(msg.port().asString() == "in4"){
			in4 = msg.value();
		}else{
			//we have a problem! Unknown port...
			MException e("Unknown input port!");
			e.print(cerr);
			MTHROW( e ) ;
		}

		Value minDist = 9999;
		int minIdx = -1;
		
		for(int ii=0; ii<inputlist.size(); ii++){
			Value distVal = 0;
			
			InputArray curr = inputlist.at(ii);
			distVal += fabs(curr.in1 - in1)/norm1;
			distVal += fabs(curr.in2 - in2)/norm2;
			distVal += fabs(curr.in3 - in3)/norm3;
			distVal += fabs(curr.in4 - in4)/norm4;
			
			if(distVal < minDist){
				minDist = distVal;
				minIdx = ii;
			}
		}

		vector<std::string> orig = actionlist.at(minIdx);
		currentActions.assign (orig.begin(), orig.end());
		
		if(currentActions.size() == 0){
			//no actions, so we may as well be passive
			return *this;
		}else{
			std::string nextAct = currentActions.at(0);
			currentActions.erase(currentActions.begin());
			
			char delim[] = "^";
			char val[256];
			strcpy(val,nextAct.c_str());
			nextActionPort = strtol(strtok(val,delim),NULL,10);
			nextAction = strtod(strtok(NULL,delim),NULL);
			long int milli = strtol(strtok(NULL,delim),NULL,10);
			holdIn( Atomic::active, Time(0,0,milli/1000,milli%1000) );
			return *this;
		}
	}else{
		//we will just ignore them, we are already doing something
	}

	return *this;
}

/*******************************************************************
* Function Name: Imitator::internalFunction()
* Description: Internal Function handler
********************************************************************/
Model &Imitator::internalFunction( const InternalMessage & )
{
	if(currentActions.size() == 0){
		//no actions, so we may as well be passive
		this->passivate();
		return *this;
	}else{
		std::string nextAct = currentActions.at(0);
		currentActions.erase(currentActions.begin());
			
		char delim[] = "^";
		char val[256];
		strcpy(val,nextAct.c_str());
		nextActionPort = strtol(strtok(val,delim),NULL,10);
		nextAction = strtod(strtok(NULL,delim),NULL);
		long int milli = strtol(strtok(NULL,delim),NULL,10);
		
		holdIn( Atomic::active, Time(0,0,milli/1000,milli%1000) );
		return *this;
	}
	
}

/*******************************************************************
* Function Name: Imitator::outputFunction()
* Description: Output function handler
********************************************************************/
Model &Imitator::outputFunction( const InternalMessage &msg )
{
	switch(nextActionPort){
		case 1:
			sendOutput(msg.time(), out1, nextAction);
			break;
		case 2: 
			sendOutput(msg.time(), out2, nextAction);
			break;
		case 3:
			sendOutput(msg.time(), out3, nextAction);
			break;
	}

	return *this ;
}

Imitator::~Imitator()
{

}
