#include "ServiceChain.h"
//#include "OchObject.h"
#include <random>
#include <iostream>
#include <string>

//#include "ConstDef.h"
//#include "TypeDef.h"
//#include "MacroDef.h"
using namespace NS_OCH;
using namespace std;



ServiceChain::ServiceChain():LengthOfSCs(5), HoldingTime(1),Wavelength(-1),Grouped(false),BlckingLocation("NULL"),MinNumUsers(1),MinBw(100)
{
	     
	//LA:moved to each SC separetly 
	//VNFList = new VNF *  [LengthOfSCs] ;	
	 
}


ServiceChain::~ServiceChain()
{
	/*for (int i=0; i < this->LengthOfSCs; i++)
		delete this->VNFList [i];*/
	
	delete [] this->VNFList;
	
}

void ServiceChain::SetSCType ()
{
	 
	int randnum;
	//Generate a random between 1 and 5
	std::random_device rd;
		std::mt19937 gen(rd());

		//std::uniform_int_distribution<> dis(1, 6);
		//LA:just low latency services

		std::uniform_int_distribution<> dis(1, 3);
		randnum = dis(gen);
	//	cout<<"this is the random number:"<<randnum;
		switch (randnum)
		{
		case 1:
		{
			//SCtype=WebService;
			SCtype=MIoT;
			local=true;
			BwReq=100;
			//BwReq=4; 
			//latency=0.5; //0.005
			latency=0.005;
			LatencyClass="Intermediate";
			LengthOfSCs=3;
			VNFList = new VNF *  [LengthOfSCs];
			std::string SCVNF []= {"NAT","FW","IDPS"};
			for (int i=0;i<this->LengthOfSCs;i++)
			{
				#ifdef DEBUGLA
				cout<<"\nCreating a VNF of type:"<<SCVNF[i]<<endl;
				#endif	
				this->VNFList[i]= new VNF (SCVNF[i]);
			}
			
		}
			break;
		case 2:
		{	//SCtype=VideoStreaming;
			SCtype=AugmentedReality;
			local=false;
			//BwReq=4;
			BwReq=100;
			//latency=0.1; //LA:0.1
			latency=0.001;
			LatencyClass="Stringent";
			VNFList = new VNF *  [LengthOfSCs];
			std::string SCVNF []= {"NAT","FW","TM","VOC","IDPS"};
			for (int i=0;i<this->LengthOfSCs;i++)
				{
		#ifdef DEBUGLA
					cout<<"\nCreating a VNF of type:"<<SCVNF[i]<<endl;
		#endif	
					this->VNFList[i]= new VNF (SCVNF[i]);
				}
			
		}
		break;
		case 3:
		{
			SCtype=SmartFactory;
			local=false;
			BwReq=100;
			latency=0.001; 
			LatencyClass="Stringent";
			LengthOfSCs=2;
			VNFList = new VNF *  [LengthOfSCs];
			std::string SCVNF []= {"NAT","FW"};
			for (int i=0;i<this->LengthOfSCs;i++)
			{
				#ifdef DEBUGLA
					cout<<"\nCreating a VNF of type:"<<SCVNF[i]<<endl;
				#endif
				this->VNFList[i]= new VNF (SCVNF[i]);
			}
		}
			break;
		case 4:
		{
			//SCtype=OnlineGaming;
			SCtype=CloudGaming;
			local=false;
			BwReq=4;
			//BwReq=0.05;
			latency=0.08; //LA:previous value: latency=0.06;
			LatencyClass="Relaxed";
			VNFList = new VNF *  [LengthOfSCs];
			std::string SCVNF []= {"NAT","FW","VOC","WOC","IDPS"};
			for (int i=0;i<this->LengthOfSCs;i++)
			{
				#ifdef DEBUGLA
					cout<<"\nCreating a VNF of type:"<<SCVNF[i]<<endl;
				#endif
				this->VNFList[i]= new VNF (SCVNF[i]);
			}
		}
			break;
		case 5:
		{
			SCtype=Voip;
			local=false;
			//BwReq=4;
			BwReq=0.064;
			latency=0.1;  //LA:0.1
			LatencyClass="Relaxed";
			VNFList = new VNF *  [LengthOfSCs];
			std::string SCVNF []= {"NAT","FW","TM","FW","NAT"};
			for (int i=0;i<this->LengthOfSCs;i++)
			{
				#ifdef DEBUGLA
					cout<<"\nCreating a VNF of type:"<<SCVNF[i]<<endl;
				#endif
				this->VNFList[i]= new VNF (SCVNF[i]);
			}
		}
			break;
		case 6:
		{
			SCtype=VideoStreaming;
			local=false;
			BwReq=4;
			latency=0.1; //LA:0.1
			LatencyClass="Relaxed";
			VNFList = new VNF *  [LengthOfSCs];
			std::string SCVNF []= {"NAT","FW","TM","VOC","IDPS"};
			for (int i=0;i<this->LengthOfSCs;i++)
			{
				#ifdef DEBUGLA
					cout<<"\nCreating a VNF of type:"<<SCVNF[i]<<endl;
				#endif	
				this->VNFList[i]= new VNF (SCVNF[i]);
			}
			
		}
		
		break;
		default:
	//#ifdef DEBUGLA
				cout<<"\nThe requested service chain is not found"<<endl;
//	#endif
		
		break;	
		}
		
if(BwReq*MinNumUsers<MinBw)
			MinBw=BwReq*MinNumUsers;		
}



void ServiceChain ::SetNumberOfUsers ()
{
	int randnum;
	//Generate a random between 10 to 20
	std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(5, 10);
		randnum = dis(gen);

	this->NumofUsers= randnum;

	//this->NumofUsers=10;

}
std::string ServiceChain :: GetServiceChainName()
{
	/*if(SCtype==WebService)
		return "WebService";*/
	if(SCtype==MIoT)
		return "MIoT";
	else 
		if(SCtype==Voip)
			return"VOIP";
		else
			/*if(SCtype==OnlineGaming)
				return "OnlineGaming";*/
			if(SCtype==AugmentedReality)
				return "AugmentedReality";
			else 
				if(SCtype==CloudGaming)
					return "CloudGaming";

				else	if(SCtype==VideoStreaming)
					return "VideoStreaming";
				else 
					if(SCtype==SmartFactory)
						return "SmartFactory";
}			
